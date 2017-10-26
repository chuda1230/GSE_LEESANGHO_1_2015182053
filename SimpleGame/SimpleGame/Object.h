#pragma once
//#include "Renderer.h"
class Object
{
public:
	Object(const Transform& pos, const Color& color, const float size, Renderer* renderer);
	~Object();
	//-------------------------------��Ʈ--------------------------------------------------------
	void SetColor(const Color& color);
	void SetSpeed(const Transform speed);
	void Damage(const float life);
	void SetTransform(const Transform& pos, const float size);
	//---------------------------------��Ʈ----------------------------------------------
	Color GetColor(Color& color);
	//void GetColor(Color& color); 
	float GetSize() { return m_size; }
	Transform* GetCollider();
	Transform GetTransform();
	//-----------------------------����Լ�--------------------------------------------------------
	bool IsDead() { return m_dead; }//�׾��� ���׾���
	//--------------------������Ʈ-----------------------------------------------------------
	virtual void Render();
	virtual void Update(float elapsedTime);

private:
	Transform m_speed;//�ӵ�
	Transform m_direction;//���� ����
	Transform m_transform;//���� ��ġ
	Renderer* m_renderer;
	Color m_color;
	float m_size;
	//�浹üũ-------------------------------------------------------------------
	Transform m_collider[2];
	//����----------------------------------------------
	float m_life;
	float m_lifeTime = 0;
	bool m_dead = false;

};

