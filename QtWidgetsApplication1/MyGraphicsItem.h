#pragma once
#include <QGraphicsItem>
#include <QGraphicsSceneEvent>
#include <vector>
#include <string>
#include "GSNurbsCurve.h"
#include "Transform_Tools.h"
#include "GSNurbsPiece.h"
#include <map>
class MyGraphicsItem : public QGraphicsItem
{
public:
	MyGraphicsItem(std::string,GSNurbsCurve*);
	MyGraphicsItem(std::string, GSNurbsPiece*);
	QPointF start;
	QPointF bounding;
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
		QWidget *widget);
	void setColor(const QColor &color) { brushColor = color; }
	void SetMode(std::string);
	int IsSelectMode;
	std::vector<QPointF> control_points;
	
	
	int control_points_states[10000];
	GSNurbsCurve* Curve;
	GSNurbsPiece* Piece;
	QPointF P[10000];
	std::vector<QPointF> points;
	std::string mode;
	QPainterPath* path;

	void reverse(int);

	//std::map<QPointF, std::vector<GSNurbsCurve*> > M;

protected:
	
	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
	QColor brushColor;

};
