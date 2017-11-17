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
	void AddObject(float x,float y,Color color,int size,int type,int life, int team,Transform speed = { 0.0f,0.0f,0.0f });
	Object* GetObject(int index);
	void GetList(vector<Object*>& param);
	void Update();
	void Render();
private:
	GLuint m_texture;
	GLuint m_texture2;

	vector<Object*> m_objectList;
	vector<Object*> m_bulletList;
	vector<Object*> m_buildingList;
	
	Renderer* m_renderer;
	int m_size;

	float m_prevTime = 0;
	float m_currTime = 0;
	float m_fireTime = 0;
};
