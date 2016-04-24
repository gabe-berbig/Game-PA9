#include "Engine.h"

Game::Game() {
	DASH = 0, x = 0, y = 0, p_timer = 0, e_timer;
}

Game::~Game() {
}

void Game::run() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Ninja Game");

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
	}
	///Sets Positions
	player.setPosition(500, 300);
	enemy[0].setPosition(300, 300);	//Spawning Point

	///

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			check_closeWindows(event, window);	//Closes Game if Executed
			player_movement(event);				//Moves Character
			attack(event);						//Character's attacks
		}
		border(player);					//Border so player does not go off screen
		movementUpdate(player, enemy[0]);	//Player & Enemy Movement Updates
		collision(player, enemy[0]);

		window.clear();
		window.draw(player);	//Draws Player
		window.draw(enemy[0]);		//Draws Enemy
		window.display();
	}
}

void Game::attack(sf::Event event) {
	if (event.type == sf::Event::KeyPressed)	///Keyboard Commands
		if (event.key.code == sf::Keyboard::X)		//X = Dash Attack
			DASH = ATTK_SPD;
	if (event.type == sf::Event::JoystickButtonPressed) {	///Controller Action Buttons
		if (event.joystickButton.button == 0)					//A = Dash Attack
			DASH = ATTK_SPD;
	}
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

void Game::movementUpdate(sf::Sprite &player, sf::Sprite &enemy) {
	///Player's Movements
	if (DASH != 0) {	//Dash acts like a timer, speeds up until 0
		player.move(x * 3, y * 3);	//Dash
		--DASH;						//Counts down
	}
	else
		player.move(x, y);	//Player Movement
							///Enemies Movements, follows player
	double e_x = 0, e_y = 0, e_speed = .09;	///Enemy Movement towards player
	if (enemy.getPosition().x < player.getPosition().x)
		e_x = e_speed;		//Moves to right
	else if (enemy.getPosition().x > player.getPosition().x)
		e_x = -e_speed;		//Moves to left
	if (enemy.getPosition().y < player.getPosition().y)
		e_y = e_speed;		//Moves up
	else if (enemy.getPosition().y > player.getPosition().y)
		e_y = -e_speed;		//Moves down
	if (x == 0 && y == 0)
		e_x = 0, e_y = 0;	//Won't move until player moves
	enemy.move(e_x, e_y);
}

void Game::collision(sf::Sprite &player, sf::Sprite &enemy) {
	int collision = 20, dmg = 100;
	///Enemy Collision (Damage Detection)
	if (enemy.getPosition().x > player.getPosition().x - collision && enemy.getPosition().x < player.getPosition().x + collision
		&& enemy.getPosition().y > player.getPosition().y - collision && enemy.getPosition().y < player.getPosition().y + collision) {
		if (DASH != 0) {
			enemy.setColor(sf::Color(255, dmg, dmg));	//Enemy Collision [Damage taken, changes Red]
			e_timer = 400;
		} else {
			player.setColor(sf::Color(255, dmg, dmg));	//Player Collision [Damage taken, changes Red]
			p_timer = 400;
		}
	}
	if (e_timer != 0)
		e_timer--;
	else
		enemy.setColor(sf::Color(255, 255, 255));
	if (p_timer != 0)
		p_timer--;
	else
		player.setColor(sf::Color(255, 255, 255));
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
	if (player.getPosition().x >= SCREEN_X)						///If Player goes off screen, spawns on the other side
		player.setPosition(1, player.getPosition().y);				//Right Border
	if (player.getPosition().x <= 0)
		player.setPosition(SCREEN_X - 1, player.getPosition().y);		//Left Border
	if (player.getPosition().y >= SCREEN_Y)
		player.setPosition(player.getPosition().x - 1, 1);			//Top Border
	if (player.getPosition().y <= 0)
		player.setPosition(player.getPosition().x, SCREEN_Y - 1);	//Bottom Border
}

//void Game::createPlayer(sf::Sprite &player) {	///Can't get this to work
//	sf::Texture player_texture;
//	if (!player_texture.loadFromFile("player.png")) {
//		//Error Loading
//	}
//	player.setTexture(player_texture);
//}
