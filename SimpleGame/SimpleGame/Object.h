#pragma once
//#include "Renderer.h"
#define TEAM_1 10
#define TEAM_2 20
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3
class Object
{
public:
	Object(const Transform& pos, const Color& color, const float size, Renderer* renderer,int type,int life,int team,Object* parent=nullptr);
	~Object();
	vector<Object*> m_arrowList;
	vector<Object*> m_bulletList;
	void SetColor(const Color& color);
	void SetSpeed(const Transform speed);
	void Damage(const float life);
	void SetTransform(const Transform& pos, const float size);
	void ShowLife();
	Color GetColor(Color& color);
	Object* m_parent;
	//void GetColor(Color& color); 
	float GetSize() { return m_size; }
	Transform* GetCollider();	//�浹
	Transform GetTransform();	//��ġ
	int GetType();
	int GetTeam();
	void CreateArrow();
	void CreateBullet();
	
	bool IsDead() { //�������
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
	int m_team;
	float m_damage = 0;
	bool m_dead = false;

	float m_prevTime_a = 0;
	float m_currTime_a = 0;
	float m_fireTime_a = 0;
	float m_prevTime_b = 0;
	float m_currTime_b = 0;
	float m_fireTime_b = 0;

};

