#include "Engine.h"

Game::Game() {
	srand((unsigned int)time(NULL));
}

Game::~Game() {
}

void Game::run() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Shogun-Master Makano");

	sf::Texture enemy_t;
	Player *player = new Player();
	Enemy enemy[MAX_ENEMIES];
	Star *star = new Star();
	visualObj background;

	player->load("sprites/player.png");
	background.load("sprites/background.png");
	star->load("sprites/star.png");

	background.setOrigin(0, 0);
	player->setPosition(500, 330);
	for (int x = 0; x < MAX_ENEMIES; x++) {
		enemy[x].load("sprites/enemy.png");
		enemy[x].spawn();	//Spawning Point
	}

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {	///Event Updates
			check_closeWindows(event, window);	//Closes Game
			player->eventUpdate(event);			//Updates Character
			star->eventUpdate(event);			//Updates Star
		}

		///Movement Updates
		moveUpdate((Player*)player, enemy, (Star*)star);

		//Collision with projectile
		for (int x = 0; x < MAX_ENEMIES; x++) {
			enemy[x].checkCollision(star);
			//enemy[x].respawn();
		}

		///Displays everything
		window.clear();				//Clears Window
		background.draw(window);	//Displays Background
		star->draw(window);			//Displays player's star
		player->draw(window);		//Displays Player
		for (int x = 0; x < MAX_ENEMIES; x++)	///Runs through all enemies
			enemy[x].draw(window);	//Displays Enemies
		window.display();			//Displays Window to Screen
	}
}

void Game::moveUpdate(Player *player, Enemy enemy[], Star *star) {
	player->moveUpdate();						//Player's Movements
	for (int x = 0; x < MAX_ENEMIES; x++)	///Spawns total enemies
		enemy[x].moveUpdate();
	star->moveUpdate((Player*)player);			//Stars Movement
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