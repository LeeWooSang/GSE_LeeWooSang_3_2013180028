#include "stdafx.h"
#include "Object.h"
#include <Windows.h>
#include "SceneMgr.h"
#include <math.h>

Object::Object(float x, float y, int type , int teamType) :
	m_x(x),
	m_y(y),
	m_z(0),
	m_size(30),
	m_isColision(false),
	m_type(type),
	m_parentID(-1),
	m_lastBullet(0.f),
	m_lastArrow(0.f),
	m_teamType(teamType)
{
	if (type == OBJECT_BUILDING)
	{
		m_color[0] = 1;
		m_color[1] = 1;
		m_color[2] = 0;
		m_color[3] = 1;

		m_moveDir[0] = 0;
		m_moveDir[1] = 0;

		m_speed = 0.f;

		m_size = 100;
		m_life = 500;

		m_lifeTime = 100000.f;
	}
	else if (type == OBJECT_CHARACTER)
	{
		if (teamType == RED_TEAM)
		{
			m_color[0] = 1;
			m_color[1] = 0;
			m_color[2] = 0;
			m_color[3] = 1;
		}
		else if (teamType == BLUE_TEAM)
		{
			m_color[0] = 0;
			m_color[1] = 0;
			m_color[2] = 1;
			m_color[3] = 1;
		}
		m_moveDir[0] = (((float)std::rand() / (float)RAND_MAX - 0.5f));
		m_moveDir[1] = (((float)std::rand() / (float)RAND_MAX - 0.5f));

		m_speed = 300.f;

		m_size = 10;
		m_life = 10;

		m_lifeTime = 100000.f;
	}
	else if (type == OBJECT_BULLET)
	{
		if (teamType == RED_TEAM)
		{
			m_color[0] = 1;
			m_color[1] = 0;
			m_color[2] = 0;
			m_color[3] = 1;
		}
		else if (teamType == BLUE_TEAM)
		{
			m_color[0] = 0;
			m_color[1] = 0;
			m_color[2] = 1;
			m_color[3] = 1;
		}
		m_moveDir[0] = (((float)std::rand() / (float)RAND_MAX - 0.5f));
		m_moveDir[1] = (((float)std::rand() / (float)RAND_MAX - 0.5f));

		m_speed = 600.f;

		m_size = 4;
		m_life = 20;

		m_lifeTime = 100000.f;
	}
	else if (type == OBJECT_ARROW)
	{
		if (teamType == RED_TEAM)
		{
			m_color[0] = 0.5;
			m_color[1] = 0.2;
			m_color[2] = 0.7;
			m_color[3] = 1;
		}
		else if (teamType == BLUE_TEAM)
		{
			m_color[0] = 1;
			m_color[1] = 1;
			m_color[2] = 0;
			m_color[3] = 1;
		}

		m_moveDir[0] = (((float)std::rand() / (float)RAND_MAX - 0.5f));
		m_moveDir[1] = (((float)std::rand() / (float)RAND_MAX - 0.5f));

		m_speed = 100.f;

		m_size = 4;
		m_life = 20;

		m_lifeTime = 100000.f;
	}

	else
	{
		std::cout << "Wrong Object Type" << type << "\n";
	}
}


Object::~Object()
{
}


void Object::Update(float elapsedTime)
{

	float elapsedTimeInSecond = elapsedTime * 0.001f ;
	
	m_lastBullet += elapsedTimeInSecond;
	m_lastArrow += elapsedTimeInSecond;

	// 현재위치 = 이전위치 + 속도 * 시간
		m_x = m_x + m_speed * m_moveDir[0] * elapsedTimeInSecond;
		m_y = m_y + m_speed * m_moveDir[1] * elapsedTimeInSecond;
	

	if (m_x > 250)
	{
		m_x = 250;
		m_moveDir[0] = -m_moveDir[0];

		if (m_type == OBJECT_BULLET)
			m_life = 0.f;
	}

	if (m_x < -250)
	{
		m_x = -250;
		m_moveDir[0] = -m_moveDir[0];

		if (m_type == OBJECT_BULLET)
			m_life = 0.f;			
	}

	if (m_y > 400)
	{
		m_y = 400;
		m_moveDir[1] = -m_moveDir[1];

		if (m_type == OBJECT_BULLET)
			m_life = 0.f;
	}

	if (m_y < -400)
	{
		m_y = -400;
		m_moveDir[1] = -m_moveDir[1];

		if (m_type == OBJECT_BULLET)
			m_life = 0.f;
	}
}
