#include "visualObj.h"

visualObj::visualObj() {
	srand((unsigned int)time(NULL));
}

void visualObj::load(std::string filename) {
	if (texture.loadFromFile(filename) == false)
	{
		filename = "";
		isLoaded = false;
	} else {
		filename = filename;
		sprite.setTexture(texture);
		isLoaded = true;
	}
	sprite.setOrigin(getWidth() / 2, getHeight() / 2);
}

void visualObj::draw(sf::RenderWindow & window) {
	if (isLoaded)
		window.draw(sprite);
}

void visualObj::setOrigin(int x, int y) {
	sprite.setOrigin(x, y);
}

void visualObj::setPosition(double x, double y) {
	if (isLoaded)
		sprite.setPosition(x, y);
}

void visualObj::setColor(int r, int b, int g) {
	sprite.setColor(sf::Color(r, b, g));
}

void visualObj::move(double x, double y) {
	if (isLoaded)
		sprite.move(x, y);
}

void visualObj::rotate(double rot) {
	if (isLoaded)
		sprite.rotate(rot);
}

void visualObj::setRotation(double rot) {
	if (isLoaded)
		sprite.setRotation(rot);
}

sf::Sprite visualObj::getSprite() {
	return sprite;
}

sf::Vector2f visualObj::getPosition() {
	return sprite.getPosition();
}

double visualObj::getHeight() {
	return sprite.getGlobalBounds().height;
}

double visualObj::getWidth() {
	return sprite.getGlobalBounds().width;
}