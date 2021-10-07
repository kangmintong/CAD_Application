#pragma once

#include "GSNurbsPiece.h"

class CurvePair
{

public:

	CurvePair()
	{
		first = -1;
		second = -1;
		trans = false;
		isSelected = false;

		forceFold = false;
		foldAngle = 0;
	}

	CurvePair(int c1, int c2, bool isTrans)
	{
		first = c1;
		second = c2;
		trans = isTrans;
		isSelected = false;

		forceFold = false;
		foldAngle = 0;
	}
	~CurvePair() {}

	int first;
	int second;
	bool trans; //是否同向, true表示同向
	bool isSelected;//用于突出显示

	bool forceFold; //是否强制折叠
	float foldAngle; //折叠角度(-180~180)

	void SetSelected(bool isSel);
};

class FreeCurvePair : public CurvePair
{
public:

	enum CurveDirection
	{
		SameAsCurveOrder,
		OppositeWithCurveOrder
	};

	FreeCurvePair() 
	{
		isSimple = true;
		first = -1;
		second = -1;
		trans = false;
		isSelected = false;
		forceFold = false;
		foldAngle = 0;

		curveOneStartId = -1;
		curveOneEndId = -1;
		curveOneStartPecentage = 0;
		curveOneEndPecentage= 0;
		curveOneDirection = SameAsCurveOrder;
		curveTwoStartId = -1;
		curveTwoEndId = -1;
		curveTwoStartPecentage = 0;
		curveTwoEndPecentage = 0;
		curveTwoDirection = SameAsCurveOrder;
	}
	FreeCurvePair(const CurvePair &cp)
	{
		isSimple = true;
		first = cp.first;
		second = cp.second;
		trans = cp.trans;
		isSelected = cp.isSelected;
		forceFold = false;
		foldAngle = 0;


		curveOneStartId = -1;
		curveOneEndId = -1;
		curveOneStartPecentage = 0;
		curveOneEndPecentage = 0;
		curveOneDirection = SameAsCurveOrder;
		curveTwoStartId = -1;
		curveTwoEndId = -1;
		curveTwoStartPecentage = 0;
		curveTwoEndPecentage = 0;
		curveTwoDirection = SameAsCurveOrder;
	}
	FreeCurvePair(
		int c1sID, float c1sPercentage,
		int c1eID, float c1ePercentage, CurveDirection c1Dir,
		int c2sID, float c2sPercentage,
		int c2eID, float c2ePercentage, CurveDirection c2Dir, bool isTrans)
	{
		isSimple = false;
		first = -1;
		second = -1;
		trans = isTrans;
		isSelected = false;
		forceFold = false;
		foldAngle = 0;

		curveOneStartId = c1sID;
		curveOneEndId = c1eID;
		curveOneStartPecentage = c1sPercentage;
		curveOneEndPecentage = c1ePercentage;
		curveOneDirection = c1Dir;
		curveTwoStartId = c2sID;
		curveTwoEndId = c2eID;
		curveTwoStartPecentage = c2sPercentage;
		curveTwoEndPecentage = c2ePercentage;
		curveTwoDirection = c2Dir;
	}
	~FreeCurvePair() {}

	bool isSimple; //直接缝制，逻辑与CurvePair相同

	//以下为多线条复杂自由缝合的相关参数,此时isSimple=false,first&second无效
	int curveOneStartId;
	int curveOneEndId;
	float curveOneStartPecentage;
	float curveOneEndPecentage;
	CurveDirection curveOneDirection;
	int curveTwoStartId;
	int curveTwoEndId;
	float curveTwoStartPecentage;
	float curveTwoEndPecentage;
	CurveDirection curveTwoDirection;


public:
	
};

class GSSeawingInfo
{
public:
	GSSeawingInfo() {}
	~GSSeawingInfo() {}
	
	std::list<FreeCurvePair> pairs;

	//方向相同的话,trans==true
	void AddPair(GSNurbsCurve * c1, GSNurbsCurve * c2, bool trans = true);
	void AddPair(int id1, int id2, bool trans = true);

	void AddFreePair(FreeCurvePair &pair);

	void DeletePair(GSNurbsCurve * c);
	void DeletePair(FreeCurvePair *p);
	int FindPairedCurve(GSNurbsCurve * c);

	void UnselectAll();
};

