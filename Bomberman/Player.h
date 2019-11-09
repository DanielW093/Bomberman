#pragma once
#include "Sprite.h"
#include <SDL_keysym.h>


class Player : public CSprite
{
private:
	int aX,aY;
	int maxBombs,flameLength;
	bool kickBomb,invincible,spikeBomb,canMove;

public:
	int currentBombs;
	Player(void);
	~Player(void);

	//Movement
	void move2(SDLKey key);

	//Getters and Setters
	void setKickBomb(bool a);
	void setInvincible(bool a);
	void setSpiked(bool a);

	bool isInvincible();
	bool iskickBomb();
	bool isSpiked();

	void setArrayPos(int x,int y);
	void setMaxBombs(int a);
	void setFlameLength(int a);
	void setCurrentBombs(int a);
	void resetMaxBombs();
	void resetFlameLength();

	int getCurrentBombs();
	int getArrayX();
	int getArrayY();
	int getFlameLength();
	int getMaxBombs();
};

//