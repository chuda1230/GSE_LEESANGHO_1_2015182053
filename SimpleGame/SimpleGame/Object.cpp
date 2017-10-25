#include "stdafx.h"
#include "Object.h"


Object::Object(const Transform& pos, const Color& color, const float size, Renderer* renderer)
{
	m_transform = pos;
	m_color = color;
	m_size = size;
	m_renderer = renderer;
}


void Object::SetTransform(const Transform& pos, const float size)
{
		m_transform = pos;
		m_size = size;
}

	void Object::GetTransform(Transform & pos)
{
		pos = m_transform;
}

	void Object::SetColor(const Color & color)
{
		m_color = color;
}

	void Object::GetColor(Color & color)
{
		color = m_color;
}

	void Object::Render()
{
		m_renderer->DrawSolidRect(m_transform.x, m_transform.y, m_transform.z, m_size, m_color.r, m_color.g, m_color.b, m_color.a);
}
	void Object::Update(float speed, Transform & direction)
{
		m_transform.x += direction.x*speed;
		m_transform.y += direction.y*speed;
		m_transform.z += direction.z*speed;
}


Object::~Object()
{
}
