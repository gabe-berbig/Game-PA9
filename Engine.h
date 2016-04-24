#pragma once
#include <SFML/Graphics.hpp>

#define SCREEN_X 1000	//Size of Memory, can be changed
#define SCREEN_Y 800	//Size of Memory, can be changed
#define ATTK_SPD 250	//Speed of Player Attack
#define P_SPD .2		//Player's Speed
#define MAX_ENEMIES 5

class Game {
public:
	Game();
	~Game();
	void run();
	void attack(sf::Event event);
	void player_movement(sf::Event event);
	void movementUpdate(sf::Sprite &player, sf::Sprite &enemy);
	void collision(sf::Sprite &player, sf::Sprite &enemy);
	void check_closeWindows(sf::Event event, sf::RenderWindow &window);
	void border(sf::Sprite &player);
	//void Game::createPlayer(sf::Sprite &player);
private:
	int DASH;
	double x, y;
	int p_timer;
	int e_timer;
};
