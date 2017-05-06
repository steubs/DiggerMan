#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
using namespace std;

#include "GraphObject.h"

class Actor;
class Dirt;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
private:
	vector<Dirt*> dirt;//(Sharon)create vector to contain dirt
	vector<Actor*> actors_;
public:
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