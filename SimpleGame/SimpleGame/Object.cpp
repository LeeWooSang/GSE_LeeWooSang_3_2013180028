#include "stdafx.h"
#include "Object.h"

Object::Object(float x, float y)
{
	m_fx = x;
	m_fy = y;
	m_fz = 0.0;
	m_fsize = 25.0;
	m_color_r = 1.0;
	m_color_g = 0.0;
	m_color_b = 0.0;
	m_color_a = 1.0;

	m_vector_fx = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
	m_vector_fy = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);

	m_fSpeed = 0.005;
	m_fLife = 10000.f;
	m_fLifeTime = 100000.f;
}

Object::~Object(void)
{
}

void Object::Update(float elapsedTime)
{
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	m_fx = m_fx+ m_fSpeed * elapsedTime * m_vector_fx;
	m_fy = m_fy + m_fSpeed * elapsedTime * m_vector_fy;
	//m_fx = m_fx + m_fSpeed * elapsedTimeInSecond * m_vector_fx;
	//m_fy = m_fy + m_fSpeed * elapsedTimeInSecond * m_vector_fy;

	//cout << elapsedTimeInSecond << endl;

	if (m_fx > 250)
	{
		m_fx = 250;
		m_vector_fx = -m_vector_fx;
	}

	if (m_fx < -250)
	{
		m_fx = -250;
		m_vector_fx = -m_vector_fx;
	}

	if (m_fy > 250)
	{
		m_fy = 250;
		m_vector_fy = -m_vector_fy;
	}

	if (m_fy < -250)
	{
		m_fy = -250;
		m_vector_fy = -m_vector_fy;
	}

	if (m_fLife > 0.f)
	{
		//m_fLife -= 1;
	}

	if (m_fLifeTime > 0.f)
	{
		m_fLifeTime -= 1;
	}
}
