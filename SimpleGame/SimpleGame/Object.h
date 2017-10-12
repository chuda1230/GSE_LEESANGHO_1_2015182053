#pragma once
#include "Renderer.h"

struct Transform
{
	float x;
	float y;
	float z;
};
struct Color
{
	float r;
	float g;
	float b;
	float a;
};
class Object
{
public:
	Object(Transform pos, Color color,int size,int hp);
	void Render();
	void Update();
	~Object();
private:
	Transform m_transform;
	Renderer* building_Renderer;
	Color m_color;
	int m_size;
	int b_hp;
};

