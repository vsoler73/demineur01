#include <QApplication>
#include <QWidget>
#include <QGLViewer/qglviewer.h>

#include "GameInterface.h"

int main(int argc,char *argv[])
{
	QApplication app(argc,argv) ;
    
    	GameInterface I ;

	I.show();

	return app.exec() ;
}
