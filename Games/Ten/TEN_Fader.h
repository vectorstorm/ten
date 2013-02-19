/*
 *  TEN_Fader.h
 *  VectorStorm
 *
 *  Created by Trevor Powell on 19-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */

#ifndef TEN_FADER_H
#define TEN_FADER_H

// TODO: I've used this class heaps of times in different projects in order to
// do a simple fade to black.  Maybe promote to a "Utilities" thing as part of
// VectorStorm?

class tenFader : public vsSprite
{
	typedef vsSprite Parent;

	vsTween<float>	m_alpha;

public:

	tenFader( const vsBox2D &bounds );

	void SetIn() { FadeIn(0.f); }
	void SetOut() { FadeOut(0.f); }
	void FadeIn( float time ) { FadeTo( 0.f, time ); }
	void FadeOut( float time ) { FadeTo( 1.f, time ); }

	bool IsFading() { return m_alpha.IsTweening(); }
	bool IsOut() { return (m_alpha.GetValue() == 1.f); }

	void FadeTo( float alpha, float time ) { m_alpha.TweenTo( alpha, time ); }

	virtual void Update( float timeStep );
	virtual void Draw( vsRenderQueue *queue );
};

#endif // TEN_FADER_H

