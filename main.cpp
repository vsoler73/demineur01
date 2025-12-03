#include <stdexcept>
#include <QApplication>
#include <QWidget>
#include <QGLViewer/qglviewer.h>

#include "GameInterface.h"

int main(int argc,char *argv[])
{
    try {


	QApplication app(argc,argv) ;
    
    	GameInterface I ;

	I.show();

	return app.exec() ;
}
    catch(std::exception&e){
        std::cerr<<"error:"<<e.what()<<std::endl;
    }
}
