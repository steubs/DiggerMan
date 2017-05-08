#include "StudentWorld.h"



//////////////////////////////////////////////////////////////  ACTOR    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Actor::Actor(StudentWorld *p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :GraphObject(imageID, startX, startY, dir, size, depth), isAlive(true), world(p)
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


Dirt::Dirt(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth)
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


DiggerMan::DiggerMan(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth), life(3), health(100)
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
	int ch;
	if (getAlive()) {
		if (getWorld()->getKey(ch) == true) {
			switch (ch) {
			case KEY_PRESS_LEFT:
                    if(getDirection() != left){
                        setDirection(left);
                        break;
                        
                    }
                    else{
                        setDirection(left);
                        moveTo(x - 1, y);
                        break;
                    }
			case KEY_PRESS_RIGHT:
                    if (getDirection() != right){
                        setDirection(right);
                        break;
                    }
                    else{
                        setDirection(right);
                        moveTo(x + 1, y);
                        break;
                    }
			case KEY_PRESS_UP:
                    if(getDirection() != up){
                        setDirection(up);
                        break;
                    }
                    else{
                        setDirection(up);
                        moveTo(x, y + 1);
                        break;
                    }
			case KEY_PRESS_DOWN:
                    if(getDirection() != down){
                        setDirection(down);
                        break;
                    }
                    else{
                        setDirection(down);
                        moveTo(x, y - 1);
                        break;
                    }
			}
		}
	
	}
	else
		return;
	
}
//////////////////////////////////////////////////////////////  BOULDER  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Boulders::Boulders(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth) {
	
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
