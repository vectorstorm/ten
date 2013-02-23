/*
 *  TEN_Whale.cpp
 *  VectorStorm
 *
 *  Created by Trevor Powell on 22-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#include "TEN_Whale.h"
#include "TEN_Game.h"
#include "TEN_Scenes.h"

tenWhale::tenWhale():
	vsPhysicsSprite( vsDisplayList::Load("Whale"), 1.0f, ColFlag_Player, ColFlag_All )
{
	SetCollisionsActive(false);
	SetColor(vsColor::Blue);
	m_isSpawned = false;
	m_emitter = new vsPhysicsEmitter("Thrust", 0.1f, 160, Scene_World);

	vsBox2D box;
	box.ExpandToInclude( vsVector2D::One * -2.f );
	box.ExpandToInclude( vsVector2D::One * 2.f );
	AddFragment( vsMakeOutlineBox2D( box, "White" ) );

	Spawn(vsVector2D(0.f,0.f));
}

tenWhale::~tenWhale()
{
	vsDelete( m_emitter );
}

void
tenWhale::Spawn( const vsVector2D &pos )
{
	SetCollisionsActive(true);
	SetPosition( pos );
	SetVelocity( vsVector2D::Zero );
	SetAngularVelocity( 0.f );
	//RegisterOnScene(0);
//	m_colObject->Teleport();

	m_isSpawned = true;
}

void
tenWhale::Despawn()
{
	//Extract();
	SetCollisionsActive(false);

	m_emitter->SetSpawnRate(0.0f);
	m_emitter->SpawnImmediateBurst(60, GetPosition(), 10.0f, 3.0f, vsColor::Blue);

//	m_isSpawned = false;
//	m_delayBeforeSpawn = 2.0f;	// no respawning for at least two seconds.
//	m_timeSinceSpawn = 0.f;
}

void
tenWhale::Update( float timeStep )
{
	vsInput *input = vsInput::Instance();

	//vsVector2D lStick = input->GetLeftStick();
	float steering = input->GetLeftStick().x;

	AddTorque( m_object->GetAngularVelocity() * -6.0f * m_object->GetMomentOfInertia());		// angular damping
	AddTorque( DEGREES(-1080.0f) * steering * m_object->GetMomentOfInertia() );		// rotation from attitude jets

	AddForce( m_object->GetVelocity() * -0.3f * m_object->GetMass() );				// damping

	//if ( lStick.y > 0.f )
	if ( input->IsDown(CID_B) )
	{
		float acceleration = 30.0f;
		AddForce( m_transform.GetAngle().GetForwardVector() * acceleration /* lStick.y*/ * m_object->GetMass() );	// thrust
		m_emitter->SetSpawnRate( 30.0f );
	}
	else
	{
		m_emitter->SetSpawnRate(0.0f);
	}

	//HandleSpawnTimer(timeStep);

	Parent::Update( timeStep );

	vsVector2D forwardVec = m_transform.GetAngle().GetForwardVector();
	m_emitter->SetSpawnPosition( GetPosition() - forwardVec * 3.0f, 1.0f );
	m_emitter->SetSpawnColor( vsColor::Red );

	if ( input->IsDown(CID_B) )
		m_emitter->SetSpawnVelocity( forwardVec * -20.0f, 6.0f );

	m_emitter->Update(timeStep);
	vsPhysicsSprite::Update(timeStep);
}

void
tenWhale::Draw( vsRenderQueue *queue )
{
	vsPhysicsSprite::Draw(queue);
}

bool
tenWhale::CollisionCallback( const colEvent &event )
{
	if ( event.colFlags & ColFlag_Enemy )
	{
		//if ( !m_spawnInvulnerable )
			SetDestroyed();
		return true;
	}

	return false;
}

void
tenWhale::DestroyCallback()
{
	//Despawn();
}
