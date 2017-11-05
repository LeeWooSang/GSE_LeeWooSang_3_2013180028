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

	m_pBuilding = NULL;

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_pPlayer[i] = NULL;
		m_pBullet[i]  = NULL;
		m_pArrow[i] = NULL;
	}
}

SceneManager::~SceneManager(void)
{
	Release();
}

void SceneManager::Init(int x, int y)
{
	Init_Player(x, y);
	Init_Building();
}

void SceneManager::Draw(void)
{
	Draw_Building();
	Draw_Player();
}

void SceneManager::Init_Player(int x, int y)
{
	for (int i = 0; i < m_iobject_count; i++)
	{
		if (m_pPlayer[i] == NULL)
			m_pPlayer[i] = new Object(x, y);
	}
}

void SceneManager::Draw_Player(void)
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
				m_pPlayer[i]->Set_Color_A());
		}
	}
}

void SceneManager::Update_Player(void)
{

}

void SceneManager::Delete_Player(int index)
{
	if (m_pPlayer[index] != NULL)
	{
		delete m_pPlayer[index];
		m_pPlayer[index] = NULL;
		--m_iobject_count;
	}
}

void SceneManager::Init_Building(void)
{
	if (m_pBuilding == NULL)
	{
		m_pBuilding = new Object(0, 0);
		m_pBuilding->Get_Z(0.0);
		m_pBuilding->Get_Size(100.0);
		m_pBuilding->Get_Color_R(1.0);
		m_pBuilding->Get_Color_G(1.0);
		m_pBuilding->Get_Color_B(0.0);
		m_pBuilding->Get_Color_A(1.0);
		m_pBuilding->Get_Life(100000.0);
	}
}

void SceneManager::Draw_Building(void)
{
	if (m_pBuilding == NULL)
	{
		Init_Building();
	}

	else if(m_pBuilding != NULL)
	{
		m_pRenderer->DrawSolidRect(
			m_pBuilding->Set_X(),
			m_pBuilding->Set_Y(),
			m_pBuilding->Set_Z(),
			m_pBuilding->Set_Size(),
			m_pBuilding->Set_Color_R(),
			m_pBuilding->Set_Color_G(),
			m_pBuilding->Set_Color_B(),
			m_pBuilding->Set_Color_A());
	}
}

void SceneManager::Update_Building(void)
{

}

void SceneManager::Delete_Building(void)
{
	delete m_pBuilding;
	m_pBuilding = NULL;
}

void SceneManager::Collision(void)
{
	int icollision_count = 0;

	for (int i = 0; i < m_iobject_count; ++i)
	{
		icollision_count = 0;

		if (m_pPlayer[i] != NULL)
		{
			for (int j = 0; j < m_iobject_count; ++j)
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

					//minX2 = m_pPlayer[j]->Set_X() - m_pPlayer[j]->Set_Size() / 2.f;
					//minY2= m_pPlayer[j]->Set_Y() - m_pPlayer[j]->Set_Size() / 2.f;
					//maxX2 = m_pPlayer[j]->Set_X() + m_pPlayer[j]->Set_Size() / 2.f;
					//maxY2 = m_pPlayer[j]->Set_Y() + m_pPlayer[j]->Set_Size() / 2.f;

					minX2 = m_pBuilding->Set_X() - m_pBuilding->Set_Size() / 2.f;
					minY2 = m_pBuilding->Set_Y() - m_pBuilding->Set_Size() / 2.f;
					maxX2 = m_pBuilding->Set_X() + m_pBuilding->Set_Size() / 2.f;
					maxY2 = m_pBuilding->Set_Y() + m_pBuilding->Set_Size() / 2.f;

					if (Box_Collision(minX1, minY1, maxX1, maxY1, minX2, minY2, maxX2, maxY2))
						++icollision_count;
				}
			}
			
			// 충돌 했을 때
			if (icollision_count > 0)
			{
				m_pPlayer[i]->Get_Life(0.0);
				m_pPlayer[i]->Get_LifeTime(0.0);
				m_pPlayer[i]->Get_Color_R(1.0),
				m_pPlayer[i]->Get_Color_G(0.0),
				m_pPlayer[i]->Get_Color_B(0.0),
				m_pPlayer[i]->Get_Color_A(1.0);
				
				m_pBuilding->Get_Life(m_pBuilding->Set_Life() - 10000);
				cout << m_pBuilding->Set_Life() << endl;
			}

			else
			{
				m_pPlayer[i]->Get_Color_R(1.0),
				m_pPlayer[i]->Get_Color_G(1.0),
				m_pPlayer[i]->Get_Color_B(1.0),
				m_pPlayer[i]->Get_Color_A(1.0);
			}
		}
	}
}

bool SceneManager::Box_Collision(float minX1, float minY1, float maxX1, float maxY1, float minX2, float minY2, float maxX2, float maxY2)
{
	// 캐릭터가 빌딩보다 오른쪽에 있을 때
	if (minX1 > maxX2)
		return false;

	// 캐릭터가 빌딩보다 왼쪽에 있을 때
	if (maxX1 < minX2)
		return false;

	// 캐릭터가 빌딩보다 위쪽에 있을 때
	if (minY1 > maxY2)
		return false;

	// 캐릭터가 빌딩보다 아래쪽에 있을 때
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
				Delete_Player(i);
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

	if (m_pBuilding != NULL)
	{
		if (m_pBuilding->Set_Life() <= 0)
		{
			Delete_Building();
		}
	}
}

void SceneManager::Release(void)
{
	for (int i = 0; i < m_iobject_count; ++i)
	{
		delete m_pPlayer[i];
		m_pPlayer[i] = NULL;
	}

	delete m_pBuilding;
	m_pBuilding = NULL;
}
