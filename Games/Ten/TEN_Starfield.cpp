/*
 *  TEN_Starfield.cpp
 *  VectorStorm
 *
 *  Created by Trevor Powell on 21-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#include "TEN_Starfield.h"
#include "TEN_Scenes.h"

tenStarfield::tenStarfield():
	m_vbo( new vsRenderBuffer(vsRenderBuffer::Type_Stream) ),
	m_ibo( new vsRenderBuffer(vsRenderBuffer::Type_Static) ),
	m_material( new vsMaterial("White") ),
	m_list( new vsDisplayList(30 * 1024) ),
	m_starCount(100),
	m_star( new Star[m_starCount] )
{
	vsVector3D v[4] =
	{
		vsVector3D(2.f,2.f,0.f),
		vsVector3D(-2.f,2.f,0.f),
		vsVector3D(2.f,-2.f,0.f),
		vsVector3D(-2.f,-2.f,0.f)
	};
	uint16_t i[6] = { 0, 1, 2, 1, 3, 2 };
	m_vbo->SetArray(v,4);
	m_ibo->SetArray(i,6);
	for ( int i = 0; i < m_starCount; i++ )
	{
		m_star[i].position = vsVector3D::ZAxis * 1000.f + vsRandom::GetVector3D(1000.f);
		m_star[i].color = vsRandom::GetFloat(1.f) * vsColor::PureWhite;
	}
}

tenStarfield::~tenStarfield()
{
	vsDelete( m_vbo );
	vsDelete( m_ibo );
	vsDelete( m_material );
	vsDelete( m_list );
	vsDeleteArray( m_star );
}

void
tenStarfield::Update( float timeStep )
{
	//const vsVector3D c_velocity(100.f,30.f,0.f);
	const vsVector3D c_velocity = vsVector3D::Zero;
	vsVector3D velocity = timeStep * c_velocity;
	vsCamera3D *cam = vsSystem::GetScreen()->GetScene(Scene_World)->GetCamera3D();
	for ( int i = 0; i < m_starCount; i++ )
	{
		m_star[i].position += velocity;

		if ( !cam->IsPositionVisible( m_star[i].position, 500.f ) )
		{
			// generate a new position slightly outside our view
			m_star[i].position = vsVector3D::ZAxis * 1000.f + vsRandom::GetVector3D(1000.f);
		}
	}
}

void
tenStarfield::Draw( vsRenderQueue *queue )
{
	m_list->Clear();
	m_list->SetMatrix4x4(queue->GetMatrix());
	m_list->VertexBuffer(m_vbo);
	for ( int i = 0; i < m_starCount; i++ )
	{
		m_list->PushTranslation( m_star[i].position );
		m_list->SetColor( m_star[i].color );
		m_list->TriangleListBuffer(m_ibo);
		m_list->PopTransform();
	}
	m_list->ClearVertexArray();
	m_list->PopTransform();
	queue->AddBatch( m_material, m_list );
}

