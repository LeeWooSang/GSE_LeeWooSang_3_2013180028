#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr(int WindowWidth , int WindowHeight)
{
	m_Renderer = new Renderer(WindowWidth, WindowHeight);

	if (m_Renderer->IsInitialized())
	{
		std::cout << "SceneMgr::Render could not be initailized.\n";
	}
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_objects[i] = NULL;
	}

	m_REDTEAM_buildingTexture = m_Renderer->CreatePngTexture("./Textures/PNGs/castle3.png");
	m_BLUETEAM_buildingTexture = m_Renderer->CreatePngTexture("./Textures/PNGs/castle6.png");
}

SceneMgr::~SceneMgr()
{
	delete m_Renderer;
}

int SceneMgr::CreateObject(float x, float y, int objectType, int teamType)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_objects[i] == NULL)
		{
			m_objects[i] = new Object(x, y, objectType, teamType);
			return i;
		}
	}

}

void SceneMgr::UpdateAllObject(float elapsedTime)
{
	DoColisionTest();

	enemyCooltime += elapsedTime * 0.001f;

	//적을 5초마다 한번씩 생성
	if (enemyCooltime > 5.f)
	{
		CreateObject(float( rand() % 250 - 250 ) , float  ( rand() % 200 + 50 ) , OBJECT_CHARACTER, RED_TEAM);
		enemyCooltime = 0.f;
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL) {
			if (m_objects[i]->Get_Life() < 0.0001f || m_objects[i]->Get_LifeTime() < 0.0001f)
			{
				delete m_objects[i];
				m_objects[i] = NULL;
			}
			else
			{
				m_objects[i]->Update(elapsedTime);
				// 빌딩이면 총알 생성
				if (m_objects[i]->Get_Type() == OBJECT_BUILDING)
				{
					if (m_objects[i]->Get_LastBullet() > 10.f)
					{
						int bulletID = CreateObject(m_objects[i]->Get_X(), m_objects[i]->Get_Y(), OBJECT_BULLET, m_objects[i]->Get_TeamType());
						m_objects[i]->Set_LastBullet(0.f);
						if (bulletID >= 0)
						{
							m_objects[bulletID]->Set_ParentID(i);
						}
					}
				}
				// 캐릭터이면 화살생성
				else if (m_objects[i]->Get_Type() == OBJECT_CHARACTER)
				{
					if (m_objects[i]->Get_LastArrow() > 3.f)
					{
						int arrowID = CreateObject(m_objects[i]->Get_X(), m_objects[i]->Get_Y(), OBJECT_ARROW, m_objects[i]->Get_TeamType());
						m_objects[i]->Set_LastArrow(0.f);
						if (arrowID >= 0)
						{
							m_objects[arrowID]->Set_ParentID(i);
						}
					}
				}
			}
		}
	}
}

void SceneMgr::DoColisionTest()
{
	int collisionCount = 0;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		collisionCount = 0;
		if (m_objects[i] != NULL)
		{
			for (int j = i + 1; j < MAX_OBJECTS_COUNT; j++)
			{
				if (m_objects[j] != NULL && m_objects[i] != NULL && m_objects[j]->Get_TeamType() != m_objects[i]->Get_TeamType())
				{
					if (BoxColisionTest(m_objects[i], m_objects[j]))
					{
						//빌딩 - 캐릭터
						if (m_objects[i]->Get_Type() == OBJECT_BUILDING  && m_objects[j]->Get_Type() == OBJECT_CHARACTER)
						{
							m_objects[i]->Set_Damage(m_objects[j]->Get_Life());
							m_objects[j]->Set_Life(0.f);
							collisionCount++;
						}
						else if (m_objects[j]->Get_Type() == OBJECT_BUILDING && m_objects[i]->Get_Type() == OBJECT_CHARACTER)
						{
							m_objects[j]->Set_Damage(m_objects[i]->Get_Life());
							m_objects[i]->Set_Life(0.f);
							collisionCount++;
						}
						// 캐릭터 - 총알
						else if (m_objects[i]->Get_Type() == OBJECT_CHARACTER && m_objects[j]->Get_Type() == OBJECT_BULLET)
						{
							m_objects[i]->Set_Damage(m_objects[j]->Get_Life());
							m_objects[j]->Set_Life(0.f);
						}
						else if (m_objects[j]->Get_Type() == OBJECT_CHARACTER && m_objects[i]->Get_Type() == OBJECT_BULLET)
						{
							m_objects[j]->Set_Damage(m_objects[i]->Get_Life());
							m_objects[i]->Set_Life(0.f);
						}
						// 빌딩 - 화살
						else if (m_objects[i]->Get_Type() == OBJECT_BUILDING && m_objects[j]->Get_Type() == OBJECT_ARROW)
						{
							m_objects[i]->Set_Damage(m_objects[j]->Get_Life());
							m_objects[j]->Set_Life(0.f);
						}
						else if (m_objects[j]->Get_Type() == OBJECT_BUILDING && m_objects[i]->Get_Type() == OBJECT_ARROW)
						{
							m_objects[j]->Set_Damage(m_objects[i]->Get_Life());
							m_objects[i]->Set_Life(0.f);
						}
						// 캐릭터 - 화살
						else if (m_objects[i]->Get_Type() == OBJECT_CHARACTER && m_objects[j]->Get_Type() == OBJECT_ARROW )
						{
							if (m_objects[j]->Get_ParentID() != i)
							{
								m_objects[i]->Set_Damage(m_objects[j]->Get_Life());
								m_objects[j]->Set_Life(0.f);

								for (int k = 0; k < MAX_OBJECTS_COUNT; ++k)
								{
									if (m_objects[k] != NULL)
									{
										if (m_objects[k]->Get_ParentID() == i)
										{
											m_objects[k]->Set_ParentID(-1);
										}
									}
								}
							}
						}
						else if (m_objects[j]->Get_Type() == OBJECT_CHARACTER && m_objects[i]->Get_Type() == OBJECT_ARROW)
						{
							if (m_objects[i]->Get_ParentID() != j)
							{
								m_objects[j]->Set_Damage(m_objects[i]->Get_Life());
								m_objects[i]->Set_Life(0.f);
								for (int k = 0; k < MAX_OBJECTS_COUNT; ++k)
								{
									if (m_objects[k] != NULL)
									{
										if (m_objects[k]->Get_ParentID() == j)
										{
											m_objects[k]->Set_ParentID(-1);
										}
									}
								}
							}

						}
					}
				}
			}
		}
	}
}


void SceneMgr::DrawAllObject()
{

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i) 
	{
			if (m_objects[i] != NULL) 
			{
				if (m_objects[i]->Get_Type() == OBJECT_BUILDING)
				{
					if (m_objects[i]->Get_TeamType() == RED_TEAM)
					{
						m_Renderer->DrawTexturedRect(m_objects[i]->Get_X(), m_objects[i]->Get_Y(), 0, m_objects[i]->Get_Size(), 1, 1, 1, 1, m_REDTEAM_buildingTexture);
					}
					else if (m_objects[i]->Get_TeamType() == BLUE_TEAM)
					{
						m_Renderer->DrawTexturedRect(m_objects[i]->Get_X(), m_objects[i]->Get_Y(), 0, m_objects[i]->Get_Size(), 1, 1, 1, 1, m_BLUETEAM_buildingTexture);

					}
				}
				else
				{
					m_Renderer->DrawSolidRect(
						m_objects[i]->Get_X(), 
						m_objects[i]->Get_Y(), 
						m_objects[i]->Get_Z(),
						m_objects[i]->Get_Size(), 
						m_objects[i]->Get_Color_R(),
						m_objects[i]->Get_Color_G(), 
						m_objects[i]->Get_Color_B(),
						m_objects[i]->Get_Color_A());
				}
			}
	}

}

bool SceneMgr::BoxColisionTest(Object* a, Object* b)
{
	if (a->Get_X() + a->Get_HalfSize() < b->Get_X() - b->Get_HalfSize()
			|| a->Get_X() - a->Get_HalfSize() > b->Get_X() + b->Get_HalfSize()) {
			return false;
		}

		if (a->Get_Y() + a->Get_HalfSize() < b->Get_Y() - b->Get_HalfSize()
			|| a->Get_Y() - a->Get_HalfSize() > b->Get_Y() + b->Get_HalfSize()) {
			return false;
		}

	return true;
}

void SceneMgr::DeleteObject(int index)
{
	if (m_objects[index] != NULL)
	{
		delete m_objects[index];
		m_objects[index] = NULL;
	}
}