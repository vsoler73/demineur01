#include <iostream>
#include <math.h>

#include <QPainter>
#include <QColor>

#include "GameDrawer.h"
#include "GameInterface.h"
#include "Level.h"

static const uint32_t SQUARE_SIZE_IN_PIXELS = 50 ;
static const uint32_t mSceneCenterX = 0 ;
static const uint32_t mSceneCenterY = 0 ;

GameDrawer::GameDrawer(int W,int H)
	:mDrawBuffer(W,H)
{
}

int GameDrawer::windowCoordToGameCoordX(float x) 
{ 
    return (int)floor((x - mSceneCenterX) / SQUARE_SIZE_IN_PIXELS) ;
}
int GameDrawer::windowCoordToGameCoordY(float y) 
{ 
    return (int)floor((y - mSceneCenterY) / SQUARE_SIZE_IN_PIXELS) ;
}
float GameDrawer::gameCoordToWindowCoordX(int i) 
{ 
    return SQUARE_SIZE_IN_PIXELS * i + mSceneCenterX;
}
float GameDrawer::gameCoordToWindowCoordY(int i) 
{ 
    return SQUARE_SIZE_IN_PIXELS * i + mSceneCenterY;
}

void GameDrawer::drawButtons(const Level &game, int w, int h, const std::vector<InterfaceButton*>& buttons)
{
    QPainter painter(&mDrawBuffer) ;

    for(uint32_t i=0;buttons.size();++i)
    {
		painter.drawPixmap(buttons[i]->x,buttons[i]->y,buttons[i]->pixmap.width(),buttons[i]->pixmap.height(),buttons[i]->pixmap) ;
        painter.drawRect(QRect(QPoint(buttons[i]->x,buttons[i]->y),QSize(30,30))) ;

        std::cerr << "Je dessine un bouton" << std::endl;
    }
}

void GameDrawer::update(const Level& level,int w,int h,GameMode m)
{
    if(mDrawBuffer.width() != w || mDrawBuffer.height() != h)
        mDrawBuffer = QPixmap(w,h) ;
    
    mDrawBuffer.fill(QColor::fromRgb(0,0,0)) ;
    
    QPainter painter(&mDrawBuffer) ;
    
    painter.setPen(QColor::fromRgb(0,0,0)) ;
    
    for(uint i=0;i<=level.sizeX();++i)
        painter.drawLine(QPointF(gameCoordToWindowCoordX(0),gameCoordToWindowCoordY(i)),QPointF(gameCoordToWindowCoordX(level.sizeY()),gameCoordToWindowCoordY(i))) ;

    for(uint j=0;j<=level.sizeY();++j)
	    painter.drawLine(QPointF(gameCoordToWindowCoordX(j),gameCoordToWindowCoordY(0)),  QPointF(gameCoordToWindowCoordX(j),gameCoordToWindowCoordY(level.sizeX()))) ;
    
    int resolution = SQUARE_SIZE_IN_PIXELS ;
            
    for(uint i=0;i<level.sizeX();++i)
        for(uint j=0;j<level.sizeY();++j)
	    {
                    float mx = gameCoordToWindowCoordX(i) ;
                    float my = gameCoordToWindowCoordX(j) ;
                    
                    painter.drawPixmap(mx,my,getGameSprite( level(i,j), resolution )) ;
	    }
    
    QFont font(painter.font()) ;
    font.setPointSize(40) ;
    
    painter.setPen(QRgb(0xffffffff)) ;
    painter.setFont(font) ;
    painter.drawText(50,150,QString::number(level.collectedDiamonds())) ;

    if(m == GAME_MODE_EDITOR)
    {
        QPen newPen(QColor::fromRgb(255,0,0), Qt::SolidLine);
        newPen.setWidth(64);
        painter.setPen(newPen);

        painter.drawRect(mDrawBuffer.rect());
    }
}

QPixmap GameDrawer::pixmap() const
{
	return mDrawBuffer ;
}
QPixmap GameDrawer::getImageForNbrMine(int i)
{
    switch (i) {
    default:
    case 0:           return QPixmap(":/images/0.png");
    case 1:           return QPixmap(":/images/1.png");
    case 2:           return QPixmap(":/images/2.png");
    case 3:           return QPixmap(":/images/3.png");
    case 4:           return QPixmap(":/images/4.png");
    case 5:           return QPixmap(":/images/5.png");
    case 6:           return QPixmap(":/images/6.png");
    case 7:           return QPixmap(":/images/7.png");
    case 8:           return QPixmap(":/images/8.png");
    }
    }


QPixmap GameDrawer::getImageForObjectId(const ObjectId& oid)
{
    switch(oid)
    {
        // OSEKOUR
    case ObjectId::Void:               return QPixmap(":/images/CaseBlanche.png");
    case ObjectId::Mine:               return QPixmap(":/images/stone.png");
    case ObjectId::Drapeau:            return QPixmap(":/images/drapeau.png");


    default:
        QColor col = QColor::fromHsv(int(oid)*20,255,255) ;
        QPixmap pix(128,128) ;
        pix.fill(col) ;
        
        return pix ;
    }

}

QPixmap GameDrawer::getGameSprite(const ObjectId& oid,int resolution)
{
    // store them in a cache
    
    uint32_t item_id = (int)oid + 1000*resolution ;	// this should allow enough object ids!
    
    ImageCache::const_iterator it = mImageCache.find(item_id) ;
    
    if(it == mImageCache.end())
    {
        std::cerr << "Image for id " << oid << " and resolution " << resolution << " not in cache. Creating!" << std::endl;
        
        QPixmap pix = getImageForObjectId(oid).scaled(QSize(resolution,resolution),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        
        mImageCache[item_id] = pix ;
        
        return pix ;
    }
    else
        return it->second ;
}

//void GameDrawer::drawGameContent(QPainter& painter)
//{
//    if(!mGame)
//        return ;
//    
//}
