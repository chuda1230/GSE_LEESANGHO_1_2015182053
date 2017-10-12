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
#include "Object.h"
#include "Unit.h"

//Renderer *g_Renderer = NULL;
Object* objects[10];
Unit* unit[10];
int current=0,u_current=0;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	
	for (int i = 0;i < current;++i)
	{
		objects[i] -> Render();
		
	}
	for (int i = 0;i < u_current;++i) 
	{
		unit[i]->u_Render();
		unit[i]->u_Update();
	}
	// Renderer Test
	//g_Renderer->DrawSolidRect(0, 0, 0, 10, 1, 1, 1, 1);	
	//x,y,z,ÇÈ¼¿Å©±â,RGB

	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	bool g_Leftbuttondown = true;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		g_Leftbuttondown = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		if (g_Leftbuttondown) {
			Unit* newunit = new Unit({ 50,-20,0 }, { 255,0,0,1 }, 10, 0.2, 0.2);
			unit[u_current] = newunit;
			u_current++;
		}
		g_Leftbuttondown = false;
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


	Object* newobject = new Object({ -250,-200,0 }, { 0.0,3.0,2.0,1 }, 50,150);
	objects[current] = newobject;
	current++;

	newobject = new Object({ 250,-200,0 }, { 0.0,3.0,2.0,1 }, 50,150);
	objects[current] = newobject;
	current++;

	newobject = new Object({ 250,200,0 }, { 0,255,0,1 }, 50,150);
	objects[current] = newobject;
	current++;

	newobject = new Object({ -250,200,0 }, { 0,255,0,1 }, 50,150);
	objects[current] = newobject;
	current++;
	
	Unit* newunit = new Unit({ 50,-20,0 }, {255,0,0,1 }, 10,0.2,0.2);
	unit[u_current] = newunit;
	u_current++;
	

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	glutMainLoop();

	//delete g_Renderer;

    return 0;
}

