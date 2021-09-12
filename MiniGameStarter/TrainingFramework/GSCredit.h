#pragma once
#include "GameStates/GameStateBase.h"

class Sprite2D;
class Sprite3D;
class Text;
class GameButton;

class GSCredit :
    public GameStateBase
{
public:
	GSCredit();
	~GSCredit();

	void	Init() override;
	void	Exit() override;

	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(int x, int y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;
	void InitSound() {};

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::list<std::shared_ptr<Text>>		m_string;
	std::list<std::shared_ptr<GameButton>>	m_listButton;

};

