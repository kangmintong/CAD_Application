#pragma once

#include <GSNurbsVec3D.h>
#include <string>


//֧�ֲ��ָİ�ǰ����
//#include <QVector3D>
//#include <QString>

class AnchorPoint
{
public:
	AnchorPoint()
	{
		name = "Position";
	}
	AnchorPoint(std::string &_name)
	{
		name = _name;
	}
	AnchorPoint(std::string &_name, GSVec3D &position, GSVec3D &direction, GSVec3D &right)
	{
		name = _name;
		p = position;
		n = direction;
		h = right;
	}
	/*AnchorPoint(QString _name, QVector3D &position, QVector3D &direction, QVector3D &right)
	{
		name = std::string(_name.toLocal8Bit());
		p.setValue(position.x(), position.y(), position.z());
		n.setValue(direction.x(), direction.y(), direction.z());
		h.setValue(right.x(), right.y(), right.z());
	}*/

	std::string name;
	//λ�ó������Ϸ���
	//��ģ���ں��е�pnhͬ��
	GSVec3D p;
	GSVec3D n;
	GSVec3D h;
};