#pragma once
#include "Sprite.h"
class Fire : public CSprite
{
private:
	int timeAlive;
public:
	Fire(void);
	~Fire(void);

	void tick();
	int getTimeAlive();
};

