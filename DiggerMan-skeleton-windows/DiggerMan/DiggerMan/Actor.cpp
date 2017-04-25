#include "Actor.h"
#include "StudentWorld.h"




//////////////////////////////////////////////////////////////  ACTOR    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

//////////////////////////////////////////////////////////////  DIRT    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Dirt::Dirt(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(imageID, startX, startY, dir, size, depth)
{
	setVisible(true);
}

Dirt::~Dirt()
{
	//destruct here
}

void Dirt::doSomething()
{
	//doesn't do anything as said in specs.
}

//////////////////////////////////////////////////////////////  DIGGERMAN  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


DiggerMan::DiggerMan(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(imageID, startX, startY, dir, size, depth)
{
	setVisible(true);
}

DiggerMan::~DiggerMan()
{
	//destruct here
}

void DiggerMan::doSomething()
{
	//doesn't do anything as said in specs.
}