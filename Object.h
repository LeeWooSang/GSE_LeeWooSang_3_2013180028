
#pragma once
#include "Renderer.h"
#include <iostream>
using namespace std;

class Object
{
public:
	explicit Object();
	virtual ~Object(void);

public:
	virtual bool Init(void);
	virtual void Output(void);
	virtual void Update(void);


private:
	void Release(void);

protected:
	int m_ix, m_iy, m_iz;

	int m_iSpeed, m_iTime;

	float m_fsize;
	float m_color_r, m_color_g, m_color_b, m_color_a;


	Object* m_pPlayer;
	Object* m_pBuilding;
};