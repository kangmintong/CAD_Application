#include "GSNurbsCurve.h"
#include "GSNurbsPiece.h"
#include "GSNurbsDecltype.h"


#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))



bool GSNurbsCurve::IsPointOnLine(const GSVec3D &point, const GSVec3D &p1, const GSVec3D &p2, float detectionLimit)
{
	if ((p1.x() - p2.x()) == 0)
	{
		float dist = abs(point.x() - p1.x());
		float max_x = max(p1.x(), p2.x());
		float max_y = max(p1.y(), p2.y());

		float min_x = min(p1.x(), p2.x());
		float min_y = min(p1.y(), p2.y());

		return 	dist < detectionLimit &&
			point.x() < max_x + detectionLimit &&
			point.x() > min_x - detectionLimit &&
			point.y() < max_y + detectionLimit &&
			point.y() > min_y - detectionLimit;
	}

	float a = (p2.y() - p1.y()) / (p1.x() - p2.x());
	float b = 1;
	float c = -a * p1.x() - b * p1.y();
	float dist = abs(a*point.x() + b * point.y() + c) / sqrt(a*a + 1);

	float max_x = max(p1.x(), p2.x());
	float max_y = max(p1.y(), p2.y());

	float min_x = min(p1.x(), p2.x());
	float min_y = min(p1.y(), p2.y());


	return 	dist < detectionLimit &&
		point.x() < max_x + detectionLimit &&
		point.x() > min_x - detectionLimit &&
		point.y() < max_y + detectionLimit &&
		point.y() > min_y - detectionLimit;
}

int GSNurbsCurve::GetVecIdPercent(float percentage)
{
	int c1sId = int(this->discretePointCoordinates.size() * percentage) - 1; 
	if (c1sId < 0) c1sId = 0;

	return c1sId;
}

GSVec3D GSNurbsCurve::GetVecPercent(float percentage)
{
	int id = GetVecIdPercent(percentage);

	auto it = this->discretePointCoordinates.begin();
	std::advance(it, id);

	return *it;
}

GSNurbsCurve * GSNurbsCurve::NextCurve()
{
	if (parentPiece == 0) return 0;
	return parentPiece->NextCurve(this);
}

GSNurbsCurve * GSNurbsCurve::PrevCurve()
{
	if (parentPiece == 0) return 0;
	return parentPiece->PrevCurve(this);
}

void GSNurbsCurve::Refresh() {
	
	for (auto &p : points)
	{
		p.SetParent(this);
	}

	discretePointCoordinates.clear();

	maxPoint.setValue(-99999999.0f, -99999999.0f, 0.0f);
	minPoint.setValue(99999999.0f, 99999999.0f, 0.0f);
	

	

	Vector_Point3Df newPoints;

	if (points.size() > 2)
	{
		for (auto& p : points)
		{
			newPoints.push_back(PLib::Point3Df(p.GetPosition().x(), p.GetPosition().y(), 0));
		}
	}
	else                                                                                                                                                                     
	{
		GSNurbsPoint pf = points.front();
		GSNurbsPoint pb = points.back();
		newPoints.push_back(PLib::Point3Df(pf.GetPosition().x(), pf.GetPosition().y(), 0));
		newPoints.push_back(PLib::Point3Df(
			(pf.GetPosition().x() + pb.GetPosition().x()) / 2, 
			(pf.GetPosition().y() + pb.GetPosition().y()) / 2,
			0));
		newPoints.push_back(PLib::Point3Df(pb.GetPosition().x(), pb.GetPosition().y(), 0));
	}

	PLib::NurbsCurvef curCurve;
	curCurve.globalInterp(newPoints, NURBS_DEG);


	float u = 0.0f;
	float du = 1.0f / NURBS_U_MAX/10;
	while (u <= 1.0)
	{
		auto point = curCurve.hpointAt(u);
		discretePointCoordinates.push_back(GSVec3D(point.x(), point.y(), 0.0f));
		maxPoint.setX(max(maxPoint.x(), point.x()));
		maxPoint.setY(max(maxPoint.y(), point.y()));
		minPoint.setX(min(minPoint.x(), point.x()));
		minPoint.setY(min(minPoint.y(), point.y()));
		u += du;
	}


}

void GSNurbsCurve::SetSelected(bool selected)
{
	isSelected = selected;
}

bool GSNurbsCurve::IsContainPoint(const GSVec3D &position, const float &detectionLimit)
{
	//默认在这之前已经调用Refresh更新当前点
	if (points.size() == 2)
	{
		return IsPointOnLine(position, points.front().GetPosition(), points.back().GetPosition(), detectionLimit);
	}
	else
	{
		for (auto iter = discretePointCoordinates.begin(); iter != discretePointCoordinates.end();iter++)
		{
			auto second = iter;
			second++;
			if (second == discretePointCoordinates.end()) return false;
			if( IsPointOnLine(position, *iter, *second, detectionLimit)) return true;
		}
	}
	return false;
}

void GSNurbsCurve::ExtendCurve(const GSVec3D &position)
{
	points.push_back(GSNurbsPoint(position));
	points.back().SetParent(this);
	Refresh();
}

void GSNurbsCurve::AddNurbsPoint(const GSVec3D &position)
{
	//定位：新点在哪两个point之间
	//调用这个函数时已经确定这个位置在曲线上


	//直线的情况
	if (points.size() == 2)
	{
		auto it = points.begin();
		it++;
		points.insert(it, GSNurbsPoint(position));
		Refresh();
		return;

	}

	//曲线的情况
	//从头到尾遍历points
	
	int count = 0;
	auto dummyPoints = points;

	for (auto iter = discretePointCoordinates.begin(); iter != discretePointCoordinates.end(); iter++)
	{
		auto second = iter;
		second++;

		if (second == discretePointCoordinates.end()) break;

		if (IsPointOnLine(dummyPoints.front().GetPosition(), *iter, *second, ABS_DETECTION_LIMIT))
		{
			dummyPoints.pop_front();
			count++;
			if (dummyPoints.size() < 2) break;
		}


		if (IsPointOnLine(position, *iter, *second, ABS_DETECTION_LIMIT))
		{
			break;
		}
		
	}

	//得到的count就是这个点前面有几个节点
	auto it = points.begin();
	std::advance(it, count);
	points.insert(it, GSNurbsPoint(position));
	

	Refresh();
}


//剔除某点
void GSNurbsCurve::DeletePoint(GSNurbsPoint *pointInList)
{
	//检验
	//有些多余??
	bool check = false;
	for (auto &p : points)
	{
		if (&p == pointInList)
		{
			check = true;
		}
	}
	if (check == false) return;

	//这种情况应该删除这个curve，另作考虑
	if (points.size() == 2) return;

	auto it = points.begin();
	while (&(*it) != pointInList)	it++;
	points.erase(it);

	Refresh();
	return;
}


void GSNurbsCurve::Move(const GSVec3D &distance, bool trying)
{
	for(auto &p:points)
	{
		p.Move(distance, trying);
	}
	Refresh();
}
void GSNurbsCurve::Scale(const GSVec3D &anchor, float scale, bool trying)
{
	if (scale == 1) return;
	for (auto &p : points)
	{
		GSVec3D dist = p.position - anchor;
		dist *= scale - 1;
		p.Move(dist, trying);
	}
	Refresh();

}
void GSNurbsCurve::Scale(const GSVec3D &anchor, float scaleX, float scaleY, bool trying)
{
	if (scaleX == 1 && scaleY == 1) return;
	for (auto &p : points)
	{
		GSVec3D distY = p.position - anchor;
		distY.setX(0);
		distY *= scaleY - 1;
		GSVec3D distX = p.position - anchor;
		distX.setY(0);
		distX *= scaleX - 1;
		p.Move(distX + distY, trying);
	}
	Refresh();
}
void GSNurbsCurve::ScaleX(const GSVec3D &anchor, float scale, bool trying)
{
	if (scale == 1) return;
	for (auto &p : points)
	{
		GSVec3D dist = p.position - anchor;
		dist.setY(0);
		dist *= scale - 1;
		p.Move(dist, trying);
	}
	Refresh();

}
void GSNurbsCurve::ScaleY(const GSVec3D &anchor, float scale, bool trying)
{
	if (scale == 1) return;
	for (auto &p : points)
	{
		GSVec3D dist = p.position - anchor;
		dist.setX(0);
		dist *= scale - 1;
		p.Move(dist, trying);
	}
	Refresh();

}
void GSNurbsCurve::Rotate(const GSVec3D &anchor, const float &degree, bool trying)
{
	for (auto &p : points)
	{
		GSVec3D up(0.0f, 1.0f, 0.0f);
		GSVec3D dist = p.position - anchor;
		dist.normalize();

		float oriDir = dist.cross(up).z() <= 0 ? 1 : -1;
		float oriDegree = acos(dist.dot(up)) / 3.1415926f * 180.0f * oriDir;

		float deg =  degree -  oriDegree;

		float l = abs((p.position - anchor).length());

		GSVec3D res(anchor.x() + l*sin( deg / 180 * 3.1415926f),
					anchor.y() + l*cos( deg / 180 * 3.1415926f),
					0.0f);

		p.Move(res- p.position, trying);
	}
	Refresh();
}

//获取总长度
float GSNurbsCurve::GetLength() const
{
	float finalLenth = 0;
	auto iter = discretePointCoordinates.begin();
	for (int i = 0; i < discretePointCoordinates.size() - 1; i++)
	{
		auto nextIter = iter;
		nextIter++;
		finalLenth += (*iter - *nextIter).length();
		iter++;
	}
	return finalLenth;

}

float GSNurbsCurve::GetLengthToEnd(const GSVec3D & pnt)
{
	
	//此时应该保证那个点在线上

	auto nearestPnt = discretePointCoordinates.begin();
	float miniumDist = 999.9f;
	for (auto iter = discretePointCoordinates.begin(); iter != discretePointCoordinates.end(); iter++)
	{
		float dist = (*iter - pnt).length();
		if (miniumDist > dist)
		{
			miniumDist = dist;
			nearestPnt = iter;
		}
	}

	float len = 0.0f;
	for (auto iter = nearestPnt; iter != discretePointCoordinates.end(); iter++)
	{
		auto second = iter;
		second++;
		if (second == discretePointCoordinates.end()) break;

		len += (*iter - *second).length();
	}
	return len;
}
