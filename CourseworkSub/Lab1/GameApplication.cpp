#include "GameApplication.h"
#include "Camera.h"
#include <iostream>
#include <string>
//#include <glm/ext.hpp>

unsigned int indices[] = { 0, 1, 2 };

Transform transform;
Transform transform1;
Transform transform2;

GameApplication::GameApplication()
{
	m_CurrentState = GameState::PLAY;
	
	Screen* m_GameScreen = new Screen(); //new Screen
	Light* m_Light();
    Model* model = new Model();
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
	model.LoadModel("../res/box4obj.obj");
	model1.LoadModel("../res/monkey3.obj");
	model2.LoadModel("../res/box5obj.obj");
	m_GameCamera.InitializeCamera(glm::vec3(0, 3, -15), 70.0f, (float)m_GameScreen.GetWidth()/m_GameScreen.GetHeight(), 0.01f, 1000.0f);
	controllingModel = false;
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

	while (SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			QuitGame();
			break;
		case SDL_KEYDOWN:
			switch (evnt.key.keysym.sym)
			{
			case SDLK_RIGHT:
				if (controllingModel == false)
				{
					m_GameCamera.MoveLeftRight(-0.5);
				}
				else
				{
					transform1.SetPos(glm::vec3(transform1.GetPosition()->x - 0.5f, transform1.GetPosition()->y, transform1.GetPosition()->z));
				}
				break;
			case SDLK_LEFT:
				if (controllingModel == false)
				{
					m_GameCamera.MoveLeftRight(0.5);
				}
				else
				{
					transform1.SetPos(glm::vec3(transform1.GetPosition()->x + 0.5f, transform1.GetPosition()->y, transform1.GetPosition()->z));
				}
				break;
			case SDLK_UP:
				if (controllingModel == false)
				{
					m_GameCamera.MoveForwardBack(0.5);
				}
				else
				{
					transform1.SetPos(glm::vec3(transform1.GetPosition()->x, transform1.GetPosition()->y, transform1.GetPosition()->z + 0.5f));
				}
				break;
			case SDLK_DOWN:
				if (controllingModel == false)
				{
					m_GameCamera.MoveForwardBack (-0.5);
				}
				else
				{
					transform1.SetPos(glm::vec3(transform1.GetPosition()->x, transform1.GetPosition()->y, transform1.GetPosition()->z - 0.5f));
				}
				break;
			case SDLK_w:
				if (controllingModel == false)
				{
					m_GameCamera.Pitch(-0.25f);
				}
				else
				{
					transform1.SetRot(glm::vec3(transform1.GetRot()->x + 0.5, transform1.GetRot()->y, transform1.GetRot()->z));
				}
				break;
			case SDLK_s:
				if (controllingModel == false)
				{
					m_GameCamera.Pitch(0.25f);
				}
				else
				{
					transform1.SetRot(glm::vec3(transform1.GetRot()->x - 0.5, transform1.GetRot()->y, transform1.GetRot()->z));
				}
				break;
			case SDLK_d:
				if (controllingModel == false)
				{
					m_GameCamera.RotateY(-0.25);
				}
				else
				{
					transform1.SetRot(glm::vec3(transform1.GetRot()->x, transform1.GetRot()->y - 0.5, transform1.GetRot()->z));
				}
				break;
			case SDLK_a:
				if (controllingModel == false)
				{
					m_GameCamera.RotateY(0.25);
				}
				else
				{
					transform1.SetRot(glm::vec3(transform1.GetRot()->x, transform1.GetRot()->y + 0.5, transform1.GetRot()->z));
				}
				break;
			case SDLK_SPACE:
				SwitchControlMode();
				break;
			case SDLK_ESCAPE:
				QuitGame();
				break;
			}
			break;
		}
	}

}


void GameApplication::RenderScene()
{
	m_GameScreen.ClearScreen(1.0f, 1.0f, 1.0f, 1.0f);
	
	Shader shader("../res/shader"); //new shader
	Shader shader1("../res/shader");
	Shader shader2("../res/shader");
	Texture texture("../res/bure4.png"); //load texture
	Texture texture1("../res/water.jpg"); //load texture
	Texture texture2("../res/bure5.png");


	transform.SetPos(glm::vec3/*(sinf(counter), 0.0, 0.0));*/ (10.0, 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, counter*5, 0.0f));
	//transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));
	transform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	//transform1.SetPos(glm::vec3(0, 0, 0));//glm::vec3(10.00, 0.0, 0.0));
	//transform1.SetRot(glm::vec3(0.0, 180.0, 0.0));//counter * 2));
	//transform1.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));
	transform1.SetScale(glm::vec3(3.0f, 3.0f, 3.0f));

	transform2.SetPos(glm::vec3(-10, 0, 0));//glm::vec3(sinf(counter), 0.0, 0.0));
	transform2.SetRot(glm::vec3(0.0, counter * -5, 0.0));
	transform2.SetScale(glm::vec3(1.0f,1.0f,1.0f));//(sinf(counter), sinf(counter), sinf(counter)));

	shader.BindShader();
	shader.Update(transform, m_GameCamera);
	texture.BindTexture(0);
	model.DrawMesh();
	
	shader1.BindShader();
	shader1.Update(transform1, m_GameCamera);
	texture1.BindTexture(0);
	model1.DrawMesh();

	shader2.BindShader();
	shader2.Update(transform2, m_GameCamera);
	texture2.BindTexture(0);
	model2.DrawMesh();

	counter = counter + 0.01f;
				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	m_GameScreen.SwapBuffer();
}

void GameApplication::SwitchControlMode()
{
	controllingModel = !controllingModel;
}

void GameApplication::QuitGame()
{
	m_CurrentState = GameState::EXIT;
}
