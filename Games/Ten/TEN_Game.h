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

class tenCamera;
class tenStarfield;
class tenStar;

class tenGame: public coreGame, public vsSingleton<tenGame>
{
public:
	enum Mode
	{
		Mode_Title,
		Mode_InGame,
		Mode_Credits,
		MODE_MAX
	};
private:
	coreGameMode *m_mode[MODE_MAX];
	tenStarfield *m_starfield;
	tenCamera *m_camera;
	vsFont *m_serif;
	vsFont *m_sans;
	int m_currentMode;
	int m_nextMode;

public:
	tenGame();
	virtual ~tenGame();

	virtual void Init();
	virtual void Deinit();

	vsFont *GetSerifFont() { return m_serif; }
	vsFont *GetSansFont() { return m_sans; }

	void SetCameraFollow( vsSprite *follow );
	void SetMode(Mode m);

	//vsFont *GetFont() { return m_font; }

	virtual void Update( float timetenep );
};

#endif /* TEN_GAME_H */

