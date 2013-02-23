/*
 *  TEN_Camera.h
 *  VectorStorm
 *
 *  Created by Trevor Powell on 22-02-2013.
 *  Copyright 2013 Trevor Powell.  All rights reserved.
 *
 */
#ifndef TEN_CAMERA_H
#define TEN_CAMERA_H

class tenCamera: public vsCamera3D
{
	vsSprite * m_follow;
public:
	tenCamera();
	virtual ~tenCamera();
	void Follow( vsSprite *sprite );
	virtual void Update(float timeStep);
};

#endif /* TEN_CAMERA_H */

