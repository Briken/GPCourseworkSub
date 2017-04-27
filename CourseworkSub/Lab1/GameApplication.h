#pragma once

#include <string>
#include <ostream>
#include <glm\glm.hpp>
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <Windows.h>
#include "Screen.h" 
#include "Shader.h"
#include "Light.h"
#include "Model.h"
#include "Texture.h"
#include "Transform.h"

enum class GameState{PLAY, EXIT};

class GameApplication
{
public:
	GameApplication();
	~GameApplication();

	void run();

private:

	void InitializeSystems();
	void ManageInput();
	void MainGameLoop();
	void RenderScene();

	Screen m_GameScreen;
	Light m_Light;
	GameState m_CurrentState;
	Model model1;
	Model model2;
	Camera m_GameCamera;

	float counter;

	char cCurrPath[FILENAME_MAX];

	std::string getDir()
	{
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		/*DWORD i = GetCurrentDirectory(0, NULL);
		std::string dir = std::to_string(i);*/
		std::string dir = std::string (buffer).substr(0, pos);


		return dir;
	}
	
	
};

