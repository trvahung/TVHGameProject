#include <iostream>
#include "Tree.h"
#include "House.h"
#include "Motorbike.h"
#include "Car.h"
#include <list>
#include <memory>
#include <string>


static std::list<std::shared_ptr<BaseObject>> listObj;

void CreateObject(int n) {
	for (int i = 0; i < n; i++)
	{
		char* index;
		std::shared_ptr<BaseObject> A = std::make_shared<BaseObject>();
		
		switch (i % 4) {
		case 0:
			A = std::make_shared<Tree>();
			strcpy(A->name, "Tree");
			break;
		case 1:
			A = std::make_shared<House>();
			strcpy(A->name, "House");
			break;
		case 2:
			A = std::make_shared<Motorbike>();
			strcpy(A->name, "Motorbike");
			break;
		case 3:
			A = std::make_shared<Car>();
			strcpy(A->name, "Car");
			break;
		}
		A->id = i+1;
		listObj.push_back(A);
	}
}
int main()
{
	int n;
	
	printf("Tao bao nhieu object:");
	scanf("%d", &n);
	CreateObject(n);
	for (auto obj : listObj) {
		obj->getName();
		//printf("Object thu %d co ten la: %s\n", obj->id, obj->getName());
	}
	for (auto obj : listObj) {
		obj->move();
	}
	for (auto obj : listObj) {
		obj->printPosition();
	}
	listObj.clear();
}
