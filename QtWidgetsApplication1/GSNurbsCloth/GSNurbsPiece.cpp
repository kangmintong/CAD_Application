#include "GSNurbsPiece.h"
#include <iostream>
#include <vector>
#include <algorithm>

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

//更新
void GSNurbsPiece::Refresh()
{
	
	for (auto &piece : innerDarts)
	{
		piece.SetParent(this);
		piece.Refresh();
	}
	for (auto &piece : innerPieces)
	{
		piece.SetParent(this);
		piece.Refresh();
	}
	for (auto &curve : curves)
	{
		curve.SetParent(this);
		curve.Refresh();
	}

	float max_x = -9999999.0f;
	float max_y = -9999999.0f;
	float min_x = +9999999.0f;
	float min_y = +9999999.0f;

	for (auto &curve : curves)
	{
		max_x = max(max_x, curve.maxPoint.x());
		max_y = max(max_y, curve.maxPoint.y());
		min_x = min(min_x, curve.minPoint.x());
		min_y = min(min_y, curve.minPoint.y());
	}

	maxPoint.setValue(max_x, max_y, 0.0f);
	minPoint.setValue(min_x, min_y, 0.0f);

	GSVec3D mid = GetMidPoint();

	float interval = 0.1f;
	scalePointU.setValue(mid.x(), maxPoint.y() + interval, 0.0f);
	scalePointD.setValue(mid.x(), minPoint.y() - interval, 0.0f);
	scalePointL.setValue(minPoint.x() - interval, mid.y(), 0.0f);
	scalePointR.setValue(maxPoint.x() + interval, mid.y(), 0.0f);
	scalePointUL.setValue(minPoint.x() - interval, maxPoint.y() + interval, 0.0f);
	scalePointUR.setValue(maxPoint.x() + interval, maxPoint.y() + interval, 0.0f);
	scalePointDL.setValue(minPoint.x() - interval, minPoint.y() - interval, 0.0f);
	scalePointDR.setValue(maxPoint.x() + interval, minPoint.y() - interval, 0.0f);
	rotatePoint.setValue(mid.x(), maxPoint.y() + interval *2, 0.0f);

	for (auto &piece : innerDarts)
	{
		for (auto &c : piece.curves)
		{
			for (auto &p : c.points)
			{
				p.MoveTo(p.currentPosition);
			}
		}
	}
	for (auto &piece : innerPieces)
	{
		for (auto &c : piece.curves)
		{
			for (auto &p : c.points)
			{
				p.MoveTo(p.currentPosition);
			}
		}
	}
	for (auto &curve : curves)
	{
		for (auto &p : curve.points)
			{
				p.MoveTo(p.currentPosition);
			}
	}
}

//设置选中状态
void GSNurbsPiece::SetSelected(bool selected)
{
	isSelected = selected;
}

//检查点是否在衣片内
bool GSNurbsPiece::IsContainPoint(const GSVec3D &position) const
{
	//简易方法：直接测试包围盒
	if (position.x() < maxPoint.x() &&
		position.x() > minPoint.x() &&
		position.y() < maxPoint.y() &&
		position.y() > minPoint.y())
		return true;
	else
		return false;
}

bool GSNurbsPiece::IsInner()
{
	if (parentPiece) return true;
	return false;
}

//移位操作
void GSNurbsPiece::Move(const GSVec3D &distance, bool trying )
{
	for (auto &piece : innerDarts)
	{
		piece.Move(distance, trying);
	}
	for (auto &piece : innerPieces)
	{
		piece.Move(distance, trying);
	}
	for (auto &curve : curves)
	{
		curve.Move(distance, trying);
	}

	if(!trying)
		Refresh();
}
GSNurbsCurve* GSNurbsPiece::MovePoint(GSNurbsCurve *curve, GSNurbsPoint *point, const GSVec3D &distance, bool trying)
{
	if (point != &curve->points.front() && point != &curve->points.back())
	{
		point->Move(distance, trying);
		curve->Refresh();
		if (!trying) Refresh();
		return 0;
	}
	else if (point == &curve->points.front())
	{
		GSNurbsCurve *preCurve;
		if (&curves.front() == curve)
		{
			if(!isLine)
				preCurve = &curves.back();
			else
			{
				preCurve = 0;
			}
		}
		else
		{
			auto iter = curves.begin();
			while (&(*iter) != curve) iter++;
			iter--;
			preCurve = &(*iter);
		}
		point->Move(distance, trying);
		if(preCurve) preCurve->points.back().Move(distance, trying);

		curve->Refresh();
		if (preCurve) preCurve->Refresh();
		if (!trying) Refresh();
		return preCurve;
	}
	else
	{
		GSNurbsCurve *nextCurve;
		if (&curves.back() == curve)
		{
			if (!isLine)
				nextCurve = &curves.front();
			else
			{
				nextCurve = 0;
			}
		}
		else
		{
			auto iter = curves.begin();
			while (&(*iter) != curve) iter++;
			iter++;
			nextCurve = &(*iter);
		}
		point->Move(distance, trying);
		if (nextCurve) nextCurve->points.front().Move(distance, trying);

		curve->Refresh();
		if (nextCurve) nextCurve->Refresh();
		if (!trying) Refresh();
		return nextCurve;
	}

}
void GSNurbsPiece::MoveCurve(GSNurbsCurve *curve, const GSVec3D &distance, bool trying)
{
	if (curves.size() == 1)
	{
		curve->Move(distance, trying);
		return;
	}

	GSNurbsCurve *preCurve;
	GSNurbsCurve *nextCurve;

	auto iter = curves.begin();
	while (curve != &(*iter)) iter++;
	if (curve == &curves.front())
	{
		preCurve = &curves.back();
		iter++;
		nextCurve = &(*iter);
	}
	else if (curve == &curves.back())
	{
		nextCurve = &curves.front();
		iter--;
		preCurve = &(*iter);
	}
	else
	{
		iter--;
		preCurve = &(*iter);
		iter++;
		iter++;
		nextCurve = &(*iter);
	}

	curve->Move(distance, trying);
	preCurve->points.back().Move(distance, trying);
	nextCurve->points.front().Move(distance, trying);

	curve->Refresh();
	preCurve->Refresh();
	nextCurve->Refresh();

	if (!trying) Refresh();

	return;

}
float GSNurbsPiece::GetScaleRatio(ScaleDirection dir, const GSVec3D &startPos, const GSVec3D &endPos)
{
	GSVec3D anchor;

	switch (dir)
	{
	case U:
		anchor = GetDPoint();
		return (endPos.y() - anchor.y()) / (startPos.y() - anchor.y());
		break;
	case D:
		anchor = GetUPoint();
		return (endPos.y() - anchor.y()) / (startPos.y() - anchor.y());
		break;
	case L:
		anchor = GetRPoint();
		return (endPos.x() - anchor.x()) / (startPos.x() - anchor.x());
		break;
	case R:
		anchor = GetLPoint();
		return (endPos.x() - anchor.x()) / (startPos.x() - anchor.x());
		break;
	case UL:
		anchor = GetDRPoint();
		return   max((endPos.x() - anchor.x()) / (startPos.x() - anchor.x()),
			(endPos.y() - anchor.y()) / (startPos.y() - anchor.y()));
		break;
	case UR:
		anchor = GetDLPoint();
		return  max((endPos.x() - anchor.x()) / (startPos.x() - anchor.x()),
			(endPos.y() - anchor.y()) / (startPos.y() - anchor.y()));
		break;
	case DL:
		anchor = GetURPoint();
		return  max((endPos.x() - anchor.x()) / (startPos.x() - anchor.x()),
			(endPos.y() - anchor.y()) / (startPos.y() - anchor.y()));
		break;
	case DR:
		anchor = GetULPoint();
		return max((endPos.x() - anchor.x()) / (startPos.x() - anchor.x()),
			(endPos.y() - anchor.y()) / (startPos.y() - anchor.y()));
		break;
	default:
		return 1;
		break;
	}
}
void GSNurbsPiece::Scale(ScaleDirection dir, float ratio, bool trying)
{
	GSVec3D anchor;
	float scaleX = 1;
	float scaleY = 1;

	switch (dir)
	{
	case U:
		anchor = GetDPoint();
		scaleY = ratio;
		break;
	case D:
		anchor = GetUPoint();
		scaleY = ratio;
		break;
	case L:
		anchor = GetRPoint();
		scaleX = ratio;
		break;
	case R:
		anchor = GetLPoint();
		scaleX = ratio;
		break;
	case UL:
		anchor = GetDRPoint();
		scaleX = scaleY = ratio;
		break;
	case UR:
		anchor = GetDLPoint();
		scaleX = scaleY = ratio;
		break;
	case DL:
		anchor = GetURPoint();
		scaleX = scaleY = ratio;
		break;
	case DR:
		anchor = GetULPoint();
		scaleX = scaleY = ratio;
		break;
	default:
		break;
	}

	for (auto &ip : innerPieces)
	{
		for (auto &c : ip.curves)
		{
			c.Scale(anchor, scaleX, scaleY, trying);
		}
	}
	for (auto &id : innerDarts)
	{
		for (auto &c : id.curves)
		{
			c.Scale(anchor, scaleX, scaleY, trying);
		}
	}
	for (auto &c : curves)
	{
		c.Scale(anchor, scaleX, scaleY, trying);
	}
	
	if (!trying)
		Refresh();
}
void GSNurbsPiece::Scale(ScaleDirection dir, const GSVec3D &startPos, const GSVec3D &endPos, bool trying)
{
	GSVec3D anchor;
	float scaleX = 1;
	float scaleY = 1;

	switch (dir)
	{
	case U:
		anchor = GetDPoint();
		scaleY = (endPos.y() - anchor.y()) / (startPos.y() - anchor.y());
		break;
	case D:
		anchor = GetUPoint();
		scaleY = (endPos.y() - anchor.y()) / (startPos.y() - anchor.y());
		break;
	case L:
		anchor = GetRPoint();
		scaleX = (endPos.x() - anchor.x()) / (startPos.x() - anchor.x());
		break;
	case R:
		anchor = GetLPoint();
		scaleX = (endPos.x() - anchor.x()) / (startPos.x() - anchor.x());
		break;
	case UL:
		anchor = GetDRPoint();
		scaleX = scaleY = max((endPos.x() - anchor.x()) / (startPos.x() - anchor.x()),
			(endPos.y() - anchor.y()) / (startPos.y() - anchor.y()));
		break;
	case UR:
		anchor = GetDLPoint();
		scaleX = scaleY = max((endPos.x() - anchor.x()) / (startPos.x() - anchor.x()),
			(endPos.y() - anchor.y()) / (startPos.y() - anchor.y()));
		break;
	case DL:
		anchor = GetURPoint();
		scaleX = scaleY = max((endPos.x() - anchor.x()) / (startPos.x() - anchor.x()),
			(endPos.y() - anchor.y()) / (startPos.y() - anchor.y()));
		break;
	case DR:
		anchor = GetULPoint();
		scaleX = scaleY = max((endPos.x() - anchor.x()) / (startPos.x() - anchor.x()),
			(endPos.y() - anchor.y()) / (startPos.y() - anchor.y()));
		break;
	default:
		break;
	}


	if (scaleX == scaleY)
	{
		for (auto &ip : innerPieces)
		{
			for (auto &c : ip.curves)
			{
				c.Scale(anchor, scaleX, trying);
			}
		}
		for (auto &id : innerDarts)
		{
			for (auto &c : id.curves)
			{
				c.Scale(anchor, scaleX, trying);
			}
		}
		for (auto &c : curves)
		{
			c.Scale(anchor, scaleX, trying);
		}
	}
	else
	{
		for (auto &ip : innerPieces)
		{
			for (auto &c : ip.curves)
			{
				c.ScaleX(anchor, scaleX, trying);
				c.ScaleY(anchor, scaleY, trying);
			}
		}
		for (auto &id : innerDarts)
		{
			for (auto &c : id.curves)
			{
				c.ScaleX(anchor, scaleX, trying);
				c.ScaleY(anchor, scaleY, trying);
			}
		}
		for (auto &c : curves)
		{
			c.ScaleX(anchor, scaleX, trying);
			c.ScaleY(anchor, scaleY, trying);
		}
	}


	if (!trying)
		Refresh();
}
void GSNurbsPiece::Rotate(const GSVec3D &anchor, const float &degree, bool trying)
{
	for (auto &ip : innerPieces)
	{
		for (auto &c : ip.curves)
		{
			c.Rotate(anchor, degree, trying);
		}
	}
	for (auto &id : innerDarts)
	{
		for (auto &c : id.curves)
		{
			c.Rotate(anchor, degree, trying);
		}
	}
	for (auto &c : curves)
	{
		c.Rotate(anchor, degree, trying);
	}

	if(!trying) Refresh();
}
void GSNurbsPiece::Mirror()
{

	GSVec3D mid = GetMidPoint();

	for (auto &ip : innerPieces)
	{
		for (auto &c : ip.curves)
		{
			for (auto &p : c.points)
			{
				p.Move(GSVec3D(2 * mid.x() - 2 * p.GetPosition().x(), 0.0f, 0.0f));
			}
		}
	}
	for (auto &id : innerDarts)
	{
		for (auto &c : id.curves)
		{
			for (auto &p : c.points)
			{
				p.Move(GSVec3D(2 * mid.x() - 2 * p.GetPosition().x(), 0.0f, 0.0f));
			}
		}
	}
	for (auto &c : curves)
	{
		for (auto &p : c.points)
		{
			p.Move(GSVec3D(2 * mid.x() - 2 * p.GetPosition().x(), 0.0f, 0.0f));
		}
	}

	Refresh();
}
void GSNurbsPiece::Resize(const GSVec3D &pos1, const GSVec3D &pos2, bool trying)
{
	float max_x = max(pos1.x(), pos2.x());
	float max_y = max(pos1.y(), pos2.y());
	float min_x = min(pos1.x(), pos2.x());
	float min_y = min(pos1.y(), pos2.y());

	GSVec3D newMaxPoint(max_x, max_y, 0.0f);
	GSVec3D newMinPoint(min_x, min_y, 0.0f);

	float scaleX = -(pos1.x() - pos2.x()) / (maxPoint.x() - minPoint.x());
	float scaleY = -(pos1.y() - pos2.y()) / (maxPoint.y() - minPoint.y());

	GSVec3D anchor = minPoint;
	for (auto &ip : innerPieces)
	{
		for (auto &c : ip.curves)
		{
			c.Scale(anchor, scaleX, scaleY, trying);
		}
	}
	for (auto &id : innerDarts)
	{
		for (auto &c : id.curves)
		{
			c.Scale(anchor, scaleX, scaleY, trying);
		}
	}
	for (auto &c : curves)
	{
		c.Scale(anchor, scaleX, scaleY, trying);
	}
		
	if(!trying)
		Refresh();
	
}


void GSNurbsPiece::AddInnerPiece(const GSNurbsPiece &piece)
{
	innerPieces.push_back(piece);
	innerPieces.back().parentPiece = this;
	Refresh();
}
void GSNurbsPiece::AddInnerDart(const GSNurbsPiece &piece)
{
	innerDarts.push_back(piece);
	innerDarts.back().parentPiece = this;
	Refresh();
}

//分裂
void GSNurbsPiece::SplitCurve(int newID, GSNurbsCurve *curve, const GSVec3D &position)
{
	curve->AddNurbsPoint(position);

	GSNurbsCurve *newCurve=NULL;

	for (auto iter = curves.begin(); iter != curves.end(); iter++)
	{
		if (curve == &(*iter))
		{
			iter++;
			curves.insert(iter, GSNurbsCurve(newID));
			iter--;
			newCurve = &(*iter);
			break;
		}
	}

	
	int count = 0;
	for (auto &point : curve->points)
	{
		count++;
		if ((point.GetPosition() - position).length() < 0.001f)
		{
			break;
		}
	}

	std::list<GSNurbsPoint> pre = curve->points;
	std::list<GSNurbsPoint> nxt = curve->points;

	for (int i = 0; i < curve->points.size() - count; i++)
	{
		pre.pop_back();
	}
	for (int i = 0; i < count - 1; i++)
	{
		nxt.pop_front();
	}


	curve->points = pre;
	newCurve->points = nxt;


	Refresh();
		
}

GSNurbsCurve * GSNurbsPiece::NextCurve(GSNurbsCurve * curve)
{
	for (auto iter = curves.begin(); iter != curves.end(); iter++)
	{
		if (iter->id == curve->id)
		{
			iter++;
			if (iter == curves.end()) return &(curves.front());
			return &(*iter);
		}
	}
	return nullptr;
}

GSNurbsCurve * GSNurbsPiece::PrevCurve(GSNurbsCurve * curve)
{
	for (auto iter = curves.begin(); iter != curves.end(); iter++)
	{
		if (iter->id == curve->id)
		{
			if (iter == curves.begin()) return &(curves.back());
			iter--;
			return &(*iter);
		}
	}
	return nullptr;
}

void GSNurbsPiece::DeleteCurve(GSNurbsCurve *curve)
{
	if (!isLine)
	{
		//删除此边和一条相邻边，将另一条相邻边拉伸过去
		GSNurbsCurve *preCurve=NULL;
		GSNurbsCurve *nextCurve=NULL;

		//寻找相邻边
		auto iter = curves.begin();
		if (curve == &(*iter))
		{
			iter++;
			nextCurve = &(*iter);
			preCurve = &curves.back();
		}
		else if(curve == &curves.back())
		{
			iter = curves.end();
			iter--; iter--;
			preCurve = &(*iter);
			nextCurve = &curves.front();
		}
		else
		{
			for (iter = curves.begin(); iter != curves.end(); iter++)
			{
				auto iterNext = iter;
				iterNext++;
				//一直没找到说明操作失败了
				if (iterNext == curves.end()) return;
				if (curve == &(*iterNext))
				{
					preCurve = &(*iter);
					iterNext++;
					nextCurve = &(*iterNext);
					break;
				}
			}
		}
		
		GSVec3D pos = nextCurve->points.back().GetPosition();
		while (preCurve->points.size() != 1) preCurve->points.pop_back();
		
		//删除两条边
		for (iter = curves.begin(); iter != curves.end(); iter++)
		{
			if (curve == &(*iter))
			{
				curves.erase(iter);
				break;
			}
		}
		for (iter = curves.begin(); iter != curves.end(); iter++)
		{
			if (nextCurve == &(*iter))
			{
				curves.erase(iter);
				break;
			}
		}
		preCurve->ExtendCurve(pos);

		if (parentPiece == 0) Refresh();
		else parentPiece->Refresh();
		return;
	}
	else
	{
		if (curve == &curves.front())
		{
			curves.pop_front();
			parentPiece->Refresh();
			return;
		}
		else if (curve == &curves.back())
		{
			curves.pop_back();
			parentPiece->Refresh();
			return;
		}
		else
		{
			//和环差不多


			GSNurbsCurve *preCurve=NULL;
			GSNurbsCurve *nextCurve=NULL;

			//寻找相邻边
			auto iter = curves.begin();
			if (curve == &(*iter))
			{
				iter++;
				nextCurve = &(*iter);
				preCurve = &curves.back();
			}
			else if (curve == &curves.back())
			{
				iter = curves.end();
				iter--; iter--;
				preCurve = &(*iter);
				nextCurve = &curves.front();
			}
			else
			{
				for (iter = curves.begin(); iter != curves.end(); iter++)
				{
					auto iterNext = iter;
					iterNext++;
					//一直没找到说明操作失败了
					if (iterNext == curves.end()) return;
					if (curve == &(*iterNext))
					{
						preCurve = &(*iter);
						iterNext++;
						nextCurve = &(*iterNext);
						break;
					}
				}
			}

			GSVec3D pos = nextCurve->points.back().GetPosition();
			while (preCurve->points.size() != 1) preCurve->points.pop_back();

			//删除两条边
			for (iter = curves.begin(); iter != curves.end(); iter++)
			{
				if (curve == &(*iter))
				{
					curves.erase(iter);
					break;
				}
			}
			for (iter = curves.begin(); iter != curves.end(); iter++)
			{
				if (nextCurve == &(*iter))
				{
					curves.erase(iter);
					break;
				}
			}
			preCurve->ExtendCurve(pos);

			if (parentPiece == 0) Refresh();
			else parentPiece->Refresh();
		}
		return;
	}
}


//删除指定内线
void GSNurbsPiece::DeleteInnerPiece(const GSNurbsPiece *innerPiece)
{
	for (auto iter = innerPieces.begin(); iter != innerPieces.end(); iter++)
	{
		if (innerPiece == &(*iter))
		{
			innerPieces.erase(iter);
			return;
		}
	}
}
//删除指定内孔
void GSNurbsPiece::DeleteInnerDart(const GSNurbsPiece *innerDart)
{
	for (auto iter = innerDarts.begin(); iter != innerDarts.end(); iter++)
	{
		if (innerDart == &(*iter))
		{
			innerDarts.erase(iter);
			return;
		}
	}
}

void GSNurbsPiece::CreateRectangle(int* newIDpointer, const GSVec3D &pos1, const GSVec3D &pos2)
{
	curves.clear();
	GSVec3D UR;
	GSVec3D DL;

	UR.setX(max(pos1.x(), pos2.x()));
	UR.setY(max(pos1.y(), pos2.y()));
	DL.setX(min(pos1.x(), pos2.x()));
	DL.setY(min(pos1.y(), pos2.y()));

	GSVec3D UL(DL.x(), UR.y(), 0.0f);
	GSVec3D DR(UR.x(), DL.y(), 0.0f);

	curves.push_back(GSNurbsCurve((*newIDpointer)++, UL, DL));
	curves.push_back(GSNurbsCurve((*newIDpointer)++, DL, DR));
	curves.push_back(GSNurbsCurve((*newIDpointer)++, DR, UR));
	curves.push_back(GSNurbsCurve((*newIDpointer)++, UR, UL));

	Refresh();
}
void GSNurbsPiece::CreateCircle(int* newIDpointer, const GSVec3D &pos1, const GSVec3D &pos2)
{
	curves.clear();
	//12个点确定一个圆
	//分4段
	GSVec3D mid = pos1;
	float radius = (pos1 - pos2).length();

	GSVec3D U = mid + GSVec3D(0.0f, radius, 0.0f);
	GSVec3D D = mid + GSVec3D(0.0f, -radius, 0.0f);
	GSVec3D L = mid + GSVec3D(-radius, 0.0f, 0.0f);
	GSVec3D R = mid + GSVec3D(radius, 0.0f, 0.0f);

	GSVec3D UL1 = mid + GSVec3D(-radius * sin(30 * 3.1415926f / 180), +radius *cos(30 * 3.1415926f / 180), 0.0f);
	GSVec3D UL2 = mid + GSVec3D(-radius * sin(60 * 3.1415926f / 180), +radius *cos(60 * 3.1415926f / 180), 0.0f);
	GSVec3D DL1 = mid + GSVec3D(-radius * sin(60 * 3.1415926f / 180), -radius *cos(60 * 3.1415926f / 180), 0.0f);
	GSVec3D DL2 = mid + GSVec3D(-radius * sin(30 * 3.1415926f / 180), -radius *cos(30 * 3.1415926f / 180), 0.0f);
	GSVec3D DR1 = mid + GSVec3D(+radius * sin(30 * 3.1415926f / 180), -radius *cos(30 * 3.1415926f / 180), 0.0f);
	GSVec3D DR2 = mid + GSVec3D(+radius * sin(60 * 3.1415926f / 180), -radius *cos(60 * 3.1415926f / 180), 0.0f);
	GSVec3D UR1 = mid + GSVec3D(+radius * sin(60 * 3.1415926f / 180), +radius *cos(60 * 3.1415926f / 180), 0.0f);
	GSVec3D UR2 = mid + GSVec3D(+radius * sin(30 * 3.1415926f / 180), +radius *cos(30 * 3.1415926f / 180), 0.0f);
	
	std::list<GSVec3D> cUL;
	std::list<GSVec3D> cDL;
	std::list<GSVec3D> cDR;
	std::list<GSVec3D> cUR;

	cUL.push_back(U);
	cUL.push_back(UL1);
	cUL.push_back(UL2);
	cUL.push_back(L);
	
	cDL.push_back(L);
	cDL.push_back(DL1);
	cDL.push_back(DL2);
	cDL.push_back(D);
	
	cDR.push_back(D);
	cDR.push_back(DR1);
	cDR.push_back(DR2);
	cDR.push_back(R);
	
	cUR.push_back(R);
	cUR.push_back(UR1);
	cUR.push_back(UR2);
	cUR.push_back(U);

	curves.push_back(GSNurbsCurve((*newIDpointer)++, cUL));
	curves.push_back(GSNurbsCurve((*newIDpointer)++, cDL));
	curves.push_back(GSNurbsCurve((*newIDpointer)++, cDR));
	curves.push_back(GSNurbsCurve((*newIDpointer)++, cUR));

	Refresh();
}
void GSNurbsPiece::CreateDart(int* newIDpointer, const GSVec3D &pos1, const GSVec3D &pos2)
{
	curves.clear();
	GSVec3D UR;
	GSVec3D DL;

	UR.setX(max(pos1.x(), pos2.x()));
	UR.setY(max(pos1.y(), pos2.y()));
	DL.setX(min(pos1.x(), pos2.x()));
	DL.setY(min(pos1.y(), pos2.y()));

	GSVec3D mid = (UR + DL) *0.5f;
	GSVec3D U(mid.x(), UR.y(), 0.0f);
	GSVec3D D(mid.x(), DL.y(), 0.0f);
	GSVec3D L(DL.x(), mid.y(), 0.0f);
	GSVec3D R(UR.x(), mid.y(), 0.0f);

	curves.push_back(GSNurbsCurve((*newIDpointer)++, U, L));
	curves.push_back(GSNurbsCurve((*newIDpointer)++, L, D));
	curves.push_back(GSNurbsCurve((*newIDpointer)++, D, R));
	curves.push_back(GSNurbsCurve((*newIDpointer)++, R, U));

	Refresh();
}


void GSNurbsPiece::GenerateLineFromCurves(int* newIDpointer, const std::list<GSNurbsCurve> &srcCurves)
{
	curves.clear();
	for (auto &c : srcCurves)
	{
		GSNurbsCurve newCurve = c;
		newCurve.id = (*newIDpointer)++;
		curves.push_back(newCurve);
	} 
	isLine = true;

	Refresh();
}
void GSNurbsPiece::GeneratePieceFromCurves(int* newIDpointer, const std::list<GSNurbsCurve> &srcCurves)
{
	//其实和GenerateLineFromCurves一样
	GenerateLineFromCurves(newIDpointer, srcCurves);

	isLine = false;
}
void GSNurbsPiece::GeneratePieceFromVecs(int * newIDpointer, const std::list<GSVec3D>& vecs)
{
	std::list<GSNurbsCurve> curves;

	for (auto iter = vecs.begin(); iter != vecs.end(); iter++)
	{
		auto nxt = iter;
		nxt++;
		if (nxt == vecs.end()) nxt = vecs.begin();

		curves.push_back(GSNurbsCurve(-1, *iter, *nxt));
	}

	GeneratePieceFromCurves(newIDpointer, curves);
}


void GSNurbsPiece::SetAnchor(const double * p, const double * n, const double * h)
{
	texInfo.aPointExist = true;
	texInfo.aPoint.p.setValue(p[0], p[1], p[2]);
	texInfo.aPoint.n.setValue(n[0], n[1], n[2]);
	texInfo.aPoint.h.setValue(h[0], h[1], h[2]);
}