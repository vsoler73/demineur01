#pragma once

#include <vector>
#include <stdint.h>
#include <string>
class Level
{
public:
	Level();
	Level(const std::string& fname);

	typedef enum {
		Void         = 0x00,
		Wall         = 0x01,
		Stone        = 0x02,
		Earth        = 0x03,
		Player       = 0x04,
		ClosedExit   = 0x05,
		Diamond      = 0x06,
		Exit         = 0x07,
		Bomb         = 0x08,
		Explosion_01 = 0x09,
		Explosion_02 = 0x0a,
		Explosion_03 = 0x0b,
		Explosion_04 = 0x0c,
		Bug_top      = 0x0d,
		Bug_right    = 0x0e,
		Bug_bottom   = 0x0f,
		Bug_left     = 0x10,
		Moss         = 0x11,
		MetalWall0   = 0x12,
		MetalWall1   = 0x13,
		MetalWall2   = 0x14
	} ObjectId;

	typedef enum {
		Left  = 0x00,
		Top   = 0x01,
		Right = 0x02,
		Bottom= 0x03
	} MoveDirection ;

	void initDefault();

	typedef enum {
		PLAYER_PLAY = 0x00,
		PLAYER_DEAD = 0x01,
		PLAYER_WIN  = 0x02
	} PlayerState;

	PlayerState playerState() const { return mPlayerState ; }
	bool allDiamondCollected() const { return mAllDiamondsCollected ; }

	ObjectId operator()(uint32_t i,uint32_t j) const ;
	ObjectId& operator()(uint32_t i,uint32_t j) ;

	void movePlayer(MoveDirection d) ;

	void die() { mPlayerState = PLAYER_DEAD ; }
    void startGame() { mPlayerState = PLAYER_PLAY ; }

	uint32_t sizeX() const { return mSizeX ; }
	uint32_t sizeY() const { return mSizeY ; }

	uint32_t playerX() const { return mPlayerX ; }
	uint32_t playerY() const { return mPlayerY ; }

	void save(const std::string& fname) const ;
	void load(const std::string& fname) ;

	uint32_t collectedDiamonds() const { return mCollectedDiamonds ; }

    void fill( ObjectId o ) ;

private:
	uint32_t mSizeX ;
	uint32_t mSizeY ;

	uint32_t mExitX ;
	uint32_t mExitY ;

	uint32_t mPlayerX ;
	uint32_t mPlayerY ;

	std::vector<ObjectId> mContent ;
	PlayerState mPlayerState ;

	bool mAllDiamondsCollected ;

	uint32_t mDiamondsToCollect ;
	uint32_t mCollectedDiamonds ;
};
