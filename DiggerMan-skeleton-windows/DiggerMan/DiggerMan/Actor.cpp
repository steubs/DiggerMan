#include "Actor.h"
#include "StudentWorld.h"




//////////////////////////////////////////////////////////////  ACTOR    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Actor::Actor(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :GraphObject(imageID, startX, startY, dir, size, depth)
{
	setVisible(true);
}

Actor::~Actor()
{
	delete this;
}


void Actor::doSomething()
{

}


StudentWorld* Actor::getWorld()
{

	return m_SW;

}

//////////////////////////////////////////////////////////////  DIRT    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Dirt::Dirt(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(imageID, startX, startY, dir, size, depth)
{
	setVisible(true);
}

Dirt::~Dirt()
{
	delete this;
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
	delete this;
}

void DiggerMan::doSomething()
{

	//moveTo(getX() - 1, getY());
	
	int x;
	if (getWorld()->getKey(x) == true) //this statement specifically is causing issues for me
								 //if anyone has any ideas please let me know!
	{
		//// user hit a key this tick!
		switch (x)
		{
		case KEY_PRESS_LEFT:                                      
			moveTo(getX() - 1, getY());
			break;
	
		//default:
		//	break;
		////case KEY_PRESS_RIGHT:
		////	... move player to the right ...;
		////	break;
		////case KEY_PRESS_SPACE:
		////	... add a Squirt in front of the player...;
		////	break;
		////	// etc…
		}
	}


	//Below is the pseudocode taken from the specs, which im trying to implement above (pg.30) (read hint also)
	//getKey() is also talked about on pg 15


	//...
	//	int ch;
	//if (getWorld()->getKey(ch) == true)
	//{
	//	// user hit a key this tick!
	//	switch (ch)
	//	{
	//	case KEY_PRESS_LEFT:
	//		... move player to the left ...;
	//		break;
	//	case KEY_PRESS_RIGHT:
	//		... move player to the right ...;
	//		break;
	//	case KEY_PRESS_SPACE:
	//		... add a Squirt in front of the player...;
	//		break;
	//		// etc…
	//	}
	//}
	//...
	


	
	
	
}