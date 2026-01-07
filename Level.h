#pragma once

#include <vector>
#include <stdint.h>
#include <string>
#include "flags.h"

enum class ObjectId:uint8_t{
    Void = 0,
    Mine = 1,
    Drapeau = 2,
    CaseRevelee = 4,

    CaseBlanche = 64
};

REGISTER_ENUM_FLAGS_TYPE(ObjectId);

class Level
{
public:
	Level();
	Level(const std::string& fname);


	void initDefault();

	typedef enum {
		PLAYER_PLAY = 0x00,
		PLAYER_DEAD = 0x01,
		PLAYER_WIN  = 0x02
	} PlayerState;

	PlayerState playerState() const { return mPlayerState ; }
//	bool allDiamondCollected() const { return mAllDiamondsCollected ; }

	ObjectId operator()(uint32_t i,uint32_t j) const ;
	ObjectId& operator()(uint32_t i,uint32_t j) ;
    int NbrMine(uint32_t i, uint32_t j)const;
	void die() { mPlayerState = PLAYER_DEAD ; }
    void startGame() { mPlayerState = PLAYER_PLAY ; }

	uint32_t sizeX() const { return mSizeX ; }
	uint32_t sizeY() const { return mSizeY ; }
    bool ok(int i,int j) {
        return mSizeX>i && i>=0 && mSizeY>j && j>=0;
    }
//	uint32_t collectedDiamonds() const { return mCollectedDiamonds ; }

    void fill(ObjectId o ) ;

private:
	uint32_t mSizeX ;
	uint32_t mSizeY ;

    std::vector<ObjectId> mContent ;
    std::vector<uint8_t> mNbrMine ;
	PlayerState mPlayerState ;

    void IncrementMine(int i, int j);

//	bool mAllDiamondsCollected ;

 //   uint32_t mCollectedDiamonds ;
};
