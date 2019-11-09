#pragma once
#include "Sprite.h"
#include "Player.h"

class Bomb : public CSprite
{
private:
	int fuse,flameLength,arrayX,arrayY;
	bool spiked,exploded;
	int player;

public:
	Bomb(int player,int f,bool s,int x,int y);
	~Bomb(void);

	void tick();
	void explode();
	void setArrayX(int a);
	void setArrayY(int a);
	void setFuse(int f);
	int getArrayX();
	int getArrayY();

	bool isExploded();
	int getPlayer();
	int getFlameLength();
	int getFuse();
};

