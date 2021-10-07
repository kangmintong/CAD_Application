#pragma once

#include <vector>
#include <list>
#include "GSNurbsPoint.h"



class GSNurbsPoint;
class GSNurbsPiece;

class GSNurbsCurve{

public:
	
	int id;

	//选中状态
	bool isSelected;

	//父衣片
	GSNurbsPiece *parentPiece; 

	//节点List
	std::list<GSNurbsPoint> points;

	//分段后点坐标，可用于绘制以及位置检测，不用在每次绘制过程中重新计算
	//在任意操作中都调用一下更新函数，更新这个list和包围盒
	std::list<GSVec3D> discretePointCoordinates;

	//包围盒
	GSVec3D maxPoint;
	GSVec3D minPoint;
	
public:

	//更新离散点和包围盒
	void Refresh();

	//设置选中状态
	void SetSelected(bool selected);

	//检查点是否在线上
	bool IsContainPoint(const GSVec3D &position, const float &detectionLimit);

	//延长曲线,在指定位置添加一个新点
	//也可用于添加第一个点
	void ExtendCurve(const GSVec3D &position);

	//增加节点
	//由于一般在这之前都会调用IsContainPoint,所以不用检出限做检测
	void AddNurbsPoint(const GSVec3D &position);

	void SetParent(GSNurbsPiece *piece) { parentPiece = piece; }

	//剔除某点
	void DeletePoint(GSNurbsPoint *pointInList);

	//移位操作
	void Move(const GSVec3D &distance, bool trying = false);
	void Scale(const GSVec3D &anchor, float scale, bool trying = false);
	void Scale(const GSVec3D &anchor, float scaleX, float scaleY, bool trying = false);
	void ScaleX(const GSVec3D &anchor, float scale, bool trying = false);
	void ScaleY(const GSVec3D &anchor, float scale, bool trying = false);
	void Rotate(const GSVec3D &anchor, const float &degree, bool trying = false);
	
	//获取总长度
	float GetLength() const;

	//获取特定点到最终端点的长度(必须保证这个点在线上)
	float GetLengthToEnd(const GSVec3D &pnt);

	//一个函数,用于测定点是否在直线上
	bool IsPointOnLine(const GSVec3D &point, const GSVec3D &p1, const GSVec3D &p2, float detectionLimit);

	//根据百分比获得顶点位置
	int GetVecIdPercent(float percentage);
	GSVec3D GetVecPercent(float percentage);
	GSNurbsCurve *NextCurve();
	GSNurbsCurve *PrevCurve();

public:
	
	GSNurbsCurve(int newID, GSNurbsPiece *piece = 0)
	{
		id = newID;
		isSelected = 0;
		parentPiece = piece;
	}

	GSNurbsCurve(int newID, GSVec3D pos1, GSVec3D pos2, GSNurbsPiece *piece = 0)
	{
		id = newID;
		isSelected = 0;
		parentPiece = piece;
		points.push_back(GSNurbsPoint(pos1));
		points.push_back(GSNurbsPoint(pos2));
		for (auto &p : points)
		{
			p.SetParent(this);
		}
		Refresh();
	}

	GSNurbsCurve(int newID, std::list<GSVec3D> lstPos, GSNurbsPiece *piece = 0)
	{
		id = newID;
		isSelected = 0;
		parentPiece = piece;
		for (auto &pos : lstPos)
		{
			points.push_back(GSNurbsPoint(pos));
		}
		for (auto &p : points)
		{
			p.SetParent(this);
		}
		Refresh();
	}

};