/*
 *  TEN_Game.cpp
 *  VectorStorm
 *
 *  Created by Trevor Powell on 18-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#include "TEN_Game.h"
#include "TEN_Scenes.h"

REGISTER_MAINGAME("Ten", tenGame);

tenGame::tenGame():
	m_currentMode(-1),
	m_nextMode(-1)
{
}

tenGame::~tenGame()
{
}

void
tenGame::Init()
{
	m_sceneCount = SCENE_MAX;
	m_nextMode = -1;
	coreGame::Init();
	for ( int i = 0; i < MODE_MAX; i++ )
	{
		m_mode[i] = NULL;
	}
}


void
tenGame::Deinit()
{
	SetGameMode(NULL);
	for ( int i = 0; i < MODE_MAX; i++ )
	{
		vsDelete( m_mode[i] );
	}
	coreGame::Deinit();
}

void
tenGame::Update( float timetenep )
{
	if ( m_nextMode != m_currentMode )
	{
		m_currentMode = m_nextMode;
		SetGameMode( m_mode[m_nextMode] );
	}
	coreGame::Update(timetenep);
}

void
tenGame::SetMode(Mode m)
{
	m_nextMode = m;
}

