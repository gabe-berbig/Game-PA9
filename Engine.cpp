#include "Engine.h"


Game::Game() {
	DASH = 0, x = 0, y = 0;
	THROW = false;
	total_enemies = 3;
	p_timer = 0;
	e_timer = 0;
}

Game::~Game() {
}

void Game::run() {
	sf::Font font;
	font.loadFromFile("fonts/arial.ttf");
	
	sf::Text text;
	text.setFont(font);
	text.setString("start game");
	text.setColor(sf::Color::White);
	text.setCharacterSize(40);

	sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Shogun-Master Makano");
	srand((unsigned int)time(NULL));
	///Background
	sf::Texture background_texture;
	background_texture.loadFromFile("sprites/background.png");
	sf::Sprite background(background_texture);
	///Star
	sf::Texture star_texture;
	star_texture.loadFromFile("sprites/star.png");
	sf::Sprite star(star_texture);
	///Creates Player	[Makes into function]
	sf::Texture player_texture;
	player_texture.loadFromFile("sprites/player.png");
	sf::Sprite player(player_texture);
	///Creates Enemy	[Make into function]
	sf::Texture enemy_texture;
	enemy_texture.loadFromFile("sprites/enemy.png");
	sf::Sprite enemy[MAX_ENEMIES];
	for (int x = 0; x < MAX_ENEMIES; x++) {
		enemy[x].setTexture(enemy_texture);
		enemy[x].setPosition(rand_int(1, SCREEN_X - 100), rand_int(1, 350));	//Spawning Point
	}
	
	///Sets Positions
	player.setPosition(500, 630);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			check_closeWindows(event, window);	//Closes Game if Executed
			player_movement(event);				//Moves Character
			attack(event);						//Character's attacks
		}
		border(player);					//Border so player does not go off screen
										//Enemy UI
		movementUpdate(player, enemy, star);	//Player & Enemy Movement Updates
		collision(player, enemy[0], star);

		
		window.clear();
		window.draw(background);	//Draws Player
		window.draw(star);
		window.draw(player);	//Draws Player
		for (int x = 0; x < total_enemies; x++)
			window.draw(enemy[x]);		//Draws Enemy
		window.draw(text);
		window.display();
		
	}

}

void Game::attack(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {	///Keyboard Commands
		if (event.key.code == sf::Keyboard::Z)		//X = Dash
			DASH = ATTK_SPD;
		if (event.key.code == sf::Keyboard::X)		//X = Throw Attack
			THROW = true;
	}
	if (event.type == sf::Event::JoystickButtonPressed) {	///Controller Action Buttons
		if (event.joystickButton.button == 0)					//A = Dash
			DASH = ATTK_SPD;
		if (event.joystickButton.button == 2)					//X = Throw Attack
			THROW = true;
	}
}

void Game::throwStar(sf::Sprite &star, sf::Sprite &player) {
	int x = player.getPosition().x;
	int y = player.getPosition().y;
	star.setPosition(x + 15, y + 15);
}

void Game::player_movement(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {		///Keyboard Commands
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)	// Move Up
			x = 0, y = -P_SPD;
		if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)	// Move Down
			x = 0, y = P_SPD;
		if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)	// Move Right
			x = P_SPD, y = 0;
		if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)		// Move Left
			x = -P_SPD, y = 0;
	}
	else if (event.type == sf::Event::JoystickMoved) {	///Controller Directionals
		if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100)	//Up
			x = 0, y = -P_SPD;
		if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == -100)	//Down
			x = 0, y = P_SPD;
		if (event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100)	//Right
			x = P_SPD, y = 0;
		if (event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100)	//Left
			x = -P_SPD, y = 0;
	}
}

void Game::movementUpdate(sf::Sprite &player, sf::Sprite enemy[], sf::Sprite &star) {
	///Player's Movements
	playerUpdate(player);	//Player's movements updated
							///Enemies' Movements
	for (int x = 0; x < total_enemies; x++) {
		enemyAiUpdate(player, enemy[x]);	//Enemies' movements updated
	}
	///Stars Movement
	if (THROW != true)
		throwStar(star, player);	//Checks if player pressed Throw Star
	else if (star.getPosition().y == 0) {	///If Star goes off screen
		star.setRotation(0);					//Star rotation resets
		star.setPosition(-20, -20);				//Is places off screen
		THROW = false;							//Throw is off, player can throw more stars
	}
	else {								///Star is moved upwards towards enemies' side
		star.rotate(.8);
		star.move(0, -1);	//Star moved upwards
	}
}

void Game::playerUpdate(sf::Sprite &player) {
	if (DASH != 0) {	//Dash acts like a timer, speeds up until 0
		player.move(x * 3, y * 3);	//Dash
		--DASH;						//Counts down
	}
	else
		player.move(x, y);	//Player Movement
}

void Game::enemyAiUpdate(sf::Sprite &player, sf::Sprite &enemy) {
	if (enemy.getPosition().x > SCREEN_X)
		enemy.setPosition(-100, enemy.getPosition().y);
	if (enemy.getPosition().x <= SCREEN_X)
		enemy.move(.2, 0);
}

void Game::collision(sf::Sprite &player, sf::Sprite &enemy, sf::Sprite &star) {
	///Enemy Collision (Damage Detection)
	if ((enemy.getPosition().x > star.getPosition().x - 70 && enemy.getPosition().x < star.getPosition().x + 30)
		&& (enemy.getPosition().y < star.getPosition().y && star.getPosition().y + 30 < enemy.getPosition().y + 70)) {
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

void Game::border(sf::Sprite &player) {
	if (player.getPosition().x >= SCREEN_X - 60)						///If Player goes off screen, spawns on the other side
		player.setPosition(SCREEN_X - 60, player.getPosition().y);	//left Border
	if (player.getPosition().x <= 0)
		player.setPosition(0, player.getPosition().y);	//left Border
	if (player.getPosition().y <= 520)
		player.setPosition(player.getPosition().x, 520);	//Top Border
	if (player.getPosition().y >= SCREEN_Y - 90)
		player.setPosition(player.getPosition().x, SCREEN_Y - 90);	//Bottom Border
}

int Game::rand_int(int min, int quantity) {
	return rand() % quantity + min;
}

//void Game::createPlayer(sf::Sprite &player) {	///Can't get this to work
//	sf::Texture player_texture;
//	if (!player_texture.loadFromFile("player.png")) {
//		//Error Loading
//	}
//	player.setTexture(player_texture);
//}

