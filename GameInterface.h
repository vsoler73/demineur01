#ifndef _GAMEINTERFACE_H
#define _GAMEINTERFACE_H

#include <QObject>
#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "ui_GameInterface.h"

class DemineurGame;

class InterfaceButton
{
public:
    uint32_t x ;
    uint32_t y ;
    QPixmap pixmap ;
};

class GameInterface: public QMainWindow, private Ui::GameInterface
{
	Q_OBJECT

	public:
		GameInterface() ;

	private slots:
		void quit() const ;
		void newGame() ;
		void editGame() ;
		void about() const ;

	private:
        Level *_current_game ;
};

#endif

