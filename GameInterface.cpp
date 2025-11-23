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

    loadGame(QString("start.blv")) ;
}

void GameInterface::editGame() 
{
    if(gameViewer->currentMode() == GAME_MODE_EDITOR)
    {
		if(_current_game != NULL)
			_current_game->start();

		if(gameViewer != NULL)
			gameViewer->setCurrentMode(GAME_MODE_GAME) ;

        actionLevelEditor->setText("Enter level editor") ;
    }
    else
    {
		if(_current_game != NULL)
			_current_game->stop();
    
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
	    _current_game->stop();
	    delete _current_game ;
    }

    _current_game = new DemineurGame ;
    _current_game->start();
    
    gameViewer->setCurrentMode(GAME_MODE_GAME) ;
    gameViewer->setGame(_current_game) ;
}
void GameInterface::saveGame() const
{
	if(_current_game == NULL)
        	return ;

    	QString name = QFileDialog::getSaveFileName(NULL,"Save your level","Choose a file to save to","Levels (*.blv)") ;
        
        if(name.isNull())
            return ;
        
    	_current_game->currentState().save(name.toStdString()) ;
}

void GameInterface::loadGame() 
{
    	QString name = QFileDialog::getOpenFileName(NULL,"Load a level","Choose a file to save to","Levels (*.blv)") ;
        
        if(name.isNull())
            return ;
        
        loadGame(name) ;
}

void GameInterface::loadGame(const QString& name)
{
    DemineurGame *tmp_game = new DemineurGame ;
    tmp_game->currentState().load(name.toStdString()) ;
    
    if(_current_game != NULL)
    {
	    _current_game->stop();
	    delete _current_game ;
    }
    
    _current_game = tmp_game ;
    
    gameViewer->setGame(_current_game) ;

    if(gameViewer->currentMode() == GAME_MODE_NONE)
		gameViewer->setCurrentMode(GAME_MODE_GAME) ;
    
    if(gameViewer->currentMode() == GAME_MODE_GAME)
		_current_game->start();
}
void GameInterface::about() const
{
	QMessageBox::information(NULL,QString("About Boulder"),
		QString("Boulder implements the classical <i>Boulder Dash</i> game. <br/><br/>Programing by Cyril Soler.")) ;
}















