#pragma once
#include "GameStateBase.h"



class Sprite2D;
class Sprite3D;
class Text;
class GameButton;
class Hero;
class Enemy;
class Bomb;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

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

private:
	std::shared_ptr<Sprite2D>	m_background;
	std::shared_ptr<Text>		m_Tscore;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Hero> m_hero;
	std::list<std::shared_ptr<Enemy>> m_enemies;
	std::list<std::shared_ptr<Bomb>> m_bombs;
	bool m_State;
	bool m_bomb;
	int m_score;
	float m_time;
	void CreateEnemy();
	void CreateBomb();

};

#define MAX_ENEMY 50
#define ENEMY_CREATE_TIME 2
#define MAX_BOMB 3
