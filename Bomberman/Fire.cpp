#include "Fire.h"


Fire::Fire(void)
{
	timeAlive = 20;
}


Fire::~Fire(void)
{
}

void Fire::tick()
{
	timeAlive--;
}

int Fire::getTimeAlive()
{
	return timeAlive;
}