// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "Texture.h"
#include "Model.h"
#include <iostream>

Shaders myShaders;
Texture *myTexture = new Texture();
Model *myModel = new Model();

int Init ( ESContext *esContext )
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	myTexture->initTexture("../Texture/Woman1.tga");
	glBindTexture(GL_TEXTURE_2D, myTexture->TextureId);
	myModel->initNFG("../Model/Woman1.nfg");
	glBindBuffer(GL_ARRAY_BUFFER, myModel->m_vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myModel->m_iboID);
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
}

void Draw ( ESContext *esContext )
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(myShaders.program);

	glBindBuffer(GL_ARRAY_BUFFER, myModel->m_vboId);
	glBindTexture(GL_TEXTURE_2D, myTexture->TextureId);

	if (myShaders.positionAttribute != -1)
	{
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glEnableVertexAttribArray(myShaders.positionAttribute);
	}
	if (myShaders.uvLoc != -1)
	{
		glVertexAttribPointer(myShaders.uvLoc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)));
		glEnableVertexAttribArray(myShaders.uvLoc);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myModel->m_iboID);
	glDrawElements(GL_TRIANGLES, myModel->numberOfIndice, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update ( ESContext *esContext, float deltaTime )
{

}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{

}

void CleanUp()
{
	glBindBuffer(1, myModel->m_vboId);
	glDeleteBuffers(1, &myModel->m_vboId);

	glBindBuffer(1, myModel->m_iboID);
	glDeleteBuffers(1, &myModel->m_iboID);

	glBindTexture(1, myTexture->TextureId);
	glDeleteTextures(1, &myTexture->TextureId);
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

