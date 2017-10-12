#include "stdafx.h"
#include "Player.h"

Player::Player()
{

}

Player::~Player(void)
{
	Release();
}

bool Player::Init(void)
{
	strcpy_s(m_szName, "�׼Ұ�");
	m_iHp = 300;
	m_iMp = 200;
	m_iAtt = 80;
	m_iDef = 50;
	m_iSpeed = 10;
	m_iMoney = 0;

	m_ix = 100;
	m_iy = 100;
	m_iz = 0;
	
	m_fsize = 10.0;

	m_color_r = 1.0;
	m_color_g = 0.0;
	m_color_b = 0.0;
	m_color_a = 1.0;

	Player::Update();
	return true;
}

void Player::Output(void)
{
	cout << endl<< "==================================" << endl;
	cout << "�÷��̾�  : " << m_szName << endl;
	cout << "Hp : " << m_iHp << "\tMp : " << m_iMp << endl;
	cout << "���ݷ� : " << m_iAtt << "\t���� : " << m_iDef << endl;
	cout << "�̵��ӵ� : " << m_iSpeed << "\t������ : " << m_iMoney << endl;
	cout << "�÷��̾� x ��ġ : " << m_ix << "\t�÷��̾� y��ġ : " << m_iy << endl;
	cout << "==================================" << endl;

	Renderer* g_Renderer = NULL;
	g_Renderer->DrawSolidRect(m_ix, m_iy, m_iz, m_fsize, m_color_r, m_color_g, m_color_b, m_color_a);

}


void Player::Update(void)
{
	system("cls");

	m_ix += m_ix + m_iSpeed * m_iTime;
	m_iy += m_iy + m_iSpeed * m_iTime;

	Output();
}

void Player::Release(void)
{

}