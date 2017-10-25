#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include<iostream>
#include<vector>
#include "Renderer.h"
#include<random>
#include<ctime>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

using namespace std;

struct Transform
{
	float x;
	float y;
	float z;
	Transform operator-(Transform& param)
	{
		Transform result;
		result.x = x - param.x;
		result.y = y - param.y;
		result.z = z - param.z;
	}
};
struct Color
{
	float r;
	float g;
	float b;
	float a;
};