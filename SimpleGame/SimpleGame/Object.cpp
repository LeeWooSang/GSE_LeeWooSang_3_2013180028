#include "stdafx.h"
#include "Object.h"
#include <Windows.h>
#include "SceneMgr.h"
#include <math.h>

CObject::CObject(float x, float y, int type , int teamType) :
	m_fx(x),
	m_fy(y),
	m_fz(0),
	m_fsize(30),
	m_isColision(false),
	m_type(type),
	m_parentID(-1),
	m_lastBullet(0.f),
	m_lastArrow(0.f),
	m_teamType(teamType),
	m_animation_sheet1(0),
	m_animation_sheet2(0)
{

	if (type == OBJECT_BUILDING)
	{
		m_color[0] = 1;
		m_color[1] = 1;
		m_color[2] = 0;
		m_color[3] = 1;

		m_vector[0] = 0;
		m_vector[1] = 0;

		m_fspeed = 0.f;
		m_flevel = 0.1f;

		m_fsize = 100;
		m_life = 500;

		m_lifeTime = 100000.f;

		m_fgauge_width = m_fsize;
		m_fgauge_height = m_fsize / 10.f;
		m_fgauge = 1.0;
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

		m_vector[0] = (((float)std::rand() / (float)RAND_MAX - 0.5f));
		m_vector[1] = (((float)std::rand() / (float)RAND_MAX - 0.5f));

		m_fspeed = 300.f;
		m_flevel = 0.2f;

		m_fsize = 35;
		m_life = 100;

		m_lifeTime = 100000.f;

		m_fgauge_width = m_fsize;
		m_fgauge_height = m_fsize / 10.f;
		m_fgauge = 1.0;
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
		m_vector[0] = (((float)std::rand() / (float)RAND_MAX - 0.5f));
		m_vector[1] = (((float)std::rand() / (float)RAND_MAX - 0.5f));

		m_fspeed = 600.f;
		m_flevel = 0.3f;

		m_fsize = 7;
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

		m_vector[0] = (((float)std::rand() / (float)RAND_MAX - 0.5f));
		m_vector[1] = (((float)std::rand() / (float)RAND_MAX - 0.5f));

		m_fspeed = 100.f;
		m_flevel = 0.3f;

		m_fsize = 5;
		m_life = 20;

		m_lifeTime = 100000.f;
	}

	else
	{
		std::cout << "Wrong Object Type" << type << "\n";
	}
}


CObject::~CObject()
{
}


void CObject::Update(float elapsedTime)
{

	float elapsedTimeInSecond = elapsedTime * 0.001f ;
	
	m_lastBullet += elapsedTimeInSecond;
	m_lastArrow += elapsedTimeInSecond;

	m_last_animation_sheet1 += elapsedTimeInSecond;
	m_last_animation_sheet2 += elapsedTimeInSecond;

	// 현재위치 = 이전위치 + 속도 * 시간
	m_fx = m_fx + m_fspeed * m_vector[0] * elapsedTimeInSecond;
	m_fy = m_fy + m_fspeed * m_vector[1] * elapsedTimeInSecond;
	

	if (m_fx > 250)
	{
		m_fx = 250;
		m_vector[0] = -m_vector[0];

		if (m_type == OBJECT_BULLET || m_type == OBJECT_ARROW)
			m_life = 0.f;
	}

	if (m_fx < -250)
	{
		m_fx = -250;
		m_vector[0] = -m_vector[0];

		if (m_type == OBJECT_BULLET || m_type == OBJECT_ARROW)
			m_life = 0.f;			
	}

	if (m_fy > 400)
	{
		m_fy = 400;
		m_vector[1] = -m_vector[1];

		if (m_type == OBJECT_BULLET || m_type == OBJECT_ARROW)
			m_life = 0.f;
	}

	if (m_fy < -400)
	{
		m_fy = -400;
		m_vector[1] = -m_vector[1];

		if (m_type == OBJECT_BULLET || m_type == OBJECT_ARROW)
			m_life = 0.f;
	}
}
