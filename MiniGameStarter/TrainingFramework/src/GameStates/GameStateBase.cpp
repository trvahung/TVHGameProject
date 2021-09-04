/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"

#include "GameStatebase.h"
#include "../../GSCredit.h"
#include "../GSEnd.h"
#include "../GSLeader.h"
#include "../GSHowToPlay.h"

GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{
}

int GameStateBase::m_keyPressed = 0;

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		break;
	case StateType::STATE_CREDIT:
		gs = std::make_shared<GSCredit>();
		break;
	case StateType::STATE_END:
		gs = std::make_shared<GSEnd>();
		break;
	case StateType::STATE_LEADER:
		gs = std::make_shared<GSLeader>();
		break;
	case StateType::STATE_HOWTOPLAY:
		gs = std::make_shared<GSHowToPlay>();
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}