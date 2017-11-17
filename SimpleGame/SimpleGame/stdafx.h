#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include<iostream>
#include<vector>
#include "Renderer.h"
#include<random>
#include<ctime>
#include<Windows.h>
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 800

using namespace std;

struct Transform
{
	float x;
	float y;
	float z;
	Transform operator-(float param)
	{
		Transform result;
		result.x = x - param;
		result.y = y - param;
		result.z = z - param;
		return result;
	}
	bool operator==(Transform& param)
	{
		if (x == param.x&&y == param.y&&z == param.z)
		{
			return true;
		}
		return false;
	}
};
struct Color
{
	float r;
	float g;
	float b;
	float a;
};