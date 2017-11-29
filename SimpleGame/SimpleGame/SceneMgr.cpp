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

	m_objectList.reserve(100);
	m_size = 100;
	m_prevTime = (float)timeGetTime()*0.001f;
	Object* newObject = new Object({ 200,300,0 }, { 1,1,1,1 }, m_renderer, OBJECT_BUILDING,TEAM_1);
	m_objectList.push_back(newObject);
	newObject = new Object({ 0,350,0 }, { 1,1,1,1 }, m_renderer, OBJECT_BUILDING,  TEAM_1);
	m_objectList.push_back(newObject);
	newObject = new Object({ -200,300,0 }, { 1,1,1,1 }, m_renderer, OBJECT_BUILDING,  TEAM_1);
	m_objectList.push_back(newObject);
	newObject = new Object({ -200,-300,0 }, { 1,1,1,1 }, m_renderer, OBJECT_BUILDING,  TEAM_2);
	m_objectList.push_back(newObject);
	newObject = new Object({ 0,-350,0 }, { 1,1,1,1 },  m_renderer, OBJECT_BUILDING, TEAM_2);
	m_objectList.push_back(newObject);
	newObject = new Object({ 200,-300,0 }, { 1,1,1,1 },  m_renderer, OBJECT_BUILDING, TEAM_2);
	m_objectList.push_back(newObject);
	//m_objectList.push_back(newObject);
	m_texture[0] = m_renderer->CreatePngTexture("./Resources/station.png");
	m_texture[1] = m_renderer->CreatePngTexture("./Resources/station2.png");
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

void SceneMgr::AddObject(float x, float y)
{
	if (m_coolTime>2.0f && y<=0) {

		m_coolTime = 0;
		Transform newPos = { x,y,0 };
		Object* newObject = new Object(newPos, { 0,0,1,1 }, m_renderer, OBJECT_CHARACTER, TEAM_2);
		m_objectList.push_back(newObject);
	}
}
void SceneMgr::AI()
{
	if (m_spawnTime > 1.0f)
	{
		Transform newPos = { (rand()%WINDOW_WIDTH) - 250,rand() % (WINDOW_HEIGHT / 2),0 };
		Object* newObject = new Object(newPos, { 1,0,0,1 }, m_renderer, OBJECT_CHARACTER, TEAM_1);
		m_objectList.push_back(newObject);
		m_spawnTime = 0;
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
	m_spawnTime += elapsedTime;
	m_coolTime += elapsedTime;
	srand(time(NULL));


	Transform* s_collider = nullptr;
	Transform* o_collider = nullptr;
	Transform* b_collider = nullptr;
	Transform* a_collider = nullptr;
	Color buildingColor = { 1,0,1,1 };
	AI();
	for (auto object : m_objectList)
	{
		object->CreateArrow(elapsedTime);
		object->Update(elapsedTime);
		for (auto arrow : object->m_arrowList)
		{
			arrow->Update(elapsedTime);
		}
	}
	Transform* sta_collider;
	Transform* com_collider;
	for(auto standard:m_objectList){
		sta_collider = standard->GetCollider();
		if (standard->GetType() == OBJECT_BUILDING)
		{
			for (auto compare : m_objectList) {
				com_collider = compare->GetCollider();
				if (BoxCollision(sta_collider, com_collider) && standard->GetTeam() != compare->GetTeam())
				{
					standard->Damage(compare->GetLife());
					compare->Damage(standard->GetLife());
				}
				Transform* bul_collider;
				for(auto bullet : standard->m_arrowList)
				{
					bul_collider = bullet->GetCollider();
					if (BoxCollision(com_collider, bul_collider) && compare->GetTeam() != bullet->GetTeam())
					{
						bullet->Damage(compare->GetLife());
						compare->Damage(bullet->GetLife());
					}
				}
			}
		}
		else {
			Transform* arr_collider;
			for (auto arrow : standard->m_arrowList)
			{
				arr_collider = arrow->GetCollider();
				Transform* obj_collider;
				for (auto object : m_objectList)
				{
					obj_collider = object->GetCollider();
					if (BoxCollision(obj_collider, arr_collider) && object->GetTeam() != arrow->GetTeam()) 
					{
						arrow->Damage(object->GetLife());
						object->Damage(arrow->GetLife());
					}
				}
			}
		}
	}
	Delete();
	Render();
}

void SceneMgr::Render()
{
	for (auto data : m_objectList)
	{
		if (data->GetTeam() == TEAM_1 && data->GetType() == OBJECT_BUILDING)
			data->Render(m_texture[1]);
		else if (data->GetTeam() == TEAM_2 && data->GetType() == OBJECT_BUILDING)
			data->Render(m_texture[0]);
		else
			data->Render();
	}
}

void SceneMgr::Delete()
{
	for (vector<Object*>::iterator iter = m_objectList.begin();iter != m_objectList.end();)
	{
		Object* object = *iter;
		if (object->isDead)
		{
			//cout << "object delete"  << endl;
			iter = m_objectList.erase(iter);
		}
		else
		{
			for (auto arrowIter = object->m_arrowList.begin();arrowIter != object->m_arrowList.end();)
			{
				Object* arrow = *arrowIter;
				if (arrow->isDead)
				{
					arrowIter = object->m_arrowList.erase(arrowIter);
				}
				else
					arrowIter++;
			}
			++iter;
		}
	}
}

