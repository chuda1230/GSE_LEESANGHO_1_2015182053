#pragma once
#include"Object.h"
class SceneMgr
{
public:
	SceneMgr(Renderer* renderer);
	~SceneMgr();
	void AddObject();
	void AddObject(float x,float y);
	Object* GetObject(int index);
	void GetList(vector<Object*>& param);
	void Update();
	void Render();
private:
	vector<Object*> m_objectList;
	Renderer* m_renderer;
	int m_size;

	float m_prevTime = 0;
	float m_currTime = 0;
};
