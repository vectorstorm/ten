/*
 *  TEN_ModeCredits.cpp
 *  VectorStorm
 *
 *  Created by Trevor Powell on 19-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */

#include "TEN_ModeCredits.h"
#include "TEN_Game.h"
#include "TEN_Fader.h"

#include "TEN_Scenes.h"



tenModeCredits::tenModeCredits()
{
}

tenModeCredits::~tenModeCredits()
{
}

void
tenModeCredits::Init()
{
	Parent::Init();

	m_font = new vsFont("FreeSerif.txt");
	m_credits = new vsFile("Credits.txt");

	vsScene *s = vsSystem::GetScreen()->GetScene(Scene_Fader);
	m_fader = new tenFader( vsBox2D( s->GetTopLeftCorner(), s->GetBottomRightCorner() ) );

	m_fader->RegisterOnScene( Scene_Fader );
	m_fader->SetOut();
	m_fader->FadeIn(2.f);

	for ( int i = 0; i < MAX_CREDIT_LINES; i++ )
	{
		m_line[i] = NULL;
		m_lineUsed[i] = false;
	}
	m_creditsDone = false;
	m_lineCount = 0;
	m_creditsPos = -500.f;

	m_fadingOut = false;
	m_fadingTimer = 0.f;
	m_initTimer = 0.f;
	m_inittedFade = false;

	// If we have special credits music, trigger it here.
	//m_game->PlayMusic( daGame::Music_Credits );
}

void
tenModeCredits::Deinit()
{
	vsDelete(m_font);
	vsDelete(m_credits);

	vsDelete(m_fader);

	for ( int i = 0; i < MAX_CREDIT_LINES; i++ )
	{
		if ( m_line[i] )
			vsDelete(m_line[i]);
	}
}

void
tenModeCredits::LoadLine( int i )
{
	vsString creditString;
	m_creditsDone = !m_credits->ReadLine(&creditString);
	m_lineUsed[i] = false;

	if ( m_line[i] )
		vsDelete(m_line[i]);

	if ( !m_creditsDone )
	{
		if ( creditString[0] == '=' )
		{
			vsString actualString = &creditString.c_str()[1];
			m_line[i] = new vsSprite( m_font->CreateString2D(actualString, 60.0f, Justification_Center) );
		}
		else
			m_line[i] = new vsSprite( m_font->CreateString2D(creditString, 25.0f, Justification_Center) );
		m_line[i]->SetColor( vsColor(vsColor::Yellow) );
		m_line[i]->SetPosition( vsVector2D(0.f, -700.f) );
		m_line[i]->RegisterOnScene(Scene_UI);
		m_lineUsed[i] = true;
		m_lineId[i] = m_lineCount++;
	}
}

void
tenModeCredits::Update( float timeStep )
{
	m_initTimer += timeStep;
	// this value is how long to wait before starting the credit scroll.  Use
	// this timer to synchronise the credit scroll with music or effects, if
	// desired.
	if ( m_initTimer < 0.f )
	{
		return;
	}

	int activeLines = 0;
	for ( int i = 0; i < MAX_CREDIT_LINES; i++ )
	{
		if ( m_lineUsed[i] )
			activeLines++;
	}

	const float c_creditsScrollSpeed = 50.0f;	// 50 'units' per second
	const float c_creditLineSpacing = 50.0f;
	float top = vsSystem::GetScreen()->GetScene(Scene_UI)->GetTopLeftCorner().y - 50.0f;

	m_creditsPos += (timeStep * c_creditsScrollSpeed);

	for ( int i = 0; i < MAX_CREDIT_LINES; i++ )
	{
		if ( m_lineUsed[i] )
		{
			float yCoord = m_lineId[i] * c_creditLineSpacing;
			yCoord -= m_creditsPos;

			if ( m_creditsDone && m_lineId[i] == m_lineCount-1 && yCoord < top )
				m_fadingOut = true;

			if ( m_creditsDone && m_lineId[i] == m_lineCount-1 )	// last line
				yCoord = vsMax( yCoord, 0.f );	// last line doesn't go past halfway.

			if ( yCoord < top )
				LoadLine(i);
			else
			{
				m_line[i]->SetPosition( vsVector2D(0.f, yCoord) );
			}
		}
		else if ( !m_creditsDone )
			LoadLine(i);
	}

	if ( vsInput::Instance()->WasPressed(CID_MouseLeftButton) || vsInput::Instance()->WasPressed(CID_A) )
		m_fadingOut = true;

	if ( m_fadingOut )
	{
		m_fadingTimer += timeStep;
		const float c_fadeDuration = 2.0f;
		float frac = m_fadingTimer / c_fadeDuration;
		vsColor c = vsColor::Black;

		if ( !m_inittedFade )
		{
			//m_game->FadeOutMusic( c_fadeDuration );
			m_inittedFade = true;
		}

		if ( frac < 1.0f )
		{
			c = vsInterpolate( frac, vsColor::Yellow, vsColor::Black );

			for ( int i = 0; i < MAX_CREDIT_LINES; i++ )
			{
				if ( m_lineUsed[i] )
				{
					// this approach of fading out doesn't work for the new
					// vsFragment-based rendering of credit lines.  Probably
					// need to use a tenFader to perform the fade out, instead.
					m_line[i]->SetColor(c);
				}
			}
		}
		else
		{
			tenGame::Instance()->SetMode( tenGame::Mode_Title );
		}
	}
}

