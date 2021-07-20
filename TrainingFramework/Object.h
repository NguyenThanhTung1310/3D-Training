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
	vector<Object*> listObj;

	Matrix Rx;
	Matrix Ry;
	Matrix Rz;

	Matrix scale;
	Matrix rotation;
	Matrix trans;

	Matrix wordl;
	
	Matrix WVP;


	Matrix setRotation();

	Matrix setWordl();
	//Matrix setView();
	


	void InitObject();
	Object();
	~Object();



};