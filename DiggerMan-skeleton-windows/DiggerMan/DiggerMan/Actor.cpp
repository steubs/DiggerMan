#include "StudentWorld.h"
#include "Actor.h"
#include <cstdlib>


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
					if (!getWorld()->isThere()) {
						//getWorld()->playSound(SOUND_DIG); have to play this when digging through dirt
						moveTo(x - 1, y);
					}
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
					if (!getWorld()->isThere()) {
						//getWorld()->playSound(SOUND_DIG);
						moveTo(x + 1, y);
					}
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
					if (!getWorld()->isThere()) {
						//getWorld()->playSound(SOUND_DIG);
						moveTo(x, y + 1);
					}
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
					if (!getWorld()->isThere()) {
						//getWorld()->playSound(SOUND_DIG);
						moveTo(x, y - 1);
					}
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
		if (y == 0) {

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

////////////////////////////////////////////////////////////// GoldNugget  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GoldNugget::GoldNugget(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth), pickUpProtestor(false), pickUpDiggerman(false)
{
	setVisible(true);
}
void GoldNugget::doSomething()
{
	if (getAlive())
	{
		if (!pickUpDiggerman && !pickUpProtestor) {
			getWorld()->isClose();
			pickUpDiggerman = true;
			return;
		}
		else if (pickUpDiggerman && (!pickUpProtestor)) {
			getWorld()->isClose();
			int x = getX();
			int y = getY();
			int digX = getWorld()->getDiggerman()->getX();
			int digY = getWorld()->getDiggerman()->getY();
			double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
			if (SR <= 3.0) {
				setVisible(false);
				setAlive(false);
				getWorld()->increaseScore(10);
				getWorld()->playSound(SOUND_GOT_GOODIE);
				getWorld()->incGold();
			}
			pickUpDiggerman = false;
		}
	}
	else
		return;
}
GoldNugget::~GoldNugget()
{
}


//////////////////////////////////////////////////////////////  OIL  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Oil::Oil(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth) {
	setVisible(false);
}

void Oil::doSomething() {
	if (getAlive())
	{
		getWorld()->isClose();
		int x = getX();
		int y = getY();
		int digX = getWorld()->getDiggerman()->getX();
		int digY = getWorld()->getDiggerman()->getY();
		double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
		if (SR <= 3.0) {

			setVisible(false);
			setAlive(false);
			getWorld()->decBarrels();
			getWorld()->playSound(SOUND_FOUND_OIL);
			getWorld()->increaseScore(1000);
		}
	}
	else return;
}

Oil::~Oil() {
	
}
//////////////////////////////////////////////////////////////  SONAR  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sonar::Sonar(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth) {
	
}
void Sonar::doSomething() {
	if (getAlive()) {
		count++;
		int num = 300 - 10 * getWorld()->getLevel();
		int max = std::max(10,0);
		if (count == max) {
			setVisible(false);
			setAlive(false);
			getWorld()->decSonarInMap();
		}
	}
	else return;
}

Sonar::~Sonar() {

}

//////////////////////////////////////////////////////////////  SQUIRT  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Squirt::Squirt(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth) {

}

void Squirt::doSomething() {

}

Squirt::~Squirt() {
	
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

void RegularProtestor::setHealth(int health_)
{
	health = health_;
}

bool RegularProtestor::getLeaveOilFieldState()
{
	return leaveOilFieldState;
}

void RegularProtestor::doSomething()
{
	if (!getAlive()) return;//return if not alive
	else if (getTickCounter() > 0)
	{
		setTickCounter(getTickCounter() - 1);//decriment tick
		return;
	}
	//protestor is alive and able to move, therefore tick countrer should be set back to the level's correct value max(0,3-lvl)
	setTickCounter(max(0, 3 - 0));//placehold value
	if (!getLeaveOilFieldState())//protester moving freely
	{
		wander();
	}
	else
		return;

}

void RegularProtestor::wander()
{
	//code taken from DiggerMan but will be changed to work for RegularProtestor, differences are adding randMove instead of getKey(), wait(), etc.... Not finished
	//will keep code to check for walls, etc.
	int x = getX();
	int y = getY();

	int ch = 0;//PLACEHOLDER
	if (/*getWorld()->getKey(ch) == true*/1) {
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

void RegularProtestor::setTickCounter(int newTickCounter)
{
	tickCounter = newTickCounter;
}

RegularProtestor::~RegularProtestor()
{

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

}
