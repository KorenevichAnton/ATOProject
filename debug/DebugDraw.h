//
//  DebugDraw.h
//  MusicalAdventure
//
//  Created by user on 3/27/14.
//  Copyright ampagames 2014. All rights reserved.
//

#ifndef __DEBUG_DRAW__
#define __DEBUG_DRAW__

#include "cocos2d.h"
#include "Config.h"

//-----------------------------------------------------------------------------------------------------
class DebugDrawPrimitive: public cocos2d::CCNode
{
public:
	virtual void	draw() = 0;
};

//-----------------------------------------------------------------------------------------------------
class DebugDrawPoint: public DebugDrawPrimitive
{
public:
	static DebugDrawPoint*	create(const cocos2d::CCPoint& _origin, float _size, const cocos2d::ccColor4F& _color);

private:
	cocos2d::CCPoint		origin;
	float					size;
	cocos2d::ccColor4F		color;

private:
	DebugDrawPoint();
	~DebugDrawPoint();

	virtual void			draw();
};

//-----------------------------------------------------------------------------------------------------
class DebugDrawLine: public DebugDrawPrimitive
{
public:
	static DebugDrawLine*	create(const cocos2d::CCPoint& _origin, const cocos2d::CCPoint& _destination,
								   const cocos2d::ccColor4F& _color);

private:
	cocos2d::CCPoint		origin;
	cocos2d::CCPoint		destination;
	cocos2d::ccColor4F		color;

private:
	DebugDrawLine();
	~DebugDrawLine();

	virtual void			draw();
};

//-----------------------------------------------------------------------------------------------------
class DebugDrawCircle: public DebugDrawPrimitive
{
public:
	static DebugDrawCircle*	create(const cocos2d::CCPoint& _origin, float _radius, float _angle, int _segs,
								   bool _lineToCenter, float _scaleX, float _scaleY, const cocos2d::ccColor4F& _color);

private:
	cocos2d::CCPoint		origin;
	float					radius;
	float					angle;
	int						segs;
	bool					lineToCenter;
	float					scaleX;
	float					scaleY;
	cocos2d::ccColor4F		color;

private:
	DebugDrawCircle();
	~DebugDrawCircle();

	virtual void			draw();
};

//-----------------------------------------------------------------------------------------------------
class DebugDrawEllipse: public DebugDrawPrimitive
{
public:
	static DebugDrawEllipse*	create(const cocos2d::CCPoint& _origin, float _radiusH, float _radiusV, float _angle, int _segs,
									   bool _lineToCenter, const cocos2d::ccColor4F& _color);

private:
	cocos2d::CCPoint		origin;
	float					radiusH;
	float					radiusV;
	float					angle;
	int						segs;
	bool					lineToCenter;
	cocos2d::ccColor4F		color;

private:
	DebugDrawEllipse();
	~DebugDrawEllipse();

	virtual void				draw();
};

//-----------------------------------------------------------------------------------------------------
#endif	//__DEBUG_DRAW__