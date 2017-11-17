#include "stdafx.h"
#include "SceneMgr.h"
bool BoxCollision(Transform* standard, Transform* target)
{
	bool ix = ((standard[0].x <= target[0].x && standard[1].x >= target[0].x) || (standard[0].x <= target[1].x && standard[1].x >= target[1].x));
	bool iy = ((standard[0].y <= target[0].y && standard[1].y >= target[0].y) || (standard[0].y <= target[1].y && standard[1].y >= target[1].y));


	return (ix&&iy);
}
int dead = 0;

SceneMgr::SceneMgr()
{
	m_renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!m_renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	m_size = 100;	
	m_prevTime = (float)timeGetTime()*0.001f;
	Object* newObject = new Object({ 200,300,0 }, { 1,1,0,0 }, 50, m_renderer, OBJECT_BUILDING, 500,TEAM_1);
	m_buildingList.push_back(newObject);
	newObject = new Object({ 0,350,0 }, { 1,1,0,0 }, 50, m_renderer, OBJECT_BUILDING, 500, TEAM_1);
	m_buildingList.push_back(newObject);
	newObject = new Object({ -200,300,0 }, { 1,1,0,0 }, 50, m_renderer, OBJECT_BUILDING, 500, TEAM_1);
	m_buildingList.push_back(newObject);
	newObject = new Object({ -200,-300,0 }, { 1,1,0,0 }, 50, m_renderer, OBJECT_BUILDING, 500, TEAM_2);
	m_buildingList.push_back(newObject);
	newObject = new Object({ 0,-350,0 }, { 1,1,0,0 }, 50, m_renderer, OBJECT_BUILDING, 500, TEAM_2);
	m_buildingList.push_back(newObject);
	newObject = new Object({ 200,-300,0 }, { 1,1,0,0 }, 50, m_renderer, OBJECT_BUILDING, 500, TEAM_2);
	m_buildingList.push_back(newObject);
	//m_objectList.push_back(newObject);
	m_texture = m_renderer->CreatePngTexture("./Resources/station.png");
	m_texture2 = m_renderer->CreatePngTexture("./Resources/station2.png");
}
SceneMgr::~SceneMgr()
{
	delete m_renderer;
}
//void SceneMgr::AddObject()
//{
//	if(o_num<=10){
//	srand((unsigned)time(NULL));
//	for (int i = 0; i < 50; ++i)
//	{
//		float x = (rand() % 500) - 200;
//		float y = 200 - (rand() % 500);
//		//float size = float(rand() % 10 + 1);
//		float size = 10;
//		//cout << x << " " << y;
//		Transform newPos = { x,y };
//		Object* newObject = new Object(newPos, { 1,1,1 }, size, m_renderer,OBJECT_CHARACTER,10);
//		Transform speed = { rand() / (float)RAND_MAX * 100,rand() / (float)RAND_MAX * 100,0 };
//		newObject->SetSpeed(speed);
//		m_objectList.push_back(newObject);
//		o_num++;
//	}
//	}
//}

void SceneMgr::AddObject(float x, float y, Color color, int size, int type, int life, int team, Transform speed)
{
	if (m_objectList.size() <= 100) {
		x = x - 250;
		y = 400 - y;
		Transform newPos = { x,y,0 };
		Object* newObject = new Object(newPos, color, size, m_renderer, type, life,team);
		newObject->SetSpeed(speed);
		newObject->SetColor({ 1,1,1,1 });
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
	m_currTime = (float)timeGetTime()*0.001f;
	float elapsedTime = m_currTime - m_prevTime;
	m_prevTime = m_currTime;
	//m_fireTime += elapsedTime;
	srand(time(NULL));
	//if (m_fireTime > 0.5 && m_buildingList.size() > 0) {
	//	m_fireTime = 0;
	//	Object* newObject = new Object({ 0,0,0 }, { 1,1,1 }, 2, m_renderer, OBJECT_BULLET, 20,TEAM_1);
	//	newObject->SetSpeed({ 600,600,0 });
	//	m_bulletList.push_back(newObject);
	//}

	Transform* s_collider = nullptr;
	Transform* o_collider = nullptr;
	Transform* b_collider = nullptr;
	Transform* a_collider = nullptr;
	for (int i = 0;i < m_buildingList.size();++i)
	{
		Object* nowbui = m_buildingList[i];
		s_collider = nowbui->GetCollider();
		nowbui->CreateBullet();

		int o_size = 0;
		for (auto character : m_objectList)
		{
			o_collider = character->GetCollider();
			if (BoxCollision(s_collider, o_collider))
			{
				character->Damage(10);
				nowbui->Damage(5);
			}
		}
	}
	//여기까지 진행중

	for (int j = 0;j < m_objectList.size();++j)
	{
		Object* nowobj = m_objectList[j];
		o_collider = nowobj->GetCollider();
		nowobj->CreateArrow();

		int b_size = 0;
		for (auto building : m_buildingList)
		{
			s_collider = building->GetCollider();
			if (BoxCollision(s_collider, o_collider))
			{
				//color = { 1,0,0,1 };
				building->Damage(5);
				building->ShowLife();
				nowobj->Damage(10);
				//building->SetColor({ 1,0,0,1 });
			}
			if (building->IsDead())
			{
				m_buildingList.erase(m_buildingList.begin() + b_size);
			}
			b_size++;
		}	
		for (int i = 0;i < m_bulletList.size();++i)
		{
			Object* bullet = m_bulletList[i];
			b_collider = bullet->GetCollider();
			if (BoxCollision(o_collider, b_collider))
			{
				nowobj->Damage(10);
				bullet->Damage(20);
			}
			if (bullet->IsDead())
			{
				m_bulletList.erase(m_bulletList.begin() + i);
				continue;
			}
		}///////

		if (nowobj->IsDead()) {
			m_objectList.erase(m_objectList.begin() + j);
			continue;
		}
		nowobj->Update(elapsedTime);
	}
	for (auto data : m_bulletList)
		data->Update(elapsedTime);

	//화살발사부분
	for (auto a : m_objectList)
	{
		int a_size = 0;
		for (auto arrow : a->m_arrowList) {
			a_collider = arrow->GetCollider();
			int b_size = 0;
			for (auto building : m_buildingList) 
			{
				Transform* s_collider2 = building->GetCollider();
				if (BoxCollision(s_collider2, a_collider))
				{
					building->Damage(20);
					arrow->Damage(10);
				}
				if (building->IsDead())
				{
					m_buildingList.erase(m_buildingList.begin() + b_size);
				}
				b_size++;
			}
			int o_size = 0;
			for (auto character : m_objectList) {
				Transform* o_collider2 = character->GetCollider();
				if (BoxCollision(o_collider2, a_collider) && arrow->m_parent != character)
				{
					character->Damage(20);
					arrow->Damage(20);
				}
				if (character->IsDead()) {
					m_objectList.erase(m_objectList.begin() + o_size);
				}
				o_size++;
			}
			if (arrow->IsDead()) {
				a->m_arrowList.erase(a->m_arrowList.begin() + a_size);
				continue;
			}
			arrow->Update(elapsedTime);
			a_size++;
		}
	}
	Render();
}

void SceneMgr::Render()
{
	for (auto data : m_objectList)
	{
		data->Render();
	}
	for (auto data : m_buildingList) {
		for (auto bullet : data->m_bulletList) {
			bullet->Render();
		}
	}
	for (auto data : m_buildingList) 
	{
		if (data->GetTeam() == TEAM_1)
			data->Render(m_texture);
		else
			data->Render(m_texture2);
	}
	for (auto data : m_objectList) 
		for (auto arrow : data->m_arrowList)
				arrow->Render();
}

