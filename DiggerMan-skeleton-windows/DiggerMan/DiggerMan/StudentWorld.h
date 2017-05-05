#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <vector>
using namespace std;

#include "GraphObject.h"
#include "Actor.h"
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
	

	virtual int move()
	{
		actors_[0]->doSomething();
		return GWSTATUS_CONTINUE_GAME;//(Sharon) chose continue game to see the dirt 
		/*This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
		Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.*/
		/*decLives();*/
		//return GWSTATUS_PLAYER_DIED;
	}

	virtual void cleanUp()
	{

	}

private:
};

#endif // STUDENTWORLD_H_