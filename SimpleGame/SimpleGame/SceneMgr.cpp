#include "stdafx.h"
#include "SceneMgr.h"
bool BoxCollision(Transform* standard, Transform* target)
{
	bool isX = ((standard[0].x <= target[0].x && standard[1].x >= target[0].x) || (standard[0].x <= target[1].x && standard[1].x >= target[1].x));
	bool isY = ((standard[0].y <= target[0].y && standard[1].y >= target[0].y) || (standard[0].y <= target[1].y && standard[1].y >= target[1].y));




	return (isX&&isY);
}


SceneMgr::SceneMgr(Renderer* renderer)
{
	m_size = 100;	//50°³ÀÇ °´Ã¼
	m_prevTime = (float)timeGetTime()*0.001f;
	m_renderer = renderer;
}
SceneMgr::~SceneMgr()
{
}
int o_num = 0;
void SceneMgr::AddObject()
{
	if(o_num<=10){
	srand((unsigned)time(NULL));
	for (int i = 0; i < 50; ++i)
	{
		float x = (rand() % 500) - 200;
		float y = 200 - (rand() % 500);
		//float size = float(rand() % 10 + 1);
		float size = 10;
		//cout << x << " " << y;
		Transform newPos = { x,y };
		Object* newObject = new Object(newPos, { 1,1,1 }, size, m_renderer);
		Transform speed = { rand() / (float)RAND_MAX * 100,rand() / (float)RAND_MAX * 100,0 };
		newObject->SetSpeed(speed);
		m_objectList.push_back(newObject);
		o_num++;
	}
	}
}

void SceneMgr::AddObject(float x,float y)
{
	if (o_num <= 10) {
		srand((unsigned)time(NULL));
		x = x - 250;
		y = 250 - y;
		//float size = float(rand() % 10 + 1);
		float size = 10;
		//cout << x << " " << y;
		Transform newPos = { x,y };
		Object* newObject = new Object(newPos, { 1,1,1 }, size, m_renderer);
		Transform speed = { rand() / (float)RAND_MAX * 100,rand() / (float)RAND_MAX * 100,0 };
		newObject->SetSpeed(speed);
		m_objectList.push_back(newObject);
		o_num++;
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
	m_currTime = (float)timeGetTime()*0.001f;
	float elapsedTime = m_currTime - m_prevTime;
	m_prevTime = m_currTime;
	//srand(time(NULL));
	for (int i = 0;i < m_objectList.size();++i)
	{
		Object* data = m_objectList[i];
		Color color = { 1,1,1,0 };
		Transform* standard = nullptr;
		Transform* target = nullptr;

		data->SetColor(color);
		standard = data->GetCollider();

		for (int j = 0;j < m_objectList.size();++j)
		{
			Object* compareData = m_objectList[j];
			target = compareData->GetCollider();
			if (BoxCollision(standard, target) && i != j)
			{
				color = { 1,0,0,1 };
				data->Damage(0.01);
				compareData->Damage(0.01);
				data->SetColor(color);
			}
		}
		data->Update(elapsedTime);
		if (data->IsDead()) {
			m_objectList.erase(m_objectList.begin() + i);
			o_num--;
		}
	}
}

void SceneMgr::Render()
{
	for (auto data : m_objectList)
	{
		data->Render();
	}
}

