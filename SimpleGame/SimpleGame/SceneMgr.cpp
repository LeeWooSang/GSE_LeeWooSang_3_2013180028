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

	m_Background_Texture = m_Renderer->CreatePngTexture("./Textures/PNGs/background.png");

	m_REDTEAM_buildingTexture = m_Renderer->CreatePngTexture("./Textures/PNGs/castle3.png");
	m_REDTEAM_characterTexture = m_Renderer->CreatePngTexture("./Textures/PNGs/Red_animation.png");

	m_BLUETEAM_buildingTexture = m_Renderer->CreatePngTexture("./Textures/PNGs/castle6.png");
	m_BLUETEAM_characterTexture = m_Renderer->CreatePngTexture("./Textures/PNGs/Blue_animation.png");
	
	m_particleTexture = m_Renderer->CreatePngTexture("./Textures/PNGs/particle1.png");
}

SceneMgr::~SceneMgr()
{
	delete m_Renderer;
}

int SceneMgr::InitObject(float x, float y, int objectType, int teamType)
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
	BLUETEAM_Cooltime += elapsedTime * 0.001f;
	REDTEAM_Cooltime += elapsedTime * 0.001f;
	Particle_Cooltime += elapsedTime * 0.001f;

	//적을 3초마다 한번씩 생성
	if (enemyCooltime > 3.f)
	{
		InitObject(float( rand() % 250 - 250 ) , float  ( rand() % 200 + 50 ) , OBJECT_CHARACTER, RED_TEAM);
		enemyCooltime = 0.f;
	}

	// 애니메이션 쿨타임
	if (BLUETEAM_Cooltime > 0.1f)
	{
		if (BLUETEAM_sheet1_1 < 6)
		{
			++BLUETEAM_sheet1_1;
			BLUETEAM_Cooltime = 0.f;
		}

		else
		{			
			if (BLUETEAM_sheet1_1 == 6 && BLUETEAM_sheet1_2 == 1)
				BLUETEAM_sheet1_2 = 0;

			else
			{
				BLUETEAM_sheet1_1 = 0;
				BLUETEAM_sheet1_2 = 1;
			}
		}
	}

	if (REDTEAM_Cooltime > 0.1f)
	{
		if (REDTEAM_sheet2_1 < 3)
		{
			++REDTEAM_sheet2_1;
			REDTEAM_Cooltime = 0.f;
		}
		else
		{
			if (REDTEAM_sheet2_1 == 3 && REDTEAM_sheet2_2 == 1)
				REDTEAM_sheet2_2 = 0;

			else 
			{
				REDTEAM_sheet2_1 = 0;
				REDTEAM_sheet2_2 = 1;
			}
		}
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL) 
		{
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
					// 3초마다 총알 생성
					if (m_objects[i]->Get_LastBullet() > 3.f)
					{
						int bulletID = InitObject(m_objects[i]->Get_X(), m_objects[i]->Get_Y(), OBJECT_BULLET, m_objects[i]->Get_TeamType());
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
						int arrowID = InitObject(m_objects[i]->Get_X(), m_objects[i]->Get_Y(), OBJECT_ARROW, m_objects[i]->Get_TeamType());
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
							// 빌딩 게이지 감소
							m_objects[i]->Set_Damage_Gauge(m_objects[j]->Get_Life() / m_objects[i]->Get_Life());

							// 빌딩 체력 감소
							m_objects[i]->Set_Damage(m_objects[j]->Get_Life());

							m_objects[j]->Set_Gauge(0.f);
							m_objects[j]->Set_Life(0.f);
							++collisionCount;
						}

						else if (m_objects[j]->Get_Type() == OBJECT_BUILDING && m_objects[i]->Get_Type() == OBJECT_CHARACTER)
						{
							// 빌딩 게이지 감소
							m_objects[j]->Set_Damage_Gauge(m_objects[i]->Get_Life() / m_objects[j]->Get_Life());

							m_objects[j]->Set_Damage(m_objects[i]->Get_Life());

							m_objects[i]->Set_Gauge(0.f);
							m_objects[i]->Set_Life(0.f);
							++collisionCount;
						}

						// 빌딩 - 총알
						else if (m_objects[i]->Get_Type() == OBJECT_BUILDING && m_objects[j]->Get_Type() == OBJECT_BULLET)
						{

							// 빌딩 게이지 감소
							m_objects[i]->Set_Damage_Gauge(m_objects[j]->Get_Life() / m_objects[i]->Get_Life());

							m_objects[i]->Set_Damage(m_objects[j]->Get_Life());

							// 총알 체력 0
							m_objects[j]->Set_Life(0.f);
							++collisionCount;
							//cout << "건물체력 : " << m_objects[i]->Get_Life() << endl;

						}

						else if (m_objects[j]->Get_Type() == OBJECT_BUILDING && m_objects[i]->Get_Type() == OBJECT_BULLET)
						{
							m_objects[j]->Set_Damage_Gauge(m_objects[i]->Get_Life() / m_objects[j]->Get_Life());

							m_objects[j]->Set_Damage(m_objects[i]->Get_Life());
							// 총알 체력 0
							m_objects[i]->Set_Life(0.f);
							++collisionCount;
							//cout << "건물체력 : " << m_objects[j]->Get_Life() << endl;
						}


						else if (m_objects[j]->Get_Type() == OBJECT_BUILDING && m_objects[i]->Get_Type() == OBJECT_BULLET)
						{
							m_objects[j]->Set_Damage(m_objects[i]->Get_Life());
							// 총알 체력 0
							m_objects[i]->Set_Life(0.f);
							++collisionCount;
							//cout << "건물체력 : " << m_objects[j]->Get_Life() << endl;
						}

						// 캐릭터 - 총알
						else if (m_objects[i]->Get_Type() == OBJECT_CHARACTER && m_objects[j]->Get_Type() == OBJECT_BULLET)
						{
							m_objects[i]->Set_Damage_Gauge(m_objects[j]->Get_Life() / m_objects[i]->Get_Life());

							m_objects[i]->Set_Damage(m_objects[j]->Get_Life());
							m_objects[j]->Set_Life(0.f);
						}
						else if (m_objects[j]->Get_Type() == OBJECT_CHARACTER && m_objects[i]->Get_Type() == OBJECT_BULLET)
						{
							m_objects[j]->Set_Damage_Gauge(m_objects[i]->Get_Life() / m_objects[j]->Get_Life());

							m_objects[j]->Set_Damage(m_objects[i]->Get_Life());
							m_objects[i]->Set_Life(0.f);
						}

						// 빌딩 - 화살
						else if (m_objects[i]->Get_Type() == OBJECT_BUILDING && m_objects[j]->Get_Type() == OBJECT_ARROW)
						{
							m_objects[i]->Set_Damage_Gauge(m_objects[j]->Get_Life() / m_objects[i]->Get_Life());

							m_objects[i]->Set_Damage(m_objects[j]->Get_Life());
							m_objects[j]->Set_Life(0.f);
						}

						else if (m_objects[j]->Get_Type() == OBJECT_BUILDING && m_objects[i]->Get_Type() == OBJECT_ARROW)
						{
							m_objects[j]->Set_Damage_Gauge(m_objects[i]->Get_Life() / m_objects[j]->Get_Life());

							m_objects[j]->Set_Damage(m_objects[i]->Get_Life());
							m_objects[i]->Set_Life(0.f);
						}

						// 캐릭터 - 화살
						else if (m_objects[i]->Get_Type() == OBJECT_CHARACTER && m_objects[j]->Get_Type() == OBJECT_ARROW )
						{
							if (m_objects[j]->Get_ParentID() != i)
							{
								m_objects[i]->Set_Damage_Gauge(m_objects[j]->Get_Life() / m_objects[i]->Get_Life());

								m_objects[i]->Set_Damage(m_objects[j]->Get_Life());
								m_objects[j]->Set_Life(0.f);

								for (int k = 0; k < MAX_OBJECTS_COUNT; ++k)
								{
									if (m_objects[k] != NULL)
									{
										if (m_objects[k]->Get_ParentID() == i)
											m_objects[k]->Set_ParentID(-1);			
									}
								}
							}
						}

						else if (m_objects[j]->Get_Type() == OBJECT_CHARACTER && m_objects[i]->Get_Type() == OBJECT_ARROW)
						{
							if (m_objects[i]->Get_ParentID() != j)
							{
								m_objects[j]->Set_Damage_Gauge(m_objects[i]->Get_Life() / m_objects[j]->Get_Life());

								m_objects[j]->Set_Damage(m_objects[i]->Get_Life());
								m_objects[i]->Set_Life(0.f);

								for (int k = 0; k < MAX_OBJECTS_COUNT; ++k)
								{
									if (m_objects[k] != NULL)
									{
										if (m_objects[k]->Get_ParentID() == j)
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
	

void SceneMgr::DrawAllObject()
{
	// 배경 이미지 추가
	m_Renderer->DrawTexturedRect(0, 0, 0, 800, 1, 1, 1, 1, m_Background_Texture, 0.99);

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->Get_Type() == OBJECT_BUILDING)
			{
				if (m_objects[i]->Get_TeamType() == RED_TEAM)
				{
					m_Renderer->DrawTexturedRect(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y(),
						0, // Z
						m_objects[i]->Get_Size(),
						1, 1, 1, 1, // R, G, B, A
						m_REDTEAM_buildingTexture,
						m_objects[i]->Get_Level());

					// 게이지 바
					m_Renderer->DrawSolidRectGauge(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y() + 60,
						0, // Z
						m_objects[i]->Get_Gauge_Width(),
						m_objects[i]->Get_Gauge_Height(),
						1, 0, 0, 1, // R, G, B, A
						m_objects[i]->Get_Gauge(),
						m_objects[i]->Get_Level()
					);
				}
				else if (m_objects[i]->Get_TeamType() == BLUE_TEAM)
				{
					m_Renderer->DrawTexturedRect(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y(),
						0, // Z
						m_objects[i]->Get_Size(),
						1, 1, 1, 1, // R, G, B, A
						m_BLUETEAM_buildingTexture,
						m_objects[i]->Get_Level());

					// 게이지 바
					m_Renderer->DrawSolidRectGauge(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y() + 60,
						0, // Z
						m_objects[i]->Get_Gauge_Width(),
						m_objects[i]->Get_Gauge_Height(),
						0, 0, 1, 1, // R, G, B, A
						m_objects[i]->Get_Gauge(),
						m_objects[i]->Get_Level()
					);
				}
			}

			// 캐릭터
			else if(m_objects[i]->Get_Type() == OBJECT_CHARACTER)
			{
				if (m_objects[i]->Get_TeamType() == RED_TEAM)
				{
					m_Renderer->DrawTexturedRectSeq(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y(),
						m_objects[i]->Get_Z(),
						m_objects[i]->Get_Size(),
						m_objects[i]->Get_Color_R(),
						m_objects[i]->Get_Color_G(),
						m_objects[i]->Get_Color_B(),
						m_objects[i]->Get_Color_A(),
						m_REDTEAM_characterTexture,
						REDTEAM_sheet2_1,
						REDTEAM_sheet2_2,
						//m_objects[i]->Get_Animation_Sheet2(), 
						3, 2,
						m_objects[i]->Get_Level());

					// 게이지 바
					m_Renderer->DrawSolidRectGauge(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y() + 20,
						0, // Z
						m_objects[i]->Get_Gauge_Width(),
						m_objects[i]->Get_Gauge_Height(),
						1, 0, 0, 1, // R, G, B, A
						m_objects[i]->Get_Gauge(),
						m_objects[i]->Get_Level());
				}

				else if (m_objects[i]->Get_TeamType() == BLUE_TEAM)
				{
					m_Renderer->DrawTexturedRectSeq(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y(),
						m_objects[i]->Get_Z(),
						m_objects[i]->Get_Size(),
						m_objects[i]->Get_Color_R(),
						m_objects[i]->Get_Color_G(),
						m_objects[i]->Get_Color_B(),
						m_objects[i]->Get_Color_A(),
						m_BLUETEAM_characterTexture,
						BLUETEAM_sheet1_1,
						BLUETEAM_sheet1_2,
						//m_objects[i]->Get_Animation_Sheet2(), 
						5, 2,
						m_objects[i]->Get_Level());

					// 게이지 바
					m_Renderer->DrawSolidRectGauge(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y() + 20,
						0, // Z
						m_objects[i]->Get_Gauge_Width(),
						m_objects[i]->Get_Gauge_Height(),
						0, 0, 1, 1, // R, G, B, A
						m_objects[i]->Get_Gauge(),
						m_objects[i]->Get_Level());
				}
			}

			else if (m_objects[i]->Get_Type() == OBJECT_BULLET)
			{
				if (m_objects[i]->Get_TeamType() == RED_TEAM)
				{
					/*
					m_Renderer->DrawTexturedRect(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y(),
						m_objects[i]->Get_Z(),
						m_objects[i]->Get_Size(),
						m_objects[i]->Get_Color_R(),
						m_objects[i]->Get_Color_G(),
						m_objects[i]->Get_Color_B(),
						m_objects[i]->Get_Color_A(),
						m_BLUETEAM_bulletTexture,
						m_objects[i]->Get_Level());
					*/

					m_Renderer->DrawParticle(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y(),
						m_objects[i]->Get_Z(),
						m_objects[i]->Get_Size(),
						m_objects[i]->Get_Color_R(),
						m_objects[i]->Get_Color_G(),
						m_objects[i]->Get_Color_B(),
						m_objects[i]->Get_Color_A(),
						0, 1,
						m_particleTexture,
						Particle_Cooltime);
						
				}

				else if (m_objects[i]->Get_TeamType() == BLUE_TEAM)
				{
					m_Renderer->DrawParticle(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y(),
						m_objects[i]->Get_Z(),
						m_objects[i]->Get_Size(),
						m_objects[i]->Get_Color_R(),
						m_objects[i]->Get_Color_G(),
						m_objects[i]->Get_Color_B(),
						m_objects[i]->Get_Color_A(),
						0, -1,
						m_particleTexture,
						Particle_Cooltime);
				}
			}

			// 화살
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
					m_objects[i]->Get_Color_A(),
					m_objects[i]->Get_Level());
			}
		}
	}
	/*
	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_objects[i] != NULL)
		{
			if (m_objects[i]->Get_Type() == OBJECT_BUILDING)
			{
				if (m_objects[i]->Get_TeamType() == RED_TEAM)
				{
					m_Renderer->DrawTexturedRect(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y(),
						0, // Z
						m_objects[i]->Get_Size(),
						1, 1, 1, 1, // R, G, B, A
						m_REDTEAM_buildingTexture,
						m_objects[i]->Get_Level());

					// 게이지 바
					m_Renderer->DrawSolidRectGauge(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y() + 60,
						0, // Z
						m_objects[i]->Get_Gauge_Width(),
						m_objects[i]->Get_Gauge_Height(),
						1, 0, 0, 1, // R, G, B, A
						m_objects[i]->Get_Gauge(),
						m_objects[i]->Get_Level()
					);
				}
				else if (m_objects[i]->Get_TeamType() == BLUE_TEAM)
				{
					m_Renderer->DrawTexturedRect(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y(),
						0, // Z
						m_objects[i]->Get_Size(),
						1, 1, 1, 1, // R, G, B, A
						m_BLUETEAM_buildingTexture,
						m_objects[i]->Get_Level());

					// 게이지 바
					m_Renderer->DrawSolidRectGauge(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y() + 60,
						0, // Z
						m_objects[i]->Get_Gauge_Width(),
						m_objects[i]->Get_Gauge_Height(),
						0, 0, 1, 1, // R, G, B, A
						m_objects[i]->Get_Gauge(),
						m_objects[i]->Get_Level()
					);
				}
			}

			else
			{
				if (m_objects[i]->Get_Type() == OBJECT_CHARACTER && m_objects[i]->Get_TeamType() == BLUE_TEAM)
				{
					m_Renderer->DrawTexturedRectSeq(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y(),
						m_objects[i]->Get_Z(),
						m_objects[i]->Get_Size(),
						m_objects[i]->Get_Color_R(),
						m_objects[i]->Get_Color_G(),
						m_objects[i]->Get_Color_B(),
						m_objects[i]->Get_Color_A(),
						m_BLUETEAM_characterTexture,
						BLUETEAM_sheet1_1,
						BLUETEAM_sheet1_2,
						//m_objects[i]->Get_Animation_Sheet2(), 
						5, 2,
						m_objects[i]->Get_Level());
				}
				else if (m_objects[i]->Get_Type() == OBJECT_CHARACTER && m_objects[i]->Get_TeamType() == RED_TEAM)
				{
					m_Renderer->DrawTexturedRectSeq(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y(),
						m_objects[i]->Get_Z(),
						m_objects[i]->Get_Size(),
						m_objects[i]->Get_Color_R(),
						m_objects[i]->Get_Color_G(),
						m_objects[i]->Get_Color_B(),
						m_objects[i]->Get_Color_A(),
						m_REDTEAM_characterTexture,
						REDTEAM_sheet2_1,
						REDTEAM_sheet2_2,
						//m_objects[i]->Get_Animation_Sheet2(), 
						3, 2,
						m_objects[i]->Get_Level());
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
						m_objects[i]->Get_Color_A(),
						m_objects[i]->Get_Level());
				}

			}

			if (m_objects[i]->Get_Type() == OBJECT_CHARACTER)
			{
				if (m_objects[i]->Get_TeamType() == BLUE_TEAM)
				{
					// 게이지 바
					m_Renderer->DrawSolidRectGauge(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y() + 20,
						0, // Z
						m_objects[i]->Get_Gauge_Width(),
						m_objects[i]->Get_Gauge_Height(),
						0, 0, 1, 1, // R, G, B, A
						m_objects[i]->Get_Gauge(),
						m_objects[i]->Get_Level()
					);
				}
				else
				{
					// 게이지 바
					m_Renderer->DrawSolidRectGauge(
						m_objects[i]->Get_X(),
						m_objects[i]->Get_Y() + 20,
						0, // Z
						m_objects[i]->Get_Gauge_Width(),
						m_objects[i]->Get_Gauge_Height(),
						1, 0, 0, 1, // R, G, B, A
						m_objects[i]->Get_Gauge(),
						m_objects[i]->Get_Level()
					);
				}
			}
		}
	}
	*/
}

bool SceneMgr::BoxColisionTest(Object* a, Object* b)
{
	if (a->Get_X() + a->Get_HalfSize() < b->Get_X() - b->Get_HalfSize()
			|| a->Get_X() - a->Get_HalfSize() > b->Get_X() + b->Get_HalfSize()) 
	{
			return false;
		}

		if (a->Get_Y() + a->Get_HalfSize() < b->Get_Y() - b->Get_HalfSize()
			|| a->Get_Y() - a->Get_HalfSize() > b->Get_Y() + b->Get_HalfSize())
		{
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