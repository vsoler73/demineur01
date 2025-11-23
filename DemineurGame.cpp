#include <iostream>
#include <QTimer>
#include <QMessageBox>
#include "DemineurGame.h"

DemineurGame::DemineurGame()
{
    mTimer = NULL ;
}

void DemineurGame::init(const Level& level)
{
    // init level content
    
    mtx.lock() ;
    
    mLevelState = level ;
    mtx.unlock() ;
}

void DemineurGame::start()
{
    if(mTimer != NULL)
        delete mTimer ;
    
    mTimer = new QTimer ;
    
    mLevelState.startGame();
    QObject::connect(mTimer,SIGNAL(timeout()),this,SLOT(timerEvent())) ;
    mTimer->start(150) ;
}
void DemineurGame::stop()
{
    mTimer->stop() ;
}

void DemineurGame::explode(Level& level, int i, int j)
{
    for(int k=-1;k<2;++k)
        for(int l=-1;l<2;++l)
            if( i+k > 0 && i+k < level.sizeX()-1 && j+l > 0 && j+l < level.sizeY()-1 && level(i+k,j+l)!=Level::Exit && level(i+k,j+l)!=Level::ClosedExit)
				level(i+k,j+l) = Level::Explosion_01 ;
}
/*
bool DemineurGame::test_bestiole(const Level& L,int x,int y) const
{
    if(x < 0 && x >= L.sizeX())
        return false ;

    Level::ObjectId i = L(x,y) ;

    return (i == Level::Bug_top || i == Level::Bug_bottom || i == Level::Bug_left || i == Level::Bug_right) ;
}
*/



