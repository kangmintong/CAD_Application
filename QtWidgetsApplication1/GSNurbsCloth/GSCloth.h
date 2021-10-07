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
	//�����·�

public:

	GSCloth()
	{
		name = "�·�";
		commonID = 0;
		seawingInfo.pairs.clear();
	}
	~GSCloth() {}

public:
	
	std::list<GSNurbsPiece> pieces;
	GSSeawingInfo seawingInfo;
	std::string name;

	//ctrl-zЧ��
	std::list<std::list<GSNurbsPiece>> pList;
	std::list<GSSeawingInfo> sList;




public:

	//TexCoord,ͬidmap��Ϣһͬ��ʼ��
	//��Ҫ���ڿ���displayWidget�����texCoord
	PieceTexCoordInfo texCoord;





public:
	//���ڴ�����Ƭ�����߹��õ�ID
	//�ô��Ǳ�֤��Ƭ/���ߵĶ������
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


	
	//�ܶ�curve�ڲ����ж�����ȥɾ��ɾȥ�����鷳�������ṩһ��ʵʱ����Ч��pair�޳����Ĳ���
	void RefreshPair();


	bool HasPiece(GSNurbsPiece *p);
	void AddPiece(const GSNurbsPiece &p);
	//Ϊ��ʵʱ����Ƭ����ʾ�б��г�ȥ
	void RemovePiece(GSNurbsPiece *p);
	void BendPiece(GSNurbsPiece * p);
	GSNurbsPiece * GetPieceByID(int id);
	GSNurbsCurve * GetCurveByID(int id);


	/*�������⹦���õĺ����������Ķ������ʣ���������������*/
	/*isLeftSideָ����˳���߷����ϵ�leftside*/
	void AddEdgeDart(GSNurbsCurve *curve, float posPercent, float width, float depth, bool isLeftSide);

};