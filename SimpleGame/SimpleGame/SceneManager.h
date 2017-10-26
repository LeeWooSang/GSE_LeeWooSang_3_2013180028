#pragma once
#include "Object.h"
#include "Renderer.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

#define BULLET_OBJECTS_COUNT 50
#define PLAYER_OBJECTS_COUNT 10

class SceneManager
{
public:
	explicit SceneManager(int m_windowWidth, int m_windowHeight);
	virtual ~SceneManager(void);

public:
	void Draw_Player(void);
	void Draw_Bullet(void);
	void Update(void);
	void Collision(void);

public:
	void Get_Object_Count(int icount)		{ m_object_count = icount; }
	int Set_Object_Count(void)					{ return m_object_count; }


public:
	Object* m_pPlayer[PLAYER_OBJECTS_COUNT];
	Object* m_pBullet[BULLET_OBJECTS_COUNT];


private:
	Renderer* m_pRenderer;

	int m_windowWidth;
	int m_windowHeight;

	int m_object_count;
};