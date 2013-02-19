/*
 *  TEN_ModeTitle.h
 *  VectorStorm
 *
 *  Created by Trevor Powell on 19-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#ifndef TEN_MODETITLE_H
#define TEN_MODETITLE_H

class tenModeTitle: public coreGameMode
{
	vsSprite *m_title;
public:
	tenModeTitle();
	virtual ~tenModeTitle();

	virtual void Init();
	virtual void Deinit();

	virtual void Update( float timeStep );
};

#endif /* TEN_MODETITLE_H */

