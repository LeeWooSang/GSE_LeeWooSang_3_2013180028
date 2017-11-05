/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"
#include "SceneManager.h"

using namespace std;

//Object* pObject = new Object(0.0f, 0.0f, 0.0f, 25.0f, 1.0f, 0.0f, 0.0f, 1.0f);
SceneManager* pSceneManager = NULL;
DWORD g_prevTime = 0;
bool ButtonDown = false;
int ButtonCount = 0;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// 오브젝트 개수 감소에 따른 마우스 클릭 횟수 감소
	ButtonCount = pSceneManager->Set_Object_Count();

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		pSceneManager->Draw_Player();
	}

	pSceneManager->Draw_Building();


	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_prevTime;
	g_prevTime = currTime;

	pSceneManager->Update((float)elapsedTime);
	//pSceneManager->Draw();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		ButtonDown = true;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (ButtonDown)
		{
			if (ButtonCount <= MAX_OBJECTS_COUNT - 1)
			{
				++ButtonCount;
				pSceneManager->Get_Object_Count(ButtonCount);
				pSceneManager->Get_Index_Count(ButtonCount);
				pSceneManager->Init_Player(x - 250, -y + 250);

				cout << "\n마우스 클릭 됨\t" << "오브젝트 개수 : " << ButtonCount << endl;
			}
		}
		ButtonDown = false;
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	pSceneManager = new SceneManager(500, 500);

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);


	g_prevTime = timeGetTime();

	glutMainLoop();


	delete pSceneManager;
	pSceneManager = NULL;

    return 0;
}

