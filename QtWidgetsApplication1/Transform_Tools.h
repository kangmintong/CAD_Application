#pragma once
#include <vector>
#include <list>
#include <qpoint.h>
#include "GSNurbsVec3D.h"
#include "GSNurbsPoint.h"

class Transform_tools
{
public:
	static std::vector<QPointF>  Vec3Ds_To_QPointFs(std::list<GSVec3D>);
	static std::vector<QPointF>  GSnurbspoint_To_QPointFs(std::list<GSNurbsPoint> ps);
};