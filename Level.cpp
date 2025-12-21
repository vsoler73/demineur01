#include <stdlib.h>
#include <assert.h>

#include "Level.h"

Level::Level()
{
	initDefault() ;

	mPlayerState = PLAYER_PLAY;
//	mCollectedDiamonds = 0 ;
//  mAllDiamondsCollected = false;
}

ObjectId& Level::operator()(uint32_t i,uint32_t j)
{
	assert(i < mSizeX) ;
    assert(j < mSizeY) ;

	return mContent[mSizeX * j + i] ;
}
ObjectId Level::operator()(uint32_t i,uint32_t j) const
{
	assert(i < mSizeX) ;
	assert(j < mSizeY) ;

	return mContent[mSizeX * j + i] ;
}
int Level::NbrMine(uint32_t i, uint32_t j) const {
    assert(i < mSizeX) ;
    assert(j < mSizeY) ;

    return mNbrMine[mSizeX * j + i] ;
}



void Level::IncrementMine(int i, int j){
    if (i<0 || i<0)
        return;
    if (i>=mSizeX || j>=mSizeY)
        return;
    mNbrMine[mSizeX*j + i]++;
}

void Level::initDefault()
{
//	mCollectedDiamonds = 0 ;
	mSizeX = 50 ;
	mSizeY = 30 ;

    mContent.clear();
    mNbrMine.clear();
    mContent.resize(mSizeX*mSizeY,ObjectId::Void) ;
    mNbrMine.resize(mSizeX*mSizeY,0) ;

    for(int i=0;i<250;++i){
        int xmine=lrand48()%mSizeX;
        int ymine=lrand48()%mSizeY;
        while (xmine<2 && ymine<2){
            xmine=lrand48()%mSizeX;
            ymine=lrand48()%mSizeY;
        }
        if (!(operator()(xmine,ymine)&ObjectId::Mine)){
            operator()(xmine,ymine) |= ObjectId::Mine ;
            for(int x=-1;x<2;++x)
                for(int y=-1;y<2;++y)
                    if (!(x==0 && y==0))
                        IncrementMine(x+xmine,y+ymine);
        }
        else {
            i--;
        }
    }
}


void Level::fill( ObjectId o )
{
    for(uint i=1;i<mSizeX-1;++i)
        for(uint j=1;j<mSizeY-1;++j)
            operator()(i,j) = o ;
}
