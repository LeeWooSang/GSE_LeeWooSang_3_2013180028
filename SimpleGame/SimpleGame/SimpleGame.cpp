/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"
#include "Object.h"

using namespace std;

Renderer *g_Renderer = NULL;
Object* pObejct = new Object(0.0f, 0.0f, 0.0f, 50.0f, 1.0f, 0.0f, 0.0f, 1.0f);
bool ButtonDown = false;
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	//g_Renderer->DrawSolidRect(0, 0, 0, 4, 1, 0, 1, 1);
	pObejct->Update();

	g_Renderer->DrawSolidRect(pObejct->Set_X(), pObejct->Set_Y(), pObejct->Set_Z(), pObejct->Set_Size(),
		pObejct->Set_Color_R(), pObejct->Set_Color_G(), pObejct->Set_Color_B(), pObejct->Set_Color_A());
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{ 
		ButtonDown = true;
		pObejct->Get_X(x - 250.0);
		pObejct->Get_Y(250.0 - y);
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (ButtonDown)
			cout << "마우스 클릭 됨" << endl;
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
	g_Renderer = new Renderer(500, 500);

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	delete g_Renderer;
	delete pObejct;
	pObejct = NULL;

    return 0;
}

