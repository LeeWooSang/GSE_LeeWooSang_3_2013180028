/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include "Defines.h"

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "SceneMgr.h"


SceneMgr *g_SceneMgr = NULL;

DWORD g_prevTime = 0;

bool g_LButtonDown = false;
float g_mouseCooltime = 0.f;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_prevTime;
	g_prevTime = currTime;
	g_mouseCooltime += elapsedTime * 0.001f;
	//std::cout << " 마우스 쿨타임 : " << g_mouseCooltime << std::endl;

	g_SceneMgr->UpdateAllObject(float(elapsedTime));
	g_SceneMgr -> DrawAllObject();

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		g_LButtonDown = true;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (g_LButtonDown) {
			if (g_mouseCooltime >= 7.f && (Window_Half_HEIGHT)-y < 0.f)
			{
				g_SceneMgr->CreateObject(x - (Window_Half_WIDTH), (Window_Half_HEIGHT)-y, OBJECT_CHARACTER, BLUE_TEAM);
				g_mouseCooltime = 0.f;
			}
		}
		g_LButtonDown = false;
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
	glutInitWindowSize(WIDTH, HEIGHT);
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


	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	//Initialize Renderer

   g_SceneMgr = new SceneMgr(WIDTH, HEIGHT);

   g_SceneMgr->CreateObject(0, 300, OBJECT_BUILDING, RED_TEAM);
   g_SceneMgr->CreateObject(-150, 300, OBJECT_BUILDING, RED_TEAM);
   g_SceneMgr->CreateObject(150, 300, OBJECT_BUILDING, RED_TEAM);

   g_SceneMgr->CreateObject(0, -300, OBJECT_BUILDING, BLUE_TEAM);
   g_SceneMgr->CreateObject(-150, -300, OBJECT_BUILDING, BLUE_TEAM);
   g_SceneMgr->CreateObject(150, -300, OBJECT_BUILDING, BLUE_TEAM);

	g_prevTime = timeGetTime();

	glutMainLoop();

	delete g_SceneMgr;

    return 0;
}

