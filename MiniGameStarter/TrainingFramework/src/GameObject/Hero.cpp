#include "Hero.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "../GameManager/ResourceManagers.h"

Hero::Hero(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader,
	std::shared_ptr<Texture> texture, int numFrame, float frameTime)
	: AnimationSprite(model,shader,texture,numFrame,frameTime),m_face(true)
{
}

Hero::~Hero()
{
}

void Hero::NoMove(float deltatime) {
	m_numFrames = 13;
	auto texture = ResourceManagers::GetInstance()->GetTexture("NoMove.tga");
	this->SetTexture(texture);
	Update(deltatime);
}

void Hero::MoveDown(float deltatime) {
	m_numFrames = 8;
	auto texture = ResourceManagers::GetInstance()->GetTexture("MoveLeft.tga");
	if (m_face) {
		texture = ResourceManagers::GetInstance()->GetTexture("MoveRight.tga");
	}
	this->SetTexture(texture);
	Update(deltatime);
	if (m_position.y + m_scale.y / 2 <= Globals::screenHeight) {
		this->Set2DPosition(m_position.x, m_position.y + HERO_SPEED *deltatime);
	}
}

void Hero::MoveUp(float deltatime) {
	m_numFrames = 8;
	auto texture = ResourceManagers::GetInstance()->GetTexture("MoveUp.tga");
	this->SetTexture(texture);
	Update(deltatime);
	if (m_position.y - m_scale.y / 2 +10>= 0) {
		this->Set2DPosition(m_position.x, m_position.y - HERO_SPEED * deltatime);
	}
}

void Hero::MoveRight(float deltatime) {
	m_numFrames = 8;
	auto texture = ResourceManagers::GetInstance()->GetTexture("MoveRight.tga");
	this->SetTexture(texture);
	Update(deltatime);
	if (m_position.x + m_scale.x / 2 -10<= Globals::screenWidth) {
		this->Set2DPosition(m_position.x + HERO_SPEED * deltatime, m_position.y);
	}
	m_face = true;
}

void Hero::MoveLeft(float deltatime) {
	m_numFrames = 8;
	auto texture = ResourceManagers::GetInstance()->GetTexture("MoveLeft.tga");
	this->SetTexture(texture);
	Update(deltatime);
	if (m_position.x - m_scale.x / 2 +10>= 0) {
		this->Set2DPosition(m_position.x - HERO_SPEED * deltatime, m_position.y);
	}
	m_face = false;
}

void Hero::SetBomb(float deltatime) {
	m_numFrames = 6;
	auto texture = ResourceManagers::GetInstance()->GetTexture("SetBomb.tga");
	this->SetTexture(texture);
	Update(deltatime);
}

Vector3 Hero::GetPosition() {
	return m_position;
}