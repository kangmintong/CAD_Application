#pragma once
#include <string>
#include <vector>
#include "MyGraphicsScene.h"
#include "MyGraphicsItem.h"
#include <qgraphicsview.h>
#include <fstream>
#include <qfiledialog.h>
#include <optional>

class MyGraphicsScene;

class Draw_Manager
{
public:
	MyGraphicsScene* scene;
	QGraphicsView* graphicsView;
	std::vector<MyGraphicsItem*> items;
	Draw_Manager(QGraphicsView*);
	void SetMode(std::string);
	void save();
	void open();
	void newopen();
	std::vector<MyGraphicsScene*> scenes;
	void withdraw();
	void SaveScene();
	void Delete();
};
