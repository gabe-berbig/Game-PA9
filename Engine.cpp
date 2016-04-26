#include "Engine.h"

Game::Game() {
	total_enemies = 3;
	p_timer = 0;
	e_timer = 0;
}

Game::~Game() {
}

void Game::run() {
	sf::Texture background_t, star_t, enemy_t;
	Player *player = new Player();
	Star *star = new Star();
	visualObj background;

	sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Shogun-Master Makano");

	srand((unsigned int)time(NULL));

	background.load("sprites/background.png");
	player->load("sprites/player.png");
	star->load("sprites/star.png");
	enemy_t.loadFromFile("sprites/enemy.png");
	///Loads Sprites
	sf::Sprite enemy[MAX_ENEMIES];
	for (int x = 0; x < MAX_ENEMIES; x++) {
		enemy[x].setTexture(enemy_t);
		enemy[x].setPosition(rand_int(1, SCREEN_X-100), rand_int(1, 350));	//Spawning Point
	}
	///Sets Positions
	player->setPosition(500, 630);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			check_closeWindows(event, window);	//Closes Game if Executed
			///
			player->updateEvent(event);				//Moves Character
			star->eventUpdate(event);
			attack(event, (Player*)player);						//Character's attacks
		}
		player->border();					//Border so player does not go off screen
		//Enemy UI
		movementUpdate((Player*)player, enemy, (Star*)star);	//Player & Enemy Movement Updates
		collision(player->getSprite(), enemy[0], (Star*)star);

		window.clear();
		background.draw(window);
		star->draw(window);
		player->draw(window);
		for (int x = 0; x < total_enemies; x++)
			window.draw(enemy[x]);		//Draws Enemy
		window.display();
	}
}

void Game::attack(sf::Event event, Player *player) {
	if (event.type == sf::Event::KeyPressed) {	///Keyboard Commands
		if (event.key.code == sf::Keyboard::Z)		//X = Dash
			player->activateDash();
		//if (event.key.code == sf::Keyboard::X)		//X = Throw Attack
		//	THROW = true;
	}
	if (event.type == sf::Event::JoystickButtonPressed) {	///Controller Action Buttons
		if (event.joystickButton.button == 0)					//A = Dash
			player->activateDash();
		//if (event.joystickButton.button == 2)					//X = Throw Attack
		//	THROW = true;
	}
}

void Game::movementUpdate(Player *player, sf::Sprite enemy[], Star *star) {
		player->moveUpdate();	//Player's Movements
	for (int x = 0; x < total_enemies; x++)	///Spawns total enemies
		enemyAiUpdate(player, enemy[x]);		//Enemies' movements updated
	///Stars Movement
	star->moveUpdate((Player*)player);
}

void Game::enemyAiUpdate(Player *player, sf::Sprite &enemy) {
	if (enemy.getPosition().x > SCREEN_X)
		enemy.setPosition(-100, enemy.getPosition().y);
	if (enemy.getPosition().x <= SCREEN_X)
		enemy.move(.2, 0);
}

void Game::collision(sf::Sprite &player, sf::Sprite &enemy, Star *star) {
	///Enemy Collision (Damage Detection)
	if ((enemy.getPosition().x > star->getPosition().x - 70 && enemy.getPosition().x < star->getPosition().x + 30)
			&& (enemy.getPosition().y < star->getPosition().y && star->getPosition().y+30 < enemy.getPosition().y + 70)) {
		enemy.setColor(sf::Color(255, 100, 100));	//Enemy Collision [Damage taken, changes Red]
		e_timer = 400;
	}
	if (e_timer != 0)
		e_timer--;
	else
		enemy.setColor(sf::Color(255, 255, 255));
}

void Game::check_closeWindows(sf::Event event, sf::RenderWindow &window) {
	if (event.type == sf::Event::Closed)
		window.close();
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::Escape)	// Press Esc to Exit
			window.close();
	if (event.type == sf::Event::JoystickButtonPressed)
		if (event.joystickButton.button == 6)	//Press Back to Exit
			window.close();
}

int Game::rand_int(int min, int quantity) {
	return rand() % quantity + min;
}
