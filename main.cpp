#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(1000, 800), "Game [In Developement]");

	sf::RectangleShape player(sf::Vector2f(20, 20));
	player.setFillColor(sf::Color::Red);
	
	sf::Image player_img;
	if (!player_img.loadFromFile("p_img.png"))	//For Later
		return 1;
	sf::Sprite Sprite;

	int x = 0, y = 0, speed = 2;
	player.setPosition(300, 300);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) // move up
					player.move(x * speed, (--y * speed));
				if (event.key.code == sf::Keyboard::S) // move down
					player.move(x * speed, (++y * speed));
				if (event.key.code == sf::Keyboard::D) // move right
					player.move((++x * speed), y * speed);
				if (event.key.code == sf::Keyboard::A) // move left
					player.move((--x * speed), y * speed);
			}
		}
		window.clear();
		window.draw(player);
		window.display();
	}

	return 0;
}
