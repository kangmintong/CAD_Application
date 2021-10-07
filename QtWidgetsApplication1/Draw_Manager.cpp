#include "Draw_Manager.h"
#include <qdebug.h>

Draw_Manager::Draw_Manager(QGraphicsView* a)
{
	scene = new MyGraphicsScene();
	scene->drawmanager = this;
	scene->setSceneRect(QRectF(-500.5, -400.5, 500.5, 400.5)); //graphicsview 长宽一半正负数
	graphicsView = a;
	graphicsView->setScene(scene);
}

void Draw_Manager::SetMode(std::string s)
{
	scene->SetMode(s);
}

int scnt = 0;
void Draw_Manager::save()
{
	scnt++;
	if (scnt == 2)
	{
		scnt = 0;
		return;
	}
	std::ofstream out;
	QString file_name = QFileDialog::getSaveFileName();

	//QFile saveFile(file_name);
	out.open(file_name.toStdString());
	out.clear();
	out << scene->Items.size() << endl;
	for (int i = 0; i < scene->Items.size(); i++)
	{
		if (scene->Items[i]->Curve != NULL)
		{
			out << "0 " << scene->Items[i]->control_points.size() << " " << scene->Items[i]->mode << ' ';
			for (int j = 0; j < scene->Items[i]->control_points.size(); j++)
			{
				out << scene->Items[i]->control_points[j].x() << ' ' << scene->Items[i]->control_points[j].y() << ' ';
			}
			out << endl;
		}
		else
		{
			out << "1 " << scene->Items[i]->Piece->curves.size() << " "<<scene->Items[i]->mode<<endl;
			for (auto it = scene->Items[i]->Piece->curves.begin(); it != scene->Items[i]->Piece->curves.end(); it++)
			{
				out << it->points.size() << ' ';
				for (auto itp=it->points.begin();itp!=it->points.end();itp++)
				{
					out << itp->position.x() << ' ' << itp->position.y() << ' ';
				}
				out << endl;
			}
		}
	}

	out.close();

}

int cnt = 0;
void Draw_Manager::open()
{
	cnt++;
	if (cnt == 2)
	{
		cnt = 0;
		return;
	}
	delete scene;
	scene = new MyGraphicsScene();
	scene->setSceneRect(QRectF(-500.5, -400.5, 500.5, 400.5)); //graphicsview 长宽一半正负数
	graphicsView->setScene(scene);

	QFileDialog dig;
	dig.setAcceptMode(QFileDialog::AcceptOpen);
	dig.setFileMode(QFileDialog::ExistingFile);
	QStringList fs;

	if (dig.exec() == QDialog::Accepted)   //如果成功的执行
	{
		fs = dig.selectedFiles();            //取第一个文件名
	}
	else
		dig.close();
	if (fs.empty()) return;

	std::ifstream in;
	in.open(fs[0].toStdString());
	dig.close();
	int Item_Size, type, points, curves;
	std::string mo;
	float x, y;
	in >> Item_Size;

	for (int i = 0; i < Item_Size; i++)
	{
		in >> type;
		if (type == 0)
		{
			in >> points >> mo;
			std::list<GSVec3D> nlist;
			for (int j = 0; j < points; j++)
			{
				in >> x >> y;
				GSVec3D pos = GSVec3D(x, y, 0);
				nlist.push_back(pos);
			}
			
			scene->newpiece = new GSNurbsPiece(0);
			scene->ncurve1 = new GSNurbsCurve(0, nlist);
			scene->ncurve1->parentPiece = scene->newpiece;
			scene->newpiece->curves.push_back(*(scene->ncurve1));
	
			scene->item = new MyGraphicsItem(mo, scene->ncurve1);
			scene->item->setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
			QPointF pos;
			pos.setX(scene->ncurve1->minPoint.x());
			pos.setY(scene->ncurve1->minPoint.y());
			scene->item->setPos(pos.x(), pos.y());

			scene->addItem(scene->item);
			scene->update();
			scene->Items.push_back(scene->item);
			scene->mode = "Select";
		}
		else if (type == 1)
		{
			in >> curves >> mo;
			scene->newpiece = new GSNurbsPiece(0);
			for (int i = 0; i < curves; i++)
			{
				in >> points;
				std::list<GSVec3D> nlist;
				for (int j = 0; j < points; j++)
				{
					in >> x >> y;
					GSVec3D pos = GSVec3D(x, y, 0);
					nlist.push_back(pos);
				}
				scene->ncurve1 = new GSNurbsCurve(0, nlist);
				scene->ncurve1->parentPiece = scene->newpiece;
				scene->newpiece->curves.push_back(*(scene->ncurve1));
			}
				
				scene->newpiece->Refresh();
				scene->cloth->AddPiece(*(scene->newpiece));

				scene->item = new MyGraphicsItem(mo, scene->newpiece);
				scene->item->setColor(QColor(qrand() % 256, qrand() % 256, qrand() % 256));
				scene->item->setPos(scene->newpiece->minPoint.x(), scene->newpiece->minPoint.y());
				scene->addItem(scene->item);
				scene->update();
				scene->Items.push_back(scene->item);
				scene->mode = "Select";
			}

		
	}
}

int newcnt = 0;
void Draw_Manager::newopen()
{
	newcnt++;
	if (newcnt == 2)
	{
		newcnt = 0;
		return;
	}
	for (int i = 0; i < scene->Items.size(); i++)
	{
		scene->removeItem(scene->Items[i]);
	}
}

int wtimes = 0;
void Draw_Manager::withdraw()
{
	wtimes++;
	if (wtimes == 2)
	{
		wtimes = 0;
		return;
	}
	MyGraphicsScene* ss = scenes.back();
	if (scenes.size()) scenes.pop_back();
	delete ss;
	scene = scenes.back();
	graphicsView->setScene(scene);
	scene->update();
	
}


void Draw_Manager::SaveScene()
{
	//保存scene有问题
	MyGraphicsScene temp;

	temp.mode = scene->mode;
	temp.points = scene->points;
	temp.control_points = scene->control_points;
	temp.bounding_recs = scene->bounding_recs;
	temp.Items = scene->Items;
	temp.drawmanager = this;
	temp.setSceneRect(QRectF(-500.5, -400.5, 500.5, 400.5)); //graphicsview 长宽一半正负数
	/*for (int i = 0; i < Scene->Items.size(); i++)
	{
		temp.Items.push_back(Scene->Items[i]);
	}*/
	scenes.push_back(&temp);
	graphicsView->setScene(&temp);
	scene = &temp;
	temp.update();
	//qDebug() << "saved" << endl;
	
}

void Draw_Manager::Delete()
{
	for (auto it = scene->Items.begin(); it != scene->Items.end(); it++)
	{
		if (*it == scene->item)
		{
			scene->Items.erase(it);
			scene->removeItem(scene->item);
			scene->update();
			delete scene->item;
			break;
		}
	}
	scene->mode = "Select";
	scene->moving_id = 0;
	scene->times = 0;
	scene->moving = 0;
}