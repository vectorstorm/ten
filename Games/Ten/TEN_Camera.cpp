/*
 *  TEN_Camera.cpp
 *  VectorStorm
 *
 *  Created by Trevor Powell on 22-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#include "TEN_Camera.h"

tenCamera::tenCamera():
	m_follow(NULL)
{
	SetPosition( vsVector3D(0.f,-100.f,0.f) );
}

tenCamera::~tenCamera()
{
}

void
tenCamera::Follow( vsSprite *follow )
{
	m_follow = follow;
}

void
tenCamera::Update( float timeStep )
{
	if ( m_follow )
	{
		vsVector3D targetPos = m_follow->GetPosition();
		vsVector3D pos = targetPos;
		pos.z = -100.f;
		SetPosition( pos );
		LookAt(targetPos);
	}

	vsCamera3D::Update(timeStep);
}
