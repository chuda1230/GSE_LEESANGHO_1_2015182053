#pragma once
#define OBJECT_BUILDING 0
#define OBJECT_CHARACTER 1
#define OBJECT_BULLET 2
#include"Object.h"


class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();
	//void AddObject();
	void AddObject(float x,float y);
	void AI();
	Object* GetObject(int index);
	void GetList(vector<Object*>& param);
	void Update();
	void Render();
	void Delete();
private:
	GLuint m_texture[4];

	vector<Object*> m_objectList;
	vector<Object*> m_bulletList;
	vector<Object*> m_buildingList;
	vector<Object*> m_backgroundList;

	
	Renderer* m_renderer;
	int m_size;

	float m_prevTime = 0;
	float m_currTime = 0;
	float m_fireTime = 0;
	float m_spawnTime = 0;
	float m_coolTime = 2.0f;
};
