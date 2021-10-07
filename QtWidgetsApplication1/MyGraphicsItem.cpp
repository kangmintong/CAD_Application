#include "MyGraphicsItem.h"
#include <QPainter>
#include <QCursor>
#include <QKeyEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <cmath>
#include <qdebug.h>

#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)

MyGraphicsItem::MyGraphicsItem(std::string s, GSNurbsCurve* gc)
{
	brushColor = Qt::yellow;
	setFlag(QGraphicsItem::ItemIsFocusable);
	setFlag(QGraphicsItem::ItemIsMovable);
	setAcceptHoverEvents(true);
	mode = s;
	IsSelectMode = 0;
	Curve = gc;
	control_points = Transform_tools::GSnurbspoint_To_QPointFs(gc->points);
	points = Transform_tools::Vec3Ds_To_QPointFs(gc->discretePointCoordinates);
	
}

MyGraphicsItem::MyGraphicsItem(std::string s, GSNurbsPiece* p)
{
	brushColor = Qt::red;
	setFlag(QGraphicsItem::ItemIsFocusable);
	setFlag(QGraphicsItem::ItemIsMovable);
	setAcceptHoverEvents(true);
	mode = s;
	IsSelectMode = 0;
	Piece = p;
	Curve = NULL;
}

void MyGraphicsItem::reverse(int type)
{
	float midx = (Piece->minPoint.x() + Piece->maxPoint.x()) / 2;
	float midy = (Piece->minPoint.y() + Piece->maxPoint.y()) / 2;
	if (type == 0)
	{
		for (auto it = Piece->curves.begin(); it != Piece->curves.end(); it++)
		{
			for (auto itp = it->points.begin(); itp != it->points.end(); itp++)
			{
				itp->position.setX(2 * midx - itp->position.x());
			}
			for (auto itp = it->discretePointCoordinates.begin(); itp != it->discretePointCoordinates.end(); itp++)
			{
				itp->setX(2 * midx - itp->x());
			}
			it->Refresh();
		}
		Piece->Refresh();
		for (int i = 0; i < control_points.size(); i++)
		{
			control_points[i].setX(2 * midx - control_points[i].x());
		}
		
	}
	else if (type == 1)
	{
		for (int i = 0; i < points.size(); i++)
		{
			points[i].setY(2 * midy - points[i].y());
		}
		for (int i = 0; i < control_points.size(); i++)
		{
			control_points[i].setY(2 * midy - control_points[i].y());
		}
		for (auto it = Curve->points.begin(); it != Curve->points.end(); it++)
		{
			GSVec3D tempp = GSVec3D(it->position.x(), 2*midy-it->position.y(), 0);
			*it = GSNurbsPoint(tempp);
		}
		Curve->Refresh();
	}
}


void MyGraphicsItem::SetMode(std::string s)
{
	mode = s;
}

QRectF MyGraphicsItem::boundingRect() const
{
	if(mode=="HVLine") return QRectF(-1, -1, 1 + fabs(control_points[2].x() - control_points[0].x()),
		1 + fabs(control_points[2].y() - control_points[0].y()));
	if(mode== "SampleArc1") 
		return  QRectF(-1, -1, 1 + fabs((Piece->maxPoint).x() - (Piece->minPoint).x()),
			1 + fabs((Piece->maxPoint).y() - (Piece->minPoint).y()));
	return QRectF(-1, -1, 1 + fabs((Curve->maxPoint).x() - (Curve->minPoint).x()), 
		1 + fabs((Curve->maxPoint).y() - (Curve->minPoint).y()));
}

void MyGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
	QWidget *widget)
{
	if (mode == "SampleArc1")
	{
		painter->setBrush(brushColor);
		painter->setRenderHint(QPainter::Antialiasing, true);
		QPen pen;
		pen.setWidth(2);
		pen.setColor(Qt::black);
		QPointF anchor;
		anchor.setX((Piece->minPoint).x());
		anchor.setY((Piece->minPoint).y());
		
		path = new QPainterPath(QPointF(Piece->curves.begin()->discretePointCoordinates.begin()->x() -anchor.x(),
			Piece->curves.begin()->discretePointCoordinates.begin()->y() -anchor.y()));
		int cnt1 = 0 , cnt2 = 0;
		for (auto it = Piece->curves.begin();it!=Piece->curves.end();it++)
		{
			cnt1++;
			//qDebug() << it->discretePointCoordinates.begin()->x() << endl;
			for (auto itt = (it)->discretePointCoordinates.begin(); itt != (it)->discretePointCoordinates.end(); itt++)
			{
				if (it == Piece->curves.begin() && itt == (it)->discretePointCoordinates.begin()) continue;
				//qDebug() << itt->x() << ' ' << itt->y() << endl;
				path->lineTo(QPointF(itt->x() - anchor.x(), itt->y() - anchor.y()));
			}
			cnt2 = 0;
			for (auto iit = it->points.begin(); iit != it->points.end(); iit++)
			{
				cnt2++;
				if (++iit == it->points.end())
				{
					break;
				}
				--iit;
				//qDebug() << cnt1 << ' ' << cnt2 << endl;
				QPointF temp = QPointF(iit->position.x(), iit->position.y());
				control_points.push_back(temp);
				//M[temp].push_back(&(*it));
				//painter->drawEllipse(iit->position.x() - anchor.x(), iit->position.y() - anchor.y(), 8, 8);
			}
		}
		path->closeSubpath();
		painter->drawPath(*path);
		for (int j = 0; j < control_points.size(); j++)
		{
			painter->drawEllipse(control_points[j].x() - anchor.x(), control_points[j].y() - anchor.y(), 8, 8);
		}
		return;
	}

	if (mode == "HighLight")
	{
		painter->setRenderHint(QPainter::Antialiasing, true);
		QPen pen;
		pen.setWidth(6);
		pen.setColor(Qt::black);
		painter->setPen(pen);
		QPointF anchor;
		anchor.setX((Curve->minPoint).x());
		anchor.setY((Curve->minPoint).y());
		for (int i = 0; i < points.size() && i < 10000; i++)
		{
			P[i] = points[i];
			P[i].setX(P[i].x() - anchor.x());
			P[i].setY(P[i].y() - anchor.y());
			//qDebug() << P[i].x() << ' ' << P[i].y() << endl;
		}
		painter->drawPoints(P, Min(points.size(), 10000));

		for (int j = 0; j < control_points.size(); j++)
		{
			painter->drawEllipse(control_points[j].x() - anchor.x(), control_points[j].y() - anchor.y(), 8, 8);
		}
		return;

	}
	QPointF anchor;
	anchor.setX((Curve->minPoint).x());
	anchor.setY((Curve->minPoint).y());
	painter->setBrush(brushColor);
	painter->setRenderHint(QPainter::Antialiasing, true);
	QPen pen;
	pen.setWidth(2);
	pen.setColor(Qt::black);
	if (mode == "HVCut") pen.setStyle(Qt::DashLine);
	if (mode == "HVCut_Line") pen.setWidth(5);
	painter->setPen(pen);
	if (mode == "Line"|| mode == "Arc"||mode=="Rect"||mode=="Arc2")
	{
		for (int i = 0; i < points.size() && i < 10000; i++)
		{
			P[i] = points[i];
			P[i].setX(P[i].x() - anchor.x());
			P[i].setY(P[i].y() - anchor.y());
			//qDebug() << P[i].x() << ' ' << P[i].y() << endl;
		}
		
		painter->drawPoints(P, Min(points.size(),10000));
		
		for (int j = 0; j < control_points.size(); j++)
		{
			painter->drawEllipse(control_points[j].x() - anchor.x(), control_points[j].y() - anchor.y(), 8, 8);
		}
		
	}
	/*else if (mode == "ClosedShape")
	{
		path=new QPainterPath(QPointF(Curve->points.begin()->position.x()-anchor.x(),Curve->points.begin()->position.y()-anchor.y()));
		for (auto it = ++(Curve->discretePointCoordinates.begin()); it != Curve->discretePointCoordinates.end(); it++)
		{

			path->lineTo(QPointF(it->x() - anchor.x(), it->y() - anchor.y()));
		}
		path->closeSubpath();
		painter->drawPath(*path);
		for (int j = 0; j < control_points.size(); j++)
		{
			painter->drawEllipse(control_points[j].x()-anchor.x(), control_points[j].y()-anchor.y(), 8, 8);
		}
	}*/
	else if (mode == "HVLine")
	{
		anchor.setX(control_points[0].x());
		anchor.setY(control_points[0].y());
		painter->drawLine(QPointF(control_points[0].x()-anchor.x(), control_points[0].y()-anchor.y()),
			QPointF(control_points[1].x()-anchor.x(), control_points[1].y()-anchor.y()));
		painter->drawLine(QPointF(control_points[1].x() - anchor.x(), control_points[1].y() - anchor.y()),
			QPointF(control_points[2].x() - anchor.x(), control_points[2].y() - anchor.y()));
		painter->drawEllipse(control_points[0].x() - anchor.x(), control_points[0].y() - anchor.y(), 8, 8);
		painter->drawEllipse(control_points[2].x() - anchor.x(), control_points[2].y() - anchor.y(), 8, 8);
	}
	else if (mode == "HVCut")
	{
		
		anchor.setX(control_points[0].x());
		anchor.setY(control_points[0].y());
		painter->drawLine(QPointF(control_points[0].x() - anchor.x(), control_points[0].y() - anchor.y()),
			QPointF(control_points[1].x() - anchor.x(), control_points[1].y() - anchor.y()));
	}
	else if (mode == "HVCut_Line")
	{
		anchor.setX(control_points[0].x());
		anchor.setY(control_points[0].y());
		pen.setWidth(5);
		if(fabs(control_points[0].x()- control_points[1].x())<20) 
			painter->drawLine(QPointF(control_points[1].x() - anchor.x(), control_points[1].y() - anchor.y()-5),
				QPointF(control_points[1].x() - anchor.x(), control_points[1].y() - anchor.y()+5));
		else painter->drawLine(QPointF(control_points[1].x() - anchor.x()-5, control_points[1].y() - anchor.y()),
			QPointF(control_points[1].x() - anchor.x()+5, control_points[1].y() - anchor.y()));
	}
	
}

// 鼠标按下事件处理函数，设置被点击的图形项获得焦点，并改变光标外观
void MyGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	setFocus();
	setCursor(Qt::ClosedHandCursor);
}

// 键盘按下事件处理函数，判断是否是向下方向键，如果是，则向下移动图形项
void MyGraphicsItem::keyPressEvent(QKeyEvent *event)
{
	
	if (event->key() == Qt::Key_Down)
		moveBy(0, 10);
}

// 悬停事件处理函数，设置光标外观和提示
void MyGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	
	setCursor(Qt::CrossCursor);
	setToolTip("I am item");
}

void MyGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	
	setCursor(Qt::ArrowCursor);
}


// 右键菜单事件处理函数，为图形项添加一个右键菜单
void MyGraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	QMenu menu;
	QAction *moveAction = menu.addAction("move back");
	QAction *actAction = menu.addAction("test");
	QAction *selectedAction = menu.exec(event->screenPos());
	if (selectedAction == moveAction) {
		setPos(0, 0);
	}
}
void MyGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (!IsSelectMode) return;
	QGraphicsItem::mouseMoveEvent(event);
}
