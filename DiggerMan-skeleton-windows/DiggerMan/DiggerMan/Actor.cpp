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
    
  
    
    
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            if (i <= 33 && i >= 30 && j <= 59 && j >= 8)
            {
                continue;
            }
            if (getWorld()->dirtarr[i][j]->getX() == getWorld()->m_diggerman->getX() && getWorld()->dirtarr[i][j]->getY() == getWorld()->m_diggerman->getY()){
                
                getWorld()->dirtarr[i][j]->setVisible(false);
                
                // trying to figure out how to set all 4x4 dirt invisible
                //getWorld()->dirtarr[i+1][j]->setVisible(false);
                //getWorld()->dirtarr[i+2][j]->setVisible(false);
                //getWorld()->dirtarr[i+3][j]->setVisible(false);
                }
            }
        }
    

        
        

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
						if (x < 1)
							break;
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
						if (x > 59)
							break;
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
						if (y > 59)
							break;
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
						if (y < 1)
							break;
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
