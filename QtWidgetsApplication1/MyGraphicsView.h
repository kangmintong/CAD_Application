#pragma once
#include "QtWidgetsApplication1.h"
#include <qgraphicsview.h>


class MyGraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	explicit MyGraphicsView(QWidget *parent = 0);
	Ui::QtWidgetsApplication1Class ui;

protected:
	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent * event);
	void mouseMoveEvent(QMouseEvent *event);
signals:

public slots:

};
