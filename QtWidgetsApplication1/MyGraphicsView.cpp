#include "MyGraphicsView.h"

#include <QKeyEvent>

MyGraphicsView::MyGraphicsView(QWidget *parent) :
	QGraphicsView(parent)
{
}

void MyGraphicsView::keyPressEvent(QKeyEvent *event)
{
	//qDebug("*********MyView::keyPressEvent***************");
	switch (event->key())
	{
	case Qt::Key_Left:
		scale(1.2, 1.2);
		break;
	case Qt::Key_Right:
		scale(1 / 1.2, 1 / 1.2);
		break;
	case Qt::Key_Up:
		rotate(30);
		break;
	}
	QGraphicsView::keyPressEvent(event);
}

void MyGraphicsView::mousePressEvent(QMouseEvent *event)
{
	//qDebug("************MyView::mousePressEvent*****************");
	QGraphicsView::mousePressEvent(event);
}

void MyGraphicsView::paintEvent(QPaintEvent *event)
{
	//qDebug("************MyView::paintEvent*****************");
	QGraphicsView::paintEvent(event);
}

void MyGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
	//qDebug("************MyView::mouseMoveEvent*****************");
	QGraphicsView::mouseMoveEvent(event);
}
