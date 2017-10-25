#pragma once
//#include "Renderer.h"
class Object
{
public:
	Object(const Transform& pos, const Color& color, const float size, Renderer* renderer);
	void SetTransform(const Transform& pos, const float size);
	void GetTransform(Transform & pos);
	void SetColor(const Color& color);
	void GetColor(Color& color);
	float GetSize() { return m_size; }
	virtual void Render();
	virtual void Update(float speed, Transform & direction);
	~Object();

private:
	Transform m_transform;
	Renderer* m_renderer;
	Color m_color;
	float m_size;
	Transform m_direction;
};

