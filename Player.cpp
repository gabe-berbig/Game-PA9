#include "Player.h"
#include "Engine.h"

Player::Player() {
	dashTimer = 0;
	x = 0;
	y = 0;
}

Player::~Player() {
}

void Player::draw(sf::RenderWindow & window) {
	visualObj::draw(window);
}

void Player::eventUpdate(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {		///Keyboard Commands
		if (event.key.code == sf::Keyboard::Up)	// Move Up
			x = 0, y = -P_SPD;
		if (event.key.code == sf::Keyboard::Down)	// Move Down
			x = 0, y = P_SPD;
		if (event.key.code == sf::Keyboard::Right)	// Move Right
			x = P_SPD, y = 0;
		if (event.key.code == sf::Keyboard::Left)		// Move Left
			x = -P_SPD, y = 0;
		if (event.key.code == sf::Keyboard::Z)		//X = Dash
			activateDash();
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
	if (event.type == sf::Event::JoystickButtonPressed) {	///Controller Action Buttons
		if (event.joystickButton.button == 0)					//A = Dash
			activateDash();
	}
}

void Player::moveUpdate() {
	if (dashTimer != 0) {
		move(x * 3, y * 3);
		dashTimer--;
	} else
		move(x, y);
	border();
}

void Player::activateDash() {
	dashTimer = DASH_TIME;
}

void Player::border() {
	if (getPosition().x >= SCREEN_X - getWidth()/2)			///If Player goes off screen, spawns on the other side
		setPosition(SCREEN_X - getWidth()/2, getPosition().y);	//Right Border
	if (getPosition().x <= getWidth() / 2)
		setPosition(getWidth()/2, getPosition().y);						//left Border
	if (getPosition().y < 520 + getHeight() / 2)
		setPosition(getPosition().x, 520 + getHeight() / 2);							//Top Border
	if (getPosition().y >= SCREEN_Y - getHeight()/2 - 30)
		setPosition(getPosition().x, SCREEN_Y - getHeight()/2 - 30);	//Bottom Border
}

double Player::getMovementX() {
	return x;
}

double Player::getMovementY() {
	return y;
}