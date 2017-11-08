#pragma once
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Object.h"
#include "Renderer.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

#define MAX_OBJECTS_COUNT 10
#define MAX_BULLETS_COUNT 10

class SceneManager
{
public:
	SceneManager(int width, int height);
	~SceneManager(void);

public:
	void Init(int x, int y);
	void Draw(void);

	bool Box_Collision(float minX1, float minY1, float maxX1, float maxY1, float minX2, float minY2, float maxX2, float maxY2, float minX3, float minY3, float maxX3, float maxY3);
	void Collision(void);

	void Update(float elapsedTime);
	// 메모리 해제
	void Release(void);

public:
	void Get_Player_Count(int ButtonCount)		{ m_iobject_count = ButtonCount; }
	int		Set_Player_Count(void)							{ return m_iobject_count; }

	void Get_Bullet_Count(void)							{ if(m_ibullet_count < MAX_BULLETS_COUNT) ++m_ibullet_count; }

	int		Set_Bullet_Count(void)							{ return m_ibullet_count; }

	void Get_Index_Count(int ButtonCount)		{ m_index = ButtonCount - 1; }

public:
	void Init_Player(int x, int y);
	void Draw_Player(void);
	void Update_Player(float elapsedTime);
	void Delete_Player(int index);

	void Init_Building(void);
	void Draw_Building(void);
	void Update_Building(void);
	void Delete_Building(void);

	void Init_Bullet(void);
	void Draw_Bullet(void);
	void Update_Bullet(float elapsedTime);
	void Delete_Bullet(int index);

private:


	Renderer* m_pRenderer;
	// 캐릭터
	Object* m_pPlayer[MAX_OBJECTS_COUNT];
	// 건물
	Object* m_pBuilding;
	// 건물에서 쏘는 총알
	Object* m_pBullet[MAX_OBJECTS_COUNT];
	Object* m_pArrow[MAX_OBJECTS_COUNT];

	int m_windowWidth;
	int m_windowHeight;

	int m_iobject_count;
	int m_ibullet_count;

	int m_index;

	bool m_bBuilding_Status = false;
};