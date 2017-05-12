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
<<<<<<< HEAD
	
	
=======
	vector<vector<Dirt*>> dirt;//(Sharon)create vector to contain dirt
	vector<Actor*> actors_;
>>>>>>> origin/master
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

	vector<vector<Dirt*>> getDirt();

};

#endif // STUDENTWORLD_H_
