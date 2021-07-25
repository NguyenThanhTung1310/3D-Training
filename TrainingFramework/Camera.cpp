#include"stdafx.h"
#include"Camera.h"
#include "../Utilities/utilities.h"
#include"math.h"
#include"Globals.h"
#include<iostream>
void Camera::initCamera() {
	back = 100.0f;
	front = 0.1f;
	FOV = 45.0f;
	position.x = 0.0f; position.y = 0.0f; position.z = -2.0f;
	target.x = 0.0f; target.y = 0.0f; target.z = -1.0f;
	up.x = 0.0f; up.y = 1.0f; up.z = 0.0f;
	Wup = up;
	right = target.Cross(Wup).Normalize();

	zAxis = (position - target).Normalize();
	xAxis = (up.Cross(zAxis)).Normalize();
	yAxis = (zAxis.Cross(xAxis)).Normalize();
}
void Camera::updateCamera(float deltaTime) {
	
	//Vector3 deltaMove = -(position - target).Normalize() * deltaTime * speedCamera;
	//position += deltaMove;
	//target += deltaMove;

	right = target.Cross(Wup).Normalize();
	up = right.Cross(target).Normalize();

	zAxis = (position - target).Normalize();
	xAxis = (up.Cross(zAxis)).Normalize();
	yAxis = (zAxis.Cross(xAxis)).Normalize();

	setRotationCamera();
	setTransCamera();
	setWorldMatrixCamera();
	setViewMatrixCamera();
	setPerspectiveMatrixCamera();
	setWVP();
}
void Camera::setRotationCamera() {
	RotationCamera.m[0][0] = xAxis.x; RotationCamera.m[0][1] = xAxis.y; RotationCamera.m[0][2] = xAxis.z; RotationCamera.m[0][3] = 0;
	RotationCamera.m[1][0] = yAxis.x; RotationCamera.m[1][1] = yAxis.y; RotationCamera.m[1][2] = yAxis.z; RotationCamera.m[1][3] = 0;
	RotationCamera.m[2][0] = zAxis.x; RotationCamera.m[2][1] = zAxis.y; RotationCamera.m[2][2] = zAxis.z; RotationCamera.m[2][3] = 0;
	RotationCamera.m[3][0] = 0;	   RotationCamera.m[3][1] = 0;		  RotationCamera.m[3][2] = 0;		 RotationCamera.m[3][3] = 1;
}
void Camera::setTransCamera() {
	TransCamera.m[0][0] = 1; TransCamera.m[0][1] = 0; TransCamera.m[0][2] = 0; TransCamera.m[0][3] = 0;
	TransCamera.m[1][0] = 0; TransCamera.m[1][1] = 1; TransCamera.m[1][2] = 0; TransCamera.m[1][3] = 0;
	TransCamera.m[2][0] = 0; TransCamera.m[2][1] = 0; TransCamera.m[2][2] = 1; TransCamera.m[2][3] = 0;
	TransCamera.m[3][0] = position.x; TransCamera.m[3][1] = position.y; TransCamera.m[3][2] = position.z; TransCamera.m[3][3] = 1;
}
void Camera::setWorldMatrixCamera() {
	WorldCamera = RotationCamera * TransCamera;
}
void Camera::setViewMatrixCamera() {
	Matrix view;
	view.m[0][0] = xAxis.x; view.m[0][1] = yAxis.x; view.m[0][2] = zAxis.x; view.m[0][3] = 0;
	view.m[1][0] = xAxis.y; view.m[1][1] = yAxis.y; view.m[1][2] = zAxis.y; view.m[1][3] = 0;
	view.m[2][0] = xAxis.z; view.m[2][1] = yAxis.z; view.m[2][2] = zAxis.z; view.m[2][3] = 0;
	view.m[3][0] = -position.Dot(xAxis); view.m[3][1] = -position.Dot(yAxis); view.m[3][2] = -position.Dot(zAxis); view.m[3][3] = 1;
	ViewCamera = view;
}
void Camera::setPerspectiveMatrixCamera() {
	float aspect = (float)Globals::screenWidth / Globals::screenHeight;
	Matrix perspective;
	perspective.SetPerspective(FOV * 3.14/180, aspect, back, front);
	PerspectiveCamera = perspective;
}
void Camera::setWVP() {
	WVP = WorldCamera * ViewCamera * PerspectiveCamera;
}

void Camera::isKeyPressed(unsigned char key, float deltaTime) {
	float velocity = cameraSpeed * deltaTime;
	if (key == 'a' || key == 'A') {
		position += target * velocity;
		target += target * velocity;
	}
		
	if (key == 'd' || key == 'D') {
		position -= target * velocity;
		target -= target * velocity;
	}
		
	if (key == 'w' || key == 'W') {
		position += right * velocity;
		target += right * velocity;
	}
		
	if (key == 's' || key == 'S') {
		position -= right * velocity;
		target -= right * velocity;
	}
		
}