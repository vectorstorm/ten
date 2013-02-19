/*
 *  TEN_Fader.cpp
 *  VectorStorm
 *
 *  Created by Trevor Powell on 19-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */

#include "TEN_Fader.h"

tenFader::tenFader( const vsBox2D &box ):
	m_alpha(1.f)
{
	vsVector3D v[4] =
	{
		box.TopLeft(),
		box.TopRight(),
		box.BottomLeft(),
		box.BottomRight()
	};
	int indices[4] = { 0, 1, 2, 3 };

	vsDisplayList *list = new vsDisplayList(512);
	list->VertexArray(v,4);
	list->TriangleStrip(indices,4);

	SetDisplayList(list);

	SetColor( vsColor(0.f,0.f,0.f,1.f) );
}

void
tenFader::Update( float timeStep )
{
	m_alpha.Update( timeStep );

	m_color.a = m_alpha.GetValue();
}

void
tenFader::Draw( vsRenderQueue *queue )
{
	if ( m_alpha.GetValue() > 0.f )
	{
		Parent::Draw(queue);
	}
}

