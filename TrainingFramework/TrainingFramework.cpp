// TrainingFramework.cpp : Defines the entry point for the console application.
//


#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "stdafx.h"
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "Texture.h"
#include "Model.h"
#include "Object.h"
#include"Camera.h"
#include<iostream>

Shaders shaders;
Texture *texture = new Texture();
Model *model = new Model();
Object* object = new Object();
Camera* camera = new Camera();
Matrix a;
GLfloat angle = 180.0f;

int Init ( ESContext *esContext )
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	texture->initTexture("../Texture/Woman2.tga");
	model->initNFG("../Model/Woman2.nfg");
	object->initObject();
	object->rY.SetRotationY(angle);
	camera->initCamera();
	camera->setWorldMatrixCamera();
	camera->setViewMatrixCamera();
	return shaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
}

void Draw ( ESContext *esContext )
{
	glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaders.program);

	glBindTexture(GL_TEXTURE_2D, texture->TextureId);
	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
	if (shaders.positionAttribute != -1)
	{
		glVertexAttribPointer(shaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glEnableVertexAttribArray(shaders.positionAttribute);
	}
	if (shaders.uvLoc != -1)
	{
		glUniform1i(shaders.textureUniform, 0);
		glVertexAttribPointer(shaders.uvLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)));
		glEnableVertexAttribArray(shaders.uvLoc);
	}
	
	glUniformMatrix4fv(shaders.u_projection, 1, GL_FALSE, (const GLfloat*)camera->PerspectiveCamera.m);
	glUniformMatrix4fv(shaders.u_view, 1, GL_FALSE, (const GLfloat*)camera->ViewCamera.m);
	glUniformMatrix4fv(shaders.u_transLoc, 1, GL_FALSE, (const GLfloat*)object->world.m);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboID);
	glDrawElements(GL_TRIANGLES, model->numberOfIndices, GL_UNSIGNED_INT, 0);
		
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update ( ESContext *esContext, float deltaTime )
{
	camera->updateCamera(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{	
	float deltaTime = 0.5;
	if (bIsPressed == true) {
		camera->isKeyPressed(key, deltaTime);
	}
}

void CleanUp()
{
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

