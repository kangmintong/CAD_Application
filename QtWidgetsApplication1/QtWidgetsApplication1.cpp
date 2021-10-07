#include "QtWidgetsApplication1.h"
#include <qpainter.h>
#include <iostream>
#include <qdebug.h>
#include <vector>
#include <qgraphicsscene.h>
#include <qgraphicsitem.h>
#include <qgraphicsview.h>
#include "MyGraphicsItem.h"
#include "MyGraphicsScene.h"
#include "MyGraphicsView.h"

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	ui.centralWidget->setStyleSheet("background-color:lavender;");
	ui.mainToolBar->setStyleSheet("background-color:lavender;linen;");
	ui.statusBar->setStyleSheet("background-color:plum;");
	ui.menuBar->setStyleSheet("background-color:honeydew;");
	
	draw_manager = new Draw_Manager(ui.graphicsView);
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
	connect(ui.toolButton_3, SIGNAL(clicked()), this, SLOT(on_toolButton_3_clicked()));
	//connect(ui.toolButton, SIGNAL(clicked()), this, SLOT(on_toolButton_clicked()));
	connect(ui.toolButton_4, SIGNAL(clicked()), this, SLOT(on_toolButton_4_clicked()));
	connect(ui.toolButton_5, SIGNAL(clicked()), this, SLOT(on_toolButton_5_clicked()));
	connect(ui.toolButton_6, SIGNAL(clicked()), this, SLOT(on_toolButton_6_clicked()));
	connect(ui.toolButton_7, SIGNAL(clicked()), this, SLOT(on_toolButton_7_clicked()));
	connect(ui.toolButton_8, SIGNAL(clicked()), this, SLOT(on_toolButton_8_clicked()));
	connect(ui.toolButton_9, SIGNAL(clicked()), this, SLOT(on_toolButton_9_clicked()));
	connect(ui.toolButton_10, SIGNAL(clicked()), this, SLOT(on_toolButton_10_clicked()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(on_pushButton_4_clicked()));
	connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(on_pushButton_5_clicked()));
	
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(on_toolButton_2_clicked()));
	connect(ui.actionQuit_Q, SIGNAL(triggered()), this, SLOT(on_actionQuit_Q_triggered()));
	connect(ui.actionOpen_File_O, SIGNAL(triggered()), this, SLOT(on_actionOpen_File_O_triggered()));
	connect(ui.actionopen, SIGNAL(triggered()), this, SLOT(on_actionopen_triggered()));
	connect(ui.actionQuit_Q_2, SIGNAL(triggered()), this, SLOT(on_actionQuit_Q_2_triggered()));
	connect(ui.actionUndo_Ctrl_Z, SIGNAL(triggered()), this, SLOT(on_actionUndo_Ctrl_Z_triggered()));
	connect(ui.toolButton_2, SIGNAL(clicked()), this, SLOT(on_toolButton_2_clicked()));
	connect(ui.actionHelp_Manual_Ctrl_H, SIGNAL(triggered()), this, SLOT(on_actionHelp_Manual_Ctrl_H_triggered()));

	ui.actionQuit_Q->setShortcut(tr("ctrl+s"));
	ui.actionOpen_File_O->setShortcut(tr("ctrl+o"));
	ui.actionopen->setShortcut(tr("ctrl+n"));
	ui.actionQuit_Q_2->setShortcut(tr("ctrl+q"));
	ui.actionUndo_Ctrl_Z->setShortcut(tr("delete"));
	ui.actionHelp_Manual_Ctrl_H->setShortcut(tr("ctrl+h"));

	ui.mainToolBar->resize(QSize(200, 200));
	ui.mainToolBar->addAction(ui.actionopen);
	ui.mainToolBar->addAction(ui.actionOpen_File_O);
	ui.mainToolBar->addAction(ui.actionQuit_Q);
	ui.mainToolBar->addAction(ui.actionQuit_Q_2);
	ui.mainToolBar->addAction(ui.actionUndo_Ctrl_Z);
	ui.mainToolBar->addAction(ui.actionHelp_Manual_Ctrl_H);
	ui.mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	QIcon icon1(":/QtWidgetsApplication1/images/openfile.gif");
	ui.actionOpen_File_O->setIcon(icon1);

	QIcon icon2(":/QtWidgetsApplication1/images/newfile.png");
	ui.actionopen->setIcon(icon2);

	QIcon icon3(":/QtWidgetsApplication1/images/savefile.png");
	ui.actionQuit_Q->setIcon(icon3);

	QIcon icon4(":/QtWidgetsApplication1/images/exit.png");
	ui.actionQuit_Q_2->setIcon(icon4);

	QIcon icon5(":/QtWidgetsApplication1/images/delete.png");
	ui.actionUndo_Ctrl_Z->setIcon(icon5);

	QIcon icon6(":/QtWidgetsApplication1/images/help.png");
	ui.actionHelp_Manual_Ctrl_H->setIcon(icon6);

	
	QLabel* locationLabel = new QLabel("Status: ");
	locationLabel->setAlignment(Qt::AlignCenter);
	locationLabel->setMinimumSize(locationLabel->sizeHint());
	QLabel* aixLabel = new QLabel("Select and Move");

	//ui.statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
	ui.statusBar->setSizeGripEnabled(false); //设置是否显示右边的大小控制点
	ui.statusBar->addWidget(locationLabel);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
	QLabel *per1 = new QLabel("Ready ", this);


	ui.statusBar->addPermanentWidget(per1); 

	//statusBar()->showMessage("Status is here...", 3000); // 显示临时信息，时间3秒钟.

}

//Dialog::Dialog(QWidget *parent)
//	: QMainWindow(parent)
//{
//	ui2.setupUi(this);
//
//	
//}

void QtWidgetsApplication1::on_pushButton_clicked()
{
	draw_manager->SetMode("Line");
	QLabel* aixLabel = new QLabel("Draw Line");
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

void QtWidgetsApplication1::on_toolButton_3_clicked()
{
	draw_manager->SetMode("Arc");
	QLabel* aixLabel = new QLabel("Draw Arc");
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

//void QtWidgetsApplication1::on_toolButton_clicked()
//{
//	//draw_manager->SetMode("Rect");
//}

void QtWidgetsApplication1::on_toolButton_4_clicked()
{
	draw_manager->SetMode("Arc2");
	QLabel* aixLabel = new QLabel("Draw Arc");
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel,1);
	last = aixLabel;
}

void QtWidgetsApplication1::on_toolButton_5_clicked()
{
	draw_manager->SetMode("HVLine");
	QLabel* aixLabel = new QLabel("Horizontal and Vertical Line");
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

void QtWidgetsApplication1::on_toolButton_6_clicked()
{
	draw_manager->SetMode("HVCut");
	QLabel* aixLabel = new QLabel("Horizontal and Vertical Cut");
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

void QtWidgetsApplication1::on_toolButton_7_clicked()
{
	draw_manager->SetMode("HVReverse");
	QLabel* aixLabel = new QLabel("Horizontal and Vertical Reverse");
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

void QtWidgetsApplication1::on_toolButton_8_clicked()
{
	draw_manager->SetMode("SampleArc1");
	QLabel* aixLabel = new QLabel("Sample Figure 1");
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

void QtWidgetsApplication1::on_toolButton_9_clicked()
{
	draw_manager->SetMode("HVRectify");
	QLabel* aixLabel = new QLabel(tr("Horizontal and Vertical Rectification"));
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

void QtWidgetsApplication1::on_toolButton_10_clicked()
{
	draw_manager->SetMode("SmoothArc");
	QLabel* aixLabel = new QLabel(tr("Make the Arc Smooth"));
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

void QtWidgetsApplication1::on_toolButton_2_clicked()
{
	draw_manager->SetMode("Select");
	draw_manager->scene->moving = 0;
	QLabel* aixLabel = new QLabel("Select And Move");
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

void QtWidgetsApplication1::on_actionQuit_Q_triggered()
{
	draw_manager->save();
	QLabel* aixLabel = new QLabel(tr("Save"));
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

void QtWidgetsApplication1::on_actionOpen_File_O_triggered()
{
	draw_manager->open();
	QLabel* aixLabel = new QLabel(tr("Open the File"));
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

void QtWidgetsApplication1::on_actionopen_triggered()
{
	draw_manager->newopen();
	QLabel* aixLabel = new QLabel(tr("New File"));
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

void QtWidgetsApplication1::on_actionQuit_Q_2_triggered()
{
	qApp->quit();
}


void QtWidgetsApplication1::on_actionUndo_Ctrl_Z_triggered()
{
	draw_manager->Delete();
	QLabel* aixLabel = new QLabel(tr("Delete an Item"));
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}


void QtWidgetsApplication1::on_pushButton_4_clicked()
{
	draw_manager->SetMode("SampleArc2");
	QLabel* aixLabel = new QLabel("Sample Figure 2");
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

void QtWidgetsApplication1::on_pushButton_5_clicked()
{
	draw_manager->SetMode("SampleArc3");
	QLabel* aixLabel = new QLabel("Sample Figure 3");
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
}

int htimes = 0;
void QtWidgetsApplication1::on_actionHelp_Manual_Ctrl_H_triggered()
{
	htimes++;
	if (htimes == 2)
	{
		htimes = 0;
		return;
	}
	QLabel* aixLabel = new QLabel(tr("Help"));
	ui.statusBar->removeWidget(last);
	ui.statusBar->addWidget(aixLabel);
	last = aixLabel;
	QProcess *proc = new QProcess();
	QString path = "notepad.exe help.txt"; 
	proc->start(path);

}