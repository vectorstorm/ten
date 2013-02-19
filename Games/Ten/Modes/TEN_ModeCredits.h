/*
 *  TEN_ModeCredits.h
 *  VectorStorm
 *
 *  Created by Trevor Powell on 19-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */

#ifndef TEN_MODECREDITS_H
#define TEN_MODECREDITS_H

#define MAX_CREDIT_LINES (25)

class tenFader;

class tenModeCredits : public coreGameMode
{
	typedef coreGameMode Parent;

	vsFile *	m_credits;
	vsFont *	m_font;

	tenFader *	m_fader;

	vsSprite *	m_line[MAX_CREDIT_LINES];
	int			m_lineId[MAX_CREDIT_LINES];
	bool		m_lineUsed[MAX_CREDIT_LINES];
	int			m_lineCount;
	bool		m_creditsDone;

	bool		m_fadingOut;
	bool		m_inittedFade;
	float		m_fadingTimer;
	float		m_initTimer;


	float		m_creditsPos;

	void		LoadLine( int i );	// load a line into slot 'i'.

public:

	tenModeCredits();
	virtual ~tenModeCredits();

	virtual void Init();
	virtual void Deinit();

	virtual void Update(float timeStep);
};

#endif /* TEN_MODECREDITS_H */

