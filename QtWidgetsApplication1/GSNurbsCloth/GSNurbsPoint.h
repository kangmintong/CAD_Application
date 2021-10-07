#pragma once
#include "GSNurbsVec3D.h"
#include "nurbsGL.h"
#include "GSNurbsDecltype.h"

class GSNurbsCurve;

class GSVec3D;

class GSNurbsPoint{
public:

	bool isSelected;
	GSNurbsCurve *parentCurve;

	GSVec3D position;
	GSVec3D tryPosition;	//用于移动计算
	GSVec3D currentPosition;	


public:
	//function
	void SetSelected(bool selected);

	GSVec3D GetPosition() const;

	void Move(const GSVec3D &dir, bool trying = false);
	void MoveTo(const GSVec3D &dise);


	void SetParent(GSNurbsCurve *p);

	bool IsAtPoint(const GSVec3D &position, const float &detectionLimit) const;



	GSNurbsPoint():
		isSelected(false),
		parentCurve(0)
	{
	}

	GSNurbsPoint(float x, float y, float z) :
		isSelected(false),
		parentCurve(0)
	{
		currentPosition = position = GSVec3D(x, y, z);
	}

	GSNurbsPoint(GSVec3D pos) :
		isSelected(false),
		parentCurve(0)
	{
		currentPosition = position = pos;
	}
};