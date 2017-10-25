#include "stdafx.h"
#include "SceneMgr.h"


SceneMgr::SceneMgr(Renderer* renderer)
{
	m_size = 50;
	m_renderer = renderer;
}
SceneMgr::~SceneMgr()
{
}
void SceneMgr::AddObject()
{
	srand(time(NULL));
	for (int i = 0; i < m_size; ++i)
	{
		float x = rand() % 500 + 1;
		float y = rand() % 500 + 1;
		float size = float(rand() % 50 + 1);
		//cout << x << " " << y;
		Transform newPos = { x - 250,y - 250,0 };
		Object* newObject = new Object(newPos, { 1.0f,1.0f,1.0f }, size, m_renderer);
		m_objectList.push_back(newObject);
	}
}

Object * SceneMgr::GetObject(int index)
{
	return nullptr;
}

void SceneMgr::GetList(vector<Object*>& param)
{
	param = m_objectList;
}

void SceneMgr::Update()
{
	srand(time(NULL));
	Transform dir = { 2,1,0 };
	float speed;
	for (auto data : m_objectList)
	{
		speed = rand() / (float)RAND_MAX*0.1;
		data->Update(speed, dir);
	}
}

void SceneMgr::Render()
{
	for (auto data : m_objectList)
	{
		data->Render();
	}
}

