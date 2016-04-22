#include <SFML/Graphics.hpp>

#define SCREEN_X 1000	//Size of Memory, can be changed
#define SCREEN_Y 800	//Size of Memory, can be changed

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Game [In Developement]");
	sf::RectangleShape player(sf::Vector2f(20, 20));
	player.setFillColor(sf::Color::Green);
	player.setPosition(500, 300);	//Spawning Point

	sf::RectangleShape enemy(sf::Vector2f(20, 20));
	enemy.setFillColor(sf::Color::Red);
	enemy.setPosition(300, 300);	//Spawning Point

	double x = 0, y = 0, speed = .3;	//Speed of Player
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {		///Keyboard Commands
				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)	// Move Up
					x = 0, y = -speed;
				if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)	// Move Down
					x = 0, y = speed;
				if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)	// Move Right
					x = speed, y = 0;
				if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)		// Move Left
					x = -speed, y = 0;
				if (event.key.code == sf::Keyboard::Escape)	// Press Esc to Exit
					window.close();
			}
			if (event.type == sf::Event::JoystickMoved || event.type == sf::Event::JoystickButtonPressed) {	///Controller Directionals
				if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == 100)	//Up
					x = 0, y = -speed;
				if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position == -100)	//Down
					x = 0, y = speed;
				if (event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == 100)	//Right
					x = speed, y = 0;
				if (event.joystickMove.axis == sf::Joystick::PovX && event.joystickMove.position == -100)	//Left
					x = -speed, y = 0;
				if (event.joystickButton.button == 6)	//Press Back to Exit
					window.close();
			}
		}

		if (player.getPosition().x >= SCREEN_X)						///If Player goes off screen, spawns on the other side
			player.setPosition(1, player.getPosition().y);				//Right Border
		else if (player.getPosition().x <= 0)
			player.setPosition(SCREEN_X - 1, player.getPosition().y);		//Left Border
		else if (player.getPosition().y >= SCREEN_Y)
			player.setPosition(player.getPosition().x - 1, 1);			//Top Border
		else if (player.getPosition().y <= 0)
			player.setPosition(player.getPosition().x, SCREEN_Y - 1);	//Bottom Border

		player.move(x, y);	//Player Movement

		int collision = 10;
		if (enemy.getPosition().x > player.getPosition().x - collision && enemy.getPosition().x < player.getPosition().x + collision
			&& enemy.getPosition().y > player.getPosition().y - collision && enemy.getPosition().y < player.getPosition().y + collision)
			enemy.setPosition(0, 0);	//Enemy Collision

		double e_x = 0, e_y = 0, e_speed = .1;	///Enemy Movement towards player
		if (enemy.getPosition().x < player.getPosition().x)
			e_x = e_speed;		//Moves to right
		else if (enemy.getPosition().x > player.getPosition().x)
			e_x = -e_speed;		//Moves to left
		if (enemy.getPosition().y < player.getPosition().y)
			e_y = e_speed;		//Moves up
		else if (enemy.getPosition().y > player.getPosition().y)
			e_y = -e_speed;		//Moves down
		enemy.move(e_x, e_y);	///Enemy movement



		window.clear();
		window.draw(player);	//Draws Player
		window.draw(enemy);		//Draws Enemy
		window.display();
	}
	return 0;
}
