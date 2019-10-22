#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include<cmath>

const int UP_LEFT = 0;
const int LEFT = 1;
const int DOWN_LEFT = 2;
const int ALIENS = 0;
const int NACHEN = 1;


class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class actor : public GraphObject
{
public:
	actor(int ID, double sx, double sy, int dir, double size, int depth) :GraphObject(ID, sx, sy, dir, size, depth) { m_status = true; }
	virtual void doSomething() = 0;
	bool getStatus() const { return m_status; }
	void setdead() { m_status = false; }
private:
	bool m_status;
};

class NachenBlaster : public actor
{
public:
	NachenBlaster(StudentWorld* world) : actor(IID_NACHENBLASTER, 0, 128, 0, 1.0, 0), m_world(world), m_cabbage_count(30), m_torpedo_count(0), m_health(50) {}
	virtual void doSomething();
	int gethealth() const { return m_health; }
	int getcabbage() const { return m_cabbage_count; }
	int gettorpedo() const { return m_torpedo_count; }
	void changeTorpedo(int value) { m_torpedo_count += value; }
	void decHealth(int value) { m_health -= value; if (m_health <= 0) setdead(); }
	StudentWorld* getWorld() const { return m_world; };

private:
	StudentWorld* m_world;
	int m_cabbage_count;
	int m_torpedo_count;
	int m_health;
};

class Aliens : public actor
{
public:
	Aliens(int ID, int sx, int sy, int dir, double size, int depth, double speed, double hitpoints, int plan, int fly_dir, StudentWorld* world, int clash)
		: actor(ID, sx, sy, dir, size, depth), m_speed(speed), m_plan(plan), m_hitpoints(hitpoints), m_dir(fly_dir), m_world(world), m_clashDamage(clash){}
	virtual void doSomething();
	virtual void newFlightPlan();
	void fly();
	void changeSpeed(double speed) { m_speed = speed; }
	void changeDir(int dir) { m_dir = dir; }
	void changePlan(int length) { m_plan = length; }
	virtual bool fire() = 0;
	virtual void incScore();
	virtual void dropGoodie() = 0;
	void dechealth();
	void getDamaged(int damage) { m_hitpoints -= damage; if (m_hitpoints <= 0) setdead(); }
	StudentWorld* getWorld() const { return m_world; };


private:
	int m_plan;
	double m_speed;
	double m_hitpoints;
	int m_dir;
	int m_clashDamage;
	StudentWorld* m_world;
};

class Smallgon :public Aliens
{
public:
	Smallgon(int sx, int sy, double hitpoints, StudentWorld* world)
		:Aliens(IID_SMALLGON, sx, sy, 0, 1.5, 1, 2.0, hitpoints,0, 0, world, 5) {}
	virtual bool fire();
	virtual void dropGoodie();
};

class Smoregon :public Aliens
{
public:
	Smoregon(int sx, int sy, double hitpoints, StudentWorld* world)
		:Aliens(IID_SMOREGON, sx, sy, 0, 1.5, 1, 2.0,hitpoints,10000, 0, world, 5) {}
	virtual bool fire();
	virtual void dropGoodie();

};

class Snagglegon :public Aliens
{
public:
	Snagglegon(int sx, int sy, double hitpoints, StudentWorld* world)
		:Aliens(IID_SNAGGLEGON, sx, sy, 0, 1.5, 1, 1.75, hitpoints, 0, DOWN_LEFT, world, 15) {}
	virtual bool fire();
	virtual void dropGoodie();
	virtual void incScore();
	virtual void newFlightPlan();

};

class Explosion :public actor
{
public:
	Explosion(double sx, double sy)
		:actor(IID_EXPLOSION, sx, sy, 0, 1, 0), m_tick_count(0) {}
	virtual void doSomething();

private:
	int m_tick_count;
};

class Projectile : public actor
{
public:
	Projectile(int ID, double sx, double sy, int dir, double speed, int side, StudentWorld* world, int damage)
		:actor(ID, sx, sy, dir, 0.5, 1 ), m_damage(damage),m_speed(speed),m_world(world),m_side(side) {}
	virtual void doSomething();
	virtual void rotate() { setDirection((getDirection() + 20) % 360); }
	int getSide() const { return m_side; }
	int getDamage() const { return m_damage; }
	StudentWorld* getWorld() const { return m_world; };

private:
	int m_damage;
	double m_speed;
	StudentWorld* m_world;
	int m_side;

};

class Turnip : public Projectile
{
public:
	Turnip(double sx, double sy, StudentWorld* world)
		: Projectile(IID_TURNIP, sx, sy, 0, 6, ALIENS, world, 2) {}

};

class Cabbage : public Projectile
{
public:
	Cabbage(double sx, double sy, StudentWorld* world)
		: Projectile(IID_CABBAGE, sx, sy, 0, 8, NACHEN, world, 2) {}

};

class Torpedo : public Projectile
{
public:
	Torpedo(double sx, double sy, int side, int dir, StudentWorld* world)
		: Projectile(IID_TORPEDO, sx, sy, dir, 8, side, world, 8) {}
	virtual void rotate() { return; }

};


class Goodie : public actor
{
public:
	Goodie(int ID, double sx, double sy, StudentWorld* world)
		: actor(ID, sx, sy, 0, 0.5, 1), m_world(world) {}
	virtual void doSomething();
	virtual void benefit() = 0;
	StudentWorld* getWorld() const { return m_world; };

private:
	StudentWorld* m_world;


};

class ExtraLifeGoodie : public Goodie
{
public:
	ExtraLifeGoodie(double sx, double sy, StudentWorld* world)
		:Goodie(IID_LIFE_GOODIE, sx, sy, world) {}
	virtual void benefit();
};

class RepairGoodie : public Goodie
{
public:
	RepairGoodie(double sx, double sy, StudentWorld* world)
		:Goodie(IID_REPAIR_GOODIE, sx, sy, world) {}
	virtual void benefit();
};

class TorpedoGoodie : public Goodie
{
public:
	TorpedoGoodie(double sx, double sy, StudentWorld* world)
		:Goodie(IID_TORPEDO_GOODIE, sx, sy, world) {}
	virtual void benefit();
};


class Star: public actor
{
public:
	Star(int sx, int sy, double size) : actor(IID_STAR, sx, sy, 0, size, 3){}
	virtual void doSomething();
	
};

#endif // ACTOR_H_
