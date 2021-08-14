#include "ClassLesson3.h"
#include <stdio.h>

using namespace MyClass;
BaseObject::BaseObject() {
	name = new char[20];
}
BaseObject::~BaseObject() {
	delete[] name;
}
int BaseObject:: getid() {
	return id;
}
char* BaseObject::getName() {
	return name;
}
void BaseObject::printPosition() {
	printf("Vi tri: x= %f, y= %f\n", position.pos_x, position.pos_y);
}
void BaseObject::move() {};
void StaticObject::move() {
	printf("Vat nay khong the di chuyen\n");
};
void DynamicObject::move() {
	printf("Nhap vi tri x:");
	scanf("%f", &position.pos_x);
	printf("Nhap vi tri y:");
	scanf("%f", &position.pos_y);
	printf("Da di chuyen\n");
};