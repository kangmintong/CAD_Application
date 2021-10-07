#pragma once

#include <vector>
#include <list>
#include "GSNurbsPoint.h"



class GSNurbsPoint;
class GSNurbsPiece;

class GSNurbsCurve{

public:
	
	int id;

	//ѡ��״̬
	bool isSelected;

	//����Ƭ
	GSNurbsPiece *parentPiece; 

	//�ڵ�List
	std::list<GSNurbsPoint> points;

	//�ֶκ�����꣬�����ڻ����Լ�λ�ü�⣬������ÿ�λ��ƹ��������¼���
	//����������ж�����һ�¸��º������������list�Ͱ�Χ��
	std::list<GSVec3D> discretePointCoordinates;

	//��Χ��
	GSVec3D maxPoint;
	GSVec3D minPoint;
	
public:

	//������ɢ��Ͱ�Χ��
	void Refresh();

	//����ѡ��״̬
	void SetSelected(bool selected);

	//�����Ƿ�������
	bool IsContainPoint(const GSVec3D &position, const float &detectionLimit);

	//�ӳ�����,��ָ��λ�����һ���µ�
	//Ҳ��������ӵ�һ����
	void ExtendCurve(const GSVec3D &position);

	//���ӽڵ�
	//����һ������֮ǰ�������IsContainPoint,���Բ��ü���������
	void AddNurbsPoint(const GSVec3D &position);

	void SetParent(GSNurbsPiece *piece) { parentPiece = piece; }

	//�޳�ĳ��
	void DeletePoint(GSNurbsPoint *pointInList);

	//��λ����
	void Move(const GSVec3D &distance, bool trying = false);
	void Scale(const GSVec3D &anchor, float scale, bool trying = false);
	void Scale(const GSVec3D &anchor, float scaleX, float scaleY, bool trying = false);
	void ScaleX(const GSVec3D &anchor, float scale, bool trying = false);
	void ScaleY(const GSVec3D &anchor, float scale, bool trying = false);
	void Rotate(const GSVec3D &anchor, const float &degree, bool trying = false);
	
	//��ȡ�ܳ���
	float GetLength() const;

	//��ȡ�ض��㵽���ն˵�ĳ���(���뱣֤�����������)
	float GetLengthToEnd(const GSVec3D &pnt);

	//һ������,���ڲⶨ���Ƿ���ֱ����
	bool IsPointOnLine(const GSVec3D &point, const GSVec3D &p1, const GSVec3D &p2, float detectionLimit);

	//���ݰٷֱȻ�ö���λ��
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