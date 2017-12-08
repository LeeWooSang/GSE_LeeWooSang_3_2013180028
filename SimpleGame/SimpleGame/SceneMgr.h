#pragma once
#include "Defines.h"
#include "Object.h"
#include "Renderer.h"
#include "Sound.h"

class SceneMgr
{

public:
	SceneMgr(int WindowWidth , int WindowHeight);
	~SceneMgr();

	int InitObject(float x, float y, int objectType, int teamType);
	void DeleteObject(int index);

	void UpdateAllObject(float elpasedTime);
	void DrawAllObject();

	int GetObjectCnt() { return MAX_OBJECTS_COUNT; }
	bool BoxColisionTest(Object* a, Object* b);
	void DoColisionTest();

private:
	Object* m_objects[MAX_OBJECTS_COUNT];
	Renderer* m_Renderer;
	Sound* m_sound;
	int soundBG;

	DWORD prevTime;
	DWORD currentTime;

	float enemyCooltime = 0.f;
	float BLUETEAM_Cooltime = 0.f;
	float REDTEAM_Cooltime = 0.f;

	float Particle_Cooltime = 0.f;

	int BLUETEAM_sheet1_1 = 0;
	int BLUETEAM_sheet1_2 = 0;

	int REDTEAM_sheet2_1 = 0;
	int REDTEAM_sheet2_2 = 0;
	
	int objectType;

	GLuint m_Background_Texture = 0;
	GLuint m_REDTEAM_buildingTexture = 0;
	GLuint m_REDTEAM_characterTexture = 0;
	GLuint m_BLUETEAM_buildingTexture = 0;
	GLuint m_BLUETEAM_characterTexture = 0;

	GLuint m_particleTexture = 0;
};

