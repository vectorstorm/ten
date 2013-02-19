/*
 *  TEN_Game.h
 *  VectorStorm
 *
 *  Created by Trevor Powell on 18-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#ifndef TEN_GAME_H
#define TEN_GAME_H

class tenGame: public coreGame, public vsSingleton<tenGame>
{
public:
	enum Mode
	{
		Mode_Title,
		Mode_InGame,
		MODE_MAX
	};
private:
	coreGameMode *m_mode[MODE_MAX];
	int m_currentMode;
	int m_nextMode;

public:
	tenGame();
	virtual ~tenGame();

	virtual void Init();
	virtual void Deinit();

	void tenart();
	void SetMode(Mode m);

	//vsFont *GetFont() { return m_font; }

	virtual void Update( float timetenep );
};

#endif /* TEN_GAME_H */

