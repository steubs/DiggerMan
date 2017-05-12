#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
using namespace std;


class Actor;
class Dirt;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
private:
	
	
public:
    
    Actor* m_diggerman;
    Dirt* dirtarr[64][64];
    
	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
	}

	virtual int init();
	
	virtual int move();

	virtual void cleanUp();

private:
};

#endif // STUDENTWORLD_H_
