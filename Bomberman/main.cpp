// TheGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameApp.h"
#include "MyGame.h"


int main(int argc, char* argv[])
{
	CGameApp app;
	CMyGame game;

	app.OpenWindow(570, 570, "BomberMan by Daniel Williams and Thomas Bassett");

	app.Run(&game);
	return 0;
}

