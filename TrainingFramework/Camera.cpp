#include"stdafx.h"
#include"Camera.h"
#include "../Utilities/utilities.h"
#include"math.h"
#include"Globals.h"
#include<iostream>
void Camera::initCMR() {
	m_far = 100.0f;
	m_near = 0.1f;
	m_FOV = 45.0f;
	position.x = 0.0f; position.y = 0.0f; position.z = -4.0f;
	target.x = 0.0f; target.y = 0.0f; target.z = -1.0f;
	up.x = 0.0f; up.y = 1.0f; up.z = 0.0f;
	Wup = up;
	right = target.Cross(Wup).Normalize();

	zasis = (position - target).Normalize();
	xasis = (up.Cross(zasis)).Normalize();
	yasis = (zasis.Cross(xasis)).Normalize();
}
void Camera::updateCMR(float deltaTime) {
	

	
	//Vector3 deltaMove = -(position - target).Normalize() * deltaTime * speedCamera;
	//position += deltaMove;
	//target += deltaMove;

	right = target.Cross(Wup).Normalize();
	up = right.Cross(target).Normalize();

	zasis = (position - target).Normalize();
	xasis = (up.Cross(zasis)).Normalize();
	yasis = (zasis.Cross(xasis)).Normalize();

	setRotationCMR();
	setTranslationCMR();
	setWorldMatrixCMR();
	setViewMatrixCMR();
	setPerspectiveMatrixCMR();
	setWVP();
}
void Camera::setRotationCMR() {
	Rcm.m[0][0] = xasis.x; Rcm.m[0][1] = xasis.y; Rcm.m[0][2] = xasis.z; Rcm.m[0][3] = 0;
	Rcm.m[1][0] = yasis.x; Rcm.m[1][1] = yasis.y; Rcm.m[1][2] = yasis.z; Rcm.m[1][3] = 0;
	Rcm.m[2][0] = zasis.x; Rcm.m[2][1] = zasis.y; Rcm.m[2][2] = zasis.z; Rcm.m[2][3] = 0;
	Rcm.m[3][0] = 0;	   Rcm.m[3][1] = 0;		  Rcm.m[3][2] = 0;		 Rcm.m[3][3] = 1;
}
void Camera::setTranslationCMR() {
	Tcm.m[0][0] = 1; Tcm.m[0][1] = 0; Tcm.m[0][2] = 0; Tcm.m[0][3] = 0;
	Tcm.m[1][0] = 0; Tcm.m[1][1] = 1; Tcm.m[1][2] = 0; Tcm.m[1][3] = 0;
	Tcm.m[2][0] = 0; Tcm.m[2][1] = 0; Tcm.m[2][2] = 1; Tcm.m[2][3] = 0;
	Tcm.m[3][0] = position.x; Tcm.m[3][1] = position.y; Tcm.m[3][2] = position.z; Tcm.m[3][3] = 1;
}
void Camera::setWorldMatrixCMR() {
	WCMR = Rcm * Tcm;
}
void Camera::setViewMatrixCMR() {
	Matrix tmp;
	tmp.m[0][0] = xasis.x; tmp.m[0][1] = yasis.x; tmp.m[0][2] = zasis.x; tmp.m[0][3] = 0;
	tmp.m[1][0] = xasis.y; tmp.m[1][1] = yasis.y; tmp.m[1][2] = zasis.y; tmp.m[1][3] = 0;
	tmp.m[2][0] = xasis.z; tmp.m[2][1] = yasis.z; tmp.m[2][2] = zasis.z; tmp.m[2][3] = 0;
	tmp.m[3][0] = -position.Dot(xasis); tmp.m[3][1] = -position.Dot(yasis); tmp.m[3][2] = -position.Dot(zasis); tmp.m[3][3] = 1;
	VCMR = tmp;
}
void Camera::setPerspectiveMatrixCMR() {
	float aspect = (float)Globals::screenWidth / Globals::screenHeight;
	Matrix perspective;
	perspective.SetPerspective(m_FOV * 3.14/180, aspect, m_near, m_far);
	PCMR = perspective;
}
void Camera::setWVP() {
	WVP = WCMR * VCMR * PCMR;
}

void Camera::isPressKeyEvent(unsigned char key, float deltaTime) {
	float velocity = speedCamera * deltaTime;
	if (key == 'a' || key == 'A') {
		std::cout << "a";
		position += target * velocity;
		target += target * velocity;

	}
		
	if (key == 'D' || key == 'd')
	{
		std::cout << "d";
		position -= target * velocity;
		target -= target * velocity;
	}
		
	if (key == 'W' || key == 'w') {
		std::cout << "w";
		position += right * velocity;
		target += right * velocity;
	}
		
	if (key == 's' || key == 'S') {
		std::cout << "s";
		position -= right * velocity;
		target -= right * velocity;
	}
		

}