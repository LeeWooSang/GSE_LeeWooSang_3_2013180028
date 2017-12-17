#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr::CSceneMgr(int WindowWidth , int WindowHeight)
{
	 m_pRenderer = new Renderer(WindowWidth, WindowHeight);

	if ( m_pRenderer->IsInitialized())
	{
		std::cout << "CSceneMgr::Render could not be initailized.\n";
	}

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		m_pObjects[i] = NULL;
	}
	m_Background_Texture =  m_pRenderer->CreatePngTexture("./Textures/PNGs/background.png");

	m_REDTEAM_KING_buildingTexture =  m_pRenderer->CreatePngTexture("./Textures/PNGs/RedKingTower.png");
	m_REDTEAM_PRIENCESS_buildingTexture = m_pRenderer->CreatePngTexture("./Textures/PNGs/RedPriencessTower.png");
	m_REDTEAM_characterTexture =  m_pRenderer->CreatePngTexture("./Textures/PNGs/Red_animation.png");

	m_BLUETEAM_KING_buildingTexture =  m_pRenderer->CreatePngTexture("./Textures/PNGs/BlueKingTower.png");
	m_BLUETEAM_PRIENCESS_buildingTexture = m_pRenderer->CreatePngTexture("./Textures/PNGs/BluePriencessTower.png");
	m_BLUETEAM_characterTexture =  m_pRenderer->CreatePngTexture("./Textures/PNGs/Blue_animation.png");

	m_particleTexture =  m_pRenderer->CreatePngTexture("./Textures/PNGs/particle1.png");
	m_collison_particleTexture = m_pRenderer->CreatePngTexture("./Textures/PNGs/particle2.png");
	m_Background_particleTexture = m_pRenderer->CreatePngTexture("./Textures/PNGs/spark_particle.png");

	m_pSound = new Sound();

	//m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/AboveTheTreetops/AboveTheTreetops.mp3");						// 리스항구
	//m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/FloralLife/FloralLife.mp3");												// 헤네시스
	//m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/WhenTheMorningComes/WhenTheMorningComes.mp3");	// 엘리니아
	//m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/Nightmare/Nightmare.mp3");											// 페리온
	//m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/BadGuys/BadGuys.mp3");												// 커닝시티
	//m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/ShininHarbor/ShininHarbor.mp3");									// 오르비스
	m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/SnowyVillage/SnowyVillage.mp3");									// 엘나스
	//m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/Aquarium/Aquarium.mp3");												// 아쿠아리움
	//m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/FantasticThinking/FantasticThinking.mp3");						// 루디부리엄
	//m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/LetsMarch/LetsMarch.mp3");											// 지구방위본부
	//m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/MuruengHill/MuruengHill.mp3");										// 무릉
	//m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/Leafre/Leafre.mp3");														// 리프레
	//m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/DragonNest/DragonNest.mp3");										// 용의 둥지
	//m_Background_BGM = m_pSound->CreateSound("./Sounds/MapleStory/Blackheaven/PromiseOfHeaven.mp3");								// 블랙헤븐 ost
	//m_Background_BGM = m_pSound->CreateSound("./Sounds/Reminiscence.mp3");																		// 테일즈위버 ost
	m_BLUETEAM_CHARACTER_Init_BGM = m_pSound->CreateSound("./Sounds/Init_Effect_Sound.mp3");												// 블루팀 유닛 생성
	m_BLUETEAM_CHARACTER_Attack_BGM = m_pSound->CreateSound("./Sounds/Attack_Effect_Sound.mp3");										// 블루팀 유닛 공격

	m_pSound->PlaySoundA(m_Background_BGM, true, 0.4f);
}

CSceneMgr::~CSceneMgr()
{
	m_pSound->DeleteSound(m_Background_BGM);
	m_pSound->DeleteSound(m_BLUETEAM_CHARACTER_Init_BGM);
	m_pSound->DeleteSound(m_BLUETEAM_CHARACTER_Attack_BGM);

	delete m_pSound;
	m_pSound = NULL;

	delete  m_pRenderer;
	 m_pRenderer = NULL;
}

int CSceneMgr::InitObject(float x, float y, int objectType, int teamType)
{
	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		if (m_pObjects[i] == NULL)
		{
			m_pObjects[i] = new CObject(x, y, objectType, teamType);

			if (m_pObjects[i]->Get_Type() == OBJECT_CHARACTER && m_pObjects[i]->Get_TeamType() == BLUE_TEAM)
				m_pSound->PlaySoundA(m_BLUETEAM_CHARACTER_Init_BGM, false, 0.2);

			return i;
		}
	}

}

void CSceneMgr::UpdateAllObject(float elapsedTime)
{
	DoColisionTest();

	enemyCooltime += elapsedTime * 0.001f;
	BLUETEAM_Cooltime += elapsedTime * 0.001f;
	REDTEAM_Cooltime += elapsedTime * 0.001f;
	Particle_Cooltime += elapsedTime * 0.001f;
	Background_Particle_Cooltime += elapsedTime * 0.0005;

	//적을 3초마다 한번씩 생성
	if (enemyCooltime > INIT_RED_TEAM_CHARACTER_TIME)
	{
		InitObject(float( rand() % 250 - 250 ) , float  ( rand() % 200 + 50 ) , OBJECT_CHARACTER, RED_TEAM);
		enemyCooltime = 0.f;
	}

	// 애니메이션 쿨타임
	if (BLUETEAM_Cooltime > ANIMATION_COOLTIME)
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

	if (REDTEAM_Cooltime > ANIMATION_COOLTIME)
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
		if (m_pObjects[i] != NULL) 
		{
			if (m_pObjects[i]->Get_Life() < 0.0001f || m_pObjects[i]->Get_LifeTime() < 0.0001f)
			{
				delete m_pObjects[i];
				m_pObjects[i] = NULL;
			}
			else
			{
				m_pObjects[i]->Update(elapsedTime);

				// 빌딩이면 총알 생성
				if (m_pObjects[i]->Get_Type() == OBJECT_BUILDING)
				{
					// 3초마다 총알 생성
					if (m_pObjects[i]->Get_LastBullet() > INIT_BULLET_TIME)
					{
						//if (Particle_Cooltime > 1.f)
							//Particle_Cooltime = 0.f;

						int bulletID = InitObject(m_pObjects[i]->Get_X(), m_pObjects[i]->Get_Y(), OBJECT_BULLET, m_pObjects[i]->Get_TeamType());
						m_pObjects[i]->Set_LastBullet(0.f);
						if (bulletID >= 0)
						{
							m_pObjects[bulletID]->Set_ParentID(i);
						}
					}
				}
				// 캐릭터이면 화살생성
				else if (m_pObjects[i]->Get_Type() == OBJECT_CHARACTER)
				{
					if (m_pObjects[i]->Get_LastArrow() > INIT_ARROW_TIME)
					{
						int arrowID = InitObject(m_pObjects[i]->Get_X(), m_pObjects[i]->Get_Y(), OBJECT_ARROW, m_pObjects[i]->Get_TeamType());

						m_pObjects[i]->Set_LastArrow(0.f);
						if (arrowID >= 0)
						{
							m_pObjects[arrowID]->Set_ParentID(i);
						}

						if(m_pObjects[i]->Get_TeamType() == BLUE_TEAM)
							m_pSound->PlaySoundA(m_BLUETEAM_CHARACTER_Attack_BGM, false, 0.1);
					}
				}
			}
		}
	}
}

void CSceneMgr::DoColisionTest()
{
	int collisionCount = 0;

	for (int i = 0; i < MAX_OBJECTS_COUNT; i++)
	{
		collisionCount = 0;
		if (m_pObjects[i] != NULL)
		{
			for (int j = i + 1; j < MAX_OBJECTS_COUNT; j++)
			{
				if (m_pObjects[j] != NULL && m_pObjects[i] != NULL && m_pObjects[j]->Get_TeamType() != m_pObjects[i]->Get_TeamType())
				{
					if (BoxColisionTest(m_pObjects[i], m_pObjects[j]))
					{
						//빌딩 - 캐릭터
						if (m_pObjects[i]->Get_Type() == OBJECT_BUILDING  && m_pObjects[j]->Get_Type() == OBJECT_CHARACTER)
						{
							// 빌딩 게이지 감소
							m_pObjects[i]->Set_Damage_Gauge(m_pObjects[j]->Get_Life() / m_pObjects[i]->Get_Life());

							// 빌딩 체력 감소
							m_pObjects[i]->Set_Damage(m_pObjects[j]->Get_Life());

							m_pObjects[j]->Set_Gauge(0.f);
							m_pObjects[j]->Set_Life(0.f);
							++collisionCount;
						}

						else if (m_pObjects[j]->Get_Type() == OBJECT_BUILDING && m_pObjects[i]->Get_Type() == OBJECT_CHARACTER)
						{
							// 빌딩 게이지 감소
							m_pObjects[j]->Set_Damage_Gauge(m_pObjects[i]->Get_Life() / m_pObjects[j]->Get_Life());

							m_pObjects[j]->Set_Damage(m_pObjects[i]->Get_Life());

							m_pObjects[i]->Set_Gauge(0.f);
							m_pObjects[i]->Set_Life(0.f);
							++collisionCount;
						}

						// 빌딩 - 총알
						else if (m_pObjects[i]->Get_Type() == OBJECT_BUILDING && m_pObjects[j]->Get_Type() == OBJECT_BULLET)
						{

							// 빌딩 게이지 감소
							m_pObjects[i]->Set_Damage_Gauge(m_pObjects[j]->Get_Life() / m_pObjects[i]->Get_Life());

							m_pObjects[i]->Set_Damage(m_pObjects[j]->Get_Life());

							// 총알 체력 0
							m_pObjects[j]->Set_Life(0.f);
							++collisionCount;
							//cout << "건물체력 : " << m_pObjects[i]->Get_Life() << endl;

						}

						else if (m_pObjects[j]->Get_Type() == OBJECT_BUILDING && m_pObjects[i]->Get_Type() == OBJECT_BULLET)
						{
							m_pObjects[j]->Set_Damage_Gauge(m_pObjects[i]->Get_Life() / m_pObjects[j]->Get_Life());

							m_pObjects[j]->Set_Damage(m_pObjects[i]->Get_Life());
							// 총알 체력 0
							m_pObjects[i]->Set_Life(0.f);
							++collisionCount;
							//cout << "건물체력 : " << m_pObjects[j]->Get_Life() << endl;
						}


						else if (m_pObjects[j]->Get_Type() == OBJECT_BUILDING && m_pObjects[i]->Get_Type() == OBJECT_BULLET)
						{
							m_pObjects[j]->Set_Damage(m_pObjects[i]->Get_Life());
							// 총알 체력 0
							m_pObjects[i]->Set_Life(0.f);
							++collisionCount;
							//cout << "건물체력 : " << m_pObjects[j]->Get_Life() << endl;
						}

						// 캐릭터 - 총알
						else if (m_pObjects[i]->Get_Type() == OBJECT_CHARACTER && m_pObjects[j]->Get_Type() == OBJECT_BULLET)
						{
							m_pObjects[i]->Set_Damage_Gauge(m_pObjects[j]->Get_Life() / m_pObjects[i]->Get_Life());

							m_pObjects[i]->Set_Damage(m_pObjects[j]->Get_Life());
							m_pObjects[j]->Set_Life(0.f);
							m_pObjects[j]->Set_Death(true);
						}
						else if (m_pObjects[j]->Get_Type() == OBJECT_CHARACTER && m_pObjects[i]->Get_Type() == OBJECT_BULLET)
						{
							m_pObjects[j]->Set_Damage_Gauge(m_pObjects[i]->Get_Life() / m_pObjects[j]->Get_Life());

							m_pObjects[j]->Set_Damage(m_pObjects[i]->Get_Life());
							m_pObjects[i]->Set_Life(0.f);
							m_pObjects[i]->Set_Death(true);
						}

						// 빌딩 - 화살
						else if (m_pObjects[i]->Get_Type() == OBJECT_BUILDING && m_pObjects[j]->Get_Type() == OBJECT_ARROW)
						{
							m_pObjects[i]->Set_Damage_Gauge(m_pObjects[j]->Get_Life() / m_pObjects[i]->Get_Life());

							m_pObjects[i]->Set_Damage(m_pObjects[j]->Get_Life());
							m_pObjects[j]->Set_Life(0.f);
						}

						else if (m_pObjects[j]->Get_Type() == OBJECT_BUILDING && m_pObjects[i]->Get_Type() == OBJECT_ARROW)
						{
							m_pObjects[j]->Set_Damage_Gauge(m_pObjects[i]->Get_Life() / m_pObjects[j]->Get_Life());

							m_pObjects[j]->Set_Damage(m_pObjects[i]->Get_Life());
							m_pObjects[i]->Set_Life(0.f);
						}

						// 캐릭터 - 화살
						else if (m_pObjects[i]->Get_Type() == OBJECT_CHARACTER && m_pObjects[j]->Get_Type() == OBJECT_ARROW )
						{
							if (m_pObjects[j]->Get_ParentID() != i)
							{
								m_pObjects[i]->Set_Damage_Gauge(m_pObjects[j]->Get_Life() / m_pObjects[i]->Get_Life());

								m_pObjects[i]->Set_Damage(m_pObjects[j]->Get_Life());
								m_pObjects[j]->Set_Life(0.f);

								for (int k = 0; k < MAX_OBJECTS_COUNT; ++k)
								{
									if (m_pObjects[k] != NULL)
									{
										if (m_pObjects[k]->Get_ParentID() == i)
											m_pObjects[k]->Set_ParentID(-1);			
									}
								}
							}
						}

						else if (m_pObjects[j]->Get_Type() == OBJECT_CHARACTER && m_pObjects[i]->Get_Type() == OBJECT_ARROW)
						{
							if (m_pObjects[i]->Get_ParentID() != j)
							{
								m_pObjects[j]->Set_Damage_Gauge(m_pObjects[i]->Get_Life() / m_pObjects[j]->Get_Life());

								m_pObjects[j]->Set_Damage(m_pObjects[i]->Get_Life());
								m_pObjects[i]->Set_Life(0.f);
								m_pObjects[i]->Set_Death(true);
								for (int k = 0; k < MAX_OBJECTS_COUNT; ++k)
								{
									if (m_pObjects[k] != NULL)
									{
										if (m_pObjects[k]->Get_ParentID() == j)
											m_pObjects[k]->Set_ParentID(-1);		
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
	
void CSceneMgr::DrawAllObject()
{
	// 배경 이미지 추가
	 m_pRenderer->DrawTexturedRect(0, 0, 0, 600, 1, 1, 1, 1, m_Background_Texture, 0.99);

	m_pRenderer->DrawParticleClimate(0, 0, 0, 3, 1, 1, 1, 1, -0.1, -0.1, m_Background_particleTexture, Background_Particle_Cooltime, 0.01);

	 // 텍스트 추가
	 //m_pRenderer->DrawText(-200, 100, GLUT_BITMAP_9_BY_15, 0, 0, 1, "RED TEAM");
	 //m_pRenderer->DrawText(-200, -100, GLUT_BITMAP_9_BY_15, 1, 1, 0, "BLUE TEAM");

	 m_pRenderer->DrawText(-115, 30, GLUT_BITMAP_9_BY_15, 1, 1, 1, "SIMPLEGAME");
	 m_pRenderer->DrawText(-40, 30, GLUT_BITMAP_9_BY_15, 0, 0, 0, "OF");
	 m_pRenderer->DrawText(-20, 30, GLUT_BITMAP_9_BY_15, 1, 0, 0, "LEE WOO SANG");

	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (m_pObjects[i] != NULL)
		{
			if (m_pObjects[i]->Get_Type() == OBJECT_BUILDING)
			{
				if (m_pObjects[i]->Get_TeamType() == RED_TEAM)
				{
					if (m_pObjects[i]->Get_X() == KING_TOWER_POS_X)
					{
						m_pRenderer->DrawTexturedRect(
							m_pObjects[i]->Get_X(),
							m_pObjects[i]->Get_Y(),
							0, // Z
							m_pObjects[i]->Get_Size(),
							1, 1, 1, 1, // R, G, B, A
							m_REDTEAM_KING_buildingTexture,
							m_pObjects[i]->Get_Level());
					}
					 
					else
					{
						m_pRenderer->DrawTexturedRect(
							m_pObjects[i]->Get_X(),
							m_pObjects[i]->Get_Y(),
							0, // Z
							m_pObjects[i]->Get_Size(),
							1, 1, 1, 1, // R, G, B, A
							m_REDTEAM_PRIENCESS_buildingTexture,
							m_pObjects[i]->Get_Level());
					}

					// 게이지 바
					 m_pRenderer->DrawSolidRectGauge(
						m_pObjects[i]->Get_X(),
						m_pObjects[i]->Get_Y() + 43,
						0, // Z
						m_pObjects[i]->Get_Gauge_Width(),
						m_pObjects[i]->Get_Gauge_Height(),
						1, 0, 0, 1, // R, G, B, A
						m_pObjects[i]->Get_Gauge(),
						m_pObjects[i]->Get_Level()
					);
				}

				else if (m_pObjects[i]->Get_TeamType() == BLUE_TEAM)
				{
					if (m_pObjects[i]->Get_X() == KING_TOWER_POS_X)
					{
						m_pRenderer->DrawTexturedRect(
							m_pObjects[i]->Get_X(),
							m_pObjects[i]->Get_Y(),
							0, // Z
							m_pObjects[i]->Get_Size(),
							1, 1, 1, 1, // R, G, B, A
							m_BLUETEAM_KING_buildingTexture,
							m_pObjects[i]->Get_Level());
					}

					else
					{
						m_pRenderer->DrawTexturedRect(
							m_pObjects[i]->Get_X(),
							m_pObjects[i]->Get_Y(),
							0, // Z
							m_pObjects[i]->Get_Size(),
							1, 1, 1, 1, // R, G, B, A
							m_BLUETEAM_PRIENCESS_buildingTexture,
							m_pObjects[i]->Get_Level());
					}

					// 게이지 바
					 m_pRenderer->DrawSolidRectGauge(
						m_pObjects[i]->Get_X(),
						m_pObjects[i]->Get_Y() + 43,
						0, // Z
						m_pObjects[i]->Get_Gauge_Width(),
						m_pObjects[i]->Get_Gauge_Height(),
						0, 0, 1, 1, // R, G, B, A
						m_pObjects[i]->Get_Gauge(),
						m_pObjects[i]->Get_Level()
					);
				}
			}

			// 캐릭터
			else if(m_pObjects[i]->Get_Type() == OBJECT_CHARACTER)
			{
				if (m_pObjects[i]->Get_TeamType() == RED_TEAM)
				{
					 m_pRenderer->DrawTexturedRectSeq(
						m_pObjects[i]->Get_X(),
						m_pObjects[i]->Get_Y(),
						m_pObjects[i]->Get_Z(),
						m_pObjects[i]->Get_Size(),
						m_pObjects[i]->Get_Color_R(),
						m_pObjects[i]->Get_Color_G(),
						m_pObjects[i]->Get_Color_B(),
						m_pObjects[i]->Get_Color_A(),
						m_REDTEAM_characterTexture,
						REDTEAM_sheet2_1,
						REDTEAM_sheet2_2,
						3, 2,
						m_pObjects[i]->Get_Level());

					// 게이지 바
					 m_pRenderer->DrawSolidRectGauge(
						m_pObjects[i]->Get_X(),
						m_pObjects[i]->Get_Y() + 20,
						0, // Z
						m_pObjects[i]->Get_Gauge_Width(),
						m_pObjects[i]->Get_Gauge_Height(),
						1, 0, 0, 1, // R, G, B, A
						m_pObjects[i]->Get_Gauge(),
						m_pObjects[i]->Get_Level());
				}

				else if (m_pObjects[i]->Get_TeamType() == BLUE_TEAM)
				{
					 m_pRenderer->DrawTexturedRectSeq(
						m_pObjects[i]->Get_X(),
						m_pObjects[i]->Get_Y(),
						m_pObjects[i]->Get_Z(),
						m_pObjects[i]->Get_Size(),
						m_pObjects[i]->Get_Color_R(),
						m_pObjects[i]->Get_Color_G(),
						m_pObjects[i]->Get_Color_B(),
						m_pObjects[i]->Get_Color_A(),
						m_BLUETEAM_characterTexture,
						BLUETEAM_sheet1_1,
						BLUETEAM_sheet1_2,
						5, 2,
						m_pObjects[i]->Get_Level());

					// 게이지 바
					 m_pRenderer->DrawSolidRectGauge(
						m_pObjects[i]->Get_X(),
						m_pObjects[i]->Get_Y() + 20,
						0, // Z
						m_pObjects[i]->Get_Gauge_Width(),
						m_pObjects[i]->Get_Gauge_Height(),
						0, 0, 1, 1, // R, G, B, A
						m_pObjects[i]->Get_Gauge(),
						m_pObjects[i]->Get_Level());
				}
			}

			else if (m_pObjects[i]->Get_Type() == OBJECT_BULLET)
			{
				 m_pRenderer->DrawSolidRect(
					m_pObjects[i]->Get_X(),
					m_pObjects[i]->Get_Y(),
					m_pObjects[i]->Get_Z(),
					m_pObjects[i]->Get_Size(),
					m_pObjects[i]->Get_Color_R(),
					m_pObjects[i]->Get_Color_G(),
					m_pObjects[i]->Get_Color_B(),
					m_pObjects[i]->Get_Color_A(),
					m_pObjects[i]->Get_Level());

				 if (m_pObjects[i]->Get_Death() == true)
				 {
					 m_pRenderer->DrawParticle(
						 m_pObjects[i]->Get_X(),
						 m_pObjects[i]->Get_Y(),
						 m_pObjects[i]->Get_Z(),
						 m_pObjects[i]->Get_Size(),
						 1, 1, 1, 1,
						 0, 0,
						 m_collison_particleTexture,
						 Particle_Cooltime,
						 m_pObjects[i]->Get_Level());
				 }

				if (m_pObjects[i]->Get_TeamType() == RED_TEAM)
				{
					 m_pRenderer->DrawParticle(
						m_pObjects[i]->Get_X(),
						m_pObjects[i]->Get_Y(),
						m_pObjects[i]->Get_Z(),
						m_pObjects[i]->Get_Size(),
						1, 1, 1, 1,
						- m_pObjects[i]->Get_Vector_X(),
						- m_pObjects[i]->Get_Vector_Y(),
						m_particleTexture,
						Particle_Cooltime,
						m_pObjects[i]->Get_Level());
				}

				else if (m_pObjects[i]->Get_TeamType() == BLUE_TEAM)
				{
					 m_pRenderer->DrawParticle(
						m_pObjects[i]->Get_X(),
						m_pObjects[i]->Get_Y(),
						m_pObjects[i]->Get_Z(),
						m_pObjects[i]->Get_Size(),
						1, 1, 1, 1,
						- m_pObjects[i]->Get_Vector_X(),
						- m_pObjects[i]->Get_Vector_Y(),
						m_particleTexture,
						Particle_Cooltime,
						m_pObjects[i]->Get_Level());
				}
			}

			// 화살
			else
			{
				 m_pRenderer->DrawSolidRect(
					m_pObjects[i]->Get_X(),
					m_pObjects[i]->Get_Y(),
					m_pObjects[i]->Get_Z(),
					m_pObjects[i]->Get_Size(),
					m_pObjects[i]->Get_Color_R(),
					m_pObjects[i]->Get_Color_G(),
					m_pObjects[i]->Get_Color_B(),
					m_pObjects[i]->Get_Color_A(),
					m_pObjects[i]->Get_Level());
			}
		}
	}
}

bool CSceneMgr::BoxColisionTest(CObject* a, CObject* b)
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

void CSceneMgr::DeleteObject(int index)
{
	if (m_pObjects[index] != NULL)
	{
		delete m_pObjects[index];
		m_pObjects[index] = NULL;
	}
}