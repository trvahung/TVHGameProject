#include "DynamicObject.h"
#include <stdio.h>
void DynamicObject::move() {
	printf("Nhap vi tri x:");
	scanf("%f", &position.pos_x);
	printf("Nhap vi tri y:");
	scanf("%f", &position.pos_y);
	printf("Da di chuyen\n");
};