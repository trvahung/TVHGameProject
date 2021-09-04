#pragma once
#include "AnimationSprite.h"
class Bomb :
    public AnimationSprite
{
public:
	Bomb() : AnimationSprite() {};
	Bomb(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader,
		std::shared_ptr<Texture> texture, int numFrame, float frameTime);
	~Bomb();
	void Explode(float deltatime);
	float m_time;
};

#define EXPLODE_TIME 2