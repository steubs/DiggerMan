#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class Actor : public GraphObject
{
private:

public:
	Actor(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0);
	virtual ~Actor();

	virtual void doSomething() = 0;

};
class Dirt : public Actor
{
public:
	Dirt(int imageID, int startX, int startY, Direction dir = none, double size = .25, unsigned int depth = 3);
	
	virtual void doSomething();

	virtual ~Dirt();
};





#endif // ACTOR_H_
