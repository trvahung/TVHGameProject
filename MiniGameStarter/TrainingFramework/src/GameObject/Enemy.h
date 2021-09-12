#pragma once
#include "../AnimationSprite.h"
class Enemy : public AnimationSprite {
public:
	Enemy() : AnimationSprite(), m_speed(20) {};
	Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader,
		std::shared_ptr<Texture> texture, int numFrame, float frameTime, int score);
	~Enemy();
	void Move(float x, float y,int score, float deltatime);
	Vector3 GetPosition();

protected:
	float m_speed;
};

#define BASE_SPEED	10
#define SPEED_UP	0.1f
