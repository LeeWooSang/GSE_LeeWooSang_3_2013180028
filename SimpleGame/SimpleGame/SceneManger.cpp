#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager(int width, int height)
{
	m_windowWidth = width;
	m_windowHeight = height;
	m_object_count = 0;

	m_pRenderer = new Renderer(m_windowWidth, m_windowHeight);

	if (!m_pRenderer->IsInitialized())
	{
		std::cout << "SceneMgr::Renderer could not be initialized.. \n";
	}

	for (int i = 0; i < m_object_count; ++i)
	{
		srand((unsigned)time(NULL));

		m_pBullet[i] = new Object(-250 + rand() % 500 + 10 * i, -250 + rand() % 500, -250 + rand() % 500, rand() % 10, 1.f, 1.f, 1.f, 0.0f);

		m_pBullet[i]->Get_X(-250 + rand() % 500);
		m_pBullet[i]->Get_Y(-250 + rand() % 500);
	}
}

SceneManager::~SceneManager(void)
{
	delete[] m_pBullet;
}

void SceneManager::Draw_Player(void)
{
	for (int i = 0; i < m_object_count; ++i)
	{
		m_pRenderer->DrawSolidRect(m_pPlayer[i]->Set_X(), m_pPlayer[i]->Set_Y(), m_pPlayer[i]->Set_Z(), m_pPlayer[i]->Set_Size(),
			m_pPlayer[i]->Set_Color_R(), m_pPlayer[i]->Set_Color_G(), m_pPlayer[i]->Set_Color_B(), m_pPlayer[i]->Set_Color_A());
	}
}

void SceneManager::Draw_Bullet(void)
{
	for (int i = 0; i < m_object_count; ++i)
	{
		m_pRenderer->DrawSolidRect(m_pBullet[i]->Set_X(), m_pBullet[i]->Set_Y(), m_pBullet[i]->Set_Z(), m_pBullet[i]->Set_Size(),
			m_pBullet[i]->Set_Color_R(), m_pBullet[i]->Set_Color_G(), m_pBullet[i]->Set_Color_B(), m_pBullet[i]->Set_Color_A());
	}
}

void SceneManager::Update(void)
{
	for (int i = 0; i < PLAYER_OBJECTS_COUNT; ++i)
	{
		m_pPlayer[i]->Update();
	}

	for (int i = 0; i < BULLET_OBJECTS_COUNT; ++i)
	{
		m_pBullet[i]->Update();
	}

}

void SceneManager::Collision(void)
{
	float pre_Min_x = 0.0f, pre_Min_y = 0.0f;
	float pre_Max_x = 0.0f, pre_Max_y = 0.0f;

	//float next_pre_Min_x = 0.0f, next_pre_Min_y = 0.0f;
	//float next_Max_x = 0.0f, next_Max_y = 0.0f;

	for (int i = 0; i < BULLET_OBJECTS_COUNT - 1; ++i) {
		// pre_Min x,y  Max x,y

		pre_Min_x = m_pBullet[i]->Set_X() - (m_pBullet[i]->Set_Size() / 2);
		pre_Min_y = m_pBullet[i]->Set_Y() - (m_pBullet[i]->Set_Size() / 2);
		pre_Max_x = m_pBullet[i]->Set_X() + (m_pBullet[i]->Set_Size() / 2);
		pre_Max_y = m_pBullet[i]->Set_Y() + (m_pBullet[i]->Set_Size() / 2);

		//next_pre_Min_x = m_pBullet[i + 1]->Get_x() - (m_pBullet[i + 1]->Get_size() / 2);
		//next_pre_Min_y = m_pBullet[i + 1]->Get_y() - (m_pBullet[i + 1]->Get_size() / 2);
		//next_Max_x = m_pBullet[i + 1]->Get_x() + (m_pBullet[i + 1]->Get_size() / 2);
		//next_Max_y = m_pBullet[i + 1]->Get_y() + (m_pBullet[i + 1]->Get_size() / 2);

		if (((pre_Min_x <= m_pBullet[i + 1]->Set_X()) && (m_pBullet[i + 1]->Set_X() <= pre_Max_x)) &&	// x가 범위 안에 있고,
			((pre_Min_y <= m_pBullet[i + 1]->Set_Y()) && (m_pBullet[i + 1]->Set_Y() <= pre_Max_y)))		// y가 범위 안에 있으면
		{
			m_pBullet[i]->Get_Color_R(1.0);
			m_pBullet[i]->Get_Color_G(0.0);
			m_pBullet[i]->Get_Color_B(0.0);
			m_pBullet[i]->Get_Color_A(1.0);

			m_pBullet[i + 1]->Get_Color_R(1.0);
			m_pBullet[i + 1]->Get_Color_G(0.0);
			m_pBullet[i + 1]->Get_Color_B(0.0);
			m_pBullet[i + 1]->Get_Color_A(1.0);

			cout << i << "번과" << i + 1 << "번이 충돌함" << endl;
		}
	}
}

