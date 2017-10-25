#include "stdafx.h"
#include "Unit.h"


Unit::Unit(u_Transform pos, u_Color color, int size, float mx,float my,int hp)
{
	u_transform = pos;
	u_color = color;
	u_size = size;
	m_x = mx;
	m_y = my;
	unit_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	u_hp = hp;
}
void Unit::u_Render()	//렌더러 함수
{
	unit_Renderer->DrawSolidRect(u_transform.x, u_transform.y, u_transform.z, u_size, u_color.r, u_color.g, u_color.b, u_color.a);
}
void Unit::u_Update()	//업데이트 함수
{
	u_transform.x += m_x;
	u_transform.y += m_y;
}
Unit::~Unit()
{
	delete unit_Renderer;
}
