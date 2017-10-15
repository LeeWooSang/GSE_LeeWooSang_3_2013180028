
#pragma once
#include "Renderer.h"
#include <iostream>
using namespace std;

class Object
{
public:
	explicit Object(float x, float y, float z, float size, float R, float G, float B, float A);
	virtual ~Object(void);

public:
	virtual bool Init();
	virtual void Output(void);
	virtual void Update(void);

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

private:
	void Release(void);

private:
	float m_fx, m_fy, m_fz;
	float m_fsize;
	float m_color_r, m_color_g, m_color_b, m_color_a;

	float m_fSpeed;
	int m_iTime;
	int m_iDir;
};