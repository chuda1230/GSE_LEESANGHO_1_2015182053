#include "stdafx.h"
#include "Object.h"



Object::Object(Transform pos, Color color, int size, int hp)
{
	m_transform = pos;
	m_color = color;
	m_size = size;
	building_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	b_hp = hp;
}

void Object::Render()
{
	building_Renderer->DrawSolidRect(m_transform.x, m_transform.y, m_transform.z, m_size, m_color.r, m_color.g, m_color.b, m_color.a);
}

Object::~Object()
{
	delete building_Renderer;
}
