#include "stdafx.h"
#include "SceneManager.h"

SceneManager::SceneManager(void)
{
	srand((unsigned)time(NULL));

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_pObject[i] = new Object(-250 + rand() % 500, -250 + rand() % 500, -250 + rand() % 500, rand() % 10, 1.f, 1.f, 1.f, 0.0f);

		m_pObject[i]->Get_X(-1 + rand() % 2);
		m_pObject[i]->Get_Y(-1 + rand() % 2);
	}
}

SceneManager::~SceneManager(void)
{
	delete[] m_pObject;
}

void SceneManager::Update(void)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		m_pObject[i]->Update();
}

void SceneManager::Collision(void)
{
	float pre_Min_x = 0.0f;
	float pre_Min_y = 0.0f;
	float pre_Max_x = 0.0f;
	float pre_Max_y = 0.0f;

	float next_pre_Min_x = 0.0f;
	float next_pre_Min_y = 0.0f;
	float next_Max_x = 0.0f;
	float next_Max_y = 0.0f;

	for (int i = 0; i < MAX_OBJECTS_COUNT - 1; ++i) {
		// pre_Min x,y  Max x,y

		pre_Min_x = m_pObject[i]->Set_X() - (m_pObject[i]->Set_Size() / 2);
		pre_Min_y = m_pObject[i]->Set_Y() - (m_pObject[i]->Set_Size() / 2);
		pre_Max_x = m_pObject[i]->Set_X() + (m_pObject[i]->Set_Size() / 2);
		pre_Max_y = m_pObject[i]->Set_Y() + (m_pObject[i]->Set_Size() / 2);

		//next_pre_Min_x = m_pObject[i + 1]->Get_x() - (m_pObject[i + 1]->Get_size() / 2);
		//next_pre_Min_y = m_pObject[i + 1]->Get_y() - (m_pObject[i + 1]->Get_size() / 2);
		//next_Max_x = m_pObject[i + 1]->Get_x() + (m_pObject[i + 1]->Get_size() / 2);
		//next_Max_y = m_pObject[i + 1]->Get_y() + (m_pObject[i + 1]->Get_size() / 2);

		if (((pre_Min_x <= m_pObject[i + 1]->Set_X()) && (m_pObject[i + 1]->Set_X() <= pre_Max_x)) &&	// x가 범위 안에 있고,
			((pre_Min_y <= m_pObject[i + 1]->Set_Y()) && (m_pObject[i + 1]->Set_Y() <= pre_Max_y)))		// y가 범위 안에 있으면
		{
			m_pObject[i]->Get_Color_R(1.0);
			m_pObject[i]->Get_Color_G(0.0);
			m_pObject[i]->Get_Color_B(0.0);
			m_pObject[i]->Get_Color_A(1.0);

			m_pObject[i + 1]->Get_Color_R(1.0);
			m_pObject[i + 1]->Get_Color_G(0.0);
			m_pObject[i + 1]->Get_Color_B(0.0);
			m_pObject[i + 1]->Get_Color_A(1.0);

			cout << i << "번과" << i + 1 << "번이 충돌함" << endl;
		}
	}
}

