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
	Actor(/*StudentWorld *p, */int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0);
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
	Dirt(/*StudentWorld *p,*/ int imageID, int startX, int startY, Direction dir = right, double size = .25, unsigned int depth = 3);
	void doSomething();
	~Dirt();
};

class DiggerMan : public Actor
{
private:
	int life;
	int health;
public:
	DiggerMan(/*StudentWorld *p,*/int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 0);
	void doSomething();
	~DiggerMan();
};
class Boulders : public Actor
{
private:
public:
	Boulders(/*StudentWorld *p, */int imageID, int startX, int startY, Direction dir = right, double size = 1.0, unsigned int depth = 1);
	void doSomething();
	~Boulders();
};

class Protestor : public Actor
{
private://reminder: we should make a bases class for diggerman and protestors since all three have hitpoint values 
public:
	Protestor(StudentWorld *p, int imageID, int startX, int startY, Direction dir = left, double size = 1.0, unsigned int depth = 0);
	void doSomething() = 0;
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
