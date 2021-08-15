#include "BaseObject.h"
#include <stdio.h>
BaseObject::BaseObject() {
	name = new char[20];
}
BaseObject::~BaseObject() {
	delete[] name;
}
int BaseObject::getid() {
	return id;
}
char* BaseObject::getName() {
	return name;
}
void BaseObject::printPosition() {
	printf("Vi tri: x= %f, y= %f\n", position.pos_x, position.pos_y);
}
void BaseObject::move() {};