/*
 *  ST_Game.cpp
 *  VectorStorm
 *
 *  Created by Trevor Powell on 18-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#include "ST_Game.h"
#include "ST_Scenes.h"

REGISTER_MAINGAME("Sturdy", stGame);

stGame::stGame():
	m_currentMode(-1),
	m_nextMode(-1)
{
}

stGame::~stGame()
{
}

void
stGame::Init()
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
stGame::Deinit()
{
	SetGameMode(NULL);
	for ( int i = 0; i < MODE_MAX; i++ )
	{
		vsDelete( m_mode[i] );
	}
	coreGame::Deinit();
}

void
stGame::Update( float timeStep )
{
	if ( m_nextMode != m_currentMode )
	{
		m_currentMode = m_nextMode;
		SetGameMode( m_mode[m_nextMode] );
	}
	coreGame::Update(timeStep);
}

void
stGame::SetMode(Mode m)
{
	m_nextMode = m;
}

