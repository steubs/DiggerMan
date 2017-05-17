#include "StudentWorld.h"
#include "Actor.h"


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
				if (getDirection() != left) {
					setDirection(left);
					break;
				}
				else {
					setDirection(left);
					if (x < 1)
						break;
					bool isThere = false;//started making the diggerman not run into boulders
					for (unsigned int i = 0;i < getWorld()->getActors().size(); i++) {
						if ((x - 1 == getWorld()->getActors()[i]->getX() + 3 &&
							y == getWorld()->getActors()[i]->getY()) ||
							(x - 1 == getWorld()->getActors()[i]->getX() + 3 &&
							y == getWorld()->getActors()[i]->getY() + 1) ||
							(x - 1 == getWorld()->getActors()[i]->getX() + 3 &&
							y == getWorld()->getActors()[i]->getY() + 2 )||
							(x - 1 == getWorld()->getActors()[i]->getX() + 3 &&
                             y == getWorld()->getActors()[i]->getY() + 3) || (x - 1 == getWorld()->getActors()[i]->getX() + 3 && y == getWorld()->getActors()[i]->getY() - 1) || (x - 1 == getWorld()->getActors()[i]->getX() + 3 && y == getWorld()->getActors()[i]->getY()-2) || (x - 1 == getWorld()->getActors()[i]->getX() + 3 && y == getWorld()->getActors()[i]->getY()-3))
							isThere = true;
						}
					if (isThere == true)
						break;
					moveTo(x - 1, y);
					getWorld()->removeDirt();
					break;
				}
			case KEY_PRESS_RIGHT:
				if (getDirection() != right) {
					setDirection(right);
					break;
				}
				else {
					setDirection(right);
					if (x > 59)
						break;
					moveTo(x + 1, y);
					getWorld()->removeDirt();
					break;
				}
			case KEY_PRESS_UP:
				if (getDirection() != up) {
					setDirection(up);
					break;
				}
				else {
					setDirection(up);
					if (y > 59)
						break;
					moveTo(x, y + 1);
					getWorld()->removeDirt();
					break;
				}
			case KEY_PRESS_DOWN:
				if (getDirection() != down) {
					setDirection(down);
					break;
				}
				else {
					setDirection(down);
					if (y < 1)
						break;
					moveTo(x, y - 1);
					getWorld()->removeDirt();
					break;
				}
			}
		}
	}
	else
		return;

}
//////////////////////////////////////////////////////////////  BOULDER  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Boulder::Boulder(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth) {
	
}
Boulder::~Boulder(){
	delete this;
}
void Boulder::doSomething() {

	if (getAlive()) {
		int x = getX();
		int y = getY();
		if (y < 60 && y>0)//check under the boulder only if it's inside the map
		{
			if (getWorld()->checkUnder(this)) {
				count++;//this was what counted the ticks so removing made it not work
				//idk if these variables i made have to be private or not
				if (count >= 30) {//30 ticks have to pass before the boulder falls
					if (fell==false)//if this is the first time the boulder has moved at all
						getWorld()->playSound(SOUND_FALLING_ROCK);//play the sound once
					moveTo(x, y - 1);
					fell = true;//this also helps get rid of the boulder
				}
			}
			else if (fell == true || y == 0)
			{//if the boulder has fallen or if it's at the bottom of the map
				setVisible(false);//make it go away and set alive to false
				setAlive(false);
			}

		}
	}
	else return;//gotta return if the boulder is dead
}
//////////////////////////////////////////////////////////////  Protestor  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Protestor::Protestor(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Protestor(p, imageID, startX, startY, dir, size, depth)
{
	leaveOilFieldState = false;
}

void Protestor::setLeaveOilFieldState(bool state)
{
	leaveOilFieldState = state;
}
void Protestor::setHealth(int health_)
{
	health = health_;
}

RegularProtestor::RegularProtestor(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Protestor(p, imageID, startX, startY, dir, size, depth)
{
	setHealth(5);
}

HardcoreProtestor::HardcoreProtestor(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : Protestor(p, imageID, startX, startY, dir, size, depth)
{
	setHealth(20);
}

void RegularProtestor::doSomething()
{

}

void HardcoreProtestor::doSomething()
{

}

RegularProtestor::~RegularProtestor()
{
	delete this;
}

Protestor::~Protestor()
{
	delete this;
}

HardcoreProtestor::~HardcoreProtestor()
{
	delete this;
}