#include <QGLViewer/constraint.h>
#include <QMouseEvent>
#include <QStylePainter>
#include <QMessageBox>

#include "Level.h"
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

    addButton(30,30,QPixmap(50,50));
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
    
    switch(e->key())
    {
    case Qt::Key_Left: mGame->currentState().movePlayer(Level::Left) ;
	    redraw = true ;
	    break ;

    case Qt::Key_Right:mGame->currentState().movePlayer(Level::Right) ;
	    redraw = true ;
	    break ;
    case Qt::Key_Up:   mGame->currentState().movePlayer(Level::Top) ;
	    redraw = true ;
	    break ;
    case Qt::Key_Down: mGame->currentState().movePlayer(Level::Bottom) ;
	    redraw = true ;
	    break ;

    case Qt::Key_D: if(i > 0 && i < mGame->currentState().sizeX()-1 && j > 0 && j < mGame->currentState().sizeY()-1) 
						if(e->modifiers() & Qt::ShiftModifier)
							mGame->currentState().fill(Level::Diamond);
				        else
						    mGame->currentState()(i,j) = Level::Diamond ;
	    redraw = true ;
	    break ;
        
    case Qt::Key_M: if(i > 0 && i < mGame->currentState().sizeX()-1 && j > 0 && j < mGame->currentState().sizeY()-1)
						if(e->modifiers() & Qt::ShiftModifier)
							mGame->currentState().fill(Level::Moss);
				        else
		            		mGame->currentState()(i,j) = Level::Moss ;
	    redraw = true ;
	    break ;

    case Qt::Key_B: if(i > 0 && i < mGame->currentState().sizeX()-1 && j > 0 && j < mGame->currentState().sizeY()-1)
						if(e->modifiers() & Qt::ShiftModifier)
							mGame->currentState().fill(Level::Bomb);
				        else
		            		mGame->currentState()(i,j) = Level::Bomb ;
	    redraw = true ;
	    break ;

    case Qt::Key_V: if(i > 0 && i < mGame->currentState().sizeX()-1 && j > 0 && j < mGame->currentState().sizeY()-1) 
						if(e->modifiers() & Qt::ShiftModifier)
							mGame->currentState().fill(Level::Void);
				        else
		            mGame->currentState()(i,j) = Level::Void ;
	    redraw = true ;
	    break ;

    case Qt::Key_W: if(i >= 0 && i < mGame->currentState().sizeX() && j >= 0 && j < mGame->currentState().sizeY())
						if(e->modifiers() & Qt::ShiftModifier)
							mGame->currentState().fill(Level::Wall);
				        else
		            mGame->currentState()(i,j) = Level::Wall ;
	    redraw = true ;
	    break ;

    case Qt::Key_X: if(i >= 0 && i < mGame->currentState().sizeX() && j >= 0 && j < mGame->currentState().sizeY())
						if(e->modifiers() & Qt::ShiftModifier)
							mGame->currentState().fill(Level::MetalWall0);
				        else
		            mGame->currentState()(i,j) = Level::MetalWall0 ;
	    redraw = true ;
	    break ;

    case Qt::Key_S: if(i > 0 && i < mGame->currentState().sizeX()-1 && j > 0 && j < mGame->currentState().sizeY()-1) 

						if(e->modifiers() & Qt::ShiftModifier)
							mGame->currentState().fill(Level::Stone);
				        else
        mGame->currentState()(i,j) = Level::Stone ;
	    redraw = true ;
	    break ;

    case Qt::Key_E: if(i > 0 && i < mGame->currentState().sizeX()-1 && j > 0 && j < mGame->currentState().sizeY()-1) 

						if(e->modifiers() & Qt::ShiftModifier)
							mGame->currentState().fill(Level::Earth);
				        else
        mGame->currentState()(i,j) = Level::Earth ;
	    redraw = true ;
	    break ;

    case Qt::Key_I: if(i > 0 && i < mGame->currentState().sizeX()-1 && j > 0 && j < mGame->currentState().sizeY()-1)

            switch(mGame->currentState()(i,j))
            {
            case Level::Bug_top:   if(e->modifiers() & Qt::ShiftModifier) mGame->currentState().fill(Level::Bug_right); else mGame->currentState()(i,j) = Level::Bug_right; break ;
            case Level::Bug_right: if(e->modifiers() & Qt::ShiftModifier) mGame->currentState().fill(Level::Bug_bottom); else mGame->currentState()(i,j) = Level::Bug_bottom; break ;
            case Level::Bug_bottom:if(e->modifiers() & Qt::ShiftModifier) mGame->currentState().fill(Level::Bug_left); else mGame->currentState()(i,j) = Level::Bug_left; break ;

            default:
            case Level::Bug_left:  if(e->modifiers() & Qt::ShiftModifier) mGame->currentState().fill(Level::Bug_top); else mGame->currentState()(i,j) = Level::Bug_top; break ;

            }

	    redraw = true ;
	    break ;

    default:
	    e->ignore() ;
    }
    
   
    if(redraw)
    {
	mGameDrawer->update(*mGame,width(),height(),mCurrentMode) ;

        if(mCurrentMode == GAME_MODE_EDITOR)
			mGameDrawer->drawButtons(*mGame,width(),height(),mButtons);

	update() ;
    }
}

