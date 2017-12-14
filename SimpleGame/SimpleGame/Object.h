#pragma once
//#include "Renderer.h"
#define BACKGROUND 100
#define TEAM_0 30
#define TEAM_1 10
#define TEAM_2 20
#define OBJECT_BUILDING 0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET 2
#define OBJECT_ARROW 3
class Object
{
public:
	Object(const Transform& pos, const Color& color, Renderer* renderer, int type, int team, Object* parent = nullptr);
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
	Transform* GetCollider();	//충돌
	Transform GetTransform();	//위치
	int GetType();
	float GetLife();
	int GetTeam();
	void CreateArrow(float elapsedTime);
	virtual void Render();
	virtual void Render(GLuint texture);
	virtual void Update(float elapsedTime);
	bool isDead = false;

private:
	Transform m_speed;
	Transform m_direction;
	Transform m_transform;
	Renderer* m_renderer;
	
	Color m_color;
	float m_size;

	Transform m_collider[2];

	float m_animationIndex = 0;
	float m_particleIndex = 0;
	float m_climateIndex = 0;
	GLuint m_particle;
	GLuint m_climate;



	float m_gauge;
	int m_orign_life = 0;
	int m_life;
	int m_type;
	int m_team;
	float m_damage = 0;
	float m_level = 0;
	bool m_dead = false;
	float m_prevTime_a = 0;
	float m_currTime_a = 0;
	float m_fireTime_a = 0;
	float m_prevTime_b = 0;
	float m_currTime_b = 0;
	float m_fireTime_b = 0;

	Color team1_color[2] = { {1,0,0,1},{1,0,1,1} };
	Color team2_color[2] = { {0,0,1,1},{0.8f,1,0,1} };

};

