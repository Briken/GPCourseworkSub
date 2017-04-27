#include "GameApplication.h"
#include "Camera.h"
#include <iostream>
#include <string>
//#include <glm/ext.hpp>



Vertex m_Vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
					Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
					Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

unsigned int indices[] = { 0, 1, 2 };

Transform transform;
Transform transform1;

GameApplication::GameApplication()
{
	m_CurrentState = GameState::PLAY;
	Screen* m_GameScreen = new Screen(); //new Screen
	Light* m_Light();
    Model* model1 = new Model();
	Model* model2 = new Model();
}

GameApplication::~GameApplication()
{
}

void GameApplication::run()
{
	InitializeSystems(); 
	MainGameLoop();
}

void GameApplication::InitializeSystems()
{
		
	m_Light.initLight(glm::vec3(0.1f, 0.0f, 0.0f), glm::vec4(0.1f, 0.0f, 0.0f, 1.0f), glm::vec4(0.1f, 0.0f, 0.0f, 1.0f), glm::vec4(0.1f, 0.0f, 0.0f, 1.0f));
	m_GameScreen.InitializeScreen(); 
	//model1.init(m_Vertices, sizeof(m_Vertices) / sizeof(m_Vertices[0]), indices, sizeof(indices) / sizeof(indices[0])); //size calcuated by number of bytes of an array / no bytes of one element
	model1.LoadModel("../res/monkey3.obj");
	model2.LoadModel("../res/monkey3.obj");
	m_GameCamera.InitializeCamera(glm::vec3(0, 0, -5), 70.0f, (float)m_GameScreen.GetWidth()/m_GameScreen.GetHeight(), 0.01f, 1000.0f);
	counter = 0.0f;
}

void GameApplication::MainGameLoop()
{
	while (m_CurrentState != GameState::EXIT)
	{
		ManageInput();
		RenderScene();
	}
}

void GameApplication::ManageInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDLK_RIGHT:
				m_GameCamera.MoveRight(50000);
				break;

			case SDL_QUIT:
				m_CurrentState = GameState::EXIT;
				break;
		}
	}
	
}


void GameApplication::RenderScene()
{
	m_GameScreen.ClearScreen(0.0f, 0.0f, 0.0f, 1.0f);
	
	Shader shader("../res/shader"); //new shader
	Shader shader1("../res/shader");
	Texture texture("../res/bricks.jpg"); //load texture
	Texture texture1("../res/water.jpg"); //load texture
	
	transform.SetPos(glm::vec3(sinf(counter), 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));

	transform1.SetPos(glm::vec3(sinf(counter), 0.0, 0.0));
	transform1.SetRot(glm::vec3(0.0, 0.0, counter * 2));
	transform1.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));

	shader.BindShader();
	shader.Update(transform, m_GameCamera);
	
	texture.BindTexture(0);
	model1.DrawMesh();
	
	shader1.BindShader();
	shader1.Update(transform1, m_GameCamera);

	texture1.BindTexture(0);
	model2.DrawMesh();

	counter = counter + 0.01f;
				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	m_GameScreen.SwapBuffer();
} 