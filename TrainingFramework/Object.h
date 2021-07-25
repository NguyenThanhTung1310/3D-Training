#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
//#include "../Utilities/Math.h"
#include"Shaders.h"
#include<vector>
using namespace std;
//#include "Math.h"

class Object {
public:
	Matrix rX;
	Matrix rY;
	Matrix rZ;

	Matrix scale;
	Matrix rotation;
	Matrix trans;

	Matrix world;
	
	Matrix WVP;


	Matrix setRotation();

	Matrix setWorld();
	Matrix setView();
	


	void initObject();
	Object();
	~Object();



};