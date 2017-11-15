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
	m_texureID = 0;

	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
		m_pArrow[i] = NULL;

}

Object::~Object(void)
{
	for (int i = 0; i < m_iplayer_count; ++i)
	{
		delete m_pArrow[i];
		m_pArrow[i] = NULL;
	}
}

void Object::Update(float elapsedTime)
{
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	m_fx = m_fx+ m_fSpeed * elapsedTime * m_vector_fx;
	m_fy = m_fy + m_fSpeed * elapsedTime * m_vector_fy;


	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
	{
		if (m_pArrow[i] == NULL)
		{
			if (Timer % 500 == 0)
			{
				m_pArrow[i] = new Object(m_fx, m_fy);
				m_pArrow[i]->m_fz = 0.0;
				m_pArrow[i]->m_fsize = 10.0;
				m_pArrow[i]->m_color_r = 1.0;
				m_pArrow[i]->m_color_g = 0.0;
				m_pArrow[i]->m_color_b = 0.0;
				m_pArrow[i]->m_color_a = 1.0;
				m_pArrow[i]->m_fLife = 100;
				m_pArrow[i]->m_vector_fx = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
				m_pArrow[i]->m_vector_fy = 200.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
			}
		}

		if (m_pArrow[i] != NULL)
		{
			m_pArrow[i]->m_fx = m_pArrow[i]->m_fx + m_fSpeed * elapsedTime * m_pArrow[i]->m_vector_fx;
			m_pArrow[i]->m_fy = m_pArrow[i]->m_fy + m_fSpeed * elapsedTime * m_pArrow[i]->m_vector_fy;

			if (m_pArrow[i]->m_fx > 250)
			{
				m_pArrow[i]->m_fx = 250;
				m_pArrow[i]->m_vector_fx = -m_pArrow[i]->m_vector_fx;
			}

			if (m_pArrow[i]->m_fx < -250)
			{
				m_pArrow[i]->m_fx = -250;
				m_pArrow[i]->m_vector_fx = -m_pArrow[i]->m_vector_fx;
			}

			if (m_pArrow[i]->m_fy > 250)
			{
				m_pArrow[i]->m_fy = 250;
				m_pArrow[i]->m_vector_fy = -m_pArrow[i]->m_vector_fy;
			}

			if (m_pArrow[i]->m_fy < -250)
			{
				m_pArrow[i]->m_fy = -250;
				m_pArrow[i]->m_vector_fy = -m_pArrow[i]->m_vector_fy;
			}

			if (m_pArrow[i]->m_fLife > 0.f)
			{
				//m_fLife -= 1;
			}
		}
	}

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
