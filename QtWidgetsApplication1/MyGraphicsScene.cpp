#include "MyGraphicsScene.h"
#include "MyGraphicsItem.h"
#include <iostream>
#include <qdebug.h>
#include <cmath>
#include "GSNurbsPiece.h"
#define Min(a,b) (a<b?a:b)
#define Max(a,b) (a>b?a:b)

MyGraphicsScene::MyGraphicsScene(QObject *parent) :
	QGraphicsScene(parent)
{
	clearFocus();
	points.clear();
	lastitem = NULL;
	cloth = new GSCloth();
	Mypiece = new GSNurbsPiece(1);
	Mypiece->isLine = true;
	cloth->pieces.push_back(*Mypiece);
	times = 0;
	shift = 0;
	SmoothTime = 0;
	moving = 0;
	color = QColor(255, 255, 0);
	
}

void MyGraphicsScene::SetMode(std::string s)
{
	mode = s;
}

void MyGraphicsScene::keyPressEvent(QKeyEvent *event)
{
	if ((mode == "HVLine"||mode=="HVReverse")&&shift == 0 && event->key() == Qt::Key_Shift)
	{
		shift = 1;
	}
	else if ((mode == "HVLine" || mode == "HVReverse")&&shift == 1 && event->key() == Qt::Key_Shift) shift = 0;
	QGraphicsScene::keyPressEvent(event);
}

double dis(QPointF p1, QPointF p2)
{
	return std::sqrt((p1.x() - p2.x())*(p1.x() - p2.x()) + (p1.y() - p2.y())*(p1.y() - p2.y()));
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	p = event->scenePos();

	if (mode == "Line")
	{
		
		
		QPointF start, end;
		start.setX(p.x() - 40);
		start.setY(p.y() - 40);
		end.setX(p.x() + 40);
		end.setY(p.y() + 40);
		points.push_back(start);
		points.push_back(end);

		GSVec3D pos1 = GSVec3D(start.x(), start.y(), 0);
		GSVec3D pos2 = GSVec3D(end.x(), end.y(), 0);
		Mycurve = new GSNurbsCurve(0,pos1,pos2);


		Mypiece->curves.push_back(*Mycurve);
		Mycurve->parentPiece = Mypiece;
			

		QPointF anchor;
		anchor.setX(Min(points[0].x(), points[1].x()));
		anchor.setY(Min(points[0].y(), points[1].y()));
			
		item = new MyGraphicsItem("Line",Mycurve);
		item->setColor(color);
		item->setPos(Mycurve->minPoint.x(),Mycurve->minPoint.y());
		this->addItem(item);
		points.clear();
		lastitem = item;
		Items.push_back(item);
		
		/*QLabel* aixLabel = new QLabel("Ñ¡ÔñºÍÒÆ¶¯");
		ui.statusBar->addWidget(aixLabel);*/
		mode = "Select";
		
	}
	else if (mode == "Select"&&moving == 0)
	{
		int flag = 0;
		for (int i = 0; i < Items.size(); i++)
		{

			for (int j = 0; j < (Items[i]->control_points).size(); j++)
			{

				if (dis(p, (Items[i]->control_points)[j]) < 8)
				{
					(Items[i]->control_points_states)[j] = 1;
					moving_id = j;
					flag = 1;
					moving = 1;
					item = Items[i];
					break;
				}

			}
			//if (flag&&(Items[i]->Curve->parentPiece->isLine == true||Items[i]->mode=="ClosedShape")) break;
			if (flag) break;
			if (Items[i]->mode!="SampleArc1"&& Items[i]->mode != "ClosedShape"&&Items[i]->Curve->IsContainPoint(GSVec3D(p.x(), p.y(), 0),4))
			{
				if (Items[i]->Curve->parentPiece->isLine == true)
				{
					moving = 2;
				}
				else
				{
					moving = 3;
				}
					
				
				StartPoint.setX(p.x());
				StartPoint.setY(p.y());
				moving_id = i;
				item = Items[i];
				
				break;
			}

			if (Items[i]->mode == "ClosedShape"&&p.x() >= Items[i]->Curve->minPoint.x()
				&& p.x() <= Items[i]->Curve->maxPoint.x() && p.y() >= Items[i]->Curve->minPoint.y()
				&& p.y() <= Items[i]->Curve->maxPoint.y())
			{
				moving = 4;
				StartPoint.setX(p.x());
				StartPoint.setY(p.y());
				moving_id = i;
				item = Items[i];
				break;
			}
		}
	}
	else if (mode == "Select"&&moving == 1)
	{
		moving = 0;
		(item->control_points_states)[moving_id] = 0;
	}
	else if (mode == "Select"&&moving == 2)
	{
		moving = 0;
		
	}
	else if (mode == "Select"&&moving == 3)
	{
		moving = 0;

	}
	else if (mode == "Select"&&moving == 4)
	{
		moving = 0;

	}
	else if (mode == "Arc")
	{
		QPointF start, mid, end;
		start.setX(p.x() - 70);
		start.setY(p.y() - 70);
		mid.setX(p.x());
		mid.setY(p.y());
		end.setX(p.x() + 70);
		end.setY(p.y() + 70);

		GSVec3D pos1 = GSVec3D(start.x(), start.y(), 0);
		GSVec3D pos2 = GSVec3D(mid.x(), mid.y(), 0);
		GSVec3D pos3 = GSVec3D(end.x(), end.y(), 0);
		std::list<GSVec3D> temp_list;
		temp_list.push_back(pos1);
		temp_list.push_back(pos2);
		temp_list.push_back(pos3);

		Mycurve = new GSNurbsCurve(0, temp_list);
		Mypiece->curves.push_back(*Mycurve);
		Mycurve->parentPiece = Mypiece;

		QPointF anchor;
		anchor.setX(Mycurve->minPoint.x());
		anchor.setY(Mycurve->minPoint.y());

		item = new MyGraphicsItem("Arc", Mycurve);
		item->setColor(color);
		item->setPos(Mycurve->minPoint.x(), Mycurve->minPoint.y());
		this->addItem(item);
		points.clear();
		lastitem = item;
		Items.push_back(item);
		mode = "Select";
	}
	else if (mode == "Arc2")
	{
		QPointF p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12;
		p1.setX(p.x() - 60);
		p1.setY(p.y() );
		p2.setX(p.x() - 30);
		p2.setY(p.y() - 30);
		p3.setX(p.x() + 30);
		p3.setY(p.y() + 30);
		p4.setX(p.x() + 60);
		p4.setY(p.y() );
		
		GSVec3D pos1 = GSVec3D(p1.x(), p1.y(), 0);
		GSVec3D pos2 = GSVec3D(p2.x(), p2.y(), 0);
		GSVec3D pos3 = GSVec3D(p3.x(), p3.y(), 0);
		GSVec3D pos4 = GSVec3D(p4.x(), p4.y(), 0);
		
		std::list<GSVec3D> nlist;
		nlist.push_back(pos1);
		nlist.push_back(pos2);
		nlist.push_back(pos3);
		nlist.push_back(pos4);
		
		Mycurve = new GSNurbsCurve(0, nlist);

		Mypiece->curves.push_back(*Mycurve);
		Mycurve->parentPiece = Mypiece;
		
		item = new MyGraphicsItem("Arc2", Mycurve);
		item->setColor(color);
		QPointF pos;
		pos.setX(Mycurve->minPoint.x());
		pos.setY(Mycurve->minPoint.y());
		item->setPos(pos.x(), pos.y());
		this->addItem(item);
		points.clear();
		lastitem = item;
		update();
		Items.push_back(item);
		mode = "Select";
	}
	else if (mode == "SampleArc1")
	{
		QPointF p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13;
		p1.setX(p.x() - 120);
		p1.setY(p.y() - 60);
		p2.setX(p.x() - 90);
		p2.setY(p.y() - 90);
		p3.setX(p.x() - 60);
		p3.setY(p.y() - 140);
		p4.setX(p.x() - 30);
		p4.setY(p.y() - 160);
		p5.setX(p.x());
		p5.setY(p.y() - 98);
		p6.setX(p.x() + 30);
		p6.setY(p.y() - 160);
		p7.setX(p.x() + 60);
		p7.setY(p.y() - 140);
		p8.setX(p.x() + 90);
		p8.setY(p.y() - 90);
		p9.setX(p.x() + 120);
		p9.setY(p.y() - 60);
		p10.setX(p.x() + 120);
		p10.setY(p.y() - 60);
		p11.setX(p.x() + 90);
		p11.setY(p.y() + 60);
		p12.setX(p.x());
		p12.setY(p.y() + 50);
		p13.setX(p.x() - 90);
		p13.setY(p.y() + 60);
		GSVec3D pos1 = GSVec3D(p1.x(), p1.y(), 0);
		GSVec3D pos2 = GSVec3D(p2.x(), p2.y(), 0);
		GSVec3D pos3 = GSVec3D(p3.x(), p3.y(), 0);
		GSVec3D pos4 = GSVec3D(p4.x(), p4.y(), 0);
		GSVec3D pos5 = GSVec3D(p5.x(), p5.y(), 0);
		GSVec3D pos6 = GSVec3D(p6.x(), p6.y(), 0);
		GSVec3D pos7 = GSVec3D(p7.x(), p7.y(), 0);
		GSVec3D pos8 = GSVec3D(p8.x(), p8.y(), 0);
		GSVec3D pos9 = GSVec3D(p9.x(), p9.y(), 0);
		GSVec3D pos10 = GSVec3D(p10.x(), p10.y(), 0);
		GSVec3D pos11 = GSVec3D(p11.x(), p11.y(), 0);
		GSVec3D pos12 = GSVec3D(p12.x(), p12.y(), 0);
		GSVec3D pos13 = GSVec3D(p13.x(), p13.y(), 0);

		newpiece = new GSNurbsPiece(0);
		std::list<GSVec3D> nlist;
		nlist.push_back(pos1);
		nlist.push_back(pos2);
		nlist.push_back(pos3);
		nlist.push_back(pos4);
		//nlist.push_back(pos5);
		nlist.push_back(pos6);
		nlist.push_back(pos7);
		nlist.push_back(pos8);
		/*nlist.push_back(pos9);*/
		nlist.push_back(pos10);
		ncurve1 = new GSNurbsCurve(0, nlist);
		ncurve1->Refresh();
		ncurve1->parentPiece = newpiece;
		newpiece->curves.push_back(*ncurve1);
		//qDebug() << "nnn "<<ncurve1->discretePointCoordinates.begin()->x() << endl;

		ncurve2 = new GSNurbsCurve(0, pos10, pos11);
		ncurve2->Refresh();
		ncurve2->parentPiece = newpiece;
		newpiece->curves.push_back(*ncurve2);

		nlist.clear();
		nlist.push_back(pos11);
		nlist.push_back(pos12);
		nlist.push_back(pos13);
		ncurve3 = new GSNurbsCurve(0, nlist);
		ncurve3->Refresh();
		ncurve3->parentPiece = newpiece;
		newpiece->curves.push_back(*ncurve3);

		ncurve4= new GSNurbsCurve(0, pos13, pos1);
		ncurve4->parentPiece = newpiece;
		newpiece->curves.push_back(*ncurve4);

		newpiece->Refresh();
		cloth->AddPiece(*newpiece);
		
		item = new MyGraphicsItem("SampleArc1", newpiece);
		item->setColor(color);
		item->setPos(newpiece->minPoint.x(), newpiece->minPoint.y());
		this->addItem(item);
		update();
		Items.push_back(item);
		mode = "Select";
	}
	else if (mode == "SampleArc2")
	{
	QPointF p1, p2, p3, p4, p5, p6;
	p1.setX(p.x() - 150);
	p1.setY(p.y() - 100);
	p2.setX(p.x() - 50);
	p2.setY(p.y() - 130);
	p3.setX(p.x() + 50);
	p3.setY(p.y() - 70);
	p4.setX(p.x() + 150);
	p4.setY(p.y() - 100);
	p5.setX(p.x() + 150 );
	p5.setY(p.y() + 80 );
	p6.setX(p.x() - 120);
	p6.setY(p.y() + 80);
	
	GSVec3D pos1 = GSVec3D(p1.x(), p1.y(), 0);
	GSVec3D pos2 = GSVec3D(p2.x(), p2.y(), 0);
	GSVec3D pos3 = GSVec3D(p3.x(), p3.y(), 0);
	GSVec3D pos4 = GSVec3D(p4.x(), p4.y(), 0);
	GSVec3D pos5 = GSVec3D(p5.x(), p5.y(), 0);
	GSVec3D pos6 = GSVec3D(p6.x(), p6.y(), 0);
	
	newpiece = new GSNurbsPiece(0);
	std::list<GSVec3D> nlist;
	nlist.push_back(pos1);
	nlist.push_back(pos2);
	nlist.push_back(pos3);
	nlist.push_back(pos4);
	
	ncurve1 = new GSNurbsCurve(0, nlist);
	ncurve1->Refresh();
	ncurve1->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve1);
	

	ncurve2 = new GSNurbsCurve(0, pos4, pos5);
	ncurve2->Refresh();
	ncurve2->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve2);

	nlist.clear();
	nlist.push_back(pos5);
	nlist.push_back(pos6);
	ncurve3 = new GSNurbsCurve(0, nlist);
	ncurve3->Refresh();
	ncurve3->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve3);

	ncurve4 = new GSNurbsCurve(0, pos6, pos1);
	ncurve4->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve4);

	newpiece->Refresh();
	cloth->AddPiece(*newpiece);

	item = new MyGraphicsItem("SampleArc1", newpiece);
	item->setColor(color);
	item->setPos(newpiece->minPoint.x(), newpiece->minPoint.y());
	this->addItem(item);
	update();
	Items.push_back(item);
	mode = "Select";
	}
	else if (mode == "SampleArc3")
	{
	QPointF p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12;
	p1.setX(p.x() - 150);
	p1.setY(p.y() - 100);
	p2.setX(p.x() - 0);
	p2.setY(p.y() - 70);
	p3.setX(p.x() + 150);
	p3.setY(p.y() - 100);
	p4.setX(p.x() + 200);
	p4.setY(p.y() - 40);
	p5.setX(p.x() + 170);
	p5.setY(p.y() );
	p6.setX(p.x() + 150);
	p6.setY(p.y() -50 );
	p7.setX(p.x() + 150);
	p7.setY(p.y() + 150);
	p8.setX(p.x() - 150);
	p8.setY(p.y() + 150);
	p9.setX(p.x() - 150);
	p9.setY(p.y() - 50);
	p10.setX(p.x() - 170);
	p10.setY(p.y());
	p11.setX(p.x() - 200);
	p11.setY(p.y() - 40);
	p12.setX(p.x() - 150);
	p12.setY(p.y() - 100);
	

	GSVec3D pos1 = GSVec3D(p1.x(), p1.y(), 0);
	GSVec3D pos2 = GSVec3D(p2.x(), p2.y(), 0);
	GSVec3D pos3 = GSVec3D(p3.x(), p3.y(), 0);
	GSVec3D pos4 = GSVec3D(p4.x(), p4.y(), 0);
	GSVec3D pos5 = GSVec3D(p5.x(), p5.y(), 0);
	GSVec3D pos6 = GSVec3D(p6.x(), p6.y(), 0);
	GSVec3D pos7 = GSVec3D(p7.x(), p7.y(), 0);
	GSVec3D pos8 = GSVec3D(p8.x(), p8.y(), 0);
	GSVec3D pos9 = GSVec3D(p9.x(), p9.y(), 0);
	GSVec3D pos10 = GSVec3D(p10.x(), p10.y(), 0);
	GSVec3D pos11 = GSVec3D(p11.x(), p11.y(), 0);
	GSVec3D pos12 = GSVec3D(p12.x(), p12.y(), 0);

	newpiece = new GSNurbsPiece(0);
	std::list<GSVec3D> nlist;
	nlist.push_back(pos1);
	nlist.push_back(pos2);
	nlist.push_back(pos3);

	ncurve1 = new GSNurbsCurve(0, nlist);
	ncurve1->Refresh();
	ncurve1->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve1);


	ncurve2 = new GSNurbsCurve(0, pos3, pos4);
	ncurve2->Refresh();
	ncurve2->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve2);

	ncurve2 = new GSNurbsCurve(0, pos4, pos5);
	ncurve2->Refresh();
	ncurve2->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve2);

	ncurve2 = new GSNurbsCurve(0, pos5, pos6);
	ncurve2->Refresh();
	ncurve2->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve2);

	ncurve2 = new GSNurbsCurve(0, pos6, pos7);
	ncurve2->Refresh();
	ncurve2->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve2);

	ncurve2 = new GSNurbsCurve(0, pos7, pos8);
	ncurve2->Refresh();
	ncurve2->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve2);

	ncurve2 = new GSNurbsCurve(0, pos8, pos9);
	ncurve2->Refresh();
	ncurve2->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve2);

	ncurve2 = new GSNurbsCurve(0, pos9, pos10);
	ncurve2->Refresh();
	ncurve2->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve2);

	ncurve2 = new GSNurbsCurve(0, pos10, pos11);
	ncurve2->Refresh();
	ncurve2->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve2);

	ncurve2 = new GSNurbsCurve(0, pos11, pos12);
	ncurve2->Refresh();
	ncurve2->parentPiece = newpiece;
	newpiece->curves.push_back(*ncurve2);


	newpiece->Refresh();
	cloth->AddPiece(*newpiece);

	item = new MyGraphicsItem("SampleArc1", newpiece);
	item->setColor(color);
	item->setPos(newpiece->minPoint.x(), newpiece->minPoint.y());
	this->addItem(item);
	update();
	Items.push_back(item);
	mode = "Select";
	}
	else if (mode == "HVLine")
	{
		if (times == 0)
		{
			lastitem = NULL;
			times = 1;
			Lstart.setX(p.x());
			Lstart.setY(p.y());
			//qDebug() << shift << endl;
		}
		else if (times == 1)
		{
			GSVec3D pos1 = GSVec3D(Lstart.x(), Lstart.y(), 0);
			GSVec3D pos2 = GSVec3D(p.x(), Lstart.y(), 0);
			if (shift)
			{
				pos2.setX(Lstart.x());
				pos2.setY(p.y());
			}
			GSVec3D pos3 = GSVec3D(p.x(), p.y(), 0);
			std::list<GSVec3D> nodes;
			nodes.push_back(pos1);
			nodes.push_back(pos2);
			nodes.push_back(pos3);
			Mycurve = new GSNurbsCurve(0, nodes);
			item = new MyGraphicsItem("HVLine", Mycurve);
			item->setColor(color);
			item->setPos(item->control_points[0].x(), item->control_points[0].y());
			this->addItem(item);
			points.clear();
			if (lastitem != NULL) this->removeItem(lastitem);
			update();
			lastitem = item;
			Items.push_back(item);
			mode = "Select";
			times = 0;
			shift = 0;
			
		}
	}
	else if (mode == "HVCut")
	{
		if (times == 0)
		{
			lastitem = NULL;
			times = 1;
			Lstart.setX(p.x());
			Lstart.setY(p.y());
		}
		else if (times == 1)
		{

			GSVec3D pos1 = GSVec3D(Lstart.x(), Lstart.y(), 0);
			GSVec3D pos2 = GSVec3D(p.x(), p.y(), 0);
			std::list<GSVec3D> nodes;
			nodes.push_back(pos1);
			nodes.push_back(pos2);
			Mycurve = new GSNurbsCurve(0, nodes);

			item = new MyGraphicsItem("HVCut_Line", Mycurve);
			item->setColor(color);
			item->setPos(item->control_points[0].x(), item->control_points[0].y());
			this->addItem(item);
			points.clear();
			if (lastitem != NULL) this->removeItem(lastitem);
			update();
			lastitem = item;
			mode = "Select";
			times = 0;
			shift = 0;

		}
	}
	else if (mode == "HVReverse")
	{
		for (int i = 0; i < Items.size(); i++)
		{
			if (Items[i]->mode == "SampleArc1"&&p.x() >= Items[i]->Piece->minPoint.x()
				&& p.x() <= Items[i]->Piece->maxPoint.x() && p.y() >= Items[i]->Piece->minPoint.y()
				&& p.y() <= Items[i]->Piece->maxPoint.y())
			{
				float midx = (Items[i]->Piece->minPoint.x() + Items[i]->Piece->maxPoint.x()) / 2;
				float midy = (Items[i]->Piece->minPoint.y() + Items[i]->Piece->maxPoint.y()) / 2;

				newpiece = new GSNurbsPiece(0);
				std::list<GSVec3D> nlist;
				if (shift == 0)
				{
					for (auto it = Items[i]->Piece->curves.begin(); it != Items[i]->Piece->curves.end(); it++)
					{
						nlist.clear();
						for (auto itp = it->points.begin(); itp != it->points.end(); itp++)
						{
							GSVec3D tt = GSVec3D(2 * midx - itp->position.x(), itp->position.y(),0);
							nlist.push_back(tt);
						}
						ncurve1 = new GSNurbsCurve(0, nlist);
						newpiece->curves.push_back(*ncurve1);
					}
					newpiece->Refresh();
					item = new MyGraphicsItem("SampleArc1", newpiece);
					item->setColor(color);
					item->setPos(newpiece->minPoint.x(), newpiece->minPoint.y());
					this->addItem(item);
					update();
					this->removeItem(Items[i]);
					delete Items[i];
					update();
					Items[i] = item;

				}
				else if (shift == 1)
				{
					for (auto it = Items[i]->Piece->curves.begin(); it != Items[i]->Piece->curves.end(); it++)
					{
						nlist.clear();
						for (auto itp = it->points.begin(); itp != it->points.end(); itp++)
						{
							GSVec3D tt = GSVec3D(itp->position.x(), 2*midy - itp->position.y(), 0);
							nlist.push_back(tt);
						}
						ncurve1 = new GSNurbsCurve(0, nlist);
						newpiece->curves.push_back(*ncurve1);
					}
					newpiece->Refresh();
					item = new MyGraphicsItem("SampleArc1", newpiece);
					item->setColor(color);
					item->setPos(newpiece->minPoint.x(), newpiece->minPoint.y());
					this->addItem(item);
					update();
					this->removeItem(Items[i]);
					delete Items[i];
					update();
					Items[i] = item;
				}
				update();
				break;
			}
		}
	}
	else if (mode == "HVRectify")
	{
		int flag = 0;
		for (int i = 0; i < Items.size(); i++)
		{
			if (Items[i]->Curve != NULL) continue;
			for (auto it = Items[i]->Piece->curves.begin(); it != Items[i]->Piece->curves.end(); it++)
			{
				item = Items[i];
				if (it->IsContainPoint(GSVec3D(p.x(), p.y(), 0), 4))
				{
					
					llastitem = new MyGraphicsItem("HighLight", &(*it));
					llastitem->setPos((&(*it))->minPoint.x(), (&(*it))->minPoint.y());
					this->addItem(llastitem);
					update();
					flag = 1;
					pDialog = new QDialog();
					pDialog->setObjectName(tr("Information"));
					QGridLayout* layout = new QGridLayout();

					QGroupBox* b1 = new QGroupBox();
					QRadioButton* r1 = new QRadioButton(tr("Move one end point"));
					QRadioButton* r2 = new QRadioButton(tr("Move two end points"));
					QCheckBox* c1 = new QCheckBox(tr("Another end point"));
					r1->setChecked(true);
					QVBoxLayout* vbox = new QVBoxLayout;
					vbox->addWidget(r1);
					vbox->addWidget(c1);
					vbox->addWidget(r2);
					vbox->addStretch(1);
					b1->setLayout(vbox);

					QGroupBox* b2 = new QGroupBox();
					QRadioButton* r3 = new QRadioButton(tr("Move end point only"));
					QRadioButton* r4 = new QRadioButton(tr("Move all points"));
					QCheckBox* c2 = new QCheckBox(tr("All points on a single line"));
					
					r3->setChecked(true);
					QVBoxLayout* vbox2 = new QVBoxLayout;
					vbox2->addWidget(r3);
					vbox2->addWidget(r4);
					vbox2->addWidget(c2);
					
					vbox2->addStretch(1);
					b2->setLayout(vbox2);

					QGroupBox* b3 = new QGroupBox();
					 q3 = new QRadioButton(tr("Horizontal Rectify"));
					 q4 = new QRadioButton(tr("Vertical Rectify"));
					 q4->setChecked(true);
					QPushButton* pb = new QPushButton(tr("Enter"));
					QVBoxLayout* vbox3 = new QVBoxLayout;
					vbox3->addWidget(q3);
					vbox3->addWidget(q4);
					vbox3->addWidget(pb);
					b3->setLayout(vbox3);
					

					layout->addWidget(b1);
					layout->addWidget(b2);
					layout->addWidget(b3);
					pDialog->setLayout(layout);
					pDialog->setGeometry(500, 400, 200, 200);
					pDialog->show();

					connect(pb, SIGNAL(clicked()), this, SLOT(on_enter_clicked()));
					
					break;
				}
			}
			if (flag) break;
		}
		mode = "Select";
	}
	else if (mode == "SmoothArc")
	{
		if (SmoothTime == 0)
		{
			int flag = 0;
			for (int i = 0; i < Items.size(); i++)
			{
				item = Items[i];
				if (Items[i]->Curve != NULL)
				{

				}
				else
				{
					for (auto it = Items[i]->Piece->curves.begin(); it != Items[i]->Piece->curves.end(); it++)
					{
						if (it->IsContainPoint(GSVec3D(p.x(), p.y(), 0), 4))
						{
							flag = 1;
							moving_id = i;
							llastitem = new MyGraphicsItem("HighLight", &(*it));
							llastitem->setPos((&(*it))->minPoint.x(), (&(*it))->minPoint.y());
							this->addItem(llastitem);
							update();
							SmoothTime++;
							break;
						}
					}
				}
				if (flag) break;
			} 
		}
		else if (SmoothTime == 1)
		{
			for (int j = 0; j < (item->control_points).size(); j++)
			{

				if (dis(p, (item->control_points)[j]) < 8 && llastitem->Curve->IsContainPoint(GSVec3D(p.x(),p.y(),0),8))
				{
					GSNurbsPiece* Piece = new GSNurbsPiece(0);

					for (auto it = item->Piece->curves.begin(); it != item->Piece->curves.end(); it++)
					{
						std::list<GSVec3D> l;
						for (auto iit = it->points.begin(); iit != it->points.end(); iit++)
						{
							if (dis(QPointF(iit->position.x(), iit->position.y()), item->control_points[j]) < 8)
							{
								////qDebug() << "ok" << endl;
								//iit->position.setX(p.x());
								//iit->position.setY(p.y());
								//l.push_back(GSVec3D(p.x(), p.y(), 0));
							}
							else
							{
								l.push_back(GSVec3D(iit->position.x(), iit->position.y(), 0));
							}
						}
						it->Refresh();
						GSNurbsCurve* Cur = new GSNurbsCurve(0, l);
						Cur->parentPiece = Piece;
						Piece->curves.push_back(*Cur);

					}
					Piece->Refresh();
					lastitem = item;
					//this->removeItem(item);
					update();
					item = new MyGraphicsItem("SampleArc1", Piece);
					item->setColor(color);
					item->setPos(Piece->minPoint.x(), Piece->minPoint.y());
					this->addItem(item);
					update();
					Items[moving_id] = item;
					SmoothTime++;

					break;
				}

			}
		}
		else if (SmoothTime == 2)
		{
			this->removeItem(lastitem);
			this->removeItem(llastitem);
			update();
			SmoothTime = 0;
			mode = "Select";
		}
	}
	
	QGraphicsScene::mousePressEvent(event);
}

void MyGraphicsScene::on_enter_clicked()
{
	GSNurbsPoint ttt;
	this->removeItem(llastitem);
	update();
	GSNurbsPiece* Piece = new GSNurbsPiece(0);
	for (auto it = item->Piece->curves.begin(); it != item->Piece->curves.end(); it++)
	{
	
		for (auto iit = it->points.begin(); iit != it->points.end(); iit++)
		{
			if (iit == it->points.begin()&& it->IsContainPoint(GSVec3D(p.x(), p.y(), 0), 4))
			{
				ttt = *(it->points.begin());
				if(!q3->isChecked()) iit->position.setX(it->points.back().position.x());
				else iit->position.setY(it->points.back().position.y());
				
				if (it != item->Piece->curves.begin())
				{
					it--;
					it->points.back().position.setX(iit->position.x());
					it->points.back().position.setY(iit->position.y());
					it++;
				}
				
			}
		}
		
		
	}
	for (auto it = item->Piece->curves.begin(); it != item->Piece->curves.end(); it++)
	{
		std::list<GSVec3D> l;

		for (auto iit = it->points.begin(); iit != it->points.end(); iit++)
		{
				
				l.push_back(GSVec3D(iit->position.x(), iit->position.y(), 0));
			
		}
		it->Refresh();
		GSNurbsCurve* Cur = new GSNurbsCurve(0, l);
		Cur->parentPiece = Piece;
		Piece->curves.push_back(*Cur);

	}
	

	Piece->Refresh();
	this->removeItem(item);
	update();
	llastitem = item;
	item = new MyGraphicsItem("SampleArc1", Piece);
	item->setColor(color);
	item->setPos(Piece->minPoint.x(), Piece->minPoint.y());
	this->addItem(item);
	update();
	delete pDialog;
	for (int i = 0; i < Items.size(); i++)
	{
		if (Items[i] == llastitem)
		{
			Items[i] = item;
			break;
		}
	}
	mode = "Select";
	
}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	
	
}
void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF p = event->scenePos();
	int flag = 1;
	if (mode == "Select"&&moving==1)
	{
		for (int i = 0; i < Items.size(); i++)
		{
			
			for (int j = 0; j < (Items[i]->control_points).size(); j++)
			{
				//qDebug() << (Items[i]->control_points)[j].x() << ' ' << (Items[i]->control_points)[j].y() << endl;
				if ((Items[i]->control_points_states)[j] == 1)
				{
					if (Items[i]->Curve != NULL)
					{
						flag = 0;
						GSVec3D old = GSVec3D((Items[i]->control_points)[j].x(), (Items[i]->control_points)[j].y(), 0);
						GSVec3D now = GSVec3D(p.x(), p.y(), 0);
						(Items[i]->control_points)[j].setX(p.x());
						(Items[i]->control_points)[j].setY(p.y());

						while (!(Items[i]->Curve->points).empty()) (Items[i]->Curve->points).pop_front();

						for (int k = 0; k < (Items[i]->control_points).size(); k++)
						{
							GSVec3D temp = GSVec3D((Items[i]->control_points)[k].x(), (Items[i]->control_points)[k].y(), 0);
							(Items[i]->Curve->points).push_back(GSNurbsPoint(temp));
						}
						Items[i]->Curve->Refresh();


						item = new MyGraphicsItem(Items[i]->mode, Items[i]->Curve);
						(item->control_points_states)[j] = 1;
						item->setColor(color);
						item->setPos(Items[i]->Curve->minPoint.x(), Items[i]->Curve->minPoint.y());

						this->removeItem(Items[i]);
						update();
						this->addItem(item);
						update();
						Items[i] = item;
						points.clear();
						lastitem = item;
						break;
					}
					else
					{
						flag = 0;
						GSNurbsPiece* Piece = new GSNurbsPiece(0);
						
						for (auto it = Items[i]->Piece->curves.begin(); it != Items[i]->Piece->curves.end(); it++)
						{
							std::list<GSVec3D> l;
							for (auto iit = it->points.begin(); iit != it->points.end(); iit++)
							{
								if (dis(QPointF(iit->position.x(),iit->position.y()), Items[i]->control_points[moving_id]) < 8)
								{
									//qDebug() << "ok" << endl;
									iit->position.setX(p.x());
									iit->position.setY(p.y());
									l.push_back(GSVec3D(p.x(), p.y(), 0));
								}
								else
								{
									l.push_back(GSVec3D(iit->position.x(), iit->position.y(), 0));
								}
							}
							it->Refresh();
							GSNurbsCurve* Cur = new GSNurbsCurve(0,l);
							Cur->parentPiece = Piece;
							Piece->curves.push_back(*Cur);
					
						}
						Piece->Refresh();
						item = new MyGraphicsItem("SampleArc1", Piece);
					
						this->removeItem(Items[i]);
						update();
						item->setColor(color);
						item->setPos(Piece->minPoint.x(), Piece->minPoint.y());
						this->addItem(item);
						update();
						Items[i] = item;
						(Items[i]->control_points_states)[j] = 1;
						break;
					}
				}
			}
			if (flag == 0) break;
		}
	}
	else if (mode == "Select"&&moving == 2)
	{
		
		QPointF offset;
		offset.setX(p.x() - StartPoint.x());
		offset.setY(p.y() - StartPoint.y());
		StartPoint.setX(p.x());
		StartPoint.setY(p.y());
		item->Curve->Move(GSVec3D(offset.x(),offset.y(),0));
		item->Curve->Refresh();

		
		
		item = new MyGraphicsItem(Items[moving_id]->mode, item->Curve);

		item->setColor(color);
		item->setPos(item->Curve->minPoint.x(), item->Curve->minPoint.y());
		this->removeItem(Items[moving_id]);
		update();
		this->addItem(item);
		update();
		Items[moving_id] = item;
		points.clear();
		lastitem = item;
		mode = "Select";
	}
	else if (mode == "Select"&&moving == 3)
	{
		QPointF offset;
		offset.setX(p.x() - StartPoint.x());
		offset.setY(p.y() - StartPoint.y());
		StartPoint.setX(p.x());
		StartPoint.setY(p.y());
		for (auto it = Items[moving_id]->Curve->parentPiece->curves.begin(); it != Items[moving_id]->Curve->parentPiece->curves.end(); it++)
		{
			it->Move(GSVec3D(offset.x(), offset.y(), 0));
			it->Refresh();
			cur_item = new MyGraphicsItem(Items[moving_id]->mode, &(*it));
			
			cur_item->setColor(color);
			cur_item->setPos(cur_item->Curve->minPoint.x(), cur_item->Curve->minPoint.y());
			
			
			this->removeItem(m[(&(*it))]);
			update();
			this->addItem(cur_item);
			update();
			
			if (m[(&(*it))] == item)
			{
				item = cur_item;
			}

			m[(&(*it))] = cur_item;
			points.clear();
			lastitem = cur_item;
			mode = "Select";
			
		}
		Items[moving_id] = item;



	}
	else if (mode == "Select"&&moving == 4)
	{
		QPointF offset = QPointF(p.x() - StartPoint.x(), p.y() - StartPoint.y());
		StartPoint.setX(p.x());
		StartPoint.setY(p.y());
		Items[moving_id]->Curve->Move(GSVec3D(offset.x(),offset.y(),0));
		Items[moving_id]->Curve->Refresh();
		item = new MyGraphicsItem(Items[moving_id]->mode, Items[moving_id]->Curve);

		item->setColor(color);
		item->setPos(item->Curve->minPoint.x(), item->Curve->minPoint.y());
		this->removeItem(Items[moving_id]);
		update();
		this->addItem(item);
		update();
		Items[moving_id] = item;
		points.clear();
		lastitem = item;
		mode = "Select";
	}
	else if (mode == "HVLine")
	{
		if (times == 1)
		{
			
			GSVec3D pos1 = GSVec3D(Lstart.x(), Lstart.y(), 0);
			GSVec3D pos2 = GSVec3D(p.x(), Lstart.y(), 0);
			if (shift)
			{
				pos2.setX(Lstart.x());
				pos2.setY(p.y());
			}
			GSVec3D pos3 = GSVec3D(p.x(), p.y(), 0);
			std::list<GSVec3D> nodes;
			nodes.push_back(pos1);
			nodes.push_back(pos2);
			nodes.push_back(pos3);
			Mycurve = new GSNurbsCurve(0, nodes);
			item = new MyGraphicsItem("HVLine", Mycurve);
			item->setColor(color);
			item->setPos(item->control_points[0].x(), item->control_points[0].y());
			this->addItem(item);
			points.clear();
			if (lastitem != NULL) this->removeItem(lastitem);
			update();
			lastitem = item;
		}

	}
	else if (mode == "HVCut"&&times==1)
	{
		GSVec3D pos1 = GSVec3D(Lstart.x(), Lstart.y(), 0);
		GSVec3D pos2 = GSVec3D(p.x(), p.y(), 0);
		if (fabs(fabs(p.x() - Lstart.x()) - fabs(p.y() - Lstart.y())) > 5 
			&& fabs(p.x() - Lstart.x())>5 && fabs(p.y() - Lstart.y())>5 ) return;
		std::list<GSVec3D> nodes;
		nodes.push_back(pos1);
		nodes.push_back(pos2);
		Mycurve = new GSNurbsCurve(0, nodes);
		item = new MyGraphicsItem("HVCut", Mycurve);
		item->setColor(color);
		item->setPos(item->control_points[0].x(), item->control_points[0].y());
		this->addItem(item);
		points.clear();
		if (lastitem != NULL) this->removeItem(lastitem);
		update();
		lastitem = item;
	}
}


