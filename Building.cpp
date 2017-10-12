#include "stdafx.h"
#include "Building.h"

Building::Building(void)
{

}
Building::~Building(void)
{

}

bool Building::Init(void)
{
	m_ix = 30;
	m_iy = 30;
	m_iz = 0;

	m_fsize = 5.0;

	m_color_r = 0.0;
	m_color_g = 1.0;
	m_color_b = 1.0;
	m_color_a = 0.0;

	return true;
}

void Building::Output(void)
{
	Renderer* g_Renderer = NULL;
	g_Renderer->DrawSolidRect(m_ix, m_iy, m_iz, m_fsize * 5, m_color_r, m_color_g, m_color_b, m_color_a);

	g_Renderer->DrawSolidRect(m_ix, m_iy, m_iz, m_fsize, m_color_r, m_color_g, m_color_b, m_color_a);
	g_Renderer->DrawSolidRect(m_ix +m_fsize * 2, m_iy, m_iz, m_fsize, m_color_r, m_color_g, m_color_b, m_color_a);
	g_Renderer->DrawSolidRect(m_ix - m_fsize * 2 , m_iy, m_iz, m_fsize, m_color_r, m_color_g, m_color_b, m_color_a);

	g_Renderer->DrawSolidRect(m_ix, m_iy, m_iz, m_fsize, m_color_r, m_color_g, m_color_b, m_color_a);
	g_Renderer->DrawSolidRect(m_ix, m_iy * 2, m_iz, m_fsize, m_color_r, m_color_g, m_color_b, m_color_a);
	g_Renderer->DrawSolidRect(m_ix, m_iy * 2, m_iz, m_fsize, m_color_r, m_color_g, m_color_b, m_color_a);
}

void Building::Update(void)
{

}

void Building::Release(void)
{

}
