#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>

#include "Level.h"

Level::Level()
{
	initDefault() ;

	mPlayerState = PLAYER_PLAY;
	mCollectedDiamonds = 0 ;
	mAllDiamondsCollected = false;

	mDiamondsToCollect = 40;
}
Level::Level(const std::string& fname)
{
	load(fname) ;
	mPlayerState = PLAYER_PLAY;
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

void Level::movePlayer(MoveDirection d)
{
    if(mPlayerState != PLAYER_PLAY)
        return ;
    
    uint32_t old_player_x = mPlayerX ;
    uint32_t old_player_y = mPlayerY ;
    
    uint32_t new_player_x = mPlayerX;
    uint32_t new_player_y = mPlayerY;
    
    switch(d)
    {
    case Left: if(mPlayerX > 0) new_player_x-- ;
	    break ;
    case Right: if(mPlayerX < mSizeX-1) new_player_x++ ;
	    break ;
    case Top:  if(mPlayerY > 0) new_player_y-- ;
	    break ;
    case Bottom: if(mPlayerY < mSizeY-1) new_player_y++ ;
	    break ;
    default:
	    std::cerr << "(EE) untreated case!" << std::endl;
    }
    
    if(operator()(new_player_x,new_player_y) == Level::Diamond)
    {
	    mPlayerX = new_player_x ;
	    mPlayerY = new_player_y ;

	    operator()(old_player_x,old_player_y) = Level::Void ;
	    operator()(mPlayerX    ,mPlayerY) = Level::Player ;
        
            mCollectedDiamonds++ ;
            
            if(mCollectedDiamonds >= mDiamondsToCollect)
            {
                mAllDiamondsCollected = true ;
		operator()(mExitX,mExitY) = Level::Exit ;
            }
    }
    else  if(operator()(new_player_x,new_player_y) == Level::Earth || operator()(new_player_x,new_player_y) == Level::Void || operator()(new_player_x,new_player_y) == Level::Exit)
    {
        if(operator()(new_player_x,new_player_y) == Level::Exit)
            mPlayerState = PLAYER_WIN ;
        
            mPlayerX = new_player_x ;
            mPlayerY = new_player_y ;
            
	    operator()(old_player_x,old_player_y) = Level::Void ;
	    operator()(mPlayerX,mPlayerY) = Level::Player ;
            
    } else if(operator()(new_player_x,new_player_y) == Level::Stone 
            && d == Right 
            && new_player_x + 1 < mSizeX-1
            && operator()(new_player_x + 1,new_player_y) == Level::Void)
    {
        operator()(new_player_x + 1,new_player_y) = Level::Stone ;
        operator()(new_player_x    ,new_player_y) = Level::Player ;
        operator()(mPlayerX        ,mPlayerY    ) = Level::Void ;
        
        mPlayerX = new_player_x ;
        mPlayerY = new_player_y ;
    }
    else if(operator()(new_player_x,new_player_y) == Level::Stone 
            && d == Left 
            && new_player_x - 1 > 0
            && operator()(new_player_x - 1,new_player_y) == Level::Void)
    {
        operator()(new_player_x - 1,new_player_y) = Level::Stone ;
        operator()(new_player_x    ,new_player_y) = Level::Player ;
        operator()(mPlayerX        ,mPlayerY    ) = Level::Void ;
        
        mPlayerX = new_player_x ;
        mPlayerY = new_player_y ;
    } else if(operator()(new_player_x,new_player_y) == Level::Bomb
            && d == Right
            && new_player_x + 1 < mSizeX-1
            && operator()(new_player_x + 1,new_player_y) == Level::Void)
    {
        operator()(new_player_x + 1,new_player_y) = Level::Bomb ;
        operator()(new_player_x    ,new_player_y) = Level::Player ;
        operator()(mPlayerX        ,mPlayerY    ) = Level::Void ;

        mPlayerX = new_player_x ;
        mPlayerY = new_player_y ;
    }
    else if(operator()(new_player_x,new_player_y) == Level::Bomb
            && d == Left
            && new_player_x - 1 > 0
            && operator()(new_player_x - 1,new_player_y) == Level::Void)
    {
        operator()(new_player_x - 1,new_player_y) = Level::Bomb ;
        operator()(new_player_x    ,new_player_y) = Level::Player ;
        operator()(mPlayerX        ,mPlayerY    ) = Level::Void ;

        mPlayerX = new_player_x ;
        mPlayerY = new_player_y ;
    }

}
void Level::load(const std::string &fname) 
{
   std::ifstream is(fname.c_str(),std::ios_base::in) ;
   
   is >> mSizeX ;
   is >> mSizeY ;
   is >> mPlayerX ;
   is >> mPlayerY ;

   std::cerr << "Loading game of size " << mSizeX << " x " << mSizeY << ", placer position: " << mPlayerX << ", " << mPlayerY << std::endl;
   
   is >> std::noskipws ;
   char s ;
   is >> s ;
   mContent.resize(mSizeX*mSizeY,Level::Earth) ;
   
   for(uint32_t i=0;i<mSizeY;++i)
   {
	   unsigned char s ;

       for(uint32_t j=0;j<mSizeX;++j)
       {
           is >> s ;
           operator()(j,i) = Level::ObjectId(s - ' ');

	   std::cerr << "\"" << s << "\"" << std::endl;
       }
       is >> s ;
	   std::cerr << "\"" << s << "\"" << std::endl;

       assert(s == '\n');
       
       //unsigned char s ;
       //is >> s ;
   }
   is.close() ;
}
void Level::save(const std::string &fname) const
{
   std::ofstream of(fname.c_str()) ;
   
   of << mSizeX << " " << mSizeY << std::endl;
   of << mPlayerX << " " << mPlayerY << std::endl;

   for(int i=0;i<mSizeY;++i)
   {
       for(int j=0;j<mSizeX;++j)
           of << (unsigned char)(operator()(j,i) + ' ');
       
       of << std::endl;
   }
   of.close() ;
}

void Level::initDefault()
{
	mCollectedDiamonds = 0 ;
	mSizeX = 50 ;
	mSizeY = 30 ;

	mContent.resize(mSizeX*mSizeY,Level::Earth) ;

	for(int i=0;i<mSizeX;++i)
	{
		operator()(i,0) = Level::Wall ;
		operator()(i,mSizeY-1) = Level::Wall ;
	}
	for(int j=0;j<mSizeY;++j)
	{
		operator()(0,j) = Level::Wall ;
		operator()(mSizeX-1,j) = Level::Wall ;
	}

	for(int i=0;i<100;++i)
		operator()(lrand48()%mSizeX,lrand48()%mSizeY) = Level::Wall ;
    
	for(int i=0;i<100;++i)
		operator()(1+(lrand48()%(mSizeX-2)),1+(lrand48()%(mSizeY-2))) = Level::MetalWall0 ;

	for(int i=0;i<100;++i)
		operator()(1+(lrand48()%(mSizeX-2)),1+(lrand48()%(mSizeY-2))) = Level::MetalWall1 ;

	for(int i=0;i<100;++i)
		operator()(1+(lrand48()%(mSizeX-2)),1+(lrand48()%(mSizeY-2))) = Level::Stone ;
    
	for(int i=0;i<50;++i)
		operator()(1+(lrand48()%(mSizeX-2)),1+(lrand48()%(mSizeY-2))) = Level::Diamond ;
    
	for(int i=0;i<5;++i)
		operator()(1+(lrand48()%(mSizeX-2)),1+(lrand48()%(mSizeY-2))) = Level::Bomb ;

	for(int i=0;i<6;++i)
		operator()(1+(lrand48()%(mSizeX-2)),1+(lrand48()%(mSizeY-2))) = Level::ObjectId((int)Level::Bug_top + (lrand48() & 0x3)) ;

	for(int i=0;i<6;++i)
		operator()(1+(lrand48()%(mSizeX-2)),1+(lrand48()%(mSizeY-2))) = Level::ObjectId((int)Level::Moss) ;

    	mPlayerX = 4 ;
    	mPlayerY = 4 ;
        
        mExitX = mSizeX-3 ;
        mExitY = mSizeY-3 ;
        
    	operator()(mPlayerX,mPlayerY) = Level::Player ;
        operator()(mExitX,mExitY) = Level::ClosedExit ;
}


void Level::fill( ObjectId o )
{
    for(int i=1;i<mSizeX-1;++i)
		for(int j=1;j<mSizeY-1;++j)
            operator()(i,j) = o ;
}
