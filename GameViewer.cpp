#include <QGLViewer/constraint.h>
#include <QMouseEvent>
#include <QStylePainter>
#include <QMessageBox>

#include "GameViewer.h"
#include "GameDrawer.h"
#include "GameInterface.h"
#include "DemineurGame.h"

//#define DEBUG_GAME_VIEWER 1

static const uint32_t SQUARE_SIZE_IN_PIXELS = 50 ;

GameViewer::GameViewer(QWidget *parent)
	:QWidget(parent)
{
    mGameDrawer = new GameDrawer(width(),height());
    mGame = NULL ;
    
    mMousePressed = false ;
    mSceneCenterX = 0 ;
    mSceneCenterY = 0 ;
    
    setMouseTracking(true) ;
    setFocusPolicy(Qt::StrongFocus) ;
    mCurrentMode = GAME_MODE_GAME;
}

void GameViewer::mousePressEvent(QMouseEvent *e)
{
    mMousePressed = true ;
    mOldMouseX = e->x() ;
    mOldMouseY = height()-1-e->y() ;
}
void GameViewer::mouseReleaseEvent(QMouseEvent *e)
{
    mMousePressed = false ;
}
void GameViewer::mouseMoveEvent(QMouseEvent *e)
{
    if(mMousePressed)
    {
    mSceneCenterX += e->x() - mOldMouseX ;
    mSceneCenterY += (height()-1-e->y()) - mOldMouseY ;
    
    update();
    }
    
    mOldMouseX = e->x() ;
    mOldMouseY = height()-1-e->y() ;
}

void GameViewer::pixelCoordinatesToGameCoordinate(int x,int y,int& i,int& j) const
{
}

void GameViewer::setGame(DemineurGame *g)
{
    mGame = g ;
    
    //setSceneRadius(2*std::max(mGame->currentState().sizeX(),mGame->currentState().sizeY())) ;
    //updateGL() ;
    
    QObject::connect(mGame,SIGNAL(changed()),this,SLOT(reDraw())) ;

    setGeometry(mGameDrawer->pixmap().rect());
    updateGeometry();

    mGameDrawer->update(*g,width(),height(),mCurrentMode) ;
    update() ;
}

void GameViewer::reDraw() 
{
	if(mGame != NULL)
	{
		//std::cerr << "redraw!" << std::endl;
		mGameDrawer->update(*mGame,width(),height(),mCurrentMode) ;

        if(mCurrentMode == GAME_MODE_EDITOR)
			mGameDrawer->drawButtons(*mGame,width(),height(),mButtons);

		update();
	}
 
}
void GameViewer::resizeEvent(QResizeEvent *e)
{
    if(mGame != NULL)
	    mGameDrawer->update(*mGame,width(),height(),mCurrentMode) ;
    
    update() ;
}

void GameViewer::addButton(int x,int y,const QPixmap& pixmap)
{
    InterfaceButton *i = new InterfaceButton ;

    i->x = x ;
    i->y = y ;
    i->pixmap = pixmap ;

    mButtons.push_back(i);
}

void GameViewer::paintEvent(QPaintEvent *)
{
    QStylePainter(this).drawPixmap(0,0,mGameDrawer->pixmap()) ;
#ifdef DEBUG_GAME_VIEWER    
    std::cerr << "In paint event. pasting pixmap of size " << mGameDrawer->pixmap().width() << "x" << mGameDrawer->pixmap().height() << std::endl;
#endif
}

void GameViewer::setCurrentMode(GameMode m)
{
    mCurrentMode = m ;

    if(mGame != NULL)
		mGameDrawer->update(*mGame,width(),height(),mCurrentMode) ;

    update() ;
}
    
void GameViewer::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        if(mCurrentMode != GAME_MODE_GAME)
            return ;

        break ;

    case Qt::Key_D:
    case Qt::Key_B:
    case Qt::Key_V:
    case Qt::Key_W:
    case Qt::Key_X:
    case Qt::Key_S:
    case Qt::Key_E:
    case Qt::Key_I:

        if(mCurrentMode != GAME_MODE_EDITOR)
            return ;

        break ;
    }

    int i = mGameDrawer->windowCoordToGameCoordX(mOldMouseX) ;
    int j = mGameDrawer->windowCoordToGameCoordY(height() -1 -mOldMouseY) ;
    
    e->accept() ;
    bool redraw = false ;    
   
    if(redraw)
    {
	mGameDrawer->update(*mGame,width(),height(),mCurrentMode) ;

        if(mCurrentMode == GAME_MODE_EDITOR)
			mGameDrawer->drawButtons(*mGame,width(),height(),mButtons);

	update() ;
    }
}

