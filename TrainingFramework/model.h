#pragma once
#include"../Utilities/utilities.h"
#include<vector>
#include"Vertex.h"
#include<string>
using namespace std;
class Model {
public:
	//vector<Vertex*> listVerticalData;
	int numberOfIndices;
	void initNFG(char* fileName);
	GLuint vboId;
	GLuint iboID;
	Model();
	~Model();
};