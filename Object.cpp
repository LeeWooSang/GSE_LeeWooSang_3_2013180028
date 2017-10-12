#include "stdafx.h"
#include "Object.h"
#include "Player.h"
#include "Building.h"

Object::Object()
{

}

Object::~Object(void)
{
	Release();
}

bool Object::Init(void)
{
	m_pPlayer = new Player;
	if (false == m_pPlayer->Init())
		return false;
	
	return true;
}

void Object::Output(void)
{

}

void Object::Update(void)
{

}


void Object::Release(void)
{
	delete m_pPlayer;
	m_pPlayer = NULL;
}
