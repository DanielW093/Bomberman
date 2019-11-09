#pragma once

#include "Game.h"
#include "Block.h"
#include "Unbreakable.h"
#include "Player.h"
#include "Bomb.h"
#include <vector>
#include "Fire.h"
#include "Enemy.h"
#include "Exit.h"
#include "PowerUp.h"
#include "BombUp.h"
#include "FlameUp.h"
#include "FlameDown.h"
#include "BombDown.h"
#include <algorithm>

using std::swap;
class CMyGame : public CGame
{

	
public:
	CMyGame();
	~CMyGame();

    // ----  Declare your game variables and objects here -------------

	// Variables
	bool levelOver,isExit,invincible,musicPaused,timerStop, winner;
	int leveldesign[19][19];
	int level, mouseX,mouseY,random,
		deadEnemies,numOfEnemies,singleLevel,
		spawnedEnemies,score,lives,timer,highScore;

    // Sprites and Sprite Lists
	vector<Block*> blocks;
	vector<Bomb*> bombs;
	vector<Fire*> fire;
	vector<Enemy*> enemies;

	CSpriteList bombups;
	CSpriteList flameups;
	CSpriteList flamedown;
	CSpriteList bombdown;
	CSpriteList livesl;
	
	//Menu
	CSpriteRectangle loadingBar;
	CSpriteRectangle backg;
	CSprite singlePlayerButton;
	CSprite multiPlayerButton;
	CSprite controlButton;
	CSprite mainButton;
	Exit exit;

	Player player1;
	Player player2;
	
	// Textures
	CTexture mainUp;
	CTexture mainDown;
	CTexture controlsUp;
	CTexture controlsDown;
	CTexture singleEnd;
	CTexture multEnd;
	CTexture controls;
	CTexture background;
	CTexture texture;
	CTexture texture2;
	CTexture button1;
	CTexture button2;
	CTexture texture3;	
	CTexture texture5;
	CTexture firet;
	CTexture uBlock;
	CTexture bBlock;
	CTexture enemy1;
	CTexture exitT;
	CTexture bombUpTex;
	CTexture flameUpTex;
	CTexture bombDownTex;
	CTexture flameDownTex;
	CTexture life;
	//PLayerTextures
	CTexture texture4;
	CTexture back;
	CTexture left;
	CTexture right;

	CTexture front2;
	CTexture back2;
	CTexture left2;
	CTexture right2;
	// Font
	CFont font;
	CFont highScoreFont;
	CFont winnerFont;

	// Sounds
	CSound levelmusic;
	CSound explosion;
	CSound bombplace;
	CSound pickup;
	CSound menuclick;
	
   // ---------------------Event Handling --------------------------
	
	void loading();
	//Level array
	void createList();
	void initializeLevelArray();
	void createPowerUp(int x, int y);
	// Game Loop Funtions
	virtual void OnUpdate();
	virtual void OnDraw();

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnInitializeLevel_Control();
	virtual void OnInitializeLevel_1();
	virtual void OnInitializeLevel_Multi_1();
	virtual void OnInitializeLevel_Single_1();
	virtual void OnInitializeLevel_1000();
	virtual void OnInitializeLevel_1001();
	virtual void OnStartGame();
	virtual void OnGameOver();
	virtual void OnTerminate();
	

	void HighScoreWrite(string filelocation);
	void HighScoreRead(string filelocation);

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
