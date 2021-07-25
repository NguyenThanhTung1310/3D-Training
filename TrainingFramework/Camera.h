#pragma once
#include"../Utilities/utilities.h"
class Camera {
public:
	float cameraSpeed = 1.0f;
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 Wup;
	Vector3 right;

	GLfloat FOV;
	GLfloat front;
	GLfloat back;
	Matrix RotationCamera;
	Matrix TransCamera;
	Matrix WorldCamera;
	Matrix ViewCamera;
	Matrix PerspectiveCamera;
	Matrix WVP;

	Vector3 xAxis;
	Vector3 yAxis;
	Vector3 zAxis;
	void initCamera();
	void updateCamera(float deltaTime);
	void setRotationCamera();
	void setTransCamera();
	void setWorldMatrixCamera();
	void setViewMatrixCamera();
	void setPerspectiveMatrixCamera();
	void setWVP();
	void isKeyPressed(unsigned char key, float deltaTime);
};