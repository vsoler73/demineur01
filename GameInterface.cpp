#include <iostream>
#include <math.h>

#include <QKeyEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include "GameInterface.h"
#include "DemineurGame.h"

using namespace std ;

GameInterface::GameInterface()
	:QMainWindow(NULL)
{
	setupUi(this) ;
    
	_current_game = NULL ;
    
	if(gameViewer != NULL)
		gameViewer->setCurrentMode(GAME_MODE_NONE) ;

	//mSceneCenterPos = QPointF(0,0);
	//mMousePressed = false ;

	connect(actionNew,SIGNAL(triggered()),this,SLOT(newGame())) ;
	connect(actionSave,SIGNAL(triggered()),this,SLOT(saveGame())) ;
	connect(actionLoad,SIGNAL(triggered()),this,SLOT(loadGame())) ;
	connect(actionLevelEditor,SIGNAL(triggered()),this,SLOT(editGame())) ;

    //loadGame(QString("start.blv")) ;
}

void GameInterface::editGame() 
{
    if(gameViewer->currentMode() == GAME_MODE_EDITOR)
    {
		if(gameViewer != NULL)
			gameViewer->setCurrentMode(GAME_MODE_GAME) ;

        actionLevelEditor->setText("Enter level editor") ;
    }
    else
    {   
		if(gameViewer != NULL)
			gameViewer->setCurrentMode(GAME_MODE_EDITOR) ;

        actionLevelEditor->setText("Quit level editor") ;
    }
}

void GameInterface::quit() const
{
	exit(0) ;
}

void GameInterface::newGame()
{
    if(_current_game != NULL)
    {
	    delete _current_game ;
    }

    _current_game = new DemineurGame ;
    
    gameViewer->setCurrentMode(GAME_MODE_GAME) ;
    gameViewer->setGame(_current_game) ;
}

void GameInterface::about() const
{
	QMessageBox::information(NULL,QString("About Boulder"),
		QString("Boulder implements the classical <i>Boulder Dash</i> game. <br/><br/>Programing by Cyril Soler.")) ;
}















