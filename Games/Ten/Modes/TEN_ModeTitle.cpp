/*
 *  TEN_ModeTitle.cpp
 *  VectorStorm
 *
 *  Created by Trevor Powell on 19-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#include "TEN_ModeTitle.h"
#include "TEN_Game.h"
#include "TEN_Scenes.h"

tenModeTitle::tenModeTitle()
{
}

tenModeTitle::~tenModeTitle()
{
}

void
tenModeTitle::Init()
{
	coreGameMode::Init();
	vsFont *f = tenGame::Instance()->GetSerifFont();
	vsFragment *titleFragment;
	titleFragment = f->CreateString_Fragment( FontContext_2D, "Ten", 72.f, Justification_Center);
	m_title = new vsSprite;
	m_title->AddFragment(titleFragment);
	m_title->RegisterOnScene(Scene_UI);
}

void
tenModeTitle::Deinit()
{
	vsDelete( m_title );
	coreGameMode::Deinit();
}

void
tenModeTitle::Update( float timeStep )
{
	coreGameMode::Update(timeStep);

	if ( vsInput::Instance()->WasPressed(CID_A) )
	{
		tenGame::Instance()->SetMode(tenGame::Mode_Credits);
	}
}

