#pragma once
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPaintEvent>
#include <QKeyEvent>
#include <vector>
#include "MyGraphicsItem.h"
#include "MyGSCloth.h"
#include "GSCloth.h"
#include <map>
#include <qpainterpath.h>
#include <qdialog.h>
#include "qpushbutton.h"
#include <qdialog.h>
#include <qaction.h>
#include <qmessagebox.h>
#include <qstring.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qgridlayout.h>
#include <qgroupbox.h>
#include "ui_QtWidgetsApplication1.h"
#include <qcheckbox.h>
#include <qaction.h>
#include "QtWidgetsApplication1.h"
#include <qicon.h>
#include "ui_QtWidgetsApplication1.h"



class Draw_Manager;
class MyGraphicsScene : public QGraphicsScene
{

	Q_OBJECT
		Ui::QtWidgetsApplication1Class ui;
public:
	QColor color;
	int moving;
	std::string mode;
	MyGraphicsItem* lastitem;
	std::vector<QPointF> points;
	std::vector<QPointF> control_points;
	std::vector<QPointF> bounding_recs;
	std::vector<MyGraphicsItem*> Items;
	MyGraphicsItem* item;
	MyGraphicsItem* cur_item;
	MyGraphicsItem* llastitem;
	GSNurbsPiece* choose_piece;
	GSCloth* cloth;
	GSNurbsCurve* Mycurve;
	GSNurbsPiece* Mypiece;
	explicit MyGraphicsScene(QObject *parent = 0);
	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void SetMode(std::string);
	std::map<GSNurbsCurve*, MyGraphicsItem*> m;
	int times;
	QPointF Lstart;
	int shift;
	QPointF p;
	QDialog* pDialog;
	QCheckBox* c3;
	int moving_id;
	QPointF StartPoint;
	int SmoothTime;
	QRadioButton* q3, *q4;

	GSNurbsPiece* newpiece;
	GSNurbsCurve* ncurve1;
	GSNurbsCurve* ncurve2;
	GSNurbsCurve* ncurve3;
	GSNurbsCurve* ncurve4;

	QPainterPath* path;
	Draw_Manager* drawmanager;
signals:

public slots:
	void on_enter_clicked();

};
