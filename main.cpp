#include <SFML/Graphics.hpp>

#define SCREEN_X 1000	//Size of Memory, can be changed
#define SCREEN_Y 800	//Size of Memory, can be changed

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Game [In Developement]");
	sf::RectangleShape player(sf::Vector2f(20, 20));
	player.setFillColor(sf::Color::Red);
	player.setPosition(500, 300);	//Spawning Point
	
	//sf::Image player_img;
	//if (!player_img.loadFromFile("p_img.png"))	//For Later
	//	return 1;
	//sf::Sprite Sprite;

	double x = 0, y = 0, speed = .5;	//Speed of Player
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) // Move Up
					x = 0, y = -speed;
				if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) // Move Down
					x = 0, y = speed;
				if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard:: Right) // Move Right
					x = speed, y = 0;
				if (event.key.code == sf::Keyboard:: A || event.key.code == sf::Keyboard::Left) // Move Left
					x = -speed, y = 0;
				if (event.key.code == sf::Keyboard::Escape)	// Press Esc to Exit
					window.close();
			}
		}
		if (player.getPosition().x >= SCREEN_X)
			player.setPosition(1, player.getPosition().y);
		else if (player.getPosition().x <= 0)
			player.setPosition(SCREEN_X-1, player.getPosition().y);
		else if (player.getPosition().y >= SCREEN_Y)
			player.setPosition(player.getPosition().x-1, 1);
		else if (player.getPosition().y <= 0)
			player.setPosition(player.getPosition().x, SCREEN_Y - 1);
		else
			player.move(x, y);

		window.clear();
		window.draw(player);
		window.display();
	}
	return 0;
}
