#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;
class Actor : public GraphObject
{
private:
	bool isAlive;
	StudentWorld *world;
	int health;
public:
	Actor(StudentWorld *p, int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0);
	void setAlive(bool Is);
	bool getAlive();
	int getHealth() { return health; }
	StudentWorld * getWorld();
	virtual ~Actor();
	virtual void doSomething() = 0;

};

class Dirt : public Actor
{
private:
public:
	Dirt(StudentWorld *p, int imageID, int startX, int startY, Direction dir = right, double size = .25, unsigned int depth = 3);
	void doSomething();
	~Dirt();
};

class DiggerMan : public Actor
{
private:
	
public:
	DiggerMan(StudentWorld *p,int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0);
	void doSomething();
	
	~DiggerMan();
};

class Boulder : public Actor
{
private:
public:
	Boulder(StudentWorld *p, int imageID, int startX, int startY, Direction dir = down, double size = 1.0, unsigned int depth = 1);
	int count = 0;
	bool fell = false;
	void doSomething();
	~Boulder();
};

class Oil : public Actor
{
private:
public:
	Oil(StudentWorld *p, int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 2);
	void doSomething();
	~Oil();
};

class Squirt : public Actor
{
private:
public:
	Squirt(StudentWorld *p, int imageID, int startX, int startY, Direction dir = down, double size = 1.0, unsigned int depth = 1);
	void doSomething();
	~Squirt();
};

class Protestor : public Actor
{
private:
	bool leaveOilFieldState;
	int health; 
public:
	Protestor(StudentWorld *p, int imageID, int startX, int startY, Direction dir = left, double size = 1.0, unsigned int depth = 0);
	void doSomething() = 0;
	void setLeaveOilFieldState(bool);
	void setHealth(int);
	~Protestor();
};


class HardcoreProtestor : public Protestor
{
private:
public:
	HardcoreProtestor(StudentWorld *p, int imageID, int startX, int startY, Direction dir = left, double size = 1.0, unsigned int depth = 0);
	void doSomething();
	~HardcoreProtestor();
};



#endif // ACTOR_H_
