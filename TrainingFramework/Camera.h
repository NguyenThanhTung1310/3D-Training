#pragma once
#include"../Utilities/utilities.h"
class Camera {
public:
	float speedCamera = 1.0f;
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 Wup;
	Vector3 right;

	GLfloat m_FOV;
	GLfloat m_near;
	GLfloat m_far;
	Matrix Rcm;
	Matrix Tcm;
	Matrix WCMR;
	Matrix VCMR;
	Matrix PCMR;
	Matrix WVP;

	Vector3 xasis;
	Vector3 yasis;
	Vector3 zasis;
	void initCMR();
	void updateCMR(float deltaTime);
	void setRotationCMR();
	void setTranslationCMR();
	void setWorldMatrixCMR();
	void setViewMatrixCMR();
	void setPerspectiveMatrixCMR();
	void setWVP();
	void isPressKeyEvent(unsigned char key, float deltaTime);
};