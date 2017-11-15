#pragma once
//#include "Renderer.h"
#define OBJECT_ARROW 3
class Object
{
public:
	Object(const Transform& pos, const Color& color, const float size, Renderer* renderer,int type,int life,Object* parent=nullptr);
	~Object();
	vector<Object*> m_arrowList;
	void SetColor(const Color& color);
	void SetSpeed(const Transform speed);
	void Damage(const float life);
	void SetTransform(const Transform& pos, const float size);
	void ShowLife();
	Color GetColor(Color& color);
	Object* m_parent;
	//void GetColor(Color& color); 
	float GetSize() { return m_size; }
	Transform* GetCollider();	//충돌
	Transform GetTransform();	//위치
	int GetType();
	void CreateArrow();
	
	bool IsDead() { //사망여부
		if (m_life <= 0) 
		{
			m_dead = true;
		}
		return m_dead;
	}
	virtual void Render();
	virtual void Render(GLuint texture);
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

	float m_prevTime_a = 0;
	float m_currTime_a = 0;
	float m_fireTime_a = 0;

};

