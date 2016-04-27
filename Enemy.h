#pragma once
#include "visualObj.h"

class Enemy : public visualObj {
public:
	Enemy();
	~Enemy();
	void draw(sf::RenderWindow & window);
	void Enemy::AiUpdate();
	void Enemy::enemyAi1();
	void Enemy::moveUpdate();
	void Enemy::border();
	void Enemy::checkCollision(visualObj *star);
	bool Enemy::isCollision(visualObj *star);
	void Enemy::death();
	void Enemy::respawn();
	void Enemy::spawn();
	int Enemy::rand_int(int min, int quantity);
private:
	int health;
	bool dead;
	int collisionTimer;
	int respawnTimer;
	double x;
	double y;
};