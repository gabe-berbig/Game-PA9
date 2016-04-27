#include "Star.h"
#include "Engine.h"

Star::Star() {
	isThrown = false;
}

Star::~Star() {

}

void Star::throwStar(visualObj *player) {
	int x = player->getPosition().x;
	int y = player->getPosition().y;
	int x_center = x + player->getWidth()/2 - getWidth()/2;
	int y_center = y + player->getHeight()/2 - getHeight();
	//setPosition(x_center, y - 100);	//Spawns at Player's position
	setPosition(x_center, y_center - getHeight()/2);	//Spawns at Player's position

}

void Star::draw(sf::RenderWindow & rw) {
	visualObj::draw(rw);
}

void Star::moveUpdate(visualObj *player) {
	if (isThrown == false)
		throwStar(player);	//Spawns at Player's position
		//throwStar((Player*)player);		//Checks if player pressed Throw Star
	else if (getPosition().y < (-1) * getHeight()) {	///If Star goes off screen
		setRotation(0);			//Star rotation resets
		setPosition(-20, -20);	//Is places off screen
		isThrown = false;		//Throw is off, player can throw more stars
	}
	else {							///Star is moved upwards towards enemies' side
		rotate(.8);	//Rotates star as it moves
		move(0, -1);		//Star moved upwards
	}
}

void Star::eventUpdate(sf::Event event) {
	if (event.type == sf::Event::KeyPressed)	///Keyboard Commands
		if (event.key.code == sf::Keyboard::X)		//X = Throw Attack
			isThrown = true;
	if (event.type == sf::Event::JoystickButtonPressed)		///Controller Action Buttons
		if (event.joystickButton.button == 2)					//X = Throw Attack
			isThrown = true;
}