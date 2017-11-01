
#pragma once
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Object
{
public:
	explicit Object(float x, float y);
	virtual ~Object(void);

public:
	void Update(float elapsedTime);

public:
	void Get_X(float x)			{ m_fx = x; }
	float Set_X()						{ return m_fx; }

	void Get_Y(float y)			{ m_fy = y; }
	float Set_Y()						{ return m_fy; }

	void Get_Z(float z)			{ m_fz = z; }
	float Set_Z()						{ return m_fz; }

	void Get_Size(float size)	{ m_fsize = size; }
	float Set_Size()					{ return m_fsize; }

	void Get_Color_R(float R) { m_color_r = R; }
	float Set_Color_R()			{ return m_color_r; }

	void Get_Color_G(float G) { m_color_g = G; }
	float Set_Color_G()			{ return m_color_g; }

	void Get_Color_B(float B) { m_color_b = B; }
	float Set_Color_B()			{ return m_color_b; }

	void Get_Color_A(float A) { m_color_a = A; }
	float Set_Color_A()			{ return m_color_a; }

	float Set_Life(void)			{ return m_fLife; }
	float Set_LifeTime(void)	{ return m_fLifeTime; }


private:
	float m_fx, m_fy, m_fz;
	float m_vector_fx, m_vector_fy;
	float m_fsize;
	float m_color_r, m_color_g, m_color_b, m_color_a;

	float m_fSpeed;
	int m_iDir;

	float m_fLife;
	float m_fLifeTime;
};