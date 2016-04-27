#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <time.h>

class visualObj {
public:
	visualObj();
	virtual void load(std::string filename);
	virtual void draw(sf::RenderWindow & window);
	void visualObj::setOrigin(int x, int y);
	virtual void setPosition(double x, double y);
	void visualObj::setColor(int r, int b, int g);
	virtual void move(double x, double y);
	void visualObj::rotate(double rot);
	void visualObj::setRotation(double rot);
	virtual sf::Sprite getSprite();
	sf::Vector2f getPosition();
	double getHeight();
	double getWidth();
private:
	sf::Sprite  sprite;
	sf::Texture texture;
	std::string filename;
	bool isLoaded;
};