#include "Actor.h"
<<<<<<< HEAD
#include <conio.h>
#include "StudentWorld.h"
//
//#define KEY_UP 1002
//#define KEY_DOWN 1003
//#define KEY_LEFT 1000
//#define KEY_RIGHT 1001
#define KEY_UP KEY_PRESS_UP
#define KEY_DOWN 2
#define KEY_LEFT 4
#define KEY_RIGHT 6
=======
#include "StudentWorld.h"



>>>>>>> origin/master
//////////////////////////////////////////////////////////////  ACTOR    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Actor::Actor(/*StudentWorld *p, */int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :GraphObject(imageID, startX, startY, dir, size, depth), isAlive(true)/*, world(p)*/
{
	setVisible(true);
	setAlive(true);
}

bool Actor::getAlive(){
	return isAlive;
}
void Actor::setAlive(bool Is){
	isAlive = Is;
}
StudentWorld *Actor::getWorld(){
	world = new StudentWorld("");
	return world;
}
Actor::~Actor()
{
	delete this;
}
void Actor::doSomething()
{

}

//////////////////////////////////////////////////////////////  DIRT    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


<<<<<<< HEAD
Dirt::Dirt(/*StudentWorld*p, */int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(/*p, */imageID, startX, startY, dir, size, depth)
=======
Dirt::Dirt(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth)
>>>>>>> origin/master
{
	
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


<<<<<<< HEAD
DiggerMan::DiggerMan(/*StudentWorld*p, */int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(/*p, */imageID, startX, startY, dir, size, depth), life(3), health(100)
=======
DiggerMan::DiggerMan(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth), life(3), health(100)
>>>>>>> origin/master
{
	
}

DiggerMan::~DiggerMan()
{
	delete this;
}
void DiggerMan::doSomething()
{
	int x = getX();
	int y = getY();

	if (getAlive()) {
		int ch=0;
		if (getWorld()->getKey(ch) == true) {
			switch (ch) {
			case KEY_PRESS_LEFT:
				setDirection(left);
				moveTo(x - 1, y);
				break;
			case KEY_PRESS_RIGHT:
				setDirection(right);
				moveTo(x + 1, y);
				break;
			case KEY_PRESS_UP:
				setDirection(up);
				moveTo(x, y + 1);
				break;
			case KEY_PRESS_DOWN:
				setDirection(down);
				moveTo(x, y - 1);
			default:
				return;
			}
		}
<<<<<<< HEAD
		else
		return;
	}
=======
	
	}
	else
		return;
>>>>>>> origin/master
	
}
	//doesn't do anything as said in specs.
//////////////////////////////////////////////////////////////  BOULDER  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
Boulders::Boulders(/*StudentWorld*p, */int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(/*p, */imageID, startX, startY, dir, size, depth) {
	setVisible(true);
	setAlive(true);
=======
Boulders::Boulders(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth) {
	
>>>>>>> origin/master
}
Boulders::~Boulders(){
	delete this;
}
void Boulders::doSomething() {
	if (getAlive()){
		int x = getX();
		int y = getY();
	}
	else
		return;
}

//////////////////////////////////////////////////////////////  Protestor  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
