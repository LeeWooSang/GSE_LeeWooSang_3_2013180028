#include "stdafx.h"
#include "Defines.h"
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "SceneMgr.h"

SceneMgr *g_SceneMgr = NULL;

DWORD g_prevTime = 0;

bool ButtonDown = false;
float CoolTime = 0.f;
bool MouseCool = false;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	DWORD currTime = timeGetTime();
	DWORD elapsedTime = currTime - g_prevTime;
	g_prevTime = currTime;

	CoolTime -= elapsedTime * 0.001f;

	if (CoolTime <= 0.f)
	{
		CoolTime = 0;

		if (MouseCool == false)
		{
			cout << "\n캐릭터 생성 가능!!\n" << endl;
			MouseCool = true;
		}
	}
	else
	{
		 //소수 셋째 자리까지
		cout.precision(3);
		cout << " 마우스 쿨타임 : " << fixed << CoolTime << "초 남았습니다." << endl;
	}

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
		ButtonDown = true;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (ButtonDown)
		{
			if (CoolTime <= 0.f && (Window_Half_HEIGHT)-y < 0.f)
			{
				g_SceneMgr->InitObject(x - (Window_Half_WIDTH), (Window_Half_HEIGHT)-y, OBJECT_CHARACTER, BLUE_TEAM);
				// 마우스 쿨타임 3초
				CoolTime = 3.f;
				MouseCool = false;
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

   g_SceneMgr->InitObject(0, 300, OBJECT_BUILDING, RED_TEAM);
   g_SceneMgr->InitObject(-150, 300, OBJECT_BUILDING, RED_TEAM);
   g_SceneMgr->InitObject(150, 300, OBJECT_BUILDING, RED_TEAM);

   g_SceneMgr->InitObject(0, -300, OBJECT_BUILDING, BLUE_TEAM);
   g_SceneMgr->InitObject(-150, -300, OBJECT_BUILDING, BLUE_TEAM);
   g_SceneMgr->InitObject(150, -300, OBJECT_BUILDING, BLUE_TEAM);

	g_prevTime = timeGetTime();

	glutMainLoop();

	delete g_SceneMgr;

    return 0;
}

