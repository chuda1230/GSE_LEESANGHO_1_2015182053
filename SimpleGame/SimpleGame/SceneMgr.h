#pragma once
#include"Object.h"
class SceneMgr
{
public:
	SceneMgr(Renderer* renderer);
	~SceneMgr();
	void AddObject();
	Object* GetObject(int index);
	void GetList(vector<Object*>& param);
	void Update();
	void Render();
private:
	vector<Object*> m_objectList;
	Renderer* m_renderer;
	int m_size;
};
