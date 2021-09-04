#include "Enemy.h"
#include <math.h>

Enemy::Enemy(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader,
	std::shared_ptr<Texture> texture, int numFrame, float frameTime, int score)
	: AnimationSprite(model, shader, texture,numFrame,frameTime), m_speed(BASE_SPEED+score*SPEED_UP)
{
}

Enemy::~Enemy()
{
}

Vector3 Enemy::GetPosition() {
	return m_position;
}

void Enemy::Move(float x, float y,int score, float deltatime) {
	Update(deltatime);
	float a = (y - m_position.y) / (x - m_position.x);
	float b = y - a * x;
	m_speed = BASE_SPEED + score * SPEED_UP;
	float s = m_speed * deltatime;
	if (x >= m_position.x) { m_position.x += s / sqrt(a * a + 1); }
	else { m_position.x -= s / sqrt(a * a + 1); }
	m_position.y = m_position.x * a + b;
	this->Set2DPosition(m_position.x, m_position.y);
}