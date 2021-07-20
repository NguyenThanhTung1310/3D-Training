#include"stdafx.h"
#include"Model.h"
#include"Object.h"
#include<iostream>

void Model::initNFG(char* fileName) {

	FILE* file;
	file = fopen(fileName, "r");
	if (file) std::cout << "load nfg thanh cong";
	int NrVertices, Nindices;
	float posX, posY, posZ;
	float normX, normY, normZ;
	float binormX, binormY, binormZ;
	float tgtX, tgtY, tgtZ;
	float uvX, uvY;
	int id;
	
	fscanf(file, "NrVertices: %d\n", &NrVertices);
	Vertex *veticalData = new Vertex[NrVertices];
	for (int i = 0; i < NrVertices; i++) {
		fscanf(file, "%d. ", &id);
		fscanf(file, "pos:[%f, %f, %f]; ", &posX, &posY, &posZ);
		fscanf(file, "norm:[%f, %f, %f]; ", &normX, &normY, &normZ);
		fscanf(file, "binorm:[%f, %f, %f]; ", &binormX, &binormY, &binormZ);
		fscanf(file, "tgt:[%f, %f, %f]; ", &tgtX, &tgtY, &tgtZ);
		fscanf(file, "uv:[%f, %f];\n ", &uvX, &uvY);
		veticalData[i].pos.x = posX;
		veticalData[i].pos.y = posY;
		veticalData[i].pos.z = posZ;
		veticalData[i].u_v.x = uvX;
		veticalData[i].u_v.y = uvY;
		//listVerticalData.push_back(&veticalData[i]);
	}
	glGenBuffers(1, &this->m_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_vboId);
	for (int i = 0; i < NrVertices; i++) {
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* NrVertices, veticalData, GL_STATIC_DRAW);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	fscanf(file, "NrIndices: %d\n", &Nindices);
	int iX, iY, iZ;
	numberOfIndice = Nindices;
	int *indices = new int[Nindices];
	for (int i = 0; i < Nindices; i += 3) {
		fscanf(file, "%d. ", &id);
		fscanf(file, " %d, %d, %d\n", &iX, &iY, &iZ);
		indices[i] = iX;
		indices[i + 1] = iY;
		indices[i + 2] = iZ;
	}
	glGenBuffers(1, &this->m_iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Nindices * sizeof(int), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
Model::Model() {

}
Model::~Model() {

}