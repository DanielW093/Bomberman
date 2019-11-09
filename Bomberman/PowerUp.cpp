#include "PowerUp.h"


PowerUp::PowerUp(int t)
{
	type = t;
}


PowerUp::~PowerUp(void)
{
}

int PowerUp::getType()
{
	return type;
}
