#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "../GameObject/Hero.h"
#include "../GameObject/Enemy.h"
#include "../Bomb.h"
#include <string>
#include <cstdlib>
#include <math.h>

GSPlay::GSPlay(): m_time(10), m_score(0), m_bomb(true), m_State(true)
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	m_time = 10;
	m_score = 0;
	m_bomb = false;
	m_State = true;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play1.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button clode
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	//button pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	std::shared_ptr<GameButton>  buttonPause = std::make_shared<GameButton>(model, shader, texture);
	buttonPause->Set2DPosition(50, 50);
	buttonPause->SetSize(50, 50);
	buttonPause->SetOnClick([]() {
		GameStateMachine::GetInstance()->CurrentState()->Pause();
		});
	m_listButton.push_back(buttonPause);

	//Hero
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("NoMove.tga");
	m_hero = std::make_shared<Hero>(model, shader, texture, 13, 0.1f);
	m_hero->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_hero->SetSize(50, 50);

	//score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_Tscore = std::make_shared< Text>(shader, font, "score: " + std::to_string(m_score), TextColor::RED, 1.0);
	m_Tscore->Set2DPosition(Vector2(5, 25));

	//time
	m_time = 10;

}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
	m_State = !m_State;
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed == 1) {
		switch (key) {
		case 'A':
			m_keyPressed |= KEY_MOVE_LEFT;
			break;
		case 'D':
			m_keyPressed |= KEY_MOVE_RIGHT;
			break;
		case 'W':
			m_keyPressed |= KEY_MOVE_FORWORD;
			break;
		case 'S':
			m_keyPressed |= KEY_MOVE_BACKWORD;
			break;
		case ' ':
			m_keyPressed |= KEY_SET_BOMB;
			break;
		}
	}
	else {
		switch (key) {
		case 'A':
			m_keyPressed ^= KEY_MOVE_LEFT;
			break;
		case 'D':
			m_keyPressed ^= KEY_MOVE_RIGHT;
			break;
		case 'W':
			m_keyPressed ^= KEY_MOVE_FORWORD;
			break;
		case 'S':
			m_keyPressed ^= KEY_MOVE_BACKWORD;
			break;
		case ' ':
			m_keyPressed ^= KEY_SET_BOMB;
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	

	//Buttons
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	if (m_State) {
		//Play time
		m_time += deltaTime;

		//Hero
		if (m_keyPressed == 0) {
			m_hero->NoMove(deltaTime);
		}
		else {
			if (m_keyPressed & KEY_MOVE_LEFT) {
				m_hero->MoveLeft(deltaTime);
			}
			if (m_keyPressed & KEY_MOVE_RIGHT) {
				m_hero->MoveRight(deltaTime);
			}
			if (m_keyPressed & KEY_MOVE_FORWORD) {
				m_hero->MoveUp(deltaTime);
			}
			if (m_keyPressed & KEY_MOVE_BACKWORD) {
				m_hero->MoveDown(deltaTime);
			}
		}

		//Bomb
		if (m_keyPressed & KEY_SET_BOMB) {
			m_hero->SetBomb(deltaTime);
			m_bomb = true;
		}
		else if (m_bomb == true) {
			CreateBomb();
			m_bomb = false;
		}
		std::list<std::shared_ptr<Bomb>> destroyedBomb;
		destroyedBomb.clear();
		for (auto bomb : m_bombs) {
			bomb->m_time += deltaTime;
			if (bomb->m_time >= EXPLODE_TIME) {
				bomb->Explode(deltaTime);
			}
			if (bomb->m_time >= EXPLODE_TIME + 0.5f) {
				int k = 1;
				std::list<std::shared_ptr<Enemy>> destroyedEnemy;
				destroyedEnemy.clear();
				for (auto enemy : m_enemies) {
					GLfloat a = enemy->GetPosition().x - bomb->GetPosition().x;
					GLfloat b = enemy->GetPosition().y - bomb->GetPosition().y;
					if (sqrt(a * a + b * b) <= 75) {
						destroyedEnemy.push_back(enemy);
						m_score += k;
						k++;
					}
				}
				for (auto enemy : destroyedEnemy) {
					m_enemies.remove(enemy);
				}
				destroyedBomb.push_back(bomb);
			}
		}
		for (auto bomb : destroyedBomb) {
			m_bombs.remove(bomb);
		}
		//Enemies
		if (m_time >= ENEMY_CREATE_TIME) {
			CreateEnemy();
			m_score += 1;
			m_time -= ENEMY_CREATE_TIME;
		}
		for (auto enemy : m_enemies) {
			Vector3 pos = m_hero->GetPosition();
			enemy->Move(pos.x, pos.y, m_score, deltaTime);
			GLfloat a = enemy->GetPosition().x - pos.x;
			GLfloat b = enemy->GetPosition().y - pos.y;
			if (sqrt(a * a + b * b) <= 25) {
				FILE* f;
				f = fopen("score.sav", "r");
				int max = 0;
				fscanf_s(f,"%d", &max);
				if (max < m_score) max = m_score;
				fclose(f);
				f = fopen("score.sav", "w");
				fprintf(f, "%d\n%d", max, m_score);
				fclose(f);
				GameStateMachine::GetInstance()->ChangeState(StateType::STATE_END);
			}
		}

		//Score
		auto shader = ResourceManagers::GetInstance()->GetShader("TextShader");
		std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
		m_Tscore = std::make_shared< Text>(shader, font, "score: " + std::to_string(m_score), TextColor::RED, 1.0);
		m_Tscore->Set2DPosition(Vector2(5, 25));
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_hero->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	for (auto enemy : m_enemies) {
		enemy->Draw();
	}
	for (auto bomb : m_bombs) {
		bomb->Draw();
	}
	m_Tscore->Draw();
}

void GSPlay::CreateEnemy() {
	int numEnemy = (int) m_enemies.size();
	if (numEnemy <= MAX_ENEMY) {
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto texture = ResourceManagers::GetInstance()->GetTexture("enemy.tga");
		auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
		std::shared_ptr<Enemy> C_enemy = std::make_shared<Enemy>(model, shader, texture, 8, 0.1f, m_score);
		C_enemy->SetSize(50, 50);
		switch (numEnemy%4)
		{
		case 0:
			C_enemy->Set2DPosition(rand() % Globals::screenWidth + 1, -16);
			break;
		case 1:
			C_enemy->Set2DPosition(-16, rand() % Globals::screenHeight + 1);
			break;
		case 2:
			C_enemy->Set2DPosition(rand() % Globals::screenWidth + 1, Globals::screenHeight + 16);
			break;
		case 3:
			C_enemy->Set2DPosition(Globals::screenWidth + 16, rand() % Globals::screenHeight + 1);
			break;
		}
		m_enemies.push_back(C_enemy);
	}
}

void GSPlay::CreateBomb() {
	int numBomb = (int)m_bombs.size();
	if (numBomb <= MAX_BOMB) {
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Bomb.tga");
		auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
		std::shared_ptr<Bomb> C_bomb = std::make_shared<Bomb>(model, shader, texture, 1, 0.05f);
		C_bomb->SetSize(20, 30);
		C_bomb->Set2DPosition(m_hero->GetPosition().x, m_hero->GetPosition().y);
		m_bombs.push_back(C_bomb);
	}
}