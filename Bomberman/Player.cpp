#include "Player.h"
#include "MyGame.h"

Player::Player(void)
{
	canMove =true;
	kickBomb = false;
	invincible = false;
	spikeBomb = false;
	maxBombs = 1;
	currentBombs = 0;
	flameLength = 1;
}

Player::~Player(void)
{
}

void Player::setArrayPos(int x,int y)
{
	aX = x;
	aY = y;
}

void Player::move2(SDLKey sym)
{
	
}

void Player::setKickBomb(bool a)
{
	kickBomb = a;
}

void Player::setInvincible(bool a)
{
	invincible = a;
}

bool Player::isInvincible()
{
	return invincible;
}

bool Player::iskickBomb()
{
	return kickBomb;
}

void Player::setMaxBombs(int a)
{
	if(maxBombs > 1 || a > 0)
	{
		maxBombs += a;
	}
}

void Player::resetMaxBombs()
{
	maxBombs = 1;
}

void Player::resetFlameLength()
{
	flameLength = 1;
}

void Player::setSpiked(bool a)
{
	spikeBomb = a;
}

void Player::setFlameLength(int a)
{
	if(flameLength > 1|| a > 0)
	{
		flameLength +=a;
	}
}

void Player::setCurrentBombs(int a)
{	
	currentBombs += a;
}

int Player::getFlameLength()
{
	return flameLength;
}

int Player::getMaxBombs()
{
	return maxBombs;
}

int Player::getArrayX()
{
	return aX;
}

int Player::getArrayY()
{
	return aY;
}

int Player::getCurrentBombs()
{
	return currentBombs;
}

bool Player::isSpiked()
{
	return spikeBomb;
}