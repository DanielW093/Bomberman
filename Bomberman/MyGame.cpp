#include "MyGame.h"
#include <time.h>
#include <stdlib.h>
#include "Breakable.h"
#include <random>
#include "Player.h"
#include <fstream>
#include <iostream>

using namespace std;

CMyGame::CMyGame(void)
{
	srand(time(NULL));
}

CMyGame::~CMyGame(void) {}



// --------  game initialisation --------
void CMyGame::OnInitialize()
{
	musicPaused = false;
	invincible = false;
	// Loading Sounds
	explosion.LoadAudioFile("sounds/explosion.wav");
	explosion.SetVolume(70);
	bombplace.LoadAudioFile("sounds/bombplace.wav");
	bombplace.SetVolume(40);
	pickup.LoadAudioFile("sounds/pop.wav");
	pickup.SetVolume(120);
	menuclick.LoadAudioFile("sounds/menuclick.wav");
	menuclick.SetVolume(100);

	// Loading Graphics
	winnerFont.LoadDefault();
	winnerFont.SetColor(CColor::Black());
	winnerFont.SetSize(48);
	font.LoadDefault(); 
	highScoreFont.LoadDefault();
	highScoreFont.SetColor(CColor::Black());
	highScoreFont.SetSize(48);
	texture.LoadTextureFromBitmap("textures/singleplayerbuttonup.bmp");
	texture2.LoadTextureFromBitmap("textures/singleplayerbuttondown.bmp");
	button1.LoadTextureFromBitmap("textures/multiplayerbuttonup.bmp");
	button2.LoadTextureFromBitmap("textures/multiplayerbuttondown.bmp");
	uBlock.LoadTextureFromBitmap("textures/block.bmp");
	bBlock.LoadTextureFromBitmap("textures/brick.bmp");
	singlePlayerButton.SetTexture(texture);
	texture3.LoadTextureFromBitmap("textures/bomb.bmp");
	texture5.LoadTextureFromBitmap("textures/firecenter.bmp");
	firet.LoadTextureFromBitmap("textures/fire.bmp");
	enemy1.LoadTextureFromBitmap("textures/enemy1.bmp");
	singleEnd.LoadTextureFromBitmap("textures/singleEnd.bmp");
	multEnd.LoadTextureFromBitmap("textures/multiEnd.bmp");
	controls.LoadTextureFromBitmap("textures/controls.bmp");

	//Player
	texture4.LoadTextureFromBitmap("textures/bomberman.bmp");
	back.LoadTextureFromBitmap("textures/bombermanback.bmp");
	right.LoadTextureFromBitmap("textures/bombermanright.bmp");
	left.LoadTextureFromBitmap("textures/bombermanleft.bmp");

	front2.LoadTextureFromBitmap("textures/bomberman2.bmp");
	back2.LoadTextureFromBitmap("textures/bombermanback2.bmp");
	right2.LoadTextureFromBitmap("textures/bombermanright2.bmp");
	left2.LoadTextureFromBitmap("textures/bombermanleft2.bmp");


	life.LoadTextureFromBitmap("textures/life.bmp");

	exitT.LoadTextureFromBitmap("textures/door.bmp");
	exit.SetTexture(exitT);
	exit.SetSize(30,30);
	exit.SetPosition(-100,-100);
	player1.SetTexture(texture4);
	player1.SetPosition(-600,-100);
	player2.SetPosition(-600,-100);
	player2.SetTexture(front2);

	//Powerups
	bombUpTex.LoadTextureFromBitmap("textures/bombup.bmp");
	flameUpTex.LoadTextureFromBitmap("textures/flameup.bmp");
	bombDownTex.LoadTextureFromBitmap("textures/bombdown.bmp");
	flameDownTex.LoadTextureFromBitmap("textures/flamedown.bmp");

	//button
	controlsUp.LoadTextureFromBitmap("textures/controlButton.bmp");
	controlsDown.LoadTextureFromBitmap("textures/controlButtonDown.bmp");
	controlButton.SetTexture(controlsUp);
	mainUp.LoadTextureFromBitmap("textures/mainButton.bmp");
	mainDown.LoadTextureFromBitmap("textures/mainButtonDown.bmp");
	mainButton.SetTexture(mainUp);

	//------------------End Initialisation Stuff-------------------------
}

void CMyGame::HighScoreRead(string filelocation)
{
	ifstream inFile;

	inFile.open(filelocation);

	if(inFile.fail())
	{
		ofstream create;

		create.open(filelocation);
		create << 0;

		cout << "No high score file was found, new one was created" << endl;

		create.close();
	}

	ifstream read (filelocation);

	read >> highScore;

	cout << "High score was read" << endl;

	inFile.close();
}

void CMyGame::HighScoreWrite(string filelocation)
{
	ofstream outFile;

	outFile.open(filelocation);
	if(outFile.fail())
	{
		cout << "High score failed" << endl;
	}

	outFile.clear();

	outFile << highScore;

	cout << "High score saved" << endl;

	outFile.close();
}


// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	level=1;
	StartGame();	// this allows to start the game immediately	
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
	if (level==1) {OnInitializeLevel_1();}
}

void CMyGame::OnInitializeLevel_Multi_1()
{
	player1.resetFlameLength();
	player1.resetMaxBombs();
	player2.resetFlameLength();
	player2.resetMaxBombs();

	exit.SetPosition(-200,-200);
	singleLevel = 1;
	numOfEnemies = (level-20)+3;
	cout<<"Num of enemies : " << numOfEnemies << endl;
	spawnedEnemies = 0;
	isExit = false;
	deadEnemies = 0;
	levelOver = false;
	background.LoadTextureFromBitmap("textures/greenback.bmp"); background.SetSize(570,570); 
	initializeLevelArray();
	createList();
	player1.SetPosition(45,45);
	player1.setArrayPos(1,1);
	player2.SetPosition(525,525);
	player2.setArrayPos(17,17);
	invincible = false;	
	font.SetSize(24);
	font.SetColor(CColor::Black());
	levelmusic.Clear();
	levelmusic.LoadAudioFile("sounds/levelmusic.wav");
	levelmusic.SetVolume(50);

	if (musicPaused == false)
	{
	levelmusic.Play(2000000);
	}
	else
	{
		levelmusic.Play(2000000);
		levelmusic.Pause();
	}

	flameups.clear();
	flamedown.clear();
	bombups.clear();
	bombdown.clear();

}

void CMyGame::OnInitializeLevel_1()
{	
	player1.currentBombs = 0;
	player2.currentBombs = 0;
	srand(time(NULL));
	HighScoreRead("highscore.txt");
	singlePlayerButton.SetPosition(120,120);singlePlayerButton.SetSize(100,30);	
	multiPlayerButton.SetPosition(120,80);multiPlayerButton.SetSize(100,30);	
	controlButton.SetPosition(120,40);controlButton.SetSize(100,30);	
	background.LoadTextureFromBitmap("textures/menuback.bmp"); background.SetSize(570,570); 
	exit.SetPosition(-200,-200);
	levelmusic.Pause();
	flameups.clear();
	flamedown.clear();
	bombups.clear();
	bombdown.clear();
	livesl.clear();
}

void CMyGame::OnInitializeLevel_Single_1()
{
	player1.resetFlameLength();
	player1.resetMaxBombs();
	player2.resetFlameLength();
	player2.resetMaxBombs();

	cout << musicPaused;
	timer = 0;
	exit.SetPosition(-200,-200);
	singleLevel = 1;
	numOfEnemies = (level-20)+3;
	cout<<"Num of enemies : " << numOfEnemies << endl;
	spawnedEnemies = 0;
	isExit = false;
	deadEnemies = 0;
	levelOver = false;
	background.LoadTextureFromBitmap("textures/greenback.bmp"); background.SetSize(570,570); 
	initializeLevelArray();
	createList();
	player1.SetPosition(45,45);
	player1.setArrayPos(1,1);
	invincible = false;	
	font.SetSize(24);
	font.SetColor(CColor::Black());
	levelmusic.Clear();
	levelmusic.LoadAudioFile("sounds/levelmusic.wav");
	levelmusic.SetVolume(50);
	if (musicPaused == false)
	{
	levelmusic.Play(2000000);
	}
	else
	{
		levelmusic.Play(2000000);
		levelmusic.Pause();
	}


	flameups.clear();
	flamedown.clear();
	bombups.clear();
	bombdown.clear();
}

void CMyGame::OnInitializeLevel_1000()
{
	exit.SetPosition(-200,-200);
	blocks.clear();
	enemies.clear();
	fire.clear();
	bombs.clear();
	background.SetSize(0,0);
	bombups.clear();
	flameups.clear();
	bombdown.clear();
	flamedown.clear();
	player1.SetPosition(-10000,-10000);
	mainButton.SetPosition(100,20);mainButton.SetSize(100,30);	
	font.SetSize(72);
	font.SetColor(CColor::Black());

	if(highScore < score)
	{
		highScore = score;
		HighScoreWrite("highscore.txt");
	}
}


void CMyGame::OnInitializeLevel_1001()
{
	mainButton.SetPosition(100,20);mainButton.SetSize(100,30);	
	cout << "GameOVer/n";
	exit.SetPosition(-200,-200);
	blocks.clear();
	enemies.clear();
	fire.clear();
	bombs.clear();
	background.SetSize(0,0);
	bombups.clear();
	flameups.clear();
	bombdown.clear();
	flamedown.clear();
	player1.SetPosition(-10000,-10000);
	player2.SetPosition(-10000,-10000);
	
	mainButton.SetPosition(100,30);
	font.SetSize(42);
	font.SetColor(CColor::Red());
}


// Game Logic in the OnUpdate function called every frame
// update sprites here
void CMyGame::createPowerUp(int pxpos,int pypos)
{
	//Random chance of spawning a powerup
	int sc = rand() % 100;
	if (sc < 40)
	{
		int pc = rand() % 4;
		if (pc == 0)
		{
			//Powerup 1
			CSprite* pu = new BombUp();
			pu->SetTexture(bombUpTex);
			pu->SetSize(26,26);
			pu->SetPosition(pxpos, pypos);
			bombups.add(pu);
			cout << "Bomb powerup TEST **********************************" << endl;
		}
		else if (pc == 1)
		{
			//Powerup 2
			CSprite* pu = new FlameUp();
			pu->SetTexture(flameUpTex);
			pu->SetSize(26,26);
			pu->SetPosition(pxpos, pypos);
			flameups.add(pu);
			cout << "Flame  ************************************" << endl;
		}
		else if (pc == 2)
		{
			//Powerup 3
			CSprite* pu = new FlameDown();
			pu->SetTexture(flameDownTex);
			pu->SetSize(26,26);
			pu->SetPosition(pxpos, pypos);
			flamedown.add(pu);

		}
		else if (pc == 3)
		{
			//Powerup 4
			CSprite* pu = new BombDown();
			pu->SetTexture(bombDownTex);
			pu->SetSize(26,26);
			pu->SetPosition(pxpos, pypos);
			bombdown.add(pu);
		}
	}
}

void CMyGame::OnUpdate() 
{
	if(level == 1000 || level == 15 || level == 11)
	{
		mainButton.Update(GetTime());
	}

	if(level == 10)
	{
		exit.SetPosition(-200,-200);
		for(int fo = 0; fo < fire.size(); fo++)
		{
			if(player1.HitTest(fire[fo]))
			{				
				//multiplayer player 1 die
				level = 11;
				OnInitializeLevel_1001();
				winner = false;
				break;
			}

			if(player2.HitTest(fire[fo]))
			{			
				//multiplayer player 2 die
				level = 11;
				OnInitializeLevel_1001();
				winner = true;
				break;
			}
		}

	}
	//Optimisation and Clearing
	//Fire Vector Clearing
	for(int fo = 0; fo < fire.size(); fo++)
	{
		if (fire[fo]->GetX() < 0 || fire[fo]->GetX() > 570 || fire[fo]->GetY() < 0 || fire[fo]->GetY() > 570)
		{
			fire.erase(fire.begin()+fo);
			//cout << "Fire vector size is " << fire.size() << endl;
		}
	}

	//Bomb Vector Clearing
	for(int bo = 0; bo < bombs.size(); bo++)
	{
		if (bombs[bo]->GetX() < 0 || bombs[bo]->GetX() > 570 || bombs[bo]->GetY() < 0 || bombs[bo]->GetY() > 570)
		{
			bombs.erase(bombs.begin()+bo);
			//cout << "Bomb vector size is " << bombs.size() << endl;
		}
	}

	//Block Vector Clearing
	for(int bo = 0; bo < blocks.size(); bo++)
	{
		if (blocks[bo]->GetX() < 0 || blocks[bo]->GetX() > 570 || blocks[bo]->GetY() < 0 || blocks[bo]->GetY() > 570)
		{
			blocks.erase(blocks.begin()+bo);
			//cout << "Block vector size is " << blocks.size() << endl;
		}
	}

	//Powerup Clearing
	for (int i = 0; i < bombups.size(); i++)
	{
		if (bombups[i]->GetX() < 0)
		{
			bombups.erase(i--);
			//cout << "Bomb up spritelist size is " << bombups.size() << endl;
		}
	}

	for (int i = 0; i < flameups.size(); i++)
	{
		if (flameups[i]->GetX() < 0)
		{
			flameups.erase(i--);
			//cout << "Flame up spritelist size is " << flameups.size() << endl;
		}
	}

	for (int i = 0; i < flamedown.size(); i++)
	{
		if (flamedown[i]->GetX() < 0)
		{
			flamedown.erase(i--);
			//cout << "Flame down spritelist size is " << flamedown.size() << endl;
		}
	}

	for (int i = 0; i < bombdown.size(); i++)
	{
		if (bombdown[i]->GetX() < 0)
		{
			bombdown.erase(i--);
			//cout << "Bomb down spritelist size is " << bombdown.size() << endl;
		}
	}

	//Menu updates and logic
	if(level == 1)
	{
		singlePlayerButton.Update(GetTime());
		multiPlayerButton.Update(GetTime());
		controlButton.Update(GetTime());

		
		if(controlButton.HitTest(mouseX,mouseY))
		{
			controlButton.SetTexture(controlsDown);
		}
		else
		{
			controlButton.SetTexture(controlsUp);
		}

		if(singlePlayerButton.HitTest(mouseX,mouseY))
		{
			singlePlayerButton.SetTexture(texture2);
		}
		else
		{
			singlePlayerButton.SetTexture(texture);
		}

		if(multiPlayerButton.HitTest(mouseX,mouseY))
		{
			multiPlayerButton.SetTexture(button2);
		}
		else
		{
			multiPlayerButton.SetTexture(button1);
		}
	}

	

		if(mainButton.HitTest(mouseX,mouseY))
		{
			mainButton.SetTexture(mainDown);
		}
		else
		{
			mainButton.SetTexture(mainUp);
		}
	// font.SetSize(40); font.SetColor( 128,255,128); 
	// font.DrawNumber( 750,550, score);

	player1.Update(GetTime());
	player2.Update(GetTime());

	if(level >1)
	{
		for(int n = 0; n < bombups.size(); n++)
		{
			bombups[n]->Update(GetTime());

			for(int p = 0; p<fire.size(); p++)
			{
				if(bombups[n]->HitTest(fire[p]))
				{					
					bombups[n]->SetPosition(-100,-100);
				}
			}

			if(bombups[n]->HitTest(player1.GetX(),player1.GetY()))
			{
				//Bomb up
				player1.setMaxBombs(1);
				bombups.erase(n--);
				pickup.Play();
			}
			else if(bombups[n]->HitTest(player2.GetX(),player2.GetY()))
			{
				//Bomb up
				player2.setMaxBombs(1);
				bombups.erase(n--);
				pickup.Play();
			}	
		}

		for(int n = 0; n < bombdown.size(); n++)
		{
			bombdown[n]->Update(GetTime());

			for(int p = 0; p<fire.size(); p++)
			{
				if(bombdown[n]->HitTest(fire[p]))
				{					
					bombdown[n]->SetPosition(-100,-100);
				}
			}

			if(bombdown[n]->HitTest(player1.GetX(),player1.GetY()))
			{
				//Bomb Down
				player1.setMaxBombs(-1);
				bombdown.erase(n--);
				pickup.Play();
			}
			else if(bombdown[n]->HitTest(player2.GetX(),player2.GetY()))
			{
				//Bomb Down
				player2.setMaxBombs(-1);
				bombdown.erase(n--);
				pickup.Play();
			}
		}

		for(int n = 0; n < flameups.size(); n++)
		{
			flameups[n]->Update(GetTime());

			for(int p = 0; p<fire.size(); p++)
			{
				if(flameups[n]->HitTest(fire[p]))
				{					
					flameups[n]->SetPosition(-100,-100);
				}
			}

			if(flameups[n]->HitTest(player1.GetX(),player1.GetY()))
			{
				//Bomb up
				player1.setFlameLength(1);
				flameups.erase(n--);
				pickup.Play();
			}
			else if(flameups[n]->HitTest(player2.GetX(),player2.GetY()))
			{
				//Bomb up
				player2.setFlameLength(1);
				flameups.erase(n--);
				pickup.Play();
			}
		}

		for(int n = 0; n < flamedown.size(); n++)
		{
			flamedown[n]->Update(GetTime());

			for(int p = 0; p<fire.size(); p++)
			{
				if(flamedown[n]->HitTest(fire[p]))
				{					
					flamedown[n]->SetPosition(-100,-100);
				}
			}

			if(flamedown[n]->HitTest(player1.GetX(),player1.GetY()))
			{
				//Bomb Down
				player1.setFlameLength(-1);
				flamedown.erase(n--);
				pickup.Play();
			}
			else if(flamedown[n]->HitTest(player2.GetX(),player2.GetY()))
			{
				//Bomb Down
				player2.setFlameLength(-1);
				flamedown.erase(n--);
				pickup.Play();
			}
		}

		for(int n = 0; n< blocks.size(); n++)
		{
			blocks[n]->Update(GetTime());
		}

		for(int i = 0;i < bombs.size();i++)
		{
			bombs[i]->Update(GetTime());
			bombs[i]->tick();

			if(bombs[i]->getFuse() <= 0)
			{
				//Create explosion
				if(bombs[i]->isExploded() == false)
				{
					int fireLength = bombs[i]->getFlameLength();
					cout << fireLength;
					Fire* center = new Fire();
					center->SetTexture(texture5);
					center->SetSize(30,30);
					center->SetPosition(bombs[i]->GetX(),bombs[i]->GetY());
					fire.push_back(center);
					int bombx = bombs[i]->GetX();
					int bomby = bombs[i]->GetY();
					bombs[i]->SetPosition(-100,-100);
					bombs[i]->explode();
					explosion.Play();
					leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()] = 0;

					bool stopleft,stopright,stopup,stopdown;
					stopleft = false;
					stopright = false;
					stopup = false;
					stopdown = false;



					double pxpos = 0 ;
					double pypos = 0 ;
					for(int a =0 ; a <=fireLength;a++)
					{
						//Right
						if(stopright == false)
						{
							if(leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()+a] == 0)
							{
								Fire* f = new Fire();
								f->SetTexture(firet);
								f->SetSize(30,28);
								f->SetPosition(bombx+(a*30),bomby);
								fire.push_back(f);
								cout << "Flame Right" <<endl;
							}
							else
							{

								stopright = true;
								if(leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()+a] == 9)
								{
									for(int p = 0;p < bombs.size();p++)		
									{
										if(leveldesign[bombs[p]->getArrayX()][bombs[p]->getArrayY()] == leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()+a])
										{
											bombs[p]->setFuse(0);
											break;
										}
									}
								}

								if(leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()+a] == 2)
								{
									for(int n = 0; n< blocks.size(); n++)
									{
										int arrayY = blocks[n]->getArrayY();
										int arrayX = blocks[n]->getArrayX();

										if(arrayY == bombs[i]->getArrayY()+a && arrayX == bombs[i]->getArrayX())
										{
											cout << "power up drop" << endl;
											createPowerUp(blocks[n]->GetX(),blocks[n]->GetY());
										}
									}
									leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()+a] = 0;
								}

								for(int n = 0; n< blocks.size(); n++)
								{
									if(leveldesign[blocks[n]->getArrayX()][blocks[n]->getArrayY()] == leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()+a])
									{
										if(blocks[n]->isExit())
										{
											exit.SetPosition(blocks[n]->GetX(),blocks[n]->GetY());
											blocks[n]->setExit(false);
											leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()+a] = 0;
										}				

										blocks[n]->setBroken(true);	
										blocks[n]->SetPosition(-200,-200);
									}
								}
							}
						}

						///Left
						if(stopleft == false)
						{
							if(leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()-a] == 0)
							{
								Fire* f = new Fire();
								f->SetTexture(firet);
								f->SetSize(30,28);
								f->SetPosition(bombx-(a*30),bomby);
								fire.push_back(f);
								cout << "Flame Left" <<endl;
							}
							else
							{
								stopleft = true;
								if(leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()-a] == 9)
								{
									for(int p = 0;p < bombs.size();p++)		
									{
										if(leveldesign[bombs[p]->getArrayX()][bombs[p]->getArrayY()] == leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()-a])
										{
											bombs[p]->setFuse(0);
											
											break;
										}
									}
								}
								if(leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()-a] == 2)
								{
									for(int n = 0; n< blocks.size(); n++)
									{
										int arrayY = blocks[n]->getArrayY();
										int arrayX = blocks[n]->getArrayX();

										if(arrayY == bombs[i]->getArrayY()-a && arrayX == bombs[i]->getArrayX())
										{
											cout << "power up drop" << endl;
											createPowerUp(blocks[n]->GetX(),blocks[n]->GetY());
										}
									}
									leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()-a] = 0;

								}
								for(int n = 0; n< blocks.size(); n++)
								{
									if(leveldesign[blocks[n]->getArrayX()][blocks[n]->getArrayY()] == leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()-a])
									{
										if(blocks[n]->isExit())
										{
											blocks[n]->setExit(false);
											exit.SetPosition(blocks[n]->GetX(),blocks[n]->GetY());
											leveldesign[bombs[i]->getArrayX()][bombs[i]->getArrayY()-a] = 0;
										}
										blocks[n]->SetPosition(-200,-200);
										blocks[n]->setBroken(true);
									}
								}									
							}
						}
						//Up
						if(stopup == false)
						{
							if(leveldesign[bombs[i]->getArrayX()+a][bombs[i]->getArrayY()] == 0)
							{
								Fire* f = new Fire();
								f->SetTexture(firet);
								f->SetSize(30,28);
								f->Rotate(90);
								f->SetPosition(bombx,bomby+(a*30));
								fire.push_back(f);
								cout << "Flame Up" <<endl;
							}
							else
							{
								stopup = true;
								if(leveldesign[bombs[i]->getArrayX()+a][bombs[i]->getArrayY()] == 9)
								{
									for(int p = 0;p < bombs.size();p++)		
									{
										if(leveldesign[bombs[p]->getArrayX()][bombs[p]->getArrayY()] == leveldesign[bombs[i]->getArrayX()+a][bombs[i]->getArrayY()])
										{
											bombs[p]->setFuse(0);
											
											break;
										}
									}
								}
								if(leveldesign[bombs[i]->getArrayX()+a][bombs[i]->getArrayY()] == 2)
								{
									for(int n = 0; n< blocks.size(); n++)
									{
										int arrayY = blocks[n]->getArrayY();
										int arrayX = blocks[n]->getArrayX();

										if(arrayY == bombs[i]->getArrayY() && arrayX == bombs[i]->getArrayX()+a)
										{
											cout << "power up drop" << endl;
											createPowerUp(blocks[n]->GetX(),blocks[n]->GetY());
										}
									}
									leveldesign[bombs[i]->getArrayX()+a][bombs[i]->getArrayY()] = 0;

								}
								for(int n = 0; n< blocks.size(); n++)
								{
									if(leveldesign[blocks[n]->getArrayX()][blocks[n]->getArrayY()] == leveldesign[bombs[i]->getArrayX()+a][bombs[i]->getArrayY()])
									{
										if(blocks[n]->isExit())
										{
											blocks[n]->setExit(false);
											exit.SetPosition(blocks[n]->GetX(),blocks[n]->GetY());
											leveldesign[bombs[i]->getArrayX()+a][bombs[i]->getArrayY()] = 0;
										}
										blocks[n]->SetPosition(-200,-200);
										blocks[n]->setBroken(true);
									}
								}

							}
						}

						//Down
						if(stopdown == false)
						{
							if(leveldesign[bombs[i]->getArrayX()-a][bombs[i]->getArrayY()] == 0)
							{
								Fire* f = new Fire();
								f->SetTexture(firet);
								f->SetSize(30,28);
								f->Rotate(90);
								f->SetPosition(bombx,bomby-(a*30));
								fire.push_back(f);
								cout << "Flame Down" <<endl;
							}
							else
							{
								stopdown = true;
								if(leveldesign[bombs[i]->getArrayX()-a][bombs[i]->getArrayY()] == 9)
								{
									for(int p = 0;p < bombs.size();p++)		
									{
										if(leveldesign[bombs[p]->getArrayX()][bombs[p]->getArrayY()] == leveldesign[bombs[i]->getArrayX()-a][bombs[i]->getArrayY()])
										{
											bombs[p]->setFuse(0);
											break;
										}
									}
								}
								if(leveldesign[bombs[i]->getArrayX()-a][bombs[i]->getArrayY()] == 2)
								{
									for(int n = 0; n< blocks.size(); n++)
									{
										int arrayY = blocks[n]->getArrayY();
										int arrayX = blocks[n]->getArrayX();

										if(arrayY == bombs[i]->getArrayY() && arrayX == bombs[i]->getArrayX()-a)
										{
											cout << "power up drop" << endl;
											createPowerUp(blocks[n]->GetX(),blocks[n]->GetY());
										}
									}
									leveldesign[bombs[i]->getArrayX()-a][bombs[i]->getArrayY()] = 0;
								}
								for(int n = 0; n< blocks.size(); n++)
								{
									if(leveldesign[blocks[n]->getArrayX()][blocks[n]->getArrayY()] == leveldesign[bombs[i]->getArrayX()-a][bombs[i]->getArrayY()])
									{
										if(blocks[n]->isExit())
										{
											blocks[n]->setExit(false);
											exit.SetPosition(blocks[n]->GetX(),blocks[n]->GetY());												
											leveldesign[bombs[i]->getArrayX()-a][bombs[i]->getArrayY()] = 0;
										}
										blocks[n]->SetPosition(-200,-200);
										blocks[n]->setBroken(true);
									}
								}
							}
						}
					}
					
					bombs[i]->setArrayX(-100);
					bombs[i]->setArrayY(-100);
					stopleft = false;
					stopright = false;
					stopup = false;
					stopdown = false;

		
					if(bombs[i]->getPlayer() == 1)
					{
						player1.setCurrentBombs(-1);
					}

					if(bombs[i]->getPlayer() == 2)
					{
						player2.setCurrentBombs(-1);
					}
				}
			}
		}

		for(int i = 0;i < fire.size();i++)
		{
			fire[i]->Update(GetTime());
			fire[i]->tick();

			if(fire[i]->getTimeAlive() <= 0)
			{
				fire[i]->SetPosition(-100,-100);
			}
		}
	}

	if(level >=21 && level != 1000)
	{
		livesl.Update(GetTime());

		if(player1.HitTest(exit.GetX(),exit.GetY()) && levelOver)
		{
			cout << "Level Complete" << endl;
			level++;
			OnInitializeLevel_Single_1();
		}

		for(int i = 0;i < enemies.size();i++)
		{
			enemies[i]->Update(GetTime());			
			enemies[i]->tick(blocks,bombs);

			//Check if enemies collide with player
			if (player1.HitTest(enemies[i]) && (invincible == false))
			{
				lives--;
				player1.SetPosition(45,45);
				player1.setArrayPos(1,1);				
				invincible = true;
				if(lives <= 0)
				{
					//GameOver
					level = 1000;
					OnInitializeLevel_1000();
				}
			}

			//Check if enemies collide with fire
			if(fire.size() != NULL)
			{
				for(int a = 0; a < fire.size();a++)
				{
					if(enemies[i]->HitTest(fire[a]))
					{
						enemies[i]->SetPosition(-1000,-1000);
						deadEnemies++;
						score++;
						if(deadEnemies == numOfEnemies)
						{
							levelOver = true;
						}
					}	
				}
			}
		}

	


	for (int fl = 0; fl < fire.size(); fl++)
	{
		//Player 1 killed by fire
		if (player1.HitTest(fire[fl]) && (invincible == false))
		{
			//Kill player of 2 of 2
			lives--;
			player1.SetPosition(45,45);
			player1.setArrayPos(1,1);
			invincible = true;
			if((lives <= 0))
			{
				//GameOver
				level = 1000;
				OnInitializeLevel_1000();
			}
		}
	}

	}

	exit.Update(GetTime());

	if(invincible == true)
	{
		timer++;
		if(timer > 21)
		{
			timer = 0;
			invincible = false;
		}
	}
}

// draw sprites here
void CMyGame::OnDraw()
{	
	background.Draw((background.GetWidth()/2),(background.GetHeight()/2));
	
	
	if(level ==15)
	{
		controls.Draw(285,285);
	}

	//Menu Draws
	exit.Draw();
	if(level == 1)
	{
		singlePlayerButton.Draw();
		multiPlayerButton.Draw();
		controlButton.Draw();
		highScoreFont.DrawTextW(310, 525, "High score");
		highScoreFont.DrawNumber(385, 485, highScore);
	}

	if(level>1)
	{
		for (int n = 0; n < bombups.size(); n++)
		{
			bombups[n]->Draw();
		}

		for (int n = 0; n < bombdown.size(); n++)
		{
			bombdown[n]->Draw();
		}

		for (int n = 0; n < flameups.size(); n++)
		{
			flameups[n]->Draw();
		}

		for (int n = 0; n < flamedown.size(); n++)
		{
			flamedown[n]->Draw();
		}

		for(int n = 0; n< blocks.size(); n++)
		{
			blocks[n]->Draw();
		}

		for(int i = 0;i < bombs.size();i++)
		{
			bombs[i]->Draw();
		}

		for(int i = 0;i < fire.size();i++)
		{
			fire[i]->Draw();			
		}
	}
	//Level draws
	if(level >=21 && level != 1000)
	{
		for(int i = 0;i < enemies.size();i++)
		{
			enemies[i]->Draw();			
		}

		for(int a = 0; a<lives;a++)
		{
			livesl[a]->Draw();
		}
		font.DrawTextW(10, 547, "Score:");
		font.DrawNumber(90,547,score);
	}	

	player1.Draw();
	player2.Draw();

	if (level == 1000)
	{
		singleEnd.Draw(285,285);
		font.DrawNumber(270, 200, score);
	}

	if (level == 11)
	{
		multEnd.Draw(285,285);
		if (winner == true)
		{
		winnerFont.DrawTextW(165, 200, "Player one!");
		}
		else
		{
		winnerFont.DrawTextW(165, 200, "Player two!");
		}
	}

	
	if(level >999 || level == 15 ||level == 11)
	{
		mainButton.Draw();
	}

}

// called when Game is Over
void CMyGame::OnGameOver()
{

}

// one time termination code
void CMyGame::OnTerminate()
{

}

// -------    Keyboard Event Handling ------------

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{   // pause/resume if SPACE pressed
	//	player1.move2();
	if (sym == SDLK_SPACE)
	{
		if (IsPaused()) 
			{
				ResumeGame();
				if (musicPaused == false)
				{
					levelmusic.Resume();
				}
			}
		else 
			{
				PauseGame();
				if (musicPaused == false)
				{
					levelmusic.Pause();
				}
			}
	}
	// start a new game if F2 pressed
	if (sym == SDLK_F2) 
	{
		srand(time(NULL));
		NewGame();
		exit.SetPosition(-200,-200);
		blocks.clear();
		enemies.clear();
		fire.clear();
		bombs.clear();
		bombups.clear();
		flameups.clear();
		bombdown.clear();
		flamedown.clear();
		if (level = 10)
		{
			player1.SetPosition(-200, -200);
			player2.SetPosition(-200, -200);
		}
	}


	if(level > 1)
	{
		//Player 1
		int x = player1.GetX();
		int y = player1.GetY();

		if (sym == SDLK_w)
		{
				if((leveldesign[player1.getArrayX()+1][player1.getArrayY()] <= 0))
				{
					//cout << "Should move" << endl;
					player1.SetY(y+30);
					player1.setArrayPos(player1.getArrayX()+1,player1.getArrayY());	
				}
			player1.SetTexture(back);
		}

		if (sym == SDLK_s)
		{
			if((leveldesign[player1.getArrayX()-1][player1.getArrayY()] <= 0))
			{
				//cout << "Should move" << endl;
				player1.SetY(y-30);
				player1.setArrayPos(player1.getArrayX()-1,player1.getArrayY());	
			}	
			player1.SetTexture(texture4);
		}

		if (sym == SDLK_a)
		{
			if(leveldesign[player1.getArrayX()][player1.getArrayY()-1] <= 0)
			{
				//cout << "Should move" << endl;
				player1.SetX(x-30);
				player1.setArrayPos(player1.getArrayX(),player1.getArrayY()-1);	
			}	
			player1.SetTexture(left);
		}

		if (sym == SDLK_d)
		{
			if(leveldesign[player1.getArrayX()][player1.getArrayY()+1] <= 0)
			{
				//cout << "Should move" << endl;
				player1.SetX(x+30);
				player1.setArrayPos(player1.getArrayX(),player1.getArrayY()+1);	
			}	
			player1.SetTexture(right);
		}

		if(sym == SDLK_f)
		{
			if(player1.getMaxBombs() > player1.getCurrentBombs())
			{
				if(leveldesign[player1.getArrayX()][player1.getArrayY()] == 0)
				{
					Bomb* i = new Bomb(1,player1.getFlameLength(),player1.isSpiked(),player1.getArrayX(),player1.getArrayY());
					cout<<"Flame length: " << i->getFlameLength() <<" Bombs Max: " << player1.getMaxBombs() << endl;
					i->SetTexture(texture3);
					i->SetSize(30,30);
					i->SetPosition(player1.GetX(),player1.GetY());
					bombs.push_back(i);
					bombplace.Play();
					player1.setCurrentBombs(1);		
					leveldesign[player1.getArrayX()][player1.getArrayY()] = 9;
				}
			}

		}


		//Player 2
		x = player2.GetX();
		y = player2.GetY();

		if (sym == SDLK_UP)
		{
			if(leveldesign[player2.getArrayX()+1][player2.getArrayY()] <= 0)
			{
				//cout << "Should move" << endl;
				player2.SetY(y+30);
				player2.setArrayPos(player2.getArrayX()+1,player2.getArrayY());	
			}
			player2.SetTexture(back2);
		}

		if (sym == SDLK_DOWN)
		{
			if(leveldesign[player2.getArrayX()-1][player2.getArrayY()] <= 0)
			{
				//cout << "Should move" << endl;
				player2.SetY(y-30);
				player2.setArrayPos(player2.getArrayX()-1,player2.getArrayY());	
			}	
			player2.SetTexture(front2);
		}

		if (sym == SDLK_LEFT)
		{
			if(leveldesign[player2.getArrayX()][player2.getArrayY()-1] <= 0)
			{
				//cout << "Should move" << endl;
				player2.SetX(x-30);
				player2.setArrayPos(player2.getArrayX(),player2.getArrayY()-1);	
			}	
			player2.SetTexture(left2);
		}

		if (sym == SDLK_RIGHT)
		{
			if(leveldesign[player2.getArrayX()][player2.getArrayY()+1] <= 0)
			{
				//cout << "Should move" << endl;
				player2.SetX(x+30);
				player2.setArrayPos(player2.getArrayX(),player2.getArrayY()+1);	
			}	
			player2.SetTexture(right2);
		}

		if(sym == SDLK_RCTRL)
		{
			if(player2.getMaxBombs() > player2.getCurrentBombs())
			{
				if(leveldesign[player2.getArrayX()][player2.getArrayY()] == 0)
				{
					Bomb* i = new Bomb(2,player2.getFlameLength(),player2.isSpiked(),player2.getArrayX(),player2.getArrayY());
					cout<<"Flame length: " << i->getFlameLength() <<" Bombs Max: " << player2.getMaxBombs() << endl;
					i->SetTexture(texture3);
					i->SetSize(30,30);
					i->SetPosition(player2.GetX(),player2.GetY());
					bombs.push_back(i);
					bombplace.Play();
					player2.setCurrentBombs(1);		
					leveldesign[player2.getArrayX()][player2.getArrayY()] = 9;
				}
			}

		}

		if(sym == SDLK_m)
		{
			if (IsPaused())
			{
			}
			else
			{
				if (musicPaused == true)
				{
					levelmusic.Resume();
					musicPaused = false;
				}
				else
				{
					levelmusic.Pause();
					musicPaused = true;
				}
			}
		}

		//ADMIN COMMANDS

		if(sym == SDLK_p)
		{
			cout << "Called" << endl;
			for(int i = 0 ; i <blocks.size() ; i++)
			{
				if(blocks[i]->isBreakable())
				{
					Fire* f = new Fire();
					f->SetTexture(firet);
					f->SetSize(30,30);
					f->SetPosition(blocks[i]->GetX(),blocks[i]->GetY());
					fire.push_back(f);
				}														

				if(blocks[i]->isBreakable())
				{
					if(blocks[i]->isExit())
					{
						exit.SetPosition(blocks[i]->GetX(),blocks[i]->GetY());
					}
					leveldesign[blocks[i]->getArrayX()][blocks[i]->getArrayY()] = 0;
					blocks[i]->SetPosition(-200,-200);
				}
			}
		}

		if(sym == SDLK_z)
		{
			lives = 0;
			level = 1000;
			OnInitializeLevel_1000();
		}
	}
}


void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{


}

//Level stuff's
void CMyGame::createList()
{
	int y = 0;
	enemies.clear();
	blocks.clear();
	bombs.clear();
	fire.clear();	

	for(int row = 0; row< 19;row++)
	{
		int x = 0;
		for(int col = 0; col <19;col++)
		{
			if(leveldesign[row][col] == 1)
			{
				Unbreakable* i = new Unbreakable(x+15,y+15);
				i->SetTexture(uBlock);
				i->SetSize(30,30);
				blocks.push_back(i);
			}

			if(leveldesign[row][col] == 2)
			{
				Breakable* i = new Breakable(x+15,y+15,false,row,col);					
				i->SetTexture(bBlock);
				i->SetSize(30,30);
				blocks.push_back(i);			
			}

			if(leveldesign[row][col] == -1)
			{
				Breakable* i = new Breakable(x+15,y+15,false,row,col);
				exit.SetPosition(x+15,y+15);
				i->SetTexture(bBlock);
				i->SetSize(30,30);
				blocks.push_back(i);
				leveldesign[row][col] = 2;
			}
			x+=30;
		}
		y+= 30;
	}

	y = 0;

	for(int row = 0; row< 19;row++)
	{
		int x = 0;
		for(int col = 0; col <19;col++)
		{
			if(leveldesign[row][col] == 3)
			{
				random = rand() %2;

				if(leveldesign[row-1][col] != 1)
				{
					if(random == 1)
					{					
						Enemy* i = new Enemy(1,0,1,1);
						i->SetTexture(enemy1);
						i->SetSize(28,28);
						i->SetPosition(x+15,y+15);
						enemies.push_back(i);
						leveldesign[row][col] = 0 ;
					}
					else
					{
						Enemy* i = new Enemy(1,0,-1,1);
						i->SetTexture(enemy1);
						i->SetSize(28,28);
						i->SetPosition(x+15,y+15);
						enemies.push_back(i);
						leveldesign[row][col] = 0 ;		
					}
				}else

					if(leveldesign[row][col-1] != 1)
					{
						if(random == 1)
						{					
							Enemy* i = new Enemy(1,-1,0,1);
							i->SetTexture(enemy1);
							i->SetSize(28,28);
							i->SetPosition(x+15,y+15);
							enemies.push_back(i);
							leveldesign[row][col] = 0 ;
						}
						else
						{
							Enemy* i = new Enemy(1,1,0,1);
							i->SetTexture(enemy1);
							i->SetSize(28,28);
							i->SetPosition(x+15,y+15);
							enemies.push_back(i);
							leveldesign[row][col] = 0 ;
						}
					}				
			}
			x+=30;
		}
		y+= 30;
	}

}

void CMyGame::initializeLevelArray()
{
	cout << "Clearing blocks" << endl;
	blocks.clear();
	cout << "Initializing level" << endl;
	//Empty the array
	for(int row = 0; row< 19;row++)
	{
		for(int col = 0; col <19;col++)
		{
			leveldesign[row][col] = 0;
		}
	}
	//Place unblowupable blocks
	for(int col = 0; col <19;col++)
	{		
		for(int row = 0; row< 19;row++)
		{
			if((col== 0) || (col == 18))
			{
				leveldesign[row][col] = 1;
			}
		}
	}

	for(int row = 0; row< 19;row++)
	{
		for(int col = 0; col <19;col++)
		{
			if((row == 0) || (row == 18) || ((col % 2)== 0 && (row %2)==0))
			{
				leveldesign[row][col] = 1;
			}			
		}
	}

	//Random Placement Of breakable blocks
	do
	{
		for(int row = 0; row< 19;row++)
		{
			for(int col = 0; col <19;col++)
			{
				random = rand() %100;
				//----------------------------------------------------------------------------random chance-------------------------------------
				if((leveldesign[row][col] == 0 && random >= 50))
				{
					leveldesign[row][col] = 2;

					random = rand()%100;
					if(random >= 98 && isExit == false)
					{
						leveldesign[row][col] = -1;
						isExit = true;
						cout << "Exit Placed" << endl;
					}
				}
			}
		}		
	}while(isExit == false);

	//Random Placement Of Enemies
	do
	{
		for(int row = 2; row< 17;row++)
		{
			for(int col = 2; col <17;col++)
			{
				random = rand() %100;
				//----------------------------------------------------------------------------random chance-------------------------------------
				if((leveldesign[row][col] == 2)&&(random <=1)&&(spawnedEnemies < numOfEnemies))
				{
					//if(row != 1)
					//{

					spawnedEnemies++;
					cout << "Enemy spawn" << endl;
					leveldesign[row][col] = 3;


					if(leveldesign[row][col-1] == 2)
					{
						leveldesign[row][col-1] = 0;
					}

					if(leveldesign[row][col+1] == 2)
					{
						leveldesign[row][col+1] = 0;
					}

					if(leveldesign[row-1][col] == 2)
					{
						leveldesign[row-1][col] = 0;
					}

					if(leveldesign[row+1][col] == 2)
					{
						leveldesign[row+1][col] = 0;
					}
					//}
				}
			}
		}	
	}while(spawnedEnemies < numOfEnemies);


	//Clear Corners
	//1,1 1,18 18,18 18,1
	leveldesign[1][1] = 0;
	leveldesign[1][2]= 0;
	leveldesign[1][3]= 2;
	leveldesign[2][1]= 0;
	leveldesign[3][1]= 2;
	//leveldesign[17][1] = 1;

	leveldesign[17][17] = 0;
	leveldesign[17][16]= 0;
	leveldesign[17][15]=2;
	leveldesign[16][17]= 0;
	leveldesign[15][17]= 2;
	//Print out for debugging
	for(int row = 18; row>= 0;row--)
	{
		for(int col = 0; col <19;col++)
		{
			cout << leveldesign[row][col] ;
		}
		cout << endl;
	}
}

// -----  Mouse Events Handlers -------------

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{   
	mouseX = x; mouseY = y;
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	if(level == 1)
	{
		if(singlePlayerButton.HitTest(x,y))
		{	
			menuclick.Play();
			level = 21;
			OnInitializeLevel_Single_1();
			lives = 3;

			for(int a = 0;a<lives;a++)
			{
				CSprite* l = new CSprite(560-((a+1)*28), 555,life);
				l->SetSize(28,28);
				livesl.add(l);
			}

			score = 0;
		}


		if(multiPlayerButton.HitTest(x,y))
		{	
			menuclick.Play();
			level = 10;
			OnInitializeLevel_Multi_1();
		}

		if(controlButton.HitTest(x,y))
		{	
			menuclick.Play();
			level = 15;
			OnInitializeLevel_Control();
		}
	}

	if(level == 1000 || level == 15 || level == 11)
	{
		if(mainButton.HitTest(x,y))
		{
			menuclick.Play();
			level = 1;
			NewGame();
		}
	}
}

void CMyGame::OnInitializeLevel_Control()
{
	background.SetSize(0,0);
	mainButton.SetPosition(100,540);
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{

}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
