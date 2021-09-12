#include "GSEnd.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include <list>

GSEnd::GSEnd()
{
}


GSEnd::~GSEnd()
{
}


void GSEnd::Init()
{
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
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_MENU);
		});
	m_listButton.push_back(button);
	FILE* f;
	f = fopen("score.sav", "r");
	int max, score,temps;
	fscanf_s(f, "%d", &max);
	fscanf_s(f, "%d", &temps);
	fscanf_s(f, "%d", &score);
	fclose(f);

	// credit text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	std::shared_ptr<Text> str;
	str = std::make_shared< Text>(shader, font, "Your score: " + std::to_string(score), TextColor::RED, 1.0);
	str->Set2DPosition(Vector2(Globals::screenWidth/2-100, Globals::screenHeight/2));
	m_string.push_back(str);
	str = std::make_shared< Text>(shader, font, "Highest score: " + std::to_string(max), TextColor::RED, 1.0);
	str->Set2DPosition(Vector2(Globals::screenWidth / 2-100, Globals::screenHeight / 2 + 50));
	m_string.push_back(str);
	
}

void GSEnd::Exit()
{
}


void GSEnd::Pause()
{
}

void GSEnd::Resume()
{
}


void GSEnd::HandleEvents()
{
}

void GSEnd::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSEnd::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSEnd::HandleMouseMoveEvents(int x, int y)
{
}

void GSEnd::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSEnd::Draw()
{
	m_background->Draw();
	for (auto str : m_string) {
		str->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}