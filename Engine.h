#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <time.h>

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
	void movementUpdate(sf::Sprite &player, sf::Sprite enemy[]);
	void playerUpdate(sf::Sprite &player);
	void enemyAiUpdate(sf::Sprite &player, sf::Sprite &enemy);
	void collision(sf::Sprite &player, sf::Sprite &enemy);
	void check_closeWindows(sf::Event event, sf::RenderWindow &window);
	void border(sf::Sprite &player);
	int rand_int(int min, int quantity);
	//void Game::createPlayer(sf::Sprite &player);
private:
	int DASH;
	double x, y;
	int total_enemies;
	int p_timer;
	int e_timer;
};
