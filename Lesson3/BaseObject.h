#pragma once
typedef struct Position {
	float pos_x;
	float pos_y;
} Position;

class BaseObject {
public:
	int id;
	char* name;
	Position position;
	BaseObject();
	~BaseObject();
	virtual char* getName();
	virtual int getid();
	virtual void move();
	virtual void printPosition();
};