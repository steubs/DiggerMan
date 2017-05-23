#include "StudentWorld.h"
#include "Actor.h"


//////////////////////////////////////////////////////////////  ACTOR    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Actor::Actor(StudentWorld *p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :GraphObject(imageID, startX, startY, dir, size, depth), isAlive(true), world(p),health(100)
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
	
}
void Actor::doSomething()
{

}
void Actor::setHealth(int health_)
{
	health = health_;
}

//////////////////////////////////////////////////////////////  DIRT    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Dirt::Dirt(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth)
{
	
}

Dirt::~Dirt()
{
	
}
void Dirt::doSomething()
{
	//doesn't do anything as said in specs.
}

//////////////////////////////////////////////////////////////  DIGGERMAN  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


DiggerMan::DiggerMan(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth)
{
	
}

DiggerMan::~DiggerMan()
{
	//delete getWorld()->m_diggerman;
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
					if (!getWorld()->isThere())
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
					if (!getWorld()->isThere())
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
					if (!getWorld()->isThere())
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
					if (!getWorld()->isThere())
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
Boulder::Boulder(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth),count(0),fell(false) {
	
}
Boulder::~Boulder(){
	
}
void Boulder::doSomething() {

	if (getAlive()) {
		int x = getX();
		int y = getY();
		if (y == 0){

			setVisible(false);
			setAlive(false);

		}
		if (y < 60 && y>0)//check under the boulder only if it's inside the map
		{
		
			if (getWorld()->checkUnder(this)) {
				count++;
				if (count >= 30) {//30 ticks have to pass before the boulder falls
					if (fell==false)//if this is the first time the boulder has moved at all
						getWorld()->playSound(SOUND_FALLING_ROCK);//play the sound once
					moveTo(x, y - 1);
					fell = true;//this also helps get rid of the boulder
				}
			}
			else if (fell == true){ //if the boulder has fallen

				setVisible(false);
				setAlive(false);
			}
			else
				return;
		}
	}
	else 
		return;
}
//////////////////////////////////////////////////////////////  OIL  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Oil::Oil(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth) {
	setVisible(true);//setVisible(false);
	setAlive(true);
}

void Oil::doSomething() {
	if (getAlive())
	{
		if (getX() == getWorld()->getDiggerman()->getX() && getY() == getWorld()->getDiggerman()->getY()){
		
			setVisible(false);
			setAlive(false);
			getWorld()->decBarrels();
			getWorld()->increaseScore(1000);
		}
	}
	else return;
}

Oil::~Oil() {
	
}

//////////////////////////////////////////////////////////////  SQUIRT  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Squirt::Squirt(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth) {

}

void Squirt::doSomething() {

}

Squirt::~Squirt() {
	delete this;
}

////////////////////////////////////////////////////////////// PROTESTOR  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RegularProtestor::RegularProtestor(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth)
{
	leaveOilFieldState = false;
	setHealth(5);
}

void RegularProtestor::setLeaveOilFieldState(bool state)
{
	leaveOilFieldState = state;
}
bool RegularProtestor::getLeaveOilFieldState()
{
	return leaveOilFieldState;
}

void RegularProtestor::doSomething()
{
	if (!getAlive()) return;//return if not alive
	/*if (isResting())
	{
		updateRestState();
		return;
	}*/
	if (getLeaveOilFieldState())
	{
		//code taken from DiggerMan but will be changed to work for RegularProtestor, differences are adding randMove instead of getKey(), wait(), etc.... Not finished
		//will keep code to check for walls, etc.
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
						if (!getWorld()->isThere())
							moveTo(x - 1, y);
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
						if (!getWorld()->isThere())
							moveTo(x + 1, y);
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
						if (!getWorld()->isThere())
							moveTo(x, y + 1);
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
						if (!getWorld()->isThere())
							moveTo(x, y - 1);
						break;
					}
				}
			}
		}
	}
	else
		return;

}



RegularProtestor::~RegularProtestor()
{
	delete this;
}



////////////////////////////////////////////////////////////// HARDCORE PROTESTOR  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HardcoreProtestor::HardcoreProtestor(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : RegularProtestor(p, imageID, startX, startY, dir, size, depth)
{
	setHealth(20);
}


void HardcoreProtestor::doSomething()
{
	
}


HardcoreProtestor::~HardcoreProtestor()
{
	delete this;
}
////////////////////////////////////////////////////////////// GoldNugget  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GoldNugget::GoldNugget(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth)
{
	setVisible(true);
}
void GoldNugget::doSomething()
{
	if (!getAlive()) 
	{
	
	}
	else
		return;
}
GoldNugget::~GoldNugget()
{
	delete this;
}
