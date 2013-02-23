/*
 *  TEN_Game.cpp
 *  VectorStorm
 *
 *  Created by Trevor Powell on 18-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#include "TEN_Game.h"
#include "TEN_Camera.h"
#include "TEN_Scenes.h"
#include "TEN_Starfield.h"
#include "Modes/TEN_ModeTitle.h"
#include "Modes/TEN_ModeInGame.h"
#include "Modes/TEN_ModeCredits.h"

REGISTER_MAINGAME("Ten", tenGame);

tenGame::tenGame():
	//m_starfield(NULL),
	m_serif(NULL),
	m_sans(NULL),
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
	m_serif = new vsFont("FreeSerif.txt");
	m_sans = new vsFont("FreeSans.txt");
	m_mode[Mode_Title] = new tenModeTitle;
	m_mode[Mode_InGame] = new tenModeInGame;
	m_mode[Mode_Credits] = new tenModeCredits;
	SetMode(Mode_InGame);

	m_camera = new tenCamera;

	vsSystem::GetScreen()->GetScene(Scene_World)->SetCamera3D(m_camera);
	vsSystem::GetScreen()->GetScene(Scene_World)->Set3D(true);
	m_starfield = new tenStarfield;
	m_starfield->RegisterOnScene(Scene_World);
}


void
tenGame::Deinit()
{
	SetGameMode(NULL);
	for ( int i = 0; i < MODE_MAX; i++ )
	{
		vsDelete( m_mode[i] );
	}
	vsDelete( m_serif );
	vsDelete( m_sans );
	vsDelete( m_starfield );
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
tenGame::SetCameraFollow( vsSprite *follow )
{
	m_camera->Follow(follow);
}

void
tenGame::SetMode(Mode m)
{
	m_nextMode = m;
}

