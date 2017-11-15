#include "stdafx.h"
#include "Object.h"


Object::Object(const Transform& pos, const Color& color, const float size, Renderer* renderer,int type,int life,Object* parent)
{
	//srand((unsigned)time(NULL));
	m_transform = pos;
	m_color = color;
	m_size = size;
	m_renderer = renderer;
	m_type = type;
	m_life = life;
	m_parent = parent;

	m_direction = { float(rand() % 3) + 1,float(rand() % 3) + 1,0 };
	if (rand() % 2 == 1)
	{
		m_direction.x *= -1;
	}
	if (rand() % 2 == 1)
	{
		m_direction.y *= -1;
	}
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
int Object::GetType()
{
	return m_type;
}
void Object::ShowLife()
{
	cout << m_life;
}
void Object::Damage(const float damage)
{
	m_life -= damage;
}
void Object::CreateArrow()
{
	m_currTime_a = (float)timeGetTime()*0.001f;
	float elapsedTime_a = m_currTime_a - m_prevTime_a;
	m_prevTime_a = m_currTime_a;
	m_fireTime_a += elapsedTime_a;
	if (m_fireTime_a>0.5)
	{
		m_fireTime_a = 0;
		Transform parent = m_transform;
		//Object* newObject = new Object(newPos, color, size, m_renderer, type, life);
		Object* newObject = new Object(parent, { 0,1,0,1 }, 2 ,m_renderer, OBJECT_ARROW, 10, this);
		newObject->SetSpeed({ 100 ,100 ,0 });
		m_arrowList.push_back(newObject);
	}
}

Color Object::GetColor(Color & color)
{
	//color = m_color;
	return color;
}

Transform* Object::GetCollider()
{
	m_collider[0].x = m_transform.x - (m_size / 2);
	m_collider[0].y = m_transform.y - (m_size / 2);
	m_collider[0].z = 0;
	m_collider[1].x = m_transform.x + (m_size / 2);
	m_collider[1].y = m_transform.y + (m_size / 2);
	m_collider[1].z = 0;
	return m_collider;
}
void Object::Render()
{
	m_renderer->DrawSolidRect(m_transform.x, m_transform.y, m_transform.z, m_size, m_color.r, m_color.g, m_color.b, 1);

}

void Object::Render(GLuint texture)
{
	m_renderer->DrawTexturedRect(m_transform.x, m_transform.y, m_transform.z, m_size, m_color.r, m_color.g, m_color.b, 1,texture);

}
void Object::Update(float elapsedTime)
{
	m_transform.y += m_direction.y*m_speed.x*elapsedTime;
	m_transform.x += m_direction.x*m_speed.y*elapsedTime;
	m_transform.z += m_direction.z*m_speed.z*elapsedTime;



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