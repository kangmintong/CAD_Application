#include "Transform_Tools.h"

std::vector<QPointF>  Transform_tools::GSnurbspoint_To_QPointFs(std::list<GSNurbsPoint> ps)
{
	std::vector<QPointF> v;
	for (auto &p : ps)
	{
		GSVec3D pp = p.currentPosition;
		QPointF pf;
		pf.setX(pp.x());
		pf.setY(pp.y());
		v.push_back(pf);
	}
	return v;
}

std::vector<QPointF> Transform_tools::Vec3Ds_To_QPointFs(std::list<GSVec3D> ps)
{
	std::vector<QPointF> v;
	for (auto &p : ps)
	{
		QPointF pf;
		pf.setX(p.x());
		pf.setY(p.y());
		v.push_back(pf);
	}
	return v;
}