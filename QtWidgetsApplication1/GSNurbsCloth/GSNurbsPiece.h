#pragma once
#include <vector>
#include <list>
#include <memory>
#include "GSNurbsCurve.h"
#include "GSNurbsDecltype.h"
#include "AnchorPoint.h"
#include "PieceTexCoord.h"





class GSPieceTexCoordInfo
{
public:
	GSPieceTexCoordInfo()
	{
		aPointExist = false;
		activated = false;
	}

	//当前放置位是否被指定
	//没有被指定的话，在生成衣片的时候会被指定为默认位置
	//之后置为true，而且没有变回false的机会（但是无所谓）
	bool aPointExist;
	AnchorPoint aPoint;

	bool activated;


	//底层纹理offset(单一衣片)
	PieceTexCoordInfo texCoord;
};


class GSNurbsPiece {

public:
	int id;
	
	double radius;

	std::string name;

	//选中状态
	bool isSelected;

	//是线还是一个环（面片）
	bool isLine;

	//父衣片
	//为0时表示这是一个外衣片
	GSNurbsPiece *parentPiece;

	//外廓线
	std::list<GSNurbsCurve> curves;
	//内缝线
	std::list<GSNurbsPiece> innerPieces;
	//内孔
	std::list<GSNurbsPiece> innerDarts;

	//包围盒
	GSVec3D maxPoint;
	GSVec3D minPoint;

	//八向拉伸点和旋转操作点
	GSVec3D scalePointU;
	GSVec3D scalePointD;
	GSVec3D scalePointL;
	GSVec3D scalePointR;
	GSVec3D scalePointUL;
	GSVec3D scalePointUR;
	GSVec3D scalePointDL;
	GSVec3D scalePointDR;
	GSVec3D rotatePoint;




	///在模拟视图里面的功能实现部分
	//底层纹理的数据，不激活
	GSPieceTexCoordInfo texInfo;
	


	//储存显示列表的vobjID
	int id_designView;

public:

	//更新离散点、包围盒和拉伸旋转点
	void Refresh();

	//设置选中状态
	void SetSelected(bool selected);

	//检查点是否在衣片内
	bool IsContainPoint(const GSVec3D &position) const;
	//检查是否为内孔或内线
	bool IsInner();

	void SetParent(GSNurbsPiece *piece) { parentPiece = piece; }

	//移位操作
	void Move(const GSVec3D &distance, bool trying = false);
	//这个函数要返回相邻边的地址，如果没有相邻边则返回0，用于显示
	GSNurbsCurve* MovePoint(GSNurbsCurve *curve, GSNurbsPoint *point, const GSVec3D &distance, bool trying = false);
	void MoveCurve(GSNurbsCurve *curve, const GSVec3D &distance, bool trying = false);
	void Scale(ScaleDirection dir, const GSVec3D &startPos, const GSVec3D &endPos, bool trying = false);
	void Scale(ScaleDirection dir, float ratio, bool trying = false);
	float GetScaleRatio(ScaleDirection dir, const GSVec3D &startPos, const GSVec3D &endPos);
	void Rotate(const GSVec3D &anchor, const float &degree, bool trying = false);
	void Resize(const GSVec3D &pos1, const GSVec3D &pos2, bool trying = false);
	void Mirror();

	void AddInnerPiece(const GSNurbsPiece &piece);
	void AddInnerDart(const GSNurbsPiece &piece);

	//分裂
	//分裂点前半部分id不变，后半部分为newID
	void SplitCurve(int newID, GSNurbsCurve *curve, const GSVec3D &position);
	GSNurbsCurve * NextCurve(GSNurbsCurve *curve);
	GSNurbsCurve * PrevCurve(GSNurbsCurve *curve);
	//删除目标线，将相邻的另外两条线的另两个端点单独连起来
	//当然要先找一下是在外面还是里面
	//如果piece中curve数量<=4会导致删掉此piece
	//这里默认curve数量>=4，前面那种情况交由上层来决定
	void DeleteCurve(GSNurbsCurve *curve);

	//删除指定内线
	void DeleteInnerPiece(const GSNurbsPiece *innerPiece);
	//删除指定内孔
	void DeleteInnerDart(const GSNurbsPiece *innerDart);

	GSVec3D GetMidPoint() { return (maxPoint + minPoint)*0.5; }
	GSVec3D GetUPoint() { return GSVec3D(GetMidPoint().x(), maxPoint.y(), 0.0f); }
	GSVec3D GetDPoint() { return  GSVec3D(GetMidPoint().x(), minPoint.y(), 0.0f); }
	GSVec3D GetLPoint() { return  GSVec3D(minPoint.x(), GetMidPoint().y(), 0.0f); }
	GSVec3D GetRPoint() { return  GSVec3D(maxPoint.x(), GetMidPoint().y(), 0.0f); }
	GSVec3D GetULPoint() { return GSVec3D(minPoint.x(), maxPoint.y(), 0.0f); }
	GSVec3D GetURPoint() { return GSVec3D(maxPoint.x(), maxPoint.y(), 0.0f); }
	GSVec3D GetDLPoint() { return GSVec3D(minPoint.x(), minPoint.y(), 0.0f); }
	GSVec3D GetDRPoint() { return GSVec3D(maxPoint.x(), minPoint.y(), 0.0f); }

	GSVec3D & GetScalePointU() { return scalePointU; }
	GSVec3D & GetScalePointD() { return scalePointD; }
	GSVec3D & GetScalePointL() { return scalePointL; }
	GSVec3D & GetScalePointR() { return scalePointR; }
	GSVec3D & GetScalePointUL() { return scalePointUL; }
	GSVec3D & GetScalePointUR() { return scalePointUR; }
	GSVec3D & GetScalePointDL() { return scalePointDL; }
	GSVec3D & GetScalePointDR() { return scalePointDR; }
	GSVec3D & GetRotatePoint() { return rotatePoint; }

	float GetLenth() { return maxPoint.x() - minPoint.x(); }
	float GetHeight() { return maxPoint.y() - minPoint.y(); }
public:

	void CreateRectangle(int* newIDpointer, const GSVec3D &pos1, const GSVec3D &pos2);
	void CreateCircle(int* newIDpointer, const GSVec3D &pos1, const GSVec3D &pos2);
	void CreateDart(int* newIDpointer, const GSVec3D &pos1, const GSVec3D &pos2);
	void GenerateLineFromCurves(int* newIDpointer, const std::list<GSNurbsCurve> &curves);
	void GeneratePieceFromCurves(int* newIDpointer, const std::list<GSNurbsCurve> &curves);
	void GeneratePieceFromVecs(int* newIDpointer, const std::list<GSVec3D> &vecs);

public:
	//3D界面功能

	//设置anchor
	void SetAnchor(const double *p, const double *n, const double *h);

public:
	//construct function
	GSNurbsPiece(int newID, GSNurbsPiece *parent = 0, std::string newName = "衣片")
	{
		id = newID;
		name = newName;
		isSelected = false;
		isLine = false;
		parentPiece = parent;
		id_designView = -1;
		radius = -1;
	}

	~GSNurbsPiece() 
	{
		parentPiece = 0;

		curves.clear();
		innerPieces.clear();
		innerDarts.clear();
	}

};