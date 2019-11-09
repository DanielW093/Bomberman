#include "Enemy.h"

Enemy::Enemy(int l,int dX,int dY,int s)
{
	life = l;
	directionX = dX;
	directionY = dY;
	speed = s;
	srand(time(NULL));
}


Enemy::~Enemy(void)
{

}

void Enemy::tick(vector<Block*>b,vector<Bomb*> bom)
{

	for(int i = 0 ; i < b.size();i++)
	{
		if(b[i]->HitTest(this))
		{
			int random = rand() %2;
			directionX = -directionX;
			directionY = - directionY;
		}
	}

	for(int i = 0 ; i < bom.size();i++)
	{
		if(bom[i]->HitTest(this))
		{
			int random = rand() %2;
			directionX = -directionX;
			directionY = - directionY;
		}
	}
	Enemy::SetPosition(Enemy::GetX()+(directionX*speed),Enemy::GetY()+(directionY*speed));
}

void Enemy::setDead(bool a)
{
	dead = a;
}

bool Enemy::isDead()
{
	return dead;
}
