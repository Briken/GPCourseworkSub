#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Screen
{
public:
	Screen();
	~Screen();
	void InitializeScreen();
	void SwapBuffer();
	void ClearScreen(float r, float g, float b, float a);
	void EnableLighting();
	float GetWidth();
	float GetHeight();

private:

	void ReturnError(std::string errorString);
	
	

	SDL_GLContext m_GameContext; //global variable to hold the context
	SDL_Window* m_GameWindow; //holds pointer to out window
	float m_ScreenWidth;
	float m_ScreenHeight;
};

