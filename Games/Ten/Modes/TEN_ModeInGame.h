/*
 *  TEN_ModeInGame.h
 *  VectorStorm
 *
 *  Created by Trevor Powell on 19-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#ifndef TEN_MODEINGAME_H
#define TEN_MODEINGAME_H

class tenModeInGame: public coreGameMode
{
public:
	tenModeInGame();
	virtual ~tenModeInGame();

	virtual void Update( float timeStep );
};

#endif /* TEN_MODEINGAME_H */

