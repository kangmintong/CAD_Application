
#include "GSNurbsPoint.h"

void GSNurbsPoint::SetSelected(bool selected)
{
	isSelected = selected;
}

GSVec3D GSNurbsPoint::GetPosition() const
{
	return currentPosition;
}

void GSNurbsPoint::Move(const GSVec3D &dir, bool trying)
{
	if (trying)
	{
		tryPosition = dir;
		currentPosition = position + tryPosition;
	}

	else
	{
		MoveTo(position + dir);
	}

}
void GSNurbsPoint::MoveTo(const GSVec3D &dis)
{
	currentPosition = position = dis;
	tryPosition.setValue(0, 0, 0);
}

void GSNurbsPoint::SetParent(GSNurbsCurve *p)
{
	parentCurve = p;
}

bool GSNurbsPoint::IsAtPoint(const GSVec3D &position, const float &detectionLimit) const
{
	return (position - currentPosition).length() < detectionLimit;
}