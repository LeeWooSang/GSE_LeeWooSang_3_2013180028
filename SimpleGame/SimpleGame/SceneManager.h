#pragma once
#include "Object.h"
#include "Renderer.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

#define MAX_OBJECTS_COUNT 10

class SceneManager
{
public:
	SceneManager(int width, int height);
	~SceneManager(void);

public:
	void Init(int x, int y);
	void Draw(void);

	bool Box_Collision(float minX1, float minY1, float maxX1, float maxY1, float minX2, float minY2, float maxX2, float maxY2);
	void Collision(void);

	void Update(float elapsedTime);
	// 종료시 객체 삭제
	void Release(void);

public:
	void Get_Object_Count(int ButtonCount)		{ m_iobject_count = ButtonCount; }
	int		Set_Object_Count(void)						{ return m_iobject_count; }

	void Get_Index_Count(int ButtonCount)		{ m_index = ButtonCount - 1; }

public:
	void Init_Player(int x, int y);
	void Init_Building(void);

	void Draw_Player(void);
	void Draw_Building(void);

	void Update_Player(void);
	void Update_Building(void);

	void Delete_Player(int index);
	void Delete_Building(void);

private:
	Renderer* m_pRenderer;
	// 캐릭터
	Object* m_pPlayer[MAX_OBJECTS_COUNT];
	// 건물
	Object* m_pBuilding;
	Object* m_pBullet[MAX_OBJECTS_COUNT];
	Object* m_pArrow[MAX_OBJECTS_COUNT];

	int m_windowWidth;
	int m_windowHeight;
	int m_iobject_count;
	int m_index;

	bool m_bBuilding_Status = false;
};