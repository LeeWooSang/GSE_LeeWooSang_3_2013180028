#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager(int width, int height)
{
	m_windowWidth = width;
	m_windowHeight = height;

	m_pRenderer = new Renderer(m_windowWidth, m_windowHeight);

	if (!m_pRenderer->IsInitialized())
	{
		std::cout << "SceneMgr::Renderer could not be initialized.. \n";
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_pPlayer[i] = NULL;
		m_pBullet[i] = NULL;
	}
}

SceneManager::~SceneManager(void)
{
}

void SceneManager::Init(int x, int y)
{
	for (int i = 0; i < m_iobject_count; i++)
	{
		if (m_pPlayer[i] == NULL)
			m_pPlayer[i] = new Object(x, y);
	}
}

void SceneManager::Draw(void)
{
	for (int i = 0; i < m_iobject_count; i++)
	{
		if (m_pPlayer[i] != NULL)
		{
			m_pRenderer->DrawSolidRect(
				m_pPlayer[i]->Set_X(),
				m_pPlayer[i]->Set_Y(),
				m_pPlayer[i]->Set_Z(),
				m_pPlayer[i]->Set_Size(),
				m_pPlayer[i]->Set_Color_R(),
				m_pPlayer[i]->Set_Color_G(),
				m_pPlayer[i]->Set_Color_B(),
				m_pPlayer[i]->Set_Color_A() );
		}
	}
}

void SceneManager::Collision(void)
{
	int icollision_count = 0;

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		icollision_count = 0;

		if (m_pPlayer[i] != NULL)
		{
			for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
			{
				if (i == j)
					continue;

				if (m_pPlayer[j] != NULL)
				{
					float minX1, minY1;
					float maxX1, maxY1;

					float minX2, minY2;
					float maxX2, maxY2;

					minX1 = m_pPlayer[i]->Set_X() - m_pPlayer[i]->Set_Size() / 2.f;
					minY1 = m_pPlayer[i]->Set_Y() - m_pPlayer[i]->Set_Size() / 2.f;
					maxX1 = m_pPlayer[i]->Set_X() + m_pPlayer[i]->Set_Size() / 2.f;
					maxY1 = m_pPlayer[i]->Set_Y() + m_pPlayer[i]->Set_Size() / 2.f;

					minX2 = m_pPlayer[j]->Set_X() - m_pPlayer[j]->Set_Size() / 2.f;
					minY2= m_pPlayer[j]->Set_Y() - m_pPlayer[j]->Set_Size() / 2.f;
					maxX2 = m_pPlayer[j]->Set_X() + m_pPlayer[j]->Set_Size() / 2.f;
					maxY2 = m_pPlayer[j]->Set_Y() + m_pPlayer[j]->Set_Size() / 2.f;

					if (Box_Collision(minX1, minY1, maxX1, maxY1, minX2, minY2, maxX2, maxY2))
						++icollision_count;
				}
			}
			if (icollision_count > 0)
			{
				m_pPlayer[i]->Get_Color_R(1.0),
				m_pPlayer[i]->Get_Color_G(0.0),
				m_pPlayer[i]->Get_Color_B(0.0),
				m_pPlayer[i]->Get_Color_A(1.0),

				m_pPlayer[i]->Set_Color_R(),
				m_pPlayer[i]->Set_Color_G(),
				m_pPlayer[i]->Set_Color_B(),
				m_pPlayer[i]->Set_Color_A();
			}

			else
			{
				m_pPlayer[i]->Get_Color_R(1.0),
				m_pPlayer[i]->Get_Color_G(1.0),
				m_pPlayer[i]->Get_Color_B(1.0),
				m_pPlayer[i]->Get_Color_A(1.0),

				m_pPlayer[i]->Set_Color_R(),
				m_pPlayer[i]->Set_Color_G(),
				m_pPlayer[i]->Set_Color_B(),
				m_pPlayer[i]->Set_Color_A();
			}
		}
	}
}

bool SceneManager::Box_Collision(float minX1, float minY1, float maxX1, float maxY1, float minX2, float minY2, float maxX2, float maxY2)
{
	if (minX1 > maxX2)
		return false;

	if (maxX1 < minX2)
		return false;

	if (minY1 > maxY2)
		return false;

	if (maxY1 < minY2)
		return false;

	return true;
}

void SceneManager::Update(float elapsedTime)
{
	SceneManager::Collision();

	for (int i = 0; i < m_iobject_count; i++)
	{
		if (m_pPlayer[i] != NULL)
		{
			if (m_pPlayer[i]->Set_Life() < 0.0001f || m_pPlayer[i]->Set_LifeTime() < 0.0001f)
			{
				//kill object
				Release(i);
			}
			else
			{
				m_pPlayer[i]->Update(elapsedTime);
			}
		}
		//if (m_pBullet[i] != NULL)
		//{
		//	m_pBullet[i]->Update(elapsedTime);
		//}
	}
}

void SceneManager::Release(int index)
{
	if (m_pPlayer[index] != NULL)
	{
		delete m_pPlayer[index];
		m_pPlayer[index] = NULL;
	}
}
