/*
 *  ST_Game.h
 *  VectorStorm
 *
 *  Created by Trevor Powell on 18-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#ifndef MC_GAME_H
#define MC_GAME_H

class stGame: public coreGame, public vsSingleton<stGame>
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
	stGame();
	virtual ~stGame();

	virtual void Init();
	virtual void Deinit();

	void Start();
	void SetMode(Mode m);

	//vsFont *GetFont() { return m_font; }

	virtual void Update( float timeStep );
};

#endif /* MC_GAME_H */

