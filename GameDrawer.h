#pragma once

#include <map>
#include <QPixmap>

#include "Level.h"
#include "GameDefs.h"

class DemineurGame ;
class InterfaceButton;

class GameDrawer
{
	public: 
		GameDrawer(int W,int H);

        virtual void update(const Level& game, int w, int h, GameMode m) ;
        virtual void drawButtons(const Level& game,int w,int h,const std::vector<InterfaceButton*>& buttons);
		virtual QPixmap pixmap() const ;

	float gameCoordToWindowCoordX(int i)  ;
	float gameCoordToWindowCoordY(int j)  ;
    
    	int windowCoordToGameCoordX(float x) ;
    	int windowCoordToGameCoordY(float y) ;
        QPixmap getImageForNbrMine(int i);
	private:
		QPixmap mDrawBuffer ;
        
        QPixmap getImageForObjectId(const ObjectId &oid);
    QPixmap getGameSprite_oid(const ObjectId& oid,int resolution);
    QPixmap getGameSprite_number(int n, int resolution);

//private:
//    void drawBackgroundGrid();
//    void drawGameContent();
//    void pasteSprite(float x,float y,const QPixmap& pix) ;
//    
//    float gameCoordToWindowCoordY(int i) ;
//    float gameCoordToWindowCoordX(int i) ;
//
//    QPixmap getImageForObjectId(const ObjectId &oid);
//    QPixmap getGameSprite(const ObjectId& oid,int resolution);
//
    
    typedef std::map<uint64_t,QPixmap> ImageCache ;
    
    ImageCache mImageCache ;
    
};

