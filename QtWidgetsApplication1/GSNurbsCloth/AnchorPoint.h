#pragma once

#include <GSNurbsVec3D.h>
#include <string>


//支持部分改版前代码
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
	//位置朝向与上方向
	//与模拟内核中的pnh同名
	GSVec3D p;
	GSVec3D n;
	GSVec3D h;
};