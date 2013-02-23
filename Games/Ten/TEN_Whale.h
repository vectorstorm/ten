/*
 *  TEN_Whale.h
 *  VectorStorm
 *
 *  Created by Trevor Powell on 22-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#ifndef TEN_WHALE_H
#define TEN_WHALE_H

class tenWhale : public vsPhysicsSprite
{
	typedef vsPhysicsSprite Parent;
	vsPhysicsEmitter		*m_emitter;
	bool m_isSpawned;

public:
			tenWhale();
	virtual ~tenWhale();

	virtual void	Update( float timeStep );
	virtual bool	CollisionCallback( const colEvent &event );
	virtual void	DestroyCallback();

	virtual void	Draw( vsRenderQueue *queue );

	void Spawn( const vsVector2D &pos );
	void Despawn();
};

#endif /* TEN_WHALE_H */

