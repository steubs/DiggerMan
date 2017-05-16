#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>
#include<cmath>
using namespace std;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class StudentWorld : public GameWorld
{
private:
	Actor* m_diggerman;
	Dirt* dirtarr[64][60];
	vector<Actor*> actors;
public:

	StudentWorld(std::string assetDir)
		: GameWorld(assetDir)
	{
	}

	virtual int init();
	
	virtual int move();

	virtual void cleanUp();
	
	void removeDirt();

	bool checkUnder(Boulder * b);

	vector<Actor*> getActors() {
		return actors;
	}

};

#endif // STUDENTWORLD_H_
