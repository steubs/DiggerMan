#include "Actor.h"
#include "StudentWorld.h"


Actor::Actor(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0):GraphObject(imageID, startX, startY, dir, size, depth)
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
