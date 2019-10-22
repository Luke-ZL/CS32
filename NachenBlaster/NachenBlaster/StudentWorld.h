#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>


class NachenBlaster;
class Star;
class Projectile;
class Aliens;
class Explosion;
class Goodie;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
	void RemoveDeadGameObjects();
	void incDestroyed() { totalDestroyed++; }
	void setDisplay();
	void decNachenhealth(int value);
	bool checkDeath();
	bool checkComplete();
	void benefitRepair();
	void benefitTorpedo();
	void generateStar();
	void generateSmallgon();
	void generateSmoregon();
	void generateSnagglegon();
	void generateExplosion(double sx, double sy);
	void generateRepair(double sx, double sy);
	void generateTorpedoGoodie(double sx, double sy);
	void generateExtraLife(double sx, double sy);
	void generateCabbage(double sx, double sy);
	void generateTurnip(double sx, double sy);
	void generateTorpedo(double sx, double sy, int side);
	void collideAliens(Aliens* alien);
	void collideNachen();
	bool CollideProjectile(Projectile* proj);
	void collideGoodie(Goodie* good);
	bool checkFire(Aliens* alien);
	bool checkCollision(double ax, double ay, double ar, double bx, double by, double br);
	~StudentWorld();

private:
	NachenBlaster* m_Nachen;
	std::vector<Star*> m_stars;
	std::vector<Aliens*> m_aliens;
	std::vector<Projectile*> m_projectiles;
	std::vector<Explosion*> m_explosions;
	std::vector<Goodie*> m_goodies;
	int totalDestroyed;
};


#endif // STUDENTWORLD_H_
