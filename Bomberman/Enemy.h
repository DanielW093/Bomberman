#pragma once
#include "Sprite.h"
#include "Game.h"
#include <vector>
#include "Block.h"
#include <random>
#include <time.h>
#include "Fire.h"
#include "Bomb.h"
class Enemy :public CSprite
{
private:
	int life,directionX,directionY,speed;
	bool dead;

public:
	Enemy(int life,int directionX,int directionY,int speed);
	~Enemy(void);
	
	void setDead(bool a);
	void tick(vector<Block*> block,vector<Bomb*> bomb);

	bool isDead();
};

