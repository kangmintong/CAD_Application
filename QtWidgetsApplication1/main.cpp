#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <GSCloth.h>
#include <qdebug.h>
#include "MyGraphicsItem.h"
#include "MyGraphicsScene.h"
#include "MyGraphicsView.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;

    w.show();
	
    return a.exec();
}
