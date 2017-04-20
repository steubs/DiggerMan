#include "Actor.h"
#include "StudentWorld.h"


Actor::Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :GraphObject(imageID, startX, startY, dir, size, depth)
{
	setVisible(true);
}

Actor::~Actor()
{
	//destruct here
}

void Actor::doSomething()
{

}
