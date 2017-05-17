#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;
class Actor : public GraphObject
{
private:
	bool isAlive;
	StudentWorld *world;
public:
	Actor(StudentWorld *p, int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0);
	void setAlive(bool Is);
	bool getAlive();
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
	int life;
	int health;
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


class RegularProtestor : public Protestor
{
private:
public:
	RegularProtestor(StudentWorld *p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);
	void doSomething();
	~RegularProtestor();
};

class HardcoreProtestor : public Protestor
{
private:
public:
	HardcoreProtestor(StudentWorld *p, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);
	void doSomething();
	~HardcoreProtestor();
};



#endif // ACTOR_H_
