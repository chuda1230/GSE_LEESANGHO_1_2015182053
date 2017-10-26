#include "stdafx.h"
#include "Object.h"


Object::Object(const Transform& pos, const Color& color, const float size, Renderer* renderer)
{
	//srand((unsigned)time(NULL));
	m_transform = pos;
	m_color = color;
	m_size = size;
	m_renderer = renderer;

	m_direction = { float(rand() % 3) + 1,float(rand() % 3) + 1,0 };
	if (rand() % 2 == 1)
	{
		m_direction.x *= -1;
	}
	if (rand() % 2 == 1)
	{
		m_direction.y *= -1;
	}
	m_life = 10;//rand() % 10 + 1;
}


void Object::SetTransform(const Transform& pos, const float size)
{
	m_transform = pos;
	m_size = size;
}

Transform Object::GetTransform()
{
	return m_transform;
}

void Object::SetColor(const Color & color)
{
	m_color = color;
}

void Object::SetSpeed(const Transform speed)
{
	m_speed = speed;
}

void Object::Damage(const float amount)
{
	m_lifeTime += amount;
}

Color Object::GetColor(Color & color)
{
	//color = m_color;
	return color;
}

Transform* Object::GetCollider()
{
	return m_collider;
}

void Object::Render()
{
	m_renderer->DrawSolidRect(m_transform.x, m_transform.y, m_transform.z, m_size, m_color.r, m_color.g, m_color.b, m_color.a);

}
void Object::Update(float elapsedTime)
{
	m_lifeTime += elapsedTime;
	if (m_life < m_lifeTime)
	{
		m_dead = true;
	}

	m_transform.y += m_direction.y*m_speed.x*elapsedTime;
	m_transform.x += m_direction.x*m_speed.y*elapsedTime;
	m_transform.z += m_direction.z*m_speed.z*elapsedTime;

	m_collider[0].x = m_transform.x - (m_size / 2);
	m_collider[0].y = m_transform.y - (m_size / 2);
	m_collider[0].z = 0;
	m_collider[1].x = m_transform.x + (m_size / 2);
	m_collider[1].y = m_transform.y + (m_size / 2);
	m_collider[1].z = 0;

	if (m_transform.y >= 300)
	{
		m_direction.y = -1;
	}
	if (m_transform.x >= 400)
	{
		m_direction.x = -1;
	}
	if (m_transform.x <= -400)
	{
		m_direction.x = 1;
	}
	if (m_transform.y <= -300)
	{
		m_direction.y = 1;
	}
}




Object::~Object()
{
}