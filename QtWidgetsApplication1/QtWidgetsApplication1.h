#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtWidgetsApplication1.h"
#include <qlayout.h>
#include "MyGraphicsItem.h"
#include "MyGraphicsScene.h"
#include "Draw_Manager.h"
#include <qlabel.h>
#include <qprocess.h>


class Draw_Manager;

class QtWidgetsApplication1 : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);
	Draw_Manager* draw_manager;
	QLabel* last;

private:
    Ui::QtWidgetsApplication1Class ui;
	

private slots:

	void on_pushButton_clicked();
	void on_toolButton_3_clicked();
	void on_toolButton_4_clicked();
	void on_toolButton_5_clicked();
	void on_toolButton_6_clicked();
	void on_toolButton_7_clicked();
	void on_toolButton_8_clicked();
	void on_toolButton_9_clicked();
	void on_toolButton_10_clicked();
	void on_toolButton_2_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void on_actionQuit_Q_triggered();
	void on_actionOpen_File_O_triggered();
	void on_actionopen_triggered();
	void on_actionQuit_Q_2_triggered();
	void on_actionUndo_Ctrl_Z_triggered();
	void on_actionHelp_Manual_Ctrl_H_triggered();
};

//class Dialog : public QMainWindow
//{
//	Q_OBJECT
//
//public:
//	Dialog(QWidget *parent = Q_NULLPTR);
//
//private:
//	Ui::Dialog ui2;
//
//private slots:
//	
//};
