#include <stdlib.h>
#include <assert.h>

#include "Level.h"

const Level::ObjectId Level::Void=0x00;
const Level::ObjectId Level::Mine=0x01;
const Level::ObjectId Level::Drapeau=0x02;
const Level::ObjectId Level::CaseRevelee=0x04;

Level::Level()
{
	initDefault() ;

	mPlayerState = PLAYER_PLAY;
	mCollectedDiamonds = 0 ;
    mAllDiamondsCollected = false;
}

Level::ObjectId& Level::operator()(uint32_t i,uint32_t j) 
{
	assert(i < mSizeX) ;
	assert(j < mSizeY) ;

	return mContent[mSizeX * j + i] ;
}
Level::ObjectId Level::operator()(uint32_t i,uint32_t j) const
{
	assert(i < mSizeX) ;
	assert(j < mSizeY) ;

	return mContent[mSizeX * j + i] ;
}

void Level::initDefault()
{
	mCollectedDiamonds = 0 ;
	mSizeX = 50 ;
	mSizeY = 30 ;

    mContent.clear();
    mContent.resize(mSizeX*mSizeY,Level::Void) ;

    for(uint i=0;i<mSizeX;++i)
        for(uint j=0;j<mSizeY;++j)
            operator()(i,j) = Level::Void ;

	for(int i=0;i<100;++i)
        operator()(lrand48()%mSizeX,lrand48()%mSizeY) |= int(Level::Mine) ;
}


void Level::fill( ObjectId o )
{
    for(uint i=1;i<mSizeX-1;++i)
        for(uint j=1;j<mSizeY-1;++j)
            operator()(i,j) = o ;
}
