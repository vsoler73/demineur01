#pragma once

#include <QPixmap>
#include <QGLViewer/qglviewer.h>

#include "GameDefs.h"
#include "Level.h"

class GameDrawer ;
class InterfaceButton ;

class GameViewer: public QWidget
{
    Q_OBJECT
    
public:
        
    GameViewer(QWidget *parent=NULL) ;

    void setGame(Level *g) ;
    void setCurrentMode(GameMode m) ;
    GameMode currentMode() { return mCurrentMode ; }

    // rederived methods from QGLViewer

    virtual void mousePressEvent(QMouseEvent *e) ;
    virtual void mouseReleaseEvent(QMouseEvent *e) ;
    virtual void mouseMoveEvent(QMouseEvent *e) ;
    virtual void resizeEvent(QResizeEvent *e) ;
    virtual void paintEvent(QPaintEvent *);
    
    virtual void keyPressEvent(QKeyEvent *e) ;
    
    virtual void addButton(int x, int y, const QPixmap &pixmap);
public slots:
    void reDraw() ;
    
private:
    void pixelCoordinatesToGameCoordinate(int x,int y,int& i,int& j) const;

    Level *mGame ;
    GameDrawer *mGameDrawer ;

    float mSceneCenterX;
    float mSceneCenterY;
    float mOldMouseX;
    float mOldMouseY;

    bool mMousePressed ;
    GameMode mCurrentMode ;
            
    std::vector<InterfaceButton*> mButtons ;
};
