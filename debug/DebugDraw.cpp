//
//  DebugDraw.cpp
//  MusicalAdventure
//
//  Created by user on 3/27/14.
//  Copyright ampagames 2014. All rights reserved.
//

#include "DebugDraw.h"

using namespace cocos2d;

//-----------------------------------------------------------------------------------------------------
DebugDrawPoint::DebugDrawPoint():
origin(0, 0),
size(0),
color(ccc4f(0, 0, 0, 0))
{
}

//-----------------------------------------------------------------------------------------------------
DebugDrawPoint::~DebugDrawPoint()
{
}

//-----------------------------------------------------------------------------------------------------
DebugDrawPoint* DebugDrawPoint::create(const CCPoint& _origin, float _size, const ccColor4F& _color)
{
	DebugDrawPoint* primitive = new DebugDrawPoint();
	if(primitive)
	{
		primitive->origin = _origin;
		primitive->size = _size;
		primitive->color = _color;
		
		primitive->autorelease();
		return primitive;
	}
	return NULL;
}

//-----------------------------------------------------------------------------------------------------
void DebugDrawPoint::draw()
{
	ccPointSize(this->size);
	ccDrawColor4F(this->color.r, this->color.g, this->color.b, this->color.a);
	ccDrawPoint(this->origin);
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
DebugDrawLine::DebugDrawLine():
origin(0, 0),
destination(0, 0),
color(ccc4f(0, 0, 0, 0))
{
}

//-----------------------------------------------------------------------------------------------------
DebugDrawLine::~DebugDrawLine()
{
}

//-----------------------------------------------------------------------------------------------------
DebugDrawLine* DebugDrawLine::create(const CCPoint& _origin, const CCPoint& _destination, const ccColor4F& _color)
{
	DebugDrawLine* primitive = new DebugDrawLine();
	if(primitive)
	{
		primitive->origin = _origin;
		primitive->destination = _destination;
		primitive->color = _color;

		return primitive;
	}
	
	return NULL;
}

//-----------------------------------------------------------------------------------------------------
void DebugDrawLine::draw()
{
	ccDrawColor4F(this->color.r, this->color.g, this->color.b, this->color.a);
	ccDrawLine(this->origin, this->destination);
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
DebugDrawCircle::DebugDrawCircle():
origin(0, 0),
radius(0),
angle(0),
segs(0),
lineToCenter(false),
scaleX(0),
scaleY(0),
color(ccc4f(0, 0, 0, 0))
{
}

//-----------------------------------------------------------------------------------------------------
DebugDrawCircle::~DebugDrawCircle()
{
}

//-----------------------------------------------------------------------------------------------------
DebugDrawCircle* DebugDrawCircle::create(const CCPoint& _origin, float _radius, float _angle, int _segs,
									     bool _lineToCenter, float _scaleX, float _scaleY, const ccColor4F& _color)
{
	DebugDrawCircle* primitive = new DebugDrawCircle();
	if(primitive)
	{
		primitive->origin = _origin;
		primitive->radius = _radius;
		primitive->angle = _angle;
		primitive->segs = _segs;
		primitive->lineToCenter = _lineToCenter;
		primitive->scaleX = _scaleX;
		primitive->scaleY = _scaleY;
		primitive->color = _color;
		primitive->autorelease();
		return primitive;
	}
	
	return NULL;
}

//-----------------------------------------------------------------------------------------------------
void DebugDrawCircle::draw()
{
	ccDrawColor4F(this->color.r, this->color.g, this->color.b, this->color.a);
	ccDrawCircle(this->origin, this->radius, this->angle, this->segs, this->lineToCenter, this->scaleX, this->scaleY);
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
DebugDrawEllipse::DebugDrawEllipse():
origin(0, 0),
radiusH(0),
radiusV(0),
angle(0),
segs(0),
lineToCenter(false),
color(ccc4f(0, 0, 0, 0))
{
}

//-----------------------------------------------------------------------------------------------------
DebugDrawEllipse::~DebugDrawEllipse()
{
}

//-----------------------------------------------------------------------------------------------------
DebugDrawEllipse* DebugDrawEllipse::create(const CCPoint& _origin, float _radiusH, float _radiusV, float _angle, int _segs,
								   bool _lineToCenter, const ccColor4F& _color)
{
	DebugDrawEllipse* primitive = new DebugDrawEllipse();
	if(primitive)
	{
		primitive->origin = _origin;
		primitive->radiusH = _radiusH;
		primitive->radiusV = _radiusV;
		primitive->angle = _angle;
		primitive->segs = _segs;
		primitive->lineToCenter = _lineToCenter;
		primitive->color = _color;

		return primitive;
	}
	
	return NULL;
}

//-----------------------------------------------------------------------------------------------------
void DebugDrawEllipse::draw()
{
	int additionalSegment = 1;
    if(this->lineToCenter)
        additionalSegment++;

    const float coef = 2.0f * (float)M_PI / this->segs;

    float* vertices = new float[2 * (this->segs + 2)]; 
    if(vertices)
	{
		memset(vertices, 0, sizeof(float) * 2 * (this->segs + 2));

		float rads, distance, angle, j, k;
		for(int i = 0; i <= this->segs; ++i)
		{
			rads = i * coef;
			distance = sqrt(pow(sinf(rads) * this->radiusV, 2) + pow(cosf(rads) * this->radiusH, 2));
			angle = atan2(sinf(rads) * this->radiusV, cosf(rads) * this->radiusH);
			j = distance * cosf(angle + this->angle) + this->origin.x;
			k = distance * sinf(angle + this->angle) + this->origin.y;

			vertices[i * 2] = j * CC_CONTENT_SCALE_FACTOR();
			vertices[i * 2 + 1] = k * CC_CONTENT_SCALE_FACTOR();
		}

		vertices[(this->segs + 1) * 2] = this->origin.x * CC_CONTENT_SCALE_FACTOR();
		vertices[(this->segs + 1) * 2 + 1] = this->origin.y * CC_CONTENT_SCALE_FACTOR();

		//glVertexPointer(2, GL_FLOAT, 0, vertices);    //TROUBLE
       	//glDrawArrays(GL_LINE_STRIP, 0, (GLsizei)this->segs + additionalSegment);

		glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
		glDrawArrays(GL_LINE_STRIP, 0, (GLsizei)this->segs + additionalSegment);

		free( vertices );
	}
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------