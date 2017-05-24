#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <algorithm>
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
	void setHealth(int health_);
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
	int count ;
	bool fell ;
public:
	Boulder(StudentWorld *p, int imageID, int startX, int startY, Direction dir = down, double size = 1.0, unsigned int depth = 1);
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

class Sonar :public Actor
{
private:
	int count = 0;
public:
	Sonar(StudentWorld *p, int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 2);
	void doSomething();
	~Sonar();
};

class Squirt : public Actor
{
private:
public:
	Squirt(StudentWorld *p, int imageID, int startX, int startY, Direction dir = down, double size = 1.0, unsigned int depth = 1);
	void doSomething();
	~Squirt();
};

class RegularProtestor : public Actor
{
private:
	bool leaveOilFieldState;
	int health;
	int numSquaresToMoveInCurrentDirection;
	int tickCounter = 0;
public:
	RegularProtestor(StudentWorld *p, int imageID, int startX, int startY, Direction dir = left, double size = 1.0, unsigned int depth = 0);
	void doSomething();
	bool getLeaveOilFieldState();
	void setLeaveOilFieldState(bool);
	void setHealth(int);
	int getTickCounter() { return tickCounter; }
	void incTickCounter() { tickCounter++; }
	void setTickCounter(int);
	void wander();
	~RegularProtestor();
};

class HardcoreProtestor : public RegularProtestor
{
private:
public:
	HardcoreProtestor(StudentWorld *p, int imageID, int startX, int startY, Direction dir = left, double size = 1.0, unsigned int depth = 0);
	void doSomething();
	~HardcoreProtestor();
};

class GoldNugget :public Actor {
	private:
		bool pickUpProtestor;
		bool pickUpDiggerman;
	public:
		GoldNugget(StudentWorld *p, int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 2);
		void doSomething();
		~GoldNugget();
};
#endif // ACTOR_H_
