#pragma once
#include "Block.h"
#include "Sprite.h"

class Breakable : public Block
{
private:
	int aX,aY;
public:
	Breakable(int x,int y,bool e,int aX,int aY);
	~Breakable(void);
};

