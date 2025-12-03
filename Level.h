#pragma once

#include <vector>
#include <stdint.h>
#include <string>
class Level
{
public:
    typedef int ObjectId;
	Level();
	Level(const std::string& fname);

    static const ObjectId
        Void,
        Mine,
        Drapeau,
        CaseRevelee;

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

	void die() { mPlayerState = PLAYER_DEAD ; }
    void startGame() { mPlayerState = PLAYER_PLAY ; }

	uint32_t sizeX() const { return mSizeX ; }
	uint32_t sizeY() const { return mSizeY ; }

	uint32_t collectedDiamonds() const { return mCollectedDiamonds ; }

    void fill(ObjectId o ) ;

private:
	uint32_t mSizeX ;
	uint32_t mSizeY ;

    std::vector<int> mContent ;
	PlayerState mPlayerState ;

	bool mAllDiamondsCollected ;

    uint32_t mCollectedDiamonds ;
};
