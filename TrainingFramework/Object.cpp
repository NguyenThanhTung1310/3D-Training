#include "../Utilities/utilities.h"
#include "Math.h"
#include"stdafx.h"
#include"Object.h"
#include"Camera.h"


Matrix Object::setRotation() {
	return Rz * Rx * Ry;
}

Matrix Object::setWordl() {
	return scale * rotation * trans;
}
void Object::InitObject() {
	Rx.SetRotationX(0);
	Ry.SetRotationY(3.14);
	Rz.SetRotationZ(0);

	scale.SetScale(1, 1, 1);
	rotation = Rz * Rx * Ry;
	trans.SetTranslation(0.0, 0.0, 0.0);

	wordl = scale * rotation * trans;
}

Object::Object() {
	
}
Object::~Object() {

}