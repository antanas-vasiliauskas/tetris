#pragma once

#include <vector>

#include "Renderer.h"
#include "Shader.h"
#include "Square.h"
#include "Texture.h"
#include "Inputs.h"
#include "Robotas.h"
#include <GLFW/glfw3.h>
#include <thread>
#include <Windows.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "Soundtrack.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900


class TetrisGame
{
	// Variables
private:
	int modas = 2;
	//Robotas Samuolis(0, 0);
	Plan bestPlan = Plan(5, 0);
	// Forms of tetris shapes
	const int shape[7][16] = {

		{0,0,1,0,
		 0,0,1,0,
		 0,0,1,0,
		 0,0,1,0},

		{0,0,2,0,
		 0,2,2,0,
		 0,2,0,0,
		 0,0,0,0},

		{0,2,0,0,
		 0,2,2,0,
		 0,0,2,0,
		 0,0,0,0},

		{0,3,0,0,
		 0,3,0,0,
		 0,3,3,0,
		 0,0,0,0},

		{0,0,4,0,
		 0,0,4,0,
		 0,4,4,0,
		 0,0,0,0},

		{0,0,0,0,
		 0,5,5,0,
		 0,5,5,0,
		 0,0,0,0},

		{0,0,6,0,
		 0,6,6,0,
		 0,0,6,0,
		 0,0,0,0},
	};
	int grid_width = 64;
	int grid_height = 64;



	// Controls size of a single tetris block, grid margin from the top left corner
	const float pixel = 2.0f / (float)SCREEN_WIDTH;

	// Calculated at runtime, before first render
	float cell_size = pixel * 40.0f;
	float margin_vertical = pixel * 50.0f;
	float margin_horizontal = pixel * 50.0f;

	// ----------------------------------------------------- RUNTIME GAME INFORMATION ------------------------------------------------------------

	std::vector<int> grid; // Represents the grid: 0-empty spaces, 1-blocks 
	// (later could be added that different numbers represents different color blocks, e.g. 1 - blue, 2 - green...)
	std::vector<int> square_indexes; // stores indexes of existing squares, so it can be removed latter.

	int currentPiece = rand() % 7; // Of which shape is current piece, can access it's form by shape[currentPiece]
	int currentRotation = 1;
	int currentX = grid_width / 2; // Represents current piece's location in grid. When new piece is added, it starts off at top middle.
	int currentY = 0;

	int tick = 10; // 1 tick - 50 miliseconds. Game updates every tick.
	int ticksToForceDown = 20; // How many ticks it takes to move one square down. Default - 1 second.
	bool forceDown = false; 
	int ticksPassed = 0;
	
	int piecesToIncreaseSpeed = 3; // nPieceCount % piecesToIncreaseSpeed == 0 -> ticksToForceDown-- 
	int pieceCount = 0;
	int score = 0;

	// When line is formed, the game is paused for a brief moment and textures of line squares are changed
	bool pause_a_bit = false; 
	int time_to_pause = 200; // milliseconds
	std::vector<int> lines; // location of lines (max 4 elements)
	std::vector<int> linesIndexes; // square blocks with different textures indexes, so they can be removed after a pause


	bool pressed_keys[4]; // Stores Input
	bool bRotateHold = true; // one Z key hold = one rotation, no more, no less

	bool is_game_over = false;

	int tetris_block_texture_1;
	int tetris_block_texture_2;
	int tetris_block_texture_3;
	int tetris_block_texture_4;
	int tetris_block_texture_5;
	int tetris_block_texture_6;
	int tekstura2;
	int border_texture_vertical;
	int border_texture_horizontal;
	int grid_element_texture;
	int background_texture;
	int boom_texture;
	
	//For settings

	int startingticksToForceDown = 20;
	int speedLimit = 2;

	// Functions
private:
	int GetBlockTexture(int n);
	int Rotate(int px, int py, int r);
	bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY, std::vector<int> &mygrid);
	
	void CalculatePlanScore(Plan &plan, std::vector<int> plan_grid); //Notice
public:

private:
	bool buvo = false;
	int Score;//Score objekto staciakampio seklys
	int RobotoTeksturos[3];
	int tekstura3;
	int tekstura4;
	int tekstura5;
	int tekstura6;
	int tekstura7;
	int tekstura8;
	int tekstura9;
	int tekstura9p; //Tekstura, kuri atsiranda prieðais visas kitas
	int tekstura10;
	int tekstura11;
	int tekstura12;
	int tekstura13;
	int tekstura14;
	int Robotas;
	int oldTime; //Saugo laika, kai paskutini karta buvo paleista DeltaTime funkcija
	int Off; //Nuoroda i off staciakampi
	int GridSizeLentele; //Nuoruoda 5 grid lentele
	int Uzpildas; //Grid lenteles pazymetu daliu uzpildas
	int highscore;//Kintamasis saugantis highscore reikme
	int mygtukas;//Kintamasis, sekantis menu mygtuko pozicija
	int SkaiciuTeksturos[10];//Skaiciu nuo 0 iki 9 teksturu numeriu saugojimo masyvas
	int GameOverLenta;//Lenta, pranesanti apie zaidimo pabaiga 
	int IsejimoLenta = NULL;//Lenta iseiti is zaidimo
	int Remelis; //remelis mygtuko pazymejimui
	int Fonas; //Fonine tekstura
	int TutorialLentele; //Totorial lentele
	int volume = 50; //Dabartinis garsas
	Soundtrack Muzika; //Muzikos grotuvas
	int Slankjuoste;//Slanjuostes zymeklis
	int Slankjuoste2;//Slanjuostes zymeklis
	int Slankjuoste3;//Slanjuostes zymeklis
	bool MusicOn = true; //Laiko bûsenà ar muzika ájungta ar iðjungta
	bool MaximiseOnStart; //Ar iðdidinti ekranà paleidþiant
	bool YraKairej = true;
	bool IseitiLentele = false;
	bool GridLentele = false;
	bool SceneInitialized = false;
	bool buttonBlocked = false;
	bool TutorialEnabled;
	bool Tutorial_Exited = false;
	enum Scenos //Scenu enumeratorius
	{
		Menu, Game, Settings, AudioSettings, GameplaySettings
	};
	Scenos Scena = Menu; //Dabartine scena
	std::vector<int> skaiciai;
	std::vector<int> skaiciai2;

private:
	void DisplayScore(int score);
	void GameOver(int score);
	void UnloadScene();
	void DisplayNumber(float x, float y, float font, int number, std::vector<int> &skaiciumasyvas);
	void UndisplayNumber(std::vector<int> &skaiciumasyvas);
	bool DeltaTime(int goal);
	//Þemiau neik. Jei ko reikia, daryk virð
private:
	std::vector<_Square> Objektai;
	Shader shaderis;
	Renderer rendereris;
	std::vector<int> TexSeklys;
	std::vector<Texture> teksturos;
	int visoSquares = -1;
public:
	TetrisGame(Shader &shader, Renderer &renderer);

	void GameLoop(int Inputs[], GLFWwindow* window);
private:
	void Draw();
	int Square(float x, float y, float width, float length, int Tekstura);
	void SquareRemove(int square);
	void Move(int square, float x, float y);
	void MoveA(int square, float x, float y);
	int AddTexture(std::string path);
	void TextureRemove(int &texture);
};
