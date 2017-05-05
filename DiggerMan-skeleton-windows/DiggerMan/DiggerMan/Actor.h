#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld; 

class Actor : public GraphObject
{
private:
	StudentWorld * m_SW;
public:
	Actor(int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0);
	virtual ~Actor();
	
	StudentWorld* getWorld();
	virtual void doSomething() = 0;

};
class Dirt : public Actor
{
public:
	Dirt(int imageID, int startX, int startY, Direction dir=right, double size = .25, unsigned int depth = 3);

	
	
	void doSomething();

	~Dirt();
};

class DiggerMan : public Actor
{
public:
	DiggerMan(int imageID, int startX, int startY, Direction dir=right, double size = 1.0, unsigned int depth = 0);

	void doSomething();

	

	~DiggerMan();
};





#endif // ACTOR_H_
