#include "GSCredit.h"

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

GSCredit::GSCredit()
{
}


GSCredit::~GSCredit()
{
}


void GSCredit::Init()
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
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// credit text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	std::shared_ptr<Text> str;
	str = std::make_shared< Text>(shader, font, "Game created by Tran Van Hung", TextColor::RED, 1.0);
	str->Set2DPosition(Vector2(5, 25));
	m_string.push_back(str);
	str = std::make_shared< Text>(shader, font, "4th year student at HUST", TextColor::RED, 1.0);
	str->Set2DPosition(Vector2(5, 50));
	m_string.push_back(str);
	str = std::make_shared< Text>(shader, font, "In this game, you have to run ", TextColor::RED, 1.0);
	str->Set2DPosition(Vector2(5, 100));
	m_string.push_back(str);
	str = std::make_shared< Text>(shader, font, "to safe your life from hungry monster", TextColor::RED, 1.0);
	str->Set2DPosition(Vector2(5, 125));
	m_string.push_back(str);
}

void GSCredit::Exit()
{
}


void GSCredit::Pause()
{
}

void GSCredit::Resume()
{
}


void GSCredit::HandleEvents()
{
}

void GSCredit::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSCredit::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSCredit::HandleMouseMoveEvents(int x, int y)
{
}

void GSCredit::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSCredit::Draw()
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