void Game::displayMenu() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Shogun Master");

	sf::Font font;
	if (!font.loadFromFile("calibri.ttf"))
		std::cout << "Can't find the font file" << std::endl;

	font.loadFromFile("calibri.ttf");

	sf::Text text("Welcome to Shogun Master", font, 40);
	text.setColor(sf::Color(44, 127, 255));
	
	sf::Text text1("1.Play the Game", font, 25);
	sf::Text text2("2.Display Instructions", font, 25);
	sf::Text text3("3.Quit", font, 25);
	sf::Text Instructions("THE INSTRUCTIONS FOR PLAYING", font, 25);

	text1.move(0.0f,40.0f);
	text2.move(0.0f,60.0f);
	text3.move(0.0f,80.0f);

	if (window.isOpen()) {
		window.clear();
		window.draw(text);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.display();

		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Num1){ //|| event.key.code == sf::Keyboard::Numpad1) {
					Game::run();
				}
				if (event.key.code == sf::Keyboard::Num2){// || event.key.code == sf::Keyboard::Numpad2) {
					window.clear();
					window.draw(Instructions);
					window.display();
				}
				if (event.key.code == sf::Keyboard::Num3){// || event.key.code == sf::Keyboard::Numpad3) {
					window.close();
				}
			}
		}
	}
	window.display();
}
