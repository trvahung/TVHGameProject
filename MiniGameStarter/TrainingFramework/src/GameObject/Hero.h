#pragma once
#include "../AnimationSprite.h"
class Hero : public AnimationSprite {
public:
	Hero() : AnimationSprite(),m_face(true) {};
	Hero(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader,
		std::shared_ptr<Texture> texture, int numFrame, float frameTime);
	~Hero();
	void MoveRight(float deltatime);
	void MoveLeft(float deltatime);
	void MoveDown(float deltatime);
	void MoveUp(float deltatime);
	void SetBomb(float deltatime);
	void NoMove(float deltatime);
	Vector3 GetPosition();
protected:
	bool m_face;
};

#define HERO_SPEED 500