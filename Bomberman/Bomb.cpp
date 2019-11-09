#include "Bomb.h"


Bomb::Bomb(int p,int f,bool s,int x,int y)
{
	player = p;
	fuse = 120;
	flameLength = f;
	spiked = s;
	exploded = false;
	arrayX = x;
	arrayY = y;
}


Bomb::~Bomb(void)
{

}

void Bomb::tick()
{
	fuse--;
}

void Bomb::explode()
{
	exploded = true;
}

void Bomb::setFuse(int f)
{
	fuse = f;
}

int Bomb::getFuse()
{
	return fuse;
}

int Bomb::getFlameLength()
{
	return flameLength;
}

int Bomb::getPlayer()
{
	return player;
}

bool Bomb::isExploded()
{
	return exploded;
}

int Bomb::getArrayX()
{
	return arrayX;
}

int Bomb::getArrayY()
{
	return arrayY;
}

void Bomb::setArrayX(int a)
{
	arrayX = a;
}

void Bomb::setArrayY(int a)
{
	arrayY = a;
}