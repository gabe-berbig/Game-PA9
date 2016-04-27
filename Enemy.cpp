#include "Enemy.h"
#include "Engine.h"

Enemy::Enemy() {
	health = 3;
	dead = false;
	respawnTimer = 0;
	collisionTimer = 0;
	x = 0.18;
	y = 0;
}

Enemy::~Enemy() {
}

void Enemy::draw(sf::RenderWindow & window) {
	visualObj::draw(window);
}

void Enemy::AiUpdate() {
	enemyAi1();
}

void Enemy::enemyAi1() {
	x = .18;
	y = rand_int(1, 10) * 0.01;
	int rand_x = rand_int(0, 2);
	int rand_y = rand_int(0, 2);
	if (rand_x == true)
		x *= -1;
	if (rand_y == true)
		y *= -1;
}

void Enemy::moveUpdate() {
	move(x, y);
	border();
}

void Enemy::border() {
	if (getPosition().x >= SCREEN_X - getWidth() / 2)			///If Player goes off screen, spawns on the other side
		x *= -1;	//Right Border
	if (getPosition().x <= getWidth() / 2)
		x *= -1;						//left Border
	if (getPosition().y <= getHeight() / 2)
		y *= -1;							//Top Border
	if (getPosition().y >= 450 - getHeight() / 2)
		y *= -1;	//Bottom Border
}

int Enemy::rand_int(int min, int quantity) {
	return rand() % quantity + min;
}

void Enemy::checkCollision(visualObj *star) {
	bool interact = isCollision(star);
	int healthColor = (105 + health * 50);


	if (interact == true) {
		if (collisionTimer == 0)
			health--;
		if (health == 0 && respawnTimer == 0)
			respawnTimer = rand_int(5, 8) * 1000;
		setColor(255, 0, 0);	//Enemy Collision [Damage taken, changes Red]
		collisionTimer = 400;
	}
	if (collisionTimer > 0)
		collisionTimer--;
	else if (collisionTimer == 0)
		setColor(255, healthColor, healthColor);	//Changes enemy's color back after certain period of time

	if (respawnTimer > 0)
		respawnTimer--;
	else if (respawnTimer == 0 && dead == true)
		respawn();

	death();	//If Health = 0, Enemy is Dead
}

void Enemy::death() {
	if (health == 0 && collisionTimer == 0) {
		setPosition(-100, -100);
		dead = true;
	}
}

void Enemy::respawn() {
	setColor(150, 255, 50);	//Changes enemy's color back after certain period of time
	spawn();
	dead = false;
	collisionTimer = 800;
	
}

void Enemy::spawn() {
	x = .18, y = 0;
	setPosition(rand_int(150, SCREEN_X - 150), 200);
	AiUpdate();
	health = 3;
}

bool Enemy::isCollision(visualObj *star) {
	///Works as collision box, creates a rectangular region to detect collision
	int top = getPosition().x + getWidth() / 2 + star->getWidth() / 2;
	int bottom = getPosition().x - getWidth() / 2 - star->getWidth() / 2;
	int right = getPosition().y + getHeight() / 2 + star->getHeight() / 2;
	int left = getPosition().y - getHeight() / 2 + star->getHeight() / 2;

	if ((bottom < star->getPosition().x && star->getPosition().x < top))	//Checks Top & Bottom Collision Box
		if ((left < star->getPosition().y && star->getPosition().y < right))	//Checks Left & Right Collision Box
			return true;
	return false;

}