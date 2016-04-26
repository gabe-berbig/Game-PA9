#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <time.h>
#include "Player.h"
#include "Star.h"

#define SCREEN_X 1000	//Size of Memory, can be changed
#define SCREEN_Y 800	//Size of Memory, can be changed
#define DASH_TIME 250	//Speed of Player Attack
#define P_SPD .2		//Player's Speed
#define MAX_ENEMIES 5

class Game {
public:
	Game();
	~Game();
	void run();
	void collision(sf::Sprite &player, sf::Sprite &enemy, Star *star);
	int rand_int(int min, int quantity);
	///Attack Class
	void attack(sf::Event event, Player *player);
	///Enemy Class
	void enemyAiUpdate(Player *player, sf::Sprite &enemy);
	///Event Class
	void movementUpdate(Player *player, sf::Sprite enemy[], Star *star);
	void check_closeWindows(sf::Event event, sf::RenderWindow &window);
private:
	int total_enemies;
	int p_timer;
	int e_timer;
};