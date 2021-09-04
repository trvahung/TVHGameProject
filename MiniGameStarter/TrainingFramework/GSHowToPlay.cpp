#include "GSHowToPlay.h"

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

GSHowToPlay::GSHowToPlay()
{
}


GSHowToPlay::~GSHowToPlay()
{
}


void GSHowToPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play2.tga");

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
	str = std::make_shared< Text>(shader, font, "Use W A S D to move", TextColor::RED, 1.0);
	str->Set2DPosition(Vector2(5, Globals::screenHeight / 2-25));
	m_string.push_back(str);
	str = std::make_shared< Text>(shader, font, "Press SPACE to set Bomb", TextColor::RED, 1.0);
	str->Set2DPosition(Vector2(5, Globals::screenHeight / 2 ));
	m_string.push_back(str);
	str = std::make_shared< Text>(shader, font, "Kill the enemies to get the best score", TextColor::RED, 1.0);
	str->Set2DPosition(Vector2(5, Globals::screenHeight / 2 + 25));
	m_string.push_back(str);
}

void GSHowToPlay::Exit()
{
}


void GSHowToPlay::Pause()
{
}

void GSHowToPlay::Resume()
{
}


void GSHowToPlay::HandleEvents()
{
}

void GSHowToPlay::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSHowToPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSHowToPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSHowToPlay::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSHowToPlay::Draw()
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