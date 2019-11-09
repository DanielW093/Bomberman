#pragma once
#include "Sprite.h"

class PowerUp : public CSprite
{
private:
	int type;

public:
	PowerUp(int type);
	~PowerUp(void);
	
	int getType();
	
};

