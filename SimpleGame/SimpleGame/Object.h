#pragma once
//#include "Renderer.h"
class Object
{
public:
	Object(const Transform& pos, const Color& color, const float size, Renderer* renderer,int type,int life);
	~Object();
	
	void SetColor(const Color& color);
	void SetSpeed(const Transform speed);
	void Damage(const float life);
	void SetTransform(const Transform& pos, const float size);
	void ShowLife();
	Color GetColor(Color& color);
	//void GetColor(Color& color); 
	float GetSize() { return m_size; }
	Transform* GetCollider();	//충돌
	Transform GetTransform();	//위치
	int GetType();
	bool IsDead() { //사망여부
		if (m_life <= 0) 
		{
			m_dead = true;
		}
		return m_dead;
	}
	virtual void Render();
	virtual void Update(float elapsedTime);

private:
	Transform m_speed;
	Transform m_direction;
	Transform m_transform;
	Renderer* m_renderer;
	Color m_color;
	float m_size;

	Transform m_collider[2];

	int m_life;
	int m_type;
	float m_damage = 0;
	bool m_dead = false;

};

