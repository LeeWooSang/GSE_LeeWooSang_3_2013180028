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
#define MAX_ARROWS_COUNT 5

#define MAX_BUILDINGS_COUNT 6

#define BLUE_TEAM 1
#define RED_TEAM	2

class SceneManager
{
public:
	SceneManager(int width, int height);
	~SceneManager(void);

public:
	void Init(int x, int y);
	void Draw(void);

	bool Box_Collision(float minX1, float minY1, float maxX1, float maxY1, float minX2, float minY2, float maxX2, float maxY2, float minX3, float minY3, float maxX3, float maxY3);
	bool Test_Box_Collision(float minX1, float minY1, float maxX1, float maxY1, float minX2, float minY2, float maxX2, float maxY2);
	void Collision(void);

	void Update(float elapsedTime);
	// �޸� ����
	void Release(void);

public:
	void Get_Player_Count(int ButtonCount)		
	{
		m_iobject_count = ButtonCount; 

		for (int i = 0; i < m_iobject_count; ++i)
		{
			if (m_pPlayer[i] != NULL)
				m_pPlayer[i]->Get_Player_Count(m_iobject_count);
		}
	}
	int		Set_Player_Count(void)							{ return m_iobject_count; }

	void Get_Bullet_Count(void)							{ if(m_ibullet_count < MAX_BULLETS_COUNT) ++m_ibullet_count; }
	int		Set_Bullet_Count(void)							{ return m_ibullet_count; }


	void Get_Index_Count(int ButtonCount)		{ m_index = ButtonCount - 1; }

public:
	void Init_Player(int x, int y);
	void Draw_Player(void);
	void Update_Player(float elapsedTime);
	void Delete_Player(int index);

	void Init_Arrow(void);
	void Draw_Arrow(void);
	void Update_Arrow(float elapsedTime);
	void Delete_Arrow(int index);

	void Init_Building(void);
	void Draw_Building(void);
	void Update_Building(void);
	void Delete_Building(int index);

	void Init_Bullet(void);
	void Draw_Bullet(void);
	void Update_Bullet(float elapsedTime);
	void Delete_Bullet(int index);

private:
	Renderer* m_pRenderer;
	// ĳ����
	Object* m_pPlayer[MAX_OBJECTS_COUNT];
	// ĳ���Ͱ� �߻��ϴ� ȭ��
	Object* m_pArrow[MAX_OBJECTS_COUNT];
	// �ǹ�
	Object* m_pBuilding;
	// �ǹ����� ��� �Ѿ�
	Object* m_pBullet[MAX_OBJECTS_COUNT];

	Object* m_pBuildings[MAX_BUILDINGS_COUNT];

	int m_windowWidth;
	int m_windowHeight;

	int m_iobject_count;
	int m_ibullet_count;

	int m_index;

	bool m_bBuilding_Status = false;
};