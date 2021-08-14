#pragma once
namespace MyClass
{
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

	class StaticObject : public BaseObject {
	public:
		void move();
	};

	class DynamicObject : public BaseObject {
	public:
		void move();
	};

	class Tree : public StaticObject{};
	class House: public StaticObject{};
	class Motorbike : public DynamicObject {};;
	class Car :public DynamicObject {};
}