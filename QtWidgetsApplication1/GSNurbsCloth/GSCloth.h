#pragma once

#include <list>

#include "GSSeawingInfo.h"

#include "GSNurbsVec3D.h"
#include "GSNurbsPoint.h"
#include "GSNurbsCurve.h"

#include "GSNurbsPiece.h"


#include "PieceTexCoord.h"




class OpenGLDesignWidget;

class GSCloth
{
	//单件衣服

public:

	GSCloth()
	{
		name = "衣服";
		commonID = 0;
		seawingInfo.pairs.clear();
	}
	~GSCloth() {}

public:
	
	std::list<GSNurbsPiece> pieces;
	GSSeawingInfo seawingInfo;
	std::string name;

	//ctrl-z效果
	std::list<std::list<GSNurbsPiece>> pList;
	std::list<GSSeawingInfo> sList;




public:

	//TexCoord,同idmap信息一同初始化
	//主要用于控制displayWidget里面的texCoord
	PieceTexCoordInfo texCoord;





public:
	//用于储存衣片与缝合线共用的ID
	//用处是保证衣片/曲线的独立编号
	int commonID;

	std::list<GSNurbsPiece> &GetPiecesVector()
	{
		return pieces; 
	}
	GSSeawingInfo * GetSeawingInfo() 
	{
		return &seawingInfo; 
	}
	std::string GetName() { return name; }
	void SetName(std::string &n) { name = n; }


	
	//很多curve在操作中动来动去删来删去，很麻烦，这里提供一个实时将无效的pair剔除掉的操作
	void RefreshPair();


	bool HasPiece(GSNurbsPiece *p);
	void AddPiece(const GSNurbsPiece &p);
	//为了实时将衣片从显示列表中除去
	void RemovePiece(GSNurbsPiece *p);
	void BendPiece(GSNurbsPiece * p);
	GSNurbsPiece * GetPieceByID(int id);
	GSNurbsCurve * GetCurveByID(int id);


	/*用于特殊功能用的函数，放在哪都不合适，就往这里塞好了*/
	/*isLeftSide指的是顺曲线方向上的leftside*/
	void AddEdgeDart(GSNurbsCurve *curve, float posPercent, float width, float depth, bool isLeftSide);

};