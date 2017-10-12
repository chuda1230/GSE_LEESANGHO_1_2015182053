#pragma once
#include"Renderer.h"
struct u_Transform
{
	float x;
	float y;
	float z;
};
struct u_Color
{
	float r;
	float g;
	float b;
	float a;
};
class Unit
{
public:
	Unit(u_Transform pos,u_Color color,int size,float mx,float my);
	void u_Render();
	void u_Update();
	void u_Disappear();
	~Unit();
private:
	u_Transform u_transform;
	Renderer* unit_Renderer;
	u_Color u_color;
	int u_size;
	float m_x;
	float m_y;
};

