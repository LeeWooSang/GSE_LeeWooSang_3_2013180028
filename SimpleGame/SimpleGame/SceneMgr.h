#pragma once
#include "Defines.h"
#include "Object.h"
#include "Renderer.h"

class SceneMgr
{

public:
	SceneMgr(int WindowWidth , int WindowHeight);
	~SceneMgr();

	int CreateObject(float x, float y, int objectType, int teamType);
	void DeleteObject(int index);

	void UpdateAllObject(float elpasedTime);
	void DrawAllObject();

	int GetObjectCnt() { return MAX_OBJECTS_COUNT; }
	 bool BoxColisionTest(Object* a, Object* b);
	 void DoColisionTest();

private:
	Object *m_objects[MAX_OBJECTS_COUNT];

	Renderer* m_Renderer;
	int prevTime;
	int currentTime;

	float enemyCooltime = 0.f;

	int objectType;

	GLuint m_REDTEAM_buildingTexture = 0;
	GLuint m_BLUETEAM_buildingTexture = 0;
};

