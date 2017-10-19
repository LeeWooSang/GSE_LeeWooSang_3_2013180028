#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager(float x, float y, float z, float size, float R, float G, float B, float A)
{
	m_fx = x;
	m_fy = y;
	m_fz = z;
	m_fsize = size;
	m_color_r = R;
	m_color_g = G;
	m_color_b = B;
	m_color_a = A;

	m_fSpeed = 0.1;
	m_iTime = 1;
	m_iDir = 1;
}

SceneManager::~SceneManager(void)
{

}

bool SceneManager::Init(void)
{
	return true;
}

void SceneManager::Output(void)
{

}

void SceneManager::Update(void)
{
	m_fx = m_fx + m_fSpeed * m_iTime * m_iDir;

	//cout << m_fx << endl;
	if (m_fx > 250)
	{
		m_fx = 250;
		m_iDir = -1;
	}

	if (m_fx < -250)
	{
		m_fx = -250;
		m_iDir = 1;
	}
}

void SceneManager::Collision(void)
{

}

void SceneManager::Release(void)
{

}
