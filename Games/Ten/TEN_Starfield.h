/*
 *  TEN_Starfield.h
 *  VectorStorm
 *
 *  Created by Trevor Powell on 21-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#ifndef TEN_STARFIELD_H
#define TEN_STARFIELD_H

class tenStarfield: public vsEntity
{
	vsRenderBuffer *m_vbo;
	vsRenderBuffer *m_ibo;
	vsMaterial *m_material;
	vsDisplayList *m_list;

	struct Star
	{
		vsVector3D position;
		vsColor color;
	};

	int m_starCount;
	Star *m_star;
public:
	tenStarfield();
	virtual ~tenStarfield();

	virtual void Update( float timeStep );
	virtual void Draw( vsRenderQueue *queue );
};

#endif /* TEN_STARFIELD_H */

