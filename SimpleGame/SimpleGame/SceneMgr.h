#pragma once
#include "Defines.h"
#include "Object.h"
#include "Renderer.h"
#include "Sound.h"

class CSceneMgr
{
public:
	CSceneMgr(int WindowWidth , int WindowHeight);
	~CSceneMgr();

	int InitObject(float x, float y, int objectType, int teamType);
	void DeleteObject(int index);

	void UpdateAllObject(float elpasedTime);
	void DrawAllObject();

	int GetObjectCnt() { return MAX_OBJECTS_COUNT; }
	bool BoxColisionTest(CObject* a, CObject* b);
	void DoColisionTest();

private:
	Renderer* m_pRenderer;
	CObject* m_pObjects[MAX_OBJECTS_COUNT];
	Sound* m_pSound;

	int m_Background_BGM = 0;
	int m_BLUETEAM_CHARACTER_Init_BGM = 0;
	int m_BLUETEAM_CHARACTER_Attack_BGM = 0;

	DWORD prevTime;
	DWORD currentTime;

	float enemyCooltime = 0.f;

	float BLUETEAM_Cooltime = 0.f;

	float REDTEAM_Cooltime = 0.f;

	float Particle_Cooltime = 0.f;
	float Background_Particle_Cooltime = 0.f;

	int BLUETEAM_sheet1_1 = 0;
	int BLUETEAM_sheet1_2 = 0;

	int REDTEAM_sheet2_1 = 0;
	int REDTEAM_sheet2_2 = 0;
	
	int objectType;
	
	GLuint m_Background_Texture = 0;

	GLuint m_REDTEAM_KING_buildingTexture = 0;
	GLuint m_REDTEAM_PRIENCESS_buildingTexture = 0;
	GLuint m_REDTEAM_characterTexture = 0;

	GLuint m_BLUETEAM_KING_buildingTexture = 0;
	GLuint m_BLUETEAM_PRIENCESS_buildingTexture = 0;
	GLuint m_BLUETEAM_characterTexture = 0;

	GLuint m_particleTexture = 0;
	GLuint m_collison_particleTexture = 0;
	GLuint m_Background_particleTexture = 0;

};

