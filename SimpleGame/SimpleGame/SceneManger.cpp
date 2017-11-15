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
		m_pArrow[i] = NULL;
	}

	for(int i = 0; i < MAX_BULLETS_COUNT; ++i)
		m_pBullet[i] = NULL;

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
	for (int i = 0; i < m_iobject_count; ++i)
	{
		if (m_pPlayer[i] == NULL)
		{
			m_pPlayer[i] = new Object(x, y);
		}
	}
}

void SceneManager::Draw_Player(void)
{
	for (int i = 0; i < m_iobject_count; ++i)
	{
		for(int j = 0; j < MAX_ARROWS_COUNT; ++j)
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

				if (m_pPlayer[i]->m_pArrow[j] != NULL)
				{
					m_pRenderer->DrawSolidRect(
						m_pPlayer[i]->m_pArrow[j]->Set_X(),
						m_pPlayer[i]->m_pArrow[j]->Set_Y(),
						m_pPlayer[i]->m_pArrow[j]->Set_Z(),
						m_pPlayer[i]->m_pArrow[j]->Set_Size(),
						m_pPlayer[i]->m_pArrow[j]->Set_Color_R(),
						m_pPlayer[i]->m_pArrow[j]->Set_Color_G(),
						m_pPlayer[i]->m_pArrow[j]->Set_Color_B(),
						m_pPlayer[i]->m_pArrow[j]->Set_Color_A()
					);
				}
			}
		}
	}
}

void SceneManager::Update_Player(float elapsedTime)
{
	SceneManager::Collision();

	for (int i = 0; i < m_iobject_count; ++i)
	{
		if (m_pPlayer[i] != NULL)
		{
			if (m_pPlayer[i]->Set_Life() < 0.0001f || m_pPlayer[i]->Set_LifeTime() < 0.0001f)
			{
				//kill object
				Delete_Player(i);
				cout << i << "번째 플레이어 삭제" << endl;
			}
			else
				m_pPlayer[i]->Update(elapsedTime);
		}
	}

	/*
	for (int i = 0; i < m_iobject_count; ++i)
	{
		for (int j = 0; j < MAX_ARROWS_COUNT; ++i)
		{
			if (m_pPlayer[i] != NULL && m_pPlayer[i]->m_pArrow[j] != NULL)
			{
				if (m_pPlayer[i]->m_pArrow[j]->Set_Life() <= 0)
				{
					Delete_Arrow(j);
					cout << i << "플레이어" << j << "번째 화살 삭제" << endl;
				}
			}
		}
	}
	*/
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

void SceneManager::Init_Arrow(void)
{
	/*
	for (int i = 0; i < m_iobject_count; ++i)
	{
		for (int j = 0; j < MAX_ARROWS_COUNT; ++j)
		{
			if ((m_pArrow[j] == NULL) && (m_pPlayer[i] != NULL))
			{
				m_pArrow[j] = new Object(m_pPlayer[i]->Set_X(), m_pPlayer[i]->Set_Y());
				m_pArrow[j]->Get_Size(10.0);
				m_pArrow[j]->Get_Color_R(1.0);
				m_pArrow[j]->Get_Color_G(0.0);
				m_pArrow[j]->Get_Color_B(0.0);
				m_pArrow[j]->Get_Color_A(1.0);
				m_pArrow[j]->Get_Life(10000);
				cout << i << "플레이어 화살 : " << j  << "개" << endl;
			}
		}
	}
	*/
}

void SceneManager::Draw_Arrow(void)
{
	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
	{
		if (m_pArrow[i] != NULL)
		{
			/*
			m_pRenderer->DrawSolidRect(
				m_pArrow[i]->Set_X(),
				m_pArrow[i]->Set_Y(),
				m_pArrow[i]->Set_Z(),
				m_pArrow[i]->Set_Size(),
				m_pArrow[i]->Set_Color_R(),
				m_pArrow[i]->Set_Color_G(),
				m_pArrow[i]->Set_Color_B(),
				m_pArrow[i]->Set_Color_A() );
				*/
		}
	}
}

void SceneManager::Update_Arrow(float elapsedTime)
{
	for (int i = 0; i < MAX_ARROWS_COUNT; ++i)
	{
		if (m_pPlayer[i]->m_pArrow[i] != NULL)
		{
			if (m_pPlayer[i]->m_pArrow[i]->Set_Life() <= 0)
			{
				Delete_Arrow(i);
				cout << i << "번째 화살 삭제" << endl;
			}

			else
				m_pPlayer[i]->m_pArrow[i]->Update(elapsedTime);
		}
	}
}

void SceneManager::Delete_Arrow(int index)
{
	delete m_pPlayer[index]->m_pArrow[index];
	m_pPlayer[index]->m_pArrow[index] = NULL;
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
		m_pBuilding->Get_TextureID(m_pRenderer->CreatePngTexture("./Textures/PNGs/castle3.png"));
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
		m_pRenderer->DrawTexturedRect(
			m_pBuilding->Set_X(),
			m_pBuilding->Set_Y(),
			m_pBuilding->Set_Z(),
			m_pBuilding->Set_Size(),
			m_pBuilding->Set_Color_R(),
			m_pBuilding->Set_Color_G(),
			m_pBuilding->Set_Color_B(),
			m_pBuilding->Set_Color_A(),
			m_pBuilding->Set_TextureID());
	}
}

void SceneManager::Update_Building(void)
{
	if (m_pBuilding != NULL)
	{
		if (m_pBuilding->Set_Life() <= 0)
		{
			Delete_Building();
			cout << "건물 삭제" << endl;
		}
	}

	if (m_pBuilding == NULL)
	{
		cout << "건물 재 생성" << endl;
		Init_Building();
	}
}

void SceneManager::Delete_Building(void)
{
	delete m_pBuilding;
	m_pBuilding = NULL;
}

void SceneManager::Init_Bullet(void)
{
	for (int i = 0; i < m_ibullet_count; ++i)
	{
		if (m_pBullet[i] == NULL)
		{
			m_pBullet[i] = new Object(m_pBuilding->Set_X(), m_pBuilding->Set_Y());
			m_pBullet[i]->Get_Life(20.0);
			m_pBullet[i]->Get_Size(10.0);
			m_pBullet[i]->Get_Color_R(0.0),
			m_pBullet[i]->Get_Color_G(0.0),
			m_pBullet[i]->Get_Color_B(0.0),
			m_pBullet[i]->Get_Color_A(1.0);
			m_pBullet[i]->Get_Life(1000);
		}
	}
}

void SceneManager::Draw_Bullet(void)
{
	for (int i = 0; i < m_ibullet_count; ++i)
	{
		if (m_pBullet[i] == NULL)
			Init_Bullet();

		else if (m_pBullet[i] != NULL)
		{
			m_pRenderer->DrawSolidRect(
				m_pBullet[i]->Set_X(),
				m_pBullet[i]->Set_Y(),
				m_pBullet[i]->Set_Z(),
				m_pBullet[i]->Set_Size(),
				m_pBullet[i]->Set_Color_R(),
				m_pBullet[i]->Set_Color_G(),
				m_pBullet[i]->Set_Color_B(),
				m_pBullet[i]->Set_Color_A());
		}
	}
}

void SceneManager::Update_Bullet(float elapsedTime)
{
	for (int i = 0; i < m_ibullet_count; ++i)
	{
		if (m_pBullet[i] != NULL)
		{
			if (m_pBullet[i]->Set_Life() <= 0)
			{
				Delete_Bullet(i);
				cout << i << "번째 총알 삭제" << endl;
			}

			else
				m_pBullet[i]->Update(elapsedTime);
		}
	}
}

void SceneManager::Delete_Bullet(int index)
{
	delete m_pBullet[index];
	m_pBullet[index] = NULL;
}

void SceneManager::Collision(void)
{
	int icollision_count1 = 0;
	int icollision_count2 = 0;

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		icollision_count1 = 0;

		if (m_pPlayer[i] != NULL)
		{
			for (int j = 0; j < m_ibullet_count; ++j)
			{
				if (m_pBullet[j] != NULL)
				{
					float minX1, minY1;
					float maxX1, maxY1;

					float minX2, minY2;
					float maxX2, maxY2;

					float minX3, minY3;
					float maxX3, maxY3;

					minX1 = m_pPlayer[i]->Set_X() - m_pPlayer[i]->Set_Size() / 2.f;
					minY1 = m_pPlayer[i]->Set_Y() - m_pPlayer[i]->Set_Size() / 2.f;
					maxX1 = m_pPlayer[i]->Set_X() + m_pPlayer[i]->Set_Size() / 2.f;
					maxY1 = m_pPlayer[i]->Set_Y() + m_pPlayer[i]->Set_Size() / 2.f;

					minX2 = m_pBuilding->Set_X() - m_pBuilding->Set_Size() / 2.f;
					minY2 = m_pBuilding->Set_Y() - m_pBuilding->Set_Size() / 2.f;
					maxX2 = m_pBuilding->Set_X() + m_pBuilding->Set_Size() / 2.f;
					maxY2 = m_pBuilding->Set_Y() + m_pBuilding->Set_Size() / 2.f;


					minX3 = m_pBullet[j]->Set_X() - m_pBullet[j]->Set_Size() / 2.f;
					minY3 = m_pBullet[j]->Set_Y() - m_pBullet[j]->Set_Size() / 2.f;
					maxX3 = m_pBullet[j]->Set_X() + m_pBullet[j]->Set_Size() / 2.f;
					maxY3 = m_pBullet[j]->Set_Y() + m_pBullet[j]->Set_Size() / 2.f;

					if (Box_Collision(minX1, minY1, maxX1, maxY1, minX2, minY2, maxX2, maxY2, minX3, minY3, maxX3, maxY3))
						++icollision_count1;
				}
			}
			
			// 충돌 했을 때
			if (icollision_count1 > 0)
			{
				m_pPlayer[i]->Get_Life(0.0);
				m_pPlayer[i]->Get_LifeTime(0.0);
				m_pPlayer[i]->Get_Color_R(1.0);
				m_pPlayer[i]->Get_Color_G(0.0);
				m_pPlayer[i]->Get_Color_B(0.0);
				m_pPlayer[i]->Get_Color_A(1.0);
			
				m_pBuilding->Get_Life(m_pBuilding->Set_Life() - 10000);
				cout << "건물 체력 : " << m_pBuilding->Set_Life() << endl;
				m_pBullet[i]->Get_Life(0.0);
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
	/*
	for (int i = 0; i < m_iobject_count; ++i)
	{
		icollision_count2 = 0;
			for (int j = 0; j < MAX_ARROWS_COUNT; ++j)
			{
				if (i == j)
					continue;
				else
				{
					float minX1, minY1;
					float maxX1, maxY1;

					float minX2, minY2;
					float maxX2, maxY2;

					minX1 = m_pPlayer[i]->Set_X() - m_pPlayer[i]->Set_Size() / 2.f;
					minY1 = m_pPlayer[i]->Set_Y() - m_pPlayer[i]->Set_Size() / 2.f;
					maxX1 = m_pPlayer[i]->Set_X() + m_pPlayer[i]->Set_Size() / 2.f;
					maxY1 = m_pPlayer[i]->Set_Y() + m_pPlayer[i]->Set_Size() / 2.f;

					minX2 = m_pPlayer[i]->m_pArrow[j]->Set_X() - m_pPlayer[i]->m_pArrow[j]->Set_Size() / 2.f;
					minY2 = m_pPlayer[i]->m_pArrow[j]->Set_Y() - m_pPlayer[i]->m_pArrow[j]->Set_Size() / 2.f;
					maxX2 = m_pPlayer[i]->m_pArrow[j]->Set_X() + m_pPlayer[i]->m_pArrow[j]->Set_Size() / 2.f;
					maxY2 = m_pPlayer[i]->m_pArrow[j]->Set_Y() + m_pPlayer[i]->m_pArrow[j]->Set_Size() / 2.f;

					if (Test_Box_Collision(minX1, minY1, maxX1, maxY1, minX2, minY2, maxX2, maxY2))
						++icollision_count2;
				}
			}

			if (icollision_count2 > 0)
			{
				m_pPlayer[i]->Get_Life(0.0);
				m_pPlayer[i]->Get_LifeTime(0.0);
				m_pPlayer[i]->Get_Color_R(0.0);
				m_pPlayer[i]->Get_Color_G(1.0);
				m_pPlayer[i]->Get_Color_B(0.0);
				m_pPlayer[i]->Get_Color_A(1.0);
			}
		}
	}
	*/
}

bool SceneManager::Box_Collision(
	float minX1, float minY1, float maxX1, float maxY1, 
	float minX2, float minY2, float maxX2, float maxY2,
	float minX3, float minY3, float maxX3, float maxY3)
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

	// 캐릭터가 총알보다 오른쪽에 있을 때
	if (minX1 > maxX3)
		return false;

	// 캐릭터가 총알보다 왼쪽에 있을 때
	if (maxX1 > minX3)
		return false;

	// 캐릭터가 총알보다 위쪽에 있을 때
	if (minY1 > maxY3)
		return false;

	// 캐릭터가 총알보다 아래쪽에 있을 때
	if (maxY1 > minY3)
		return false;

	return true;
}

bool SceneManager::Test_Box_Collision(float minX1, float minY1, float maxX1, float maxY1, float minX2, float minY2, float maxX2, float maxY2)
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

}

void SceneManager::Release(void)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		delete m_pBullet[i];
		m_pBullet[i] = NULL;

		delete m_pPlayer[i];
		m_pPlayer[i] = NULL;

		delete m_pArrow[i];
		m_pArrow[i] = NULL;
	}

	delete m_pBuilding;
	m_pBuilding = NULL;
}
