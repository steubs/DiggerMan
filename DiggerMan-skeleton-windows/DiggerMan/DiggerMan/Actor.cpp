#include "StudentWorld.h"
#include "Actor.h"
#include <algorithm>
#include <cmath>
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

bool Actor::isDirtThere() {
	int x = getX(), y = getY();

	if (getDirection() == GraphObject::Direction::left) {
		if (y < 57)
		{

			if ((getWorld()->getDirt(x - 1, y)->getAlive())
				|| (getWorld()->getDirt(x - 1, y + 1)->getAlive())
				|| (getWorld()->getDirt(x - 1, y + 2)->getAlive())
				|| (getWorld()->getDirt(x - 1, y + 3)->getAlive()))
				return true;
		}
		if (y == 59) {
			if (getWorld()->getDirt(x - 1, y)->getAlive())
				return true;
		}
		else if (y == 58) {
			if (getWorld()->getDirt(x - 1, y)->getAlive()
				|| getWorld()->getDirt(x - 1, y + 1)->getAlive())
				return true;
		}
		else if (y == 57) {
			if (getWorld()->getDirt(x - 1, y)->getAlive()
				|| getWorld()->getDirt(x - 1, y + 1)->getAlive()
				|| getWorld()->getDirt(x - 1, y + 2)->getAlive())
				return true;
		}
	}
	else if (getDirection() == GraphObject::Direction::right) {
		if (y < 57) {
			if ((getWorld()->getDirt(x + 1, y)->getAlive())
				|| (getWorld()->getDirt(x + 1, y + 1)->getAlive())
				|| (getWorld()->getDirt(x + 1, y + 2)->getAlive())
				|| (getWorld()->getDirt(x + 1, y + 3)->getAlive()))
				return true;
		}
		if (y == 59) {
			if (getWorld()->getDirt(x + 1, y)->getAlive()
				|| getWorld()->getDirt(x + 1, y)->getAlive())
				return true;
		}
		else if (y == 58) {
			if (getWorld()->getDirt(x + 1, y)->getAlive()
				|| getWorld()->getDirt(x + 1, y + 1)->getAlive())
				return true;
		}
		else if (y == 57) {
			if (getWorld()->getDirt(x + 1, y)->getAlive()
				|| getWorld()->getDirt(x + 1, y + 1)->getAlive()
				|| getWorld()->getDirt(x + 1, y + 2)->getAlive())
				return true;
		}
	}
	else if (getDirection() == GraphObject::Direction::down) {
		if (y - 1 < 60) {
			if ((getWorld()->getDirt(x, y - 1)->getAlive())
				|| (getWorld()->getDirt(x + 1, y - 1)->getAlive())
				|| (getWorld()->getDirt(x + 2, y - 1)->getAlive())
				|| (getWorld()->getDirt(x + 3, y - 1)->getAlive()))
				return true;
		}
	}
	else if (getDirection() == GraphObject::Direction::up) {
		if (y < 57)
		{
			if ((getWorld()->getDirt(x, y + 1)->getAlive())
				|| (getWorld()->getDirt(x + 1, y + 1)->getAlive())
				|| (getWorld()->getDirt(x + 2, y + 1)->getAlive())
				|| (getWorld()->getDirt(x + 3, y + 1)->getAlive())
				|| (getWorld()->getDirt(x + 4, y + 1)->getAlive()))
				return true;
		}
	}
	return false;
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
						moveTo(x - 1, y);
					}
					if (getWorld()->removeDirt()) {
						getWorld()->playSound(SOUND_DIG);
					}
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
						moveTo(x + 1, y);
					}
					if (getWorld()->removeDirt()) {
						getWorld()->playSound(SOUND_DIG);
					}
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
						moveTo(x, y + 1);
					}
					if (getWorld()->removeDirt())
						getWorld()->playSound(SOUND_DIG);
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
						moveTo(x, y - 1);
					}
					if (getWorld()->removeDirt()) {
						getWorld()->playSound(SOUND_DIG);
					}
					break;
				}
            case 'z':
                if(getWorld()->getSonar() > 0){
                    getWorld()->setallVisible();
                    getWorld()->decSonar();
                }
                    break;
            case 'Z':
                if(getWorld()->getSonar() > 0){
                    getWorld()->setallVisible();
                    getWorld()->decSonar();
                }
                    break;
			case KEY_PRESS_ESCAPE:
				setAlive(false);
				break;
			case KEY_PRESS_SPACE:
				getWorld()->decWater();
				break;
				setAlive(false); 
				break; 
			case KEY_PRESS_TAB:
				getWorld()->dropGold();
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
	if (getAlive())
	{
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
					int BX = getWorld()->getDiggerman()->getX();
					int BY = getWorld()->getDiggerman()->getY();
					double SR = pow((pow(abs(x - BX), 2) + pow(y - BY, 2)), 0.5);
					if (SR <= 3.0) {
						getWorld()->getDiggerman()->setVisible(false);
						getWorld()->getDiggerman()->setAlive(false);
					}
					//getWorld()->BoulderHitDig();
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
	setVisible(false);
}
void GoldNugget::doSomething()
{
	if (getAlive())
	{
		int x = getX();
		int y = getY();
		int digX = getWorld()->getDiggerman()->getX();
		int digY = getWorld()->getDiggerman()->getY();
		double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
		if (SR != 0 && !pickUpProtestor) {
			if (SR <= 4.0 && !pickUpDiggerman && !pickUpProtestor) {// can we leave this value so its easier to see the objects when we get close
				// you can change it back when we turn it in
				pickUpDiggerman = true;
				setVisible(true);
				return;
			}
			if (SR <= 3.0 && pickUpDiggerman && !pickUpProtestor) {
				setVisible(true);
				setVisible(false);
				setAlive(false);
				getWorld()->increaseScore(10);
				getWorld()->playSound(SOUND_GOT_GOODIE);
				getWorld()->incGold();
				pickUpDiggerman = false;
			}
		}
		else {
			pickUpProtestor = true;
			if (getWorld()->pickUPPRO(x, y)){
				getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
				setVisible(false);
				setAlive(false);
			}
		}
	}
		else
			return;
}
GoldNugget::~GoldNugget()
{
}


//////////////////////////////////////////////////////////////  OIL  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Oil::Oil(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth),pick(false) {
	setVisible(true);
}

void Oil::doSomething() {
	if (getAlive())
	{
		
		int x = getX();
		int y = getY();
		int digX = getWorld()->getDiggerman()->getX();
		int digY = getWorld()->getDiggerman()->getY();
		double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
		if (SR <= 10.0 && !pick) { // can we leave this value so its easier to see the objects when we get close
									// you can change it back when we turn it in
			pick = true;
			setVisible(true);
			return;
		}
		if (SR <= 3.0 &&pick) {
			setVisible(true);
			setVisible(false);
			setAlive(false);
			getWorld()->decBarrels();
			getWorld()->playSound(SOUND_FOUND_OIL);
			getWorld()->increaseScore(1000);
			pick = false;
		}
	}
	else 
		return;
}
Oil::~Oil() {
	
}
//////////////////////////////////////////////////////////////  SONAR  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Sonar::Sonar(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth),count(0) {
	
}
void Sonar::doSomething() {
	if (getAlive()) {
		count++;
        int x = getX();
        int y = getY();
        int digX = getWorld()->getDiggerman()->getX();
        int digY = getWorld()->getDiggerman()->getY();
        double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
        int current_level = getWorld()->getLevel();
		int a = max(100, 300 - 10 * current_level);
		if (SR <= 3) {
			setVisible(false);
			setAlive(false);
			getWorld()->decSonarInMap();
			getWorld()->incSonar();
			getWorld()->playSound(SOUND_GOT_GOODIE);
			getWorld()->increaseScore(75);
		}
		else if (count == a) {
			setVisible(false);
			setAlive(false);
			getWorld()->decSonarInMap();
		}
	}
	else return;
}

Sonar::~Sonar() {

}

//////////////////////////////////////////////////////////////  WATERPOOLS  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Water::Water(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth),count(0) {

}

void Water::doSomething() {
	if (getAlive()) {
		count++;
		int x = getX();
		int y = getY();
		int digX = getWorld()->getDiggerman()->getX();
		int digY = getWorld()->getDiggerman()->getY();
		double SR = pow((pow(abs(x - digX), 2) + pow(y - digY, 2)), 0.5);
		int current_level = getWorld()->getLevel();
		int a = max(100, 300 - 10 * current_level);
		if (SR <= 3) {
			setVisible(false);
			setAlive(false);
			getWorld()->decWaterInMap();
			getWorld()->incWater();
			getWorld()->playSound(SOUND_GOT_GOODIE);
			getWorld()->increaseScore(100);
		}
		else if (count == a) {
			setVisible(false);
			setAlive(false);
			getWorld()->decWaterInMap();
		}
	}
	else return;
}

Water::~Water() {

}

//////////////////////////////////////////////////////////////  SQUIRT  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Squirt::Squirt(StudentWorld*p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth) {

}

void Squirt::doSomething() {

}

Squirt::~Squirt() {
	
}

////////////////////////////////////////////////////////////// PROTESTOR  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RegularProtestor::RegularProtestor(StudentWorld* p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) :Actor(p, imageID, startX, startY, dir, size, depth),tickCounter(0),direction_integer(1)
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
void RegularProtestor::setTickCounter(int tickCounter_)
{
	tickCounter = tickCounter_;
}

void RegularProtestor::leaveOilField()
{

}
void RegularProtestor::doSomething()
{
	if (!getAlive()) return;//return if not alive
	
	if (leaveOilFieldState == true)
	{
		leaveOilField();
		return;
	}

	if (getHealth()==0)//this should only happen once in a protestor's life
	{
		leaveOilFieldState = true;
		getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
		tickCounter = 0;
	}

	if (tickCounter > 0)
	{
		tickCounter--;//decriment tick
		return;
	}
	
	//protestor is alive and able to move, therefore tick countrer should be set back to the level's correct value max(0,3-lvl)
	setTickCounter(max(0, 3));//placehold value
	
	if (!getLeaveOilFieldState())//protester is moving freely
	{
		if (canMovePerpendicular()) return;
		wander();
		numSquaresToMoveInCurrentDirection--;
	}
		

}

bool RegularProtestor::canMovePerpendicular()
{
	return 0;//temp
	int x = getX(), y = getY();

	if (getDirection() == left)
	{
		if ( !getWorld()->getDirt(getX()-1, getY() - 1)->getAlive()
		  && !getWorld()->getDirt(getX()-2, getY() - 1)->getAlive()
		  && !getWorld()->getDirt(getX()+1, getY() - 1)->getAlive()
		  && !getWorld()->getDirt(getX()+1, getY() - 1)->getAlive())
		{
			
			moveTo(getX(), getY());
			//moveTo(getX(), getY()-1);
			setDirection(down);
			numSquaresToMoveInCurrentDirection = rand() % 58 + 6;
			return 1;
		}
	}
	else if (getDirection() == right)
	{

	}
	else if (getDirection() == up)
	{

	}
	else if (getDirection() == down)
	{

	}
	return 0;
}

void RegularProtestor::wander()
{
	int x = getX();
	int y = getY();

	if (numSquaresToMoveInCurrentDirection <= 0)//we need to switch directions
	{

		direction_integer = rand() % 4;
		switchDirection(direction_integer);
		numSquaresToMoveInCurrentDirection = rand() % 58 + 6;
		return;
	}


	switch (direction_integer) {

	case 0:
		if (x < 1 || isDirtThere())
		{

			numSquaresToMoveInCurrentDirection = 0;//has hit a wall, switch directions and reset numSquaresTo...
			break;
		}
		if (!isDirtThere())
			moveTo(x - 1, y);
		else numSquaresToMoveInCurrentDirection = 0;
		break;
	case 1:
		if (x > 59 || isDirtThere())
		{

			numSquaresToMoveInCurrentDirection = 0;
			break;
		}
		if (!isDirtThere())
			moveTo(x + 1, y);
		else numSquaresToMoveInCurrentDirection = 0;
		break;
	case 2:
		if (y > 59 || isDirtThere())
		{

			numSquaresToMoveInCurrentDirection = 0;
			break;
		}
		if (!isDirtThere())
			moveTo(x, y + 1);
		else numSquaresToMoveInCurrentDirection = 0;
		break;
	case 3:
		if (y < 1 || isDirtThere())
		{

			numSquaresToMoveInCurrentDirection = 0;
			break;
		}
		if (!isDirtThere())
			moveTo(x, y - 1);
		else numSquaresToMoveInCurrentDirection = 0;
		break;

	}
}



void RegularProtestor::switchDirection(int direction)
{
	switch (direction)
	{
	case 0:
		setDirection(left);
		break;
	case 1:
		setDirection(right);
		break;
	case 2:
		setDirection(up);
		break;
	case 3:
		setDirection(down);
		break;
	}
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
