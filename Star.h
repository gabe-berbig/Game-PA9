#pragma once
#include "visualObj.h"

class Star : public visualObj {
public:
	Star();
	~Star();
	void Star::throwStar(visualObj *player);
	void draw(sf::RenderWindow & rw);
	void Star::eventUpdate(sf::Event event);
	void Star::moveUpdate(visualObj *player);
private:
	bool isThrown;
};