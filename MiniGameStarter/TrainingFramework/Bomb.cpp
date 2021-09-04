#include "Bomb.h"

#include "GameManager/ResourceManagers.h"

Bomb::Bomb(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader,
	std::shared_ptr<Texture> texture, int numFrame, float frameTime)
	: AnimationSprite(model, shader, texture, numFrame, frameTime), m_time(0)
{
}

Bomb::~Bomb()
{
}

void Bomb::Explode(float deltatime) {
	m_numFrames = 10;
	auto texture = ResourceManagers::GetInstance()->GetTexture("Explode.tga");
	this->SetTexture(texture);
	this->SetSize(150, 150);
	Update(deltatime);
}