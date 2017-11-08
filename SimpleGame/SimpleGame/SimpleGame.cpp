/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
//#include "Object.h"
#include "SceneMgr.h"

//Renderer *g_Renderer = NULL;
SceneMgr* g_sceneMgr=NULL;



void init() {
	srand((unsigned)time(NULL));
	g_sceneMgr = new SceneMgr();
	
		/*g_Renderer = new Renderer(WINDOW_WIDTH, WINDOW_HEIGHT);
		if (!g_Renderer->IsInitialized())
		{
			std::cout << "Renderer could not be initialized.. \n";
		}
		g_sceneMgr = new SceneMgr(g_Renderer);*/
		//g_sceneManager->AddObject();

}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	// Renderer Test
	//g_Renderer->DrawSolidRect(0, 0, 0, 10, 1, 1, 1, 1);	
	//x,y,z,ÇÈ¼¿Å©±â,RGB
	g_sceneMgr->Render();
	glutSwapBuffers();
}

void Idle(void)
{
	g_sceneMgr->Update();
	RenderScene();
}
void MouseInput(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_sceneMgr->AddObject(x, y, { 1,1,1,1 },10,OBJECT_CHARACTER,10, { 100 ,100 ,0 });
	}
	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	//g_Renderer = new Renderer(500, 500);
	//if (!g_Renderer->IsInitialized())
	//{
	//	std::cout << "Renderer could not be initialized.. \n";
	//}
	
	init();

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	//delete g_Renderer;

    return 0;
}

