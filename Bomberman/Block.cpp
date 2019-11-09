#include "Block.h"
#include "BombUp.h"

Block::Block(bool b,bool e,int x,int y,int ax,int ay)
{
	exit = e;
	breakable = b;
	broken = false;
	Block::SetPosition(x,y);
	aX = ax;
	aY = ay;
}

Block::~Block(void)
{
}

void Block::getPowerUp(vector<PowerUp*> powerups,int pxpos,
		int pypos, CTexture bombUpTex,
		CTexture flameUpTex,CTexture spikeTex,
		CTexture kickTex)
{
	
}

bool Block::isBreakable()
{
	return breakable;
}

bool Block::isBroken()
{
	return broken;
}

bool Block::isExit()
{
	return exit;
}

void Block::setExit(bool a)
{
	exit = a;
}
void Block::setArrayX(int a)
{
	aX = a;
}

void Block::setArrayY(int a)
{
	aY = a;
}

void Block::setBroken(bool a)
{
	broken = a;
}

int Block::getArrayX()
{
	return aX;
}

int Block::getArrayY()
{
	return aY;
}