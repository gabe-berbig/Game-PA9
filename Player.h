#pragma once
#include "visualObj.h"

class Player: public visualObj {
public:
	Player();
	~Player();
	void draw(sf::RenderWindow & window);
	void eventUpdate(sf::Event event);
	void Player::moveUpdate();
	void Player::activateDash();
	void Player::border();
	double Player::getMovementX();
	double Player::getMovementY();
private:
	int dashTimer;
	double x;
	double y;
};

