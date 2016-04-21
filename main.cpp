#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Game [In Developement]");
	sf::RectangleShape player(sf::Vector2f(20, 20));
	player.setFillColor(sf::Color::Red);
	
	//sf::Image player_img;
	//if (!player_img.loadFromFile("p_img.png"))	//For Later
	//	return 1;
	//sf::Sprite Sprite;

	int speed = 30;	//Speed of Player
	player.setPosition(500, 300);	//Spawning Point
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) // Move Up
					player.move(0, -speed);
				if (event.key.code == sf::Keyboard::S) // Move Down
					player.move(0, speed);
				if (event.key.code == sf::Keyboard::D) // Move Right
					player.move(speed, 0);
				if (event.key.code == sf::Keyboard::A) // Move Left
					player.move(-speed, 0);
				if (event.key.code == sf::Keyboard::Escape)	// Press Esc to Exit
					window.close();
			}
		}
		window.clear();
		window.draw(player);
		window.display();
	}
	return 0;
}
