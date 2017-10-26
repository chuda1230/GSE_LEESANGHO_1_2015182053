#pragma once
//#include "Renderer.h"
class Object
{
public:
	Object(const Transform& pos, const Color& color, const float size, Renderer* renderer);
	~Object();
	//-------------------------------세트--------------------------------------------------------
	void SetColor(const Color& color);
	void SetSpeed(const Transform speed);
	void Damage(const float life);
	void SetTransform(const Transform& pos, const float size);
	//---------------------------------게트----------------------------------------------
	Color GetColor(Color& color);
	//void GetColor(Color& color); 
	float GetSize() { return m_size; }
	Transform* GetCollider();
	Transform GetTransform();
	//-----------------------------기능함수--------------------------------------------------------
	bool IsDead() { return m_dead; }//죽었나 안죽었나
	//--------------------업데이트-----------------------------------------------------------
	virtual void Render();
	virtual void Update(float elapsedTime);

private:
	Transform m_speed;//속도
	Transform m_direction;//진행 방향
	Transform m_transform;//현재 위치
	Renderer* m_renderer;
	Color m_color;
	float m_size;
	//충돌체크-------------------------------------------------------------------
	Transform m_collider[2];
	//수명----------------------------------------------
	float m_life;
	float m_lifeTime = 0;
	bool m_dead = false;

};

