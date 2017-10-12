#pragma once
#include "Object.h"

class Player : public Object
{
public:
	explicit Player();
	virtual ~Player(void);

public:
	virtual bool Init(void);
	virtual void Output(void);
	virtual void Update(void);

	void Player::Get(int x, int y)
	{
		m_ix = x - 250;
		m_iy = -y + 500 - 250;
	}

private:
	void Release(void);

private:
	char m_szName[128];
	int m_iHp;
	int m_iMp;
	int m_iAtt;
	int m_iDef;
	int m_iMoney;
};