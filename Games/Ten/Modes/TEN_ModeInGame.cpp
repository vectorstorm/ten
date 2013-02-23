/*
 *  TEN_ModeInGame.cpp
 *  VectorStorm
 *
 *  Created by Trevor Powell on 19-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#include "TEN_ModeInGame.h"
#include "TEN_Whale.h"
#include "TEN_Game.h"
#include "TEN_Scenes.h"

class tbFlyCamera : public vsCamera3D
{
	vsVector2D	m_mousePos;
	vsEulerAngles m_angles;
	vsQuaternion	m_baseQuaternion;

public:

	tbFlyCamera();

	virtual void Update( float timeStep );
};

tbFlyCamera::tbFlyCamera():
	m_baseQuaternion(vsVector3D(0.f,0.f,1.f), vsVector3D(0.f,1.f,0.f))
{
	m_transform.SetRotation(vsQuaternion(m_angles) * m_baseQuaternion);

}

void
tbFlyCamera::Update(float timeStep)
{
	vsInput *input = vsInput::Instance();

	static float speed = 60.f;
	vsTransform3D trans = GetTransform();
	vsVector3D pos = trans.GetTranslation();//l->GetCamera3D()->GetTransform().GetTranslation();
	if ( input->IsDown(CID_Right) )
	{
		pos += trans.GetMatrix().x * speed * timeStep;
	}
	if ( input->IsDown(CID_Left) )
	{
		pos -= trans.GetMatrix().x * speed * timeStep;
	}
	if ( input->IsDown(CID_Up) )
	{
		pos += trans.GetMatrix().z * speed * timeStep;
	}
	if ( input->IsDown(CID_Down) )
	{
		pos -= trans.GetMatrix().z * speed * timeStep;
	}

	if ( input->IsDown(CID_MouseRightButton) )
	{
		vsVector2D newMousePos = input->GetMousePosition(Scene_World);
		vsVector2D delta = (newMousePos - m_mousePos) * (PI);

		m_angles.pitch += delta.y;
		m_angles.yaw += delta.x;

		/*vsQuaternion p( vsVector3D(1.f,0.f,0.f), delta.y );
		vsQuaternion y( vsVector3D(0.f,1.f,0.f), -delta.x );
		trans.SetQuaternion( trans.GetQuaternion() * y * p );*/
		trans.SetRotation(vsQuaternion(m_angles) * m_baseQuaternion);

		vsSystem::Instance()->HideCursor();
	}
	else
	{
		vsSystem::Instance()->ShowCursor(true);
	}

	m_mousePos = input->GetMousePosition(Scene_World);


	trans.SetTranslation(pos);

	// okay.  Now, we want to flatten out any bank we may have acquired.

/*	if ( trans.GetMatrix().y.y < 0.f || vsFabs(trans.GetMatrix().x.y) > 0.0001f )
	{
		vsQuaternion flatQuat( trans.GetMatrix().z, vsVector3D(0.f,1.f,0.f) );
		trans.SetQuaternion( flatQuat );
	}*/

	//	vsVector3D forward = -pos;
	//	vsTransform3D trans( vsQuaternion(forward, vsVector3D(0.f,1.f,0.f)), pos );
	//	trans.SetAsRotationAroundY( vsAngle(DEGREES(20.f)) );
	SetTransform(trans);
}

tenModeInGame::tenModeInGame()
{
}

tenModeInGame::~tenModeInGame()
{
}

void
tenModeInGame::Init()
{
	m_whale = new tenWhale();
	m_whale->RegisterOnScene( Scene_World );
	tenGame::Instance()->SetCameraFollow( m_whale );
	//vsSystem::GetScreen()->GetScene(Scene_World)->SetCamera3D( new tbFlyCamera );
}

void
tenModeInGame::Deinit()
{
	vsDelete( m_whale );
}

void
tenModeInGame::Update( float timeStep )
{
}


