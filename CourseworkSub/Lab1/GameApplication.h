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
	void SwitchControlMode();
	void QuitGame();


	Screen m_GameScreen;
	Light m_Light;
	GameState m_CurrentState;
	Model model;
	Model model1;
	Model model2;
	Camera m_GameCamera;
	bool controllingModel;
	float counter;

	
	
	
};

