#include "stdafx.h"
#include "Object.h"


Object::Object(const Transform& pos, const Color& color, Renderer* renderer, int type, int team, Object* parent)
{

	switch (type) {
	case OBJECT_CHARACTER:
		m_size = 10;
		m_life = 10;
		m_speed = { 300,300,0 };
		break;
	case OBJECT_BUILDING:
		m_size = 100;
		m_life = 500;
		break;
	case OBJECT_BULLET:
		m_size = 2;
		m_life = 20;
		m_speed = { 600,600,0 };
		break;
	case OBJECT_ARROW:
		m_size = 2;
		m_life = 10;
		m_speed = { 100,100,0 };
		break;
	}
	m_transform = pos;
	m_color = color;
	m_renderer = renderer;
	m_type = type;
	m_parent = parent;
	m_team = team;
	m_arrowList.reserve(100);

	float tempx = rand() / float(RAND_MAX);
	float tempy = 1 - tempx;
	m_direction = {tempx,tempy,0};
	if (rand() % 2 < 1)
	{
		m_direction.x *= -1;
	}
	if (rand() % 2 < 1)
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
int Object::GetTeam()
{
	return m_team;
}
void Object::ShowLife()
{
	cout << m_life;
}
void Object::Damage(const float damage)
{
	m_life -= damage;
	if (m_life <= 0)
	{
		m_life = 0;
		isDead = true;
	}
}
float Object::GetLife()
{
	return m_life;
}
void Object::CreateArrow(float elapsedTime_a)
{
	m_fireTime_a += elapsedTime_a;
	if (m_fireTime_a>=1.0)
	{
		m_fireTime_a = 0;
		Transform parent = m_transform;
		//Object* newObject = new Object(newPos, color, size, m_renderer, type, life);
		Color* teamColor;
		if (m_team == TEAM_1)
		{
			teamColor = team1_color;
		}
		else {
			teamColor = team2_color;
		}
		Object* newObject;
		if (m_type == OBJECT_BUILDING)
		{
			newObject = new Object(parent, teamColor[0],  m_renderer, OBJECT_BULLET,  m_team, this);
		}
		else
		{
			newObject = new Object(parent, teamColor[1], m_renderer, OBJECT_ARROW, m_team, this);
		}
		m_arrowList.push_back(newObject);
	}
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

Color Object::GetColor(Color & color)
{
	//color = m_color;
	return color;
}
void Object::Render()
{
	m_renderer->DrawSolidRect(m_transform.x, m_transform.y, m_transform.z, m_size, m_color.r, m_color.g, m_color.b, 1);

	for (auto arrow : m_arrowList)
		arrow->Render();
}

void Object::Render(GLuint texture)
{
	m_renderer->DrawTexturedRect(m_transform.x, m_transform.y, m_transform.z, m_size, m_color.r, m_color.g, m_color.b, 1,texture);
	for (auto arrow : m_arrowList)
		arrow->Render();
}
void Object::Update(float elapsedTime)
{
	m_transform.y += m_direction.y*m_speed.x*elapsedTime;
	m_transform.x += m_direction.x*m_speed.y*elapsedTime;
	m_transform.z += m_direction.z*m_speed.z*elapsedTime;



	if (m_transform.y >= (WINDOW_HEIGHT / 2-10))
	{
		m_transform.y = (WINDOW_HEIGHT / 2 - 10);
		m_direction.y *= -1;
	}
	if (m_transform.x >= (WINDOW_WIDTH/2-10))
	{
		m_transform.x = (WINDOW_WIDTH / 2 - 10);
		m_direction.x *= -1;
	}
	if (m_transform.x <= -(WINDOW_WIDTH / 2 - 10))
	{
		m_transform.x = -(WINDOW_WIDTH / 2 - 10);
		m_direction.x *= -1;
	}
	if (m_transform.y <= -(WINDOW_HEIGHT/2-10))
	{
		m_transform.y = -(WINDOW_HEIGHT / 2 - 10);
		m_direction.y *= -1;
	}
}





Object::~Object()
{
}