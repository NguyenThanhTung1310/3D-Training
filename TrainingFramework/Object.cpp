#include "../Utilities/utilities.h"
#include "Math.h"
#include"stdafx.h"
#include"Object.h"
#include"Camera.h"


Matrix Object::setRotation() {
	return rX * rY * rZ;
}

Matrix Object::setWorld() {
	return scale * rotation * trans;
}
void Object::initObject() {
	rX.SetRotationX(0);
	rY.SetRotationY(3.14);
	rZ.SetRotationZ(0);

	scale.SetScale(1, 1, 1);
	rotation = rX * rY * rZ;
	trans.SetTranslation(0.0, 0.0, 0.0);

	world = scale * rotation * trans;
}

Object::Object() {
	
}
Object::~Object() {

}