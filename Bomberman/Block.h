#pragma once
#include "PowerUp.h"
#include "Sprite.h"
#include <vector>
#include "FlameUp.h"
#include "BombUp.h"
#include "Spiked.h"
#include "KickBoot.h"

class Block : public CSprite
{
private:
	bool breakable,broken,exit;
	int aX,aY;

	
public:
	Block(bool b,bool e,int x,int y,int ax,int ay);
	~Block(void);

	void onBroken();
	void setExit(bool a);
	void getPowerUp(vector<PowerUp*> list,int pxpos,
		int pypos, CTexture bombUpTex,
		CTexture flameUpTex,CTexture spikeTex,
		CTexture kickTex);

	void setArrayX(int a);
	void setArrayY(int a);
	void setBroken(bool a);
	int getArrayX();
	int getArrayY();

	bool isBreakable();
	bool isBroken();
	bool isExit();
};

