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

	//��ǰ����λ�Ƿ�ָ��
	//û�б�ָ���Ļ�����������Ƭ��ʱ��ᱻָ��ΪĬ��λ��
	//֮����Ϊtrue������û�б��false�Ļ��ᣨ��������ν��
	bool aPointExist;
	AnchorPoint aPoint;

	bool activated;


	//�ײ�����offset(��һ��Ƭ)
	PieceTexCoordInfo texCoord;
};


class GSNurbsPiece {

public:
	int id;
	
	double radius;

	std::string name;

	//ѡ��״̬
	bool isSelected;

	//���߻���һ��������Ƭ��
	bool isLine;

	//����Ƭ
	//Ϊ0ʱ��ʾ����һ������Ƭ
	GSNurbsPiece *parentPiece;

	//������
	std::list<GSNurbsCurve> curves;
	//�ڷ���
	std::list<GSNurbsPiece> innerPieces;
	//�ڿ�
	std::list<GSNurbsPiece> innerDarts;

	//��Χ��
	GSVec3D maxPoint;
	GSVec3D minPoint;

	//������������ת������
	GSVec3D scalePointU;
	GSVec3D scalePointD;
	GSVec3D scalePointL;
	GSVec3D scalePointR;
	GSVec3D scalePointUL;
	GSVec3D scalePointUR;
	GSVec3D scalePointDL;
	GSVec3D scalePointDR;
	GSVec3D rotatePoint;




	///��ģ����ͼ����Ĺ���ʵ�ֲ���
	//�ײ���������ݣ�������
	GSPieceTexCoordInfo texInfo;
	


	//������ʾ�б��vobjID
	int id_designView;

public:

	//������ɢ�㡢��Χ�к�������ת��
	void Refresh();

	//����ѡ��״̬
	void SetSelected(bool selected);

	//�����Ƿ�����Ƭ��
	bool IsContainPoint(const GSVec3D &position) const;
	//����Ƿ�Ϊ�ڿ׻�����
	bool IsInner();

	void SetParent(GSNurbsPiece *piece) { parentPiece = piece; }

	//��λ����
	void Move(const GSVec3D &distance, bool trying = false);
	//�������Ҫ�������ڱߵĵ�ַ�����û�����ڱ��򷵻�0��������ʾ
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

	//����
	//���ѵ�ǰ�벿��id���䣬��벿��ΪnewID
	void SplitCurve(int newID, GSNurbsCurve *curve, const GSVec3D &position);
	GSNurbsCurve * NextCurve(GSNurbsCurve *curve);
	GSNurbsCurve * PrevCurve(GSNurbsCurve *curve);
	//ɾ��Ŀ���ߣ������ڵ����������ߵ��������˵㵥��������
	//��ȻҪ����һ���������滹������
	//���piece��curve����<=4�ᵼ��ɾ����piece
	//����Ĭ��curve����>=4��ǰ��������������ϲ�������
	void DeleteCurve(GSNurbsCurve *curve);

	//ɾ��ָ������
	void DeleteInnerPiece(const GSNurbsPiece *innerPiece);
	//ɾ��ָ���ڿ�
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
	//3D���湦��

	//����anchor
	void SetAnchor(const double *p, const double *n, const double *h);

public:
	//construct function
	GSNurbsPiece(int newID, GSNurbsPiece *parent = 0, std::string newName = "��Ƭ")
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