#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <random>
#include <sstream>
#include "Actor.h"
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
	: GameWorld(assetDir), totalDestroyed(0)
{
	

}
bool StudentWorld::checkDeath()
{
	if (m_Nachen->gethealth() <= 0) m_Nachen->setdead();
	if (!m_Nachen->getStatus()) return true;
	return false;
}

void StudentWorld::benefitRepair()
{
	if (m_Nachen->gethealth() <= 40) m_Nachen->decHealth(-10);
	else m_Nachen->decHealth(m_Nachen->gethealth()-50);
}

void StudentWorld::benefitTorpedo()
{
	m_Nachen->changeTorpedo(5);
}

bool StudentWorld::checkComplete()
{
	int goal = 6 + 4 * getLevel();
	if (totalDestroyed >= goal) return true;
	return false;
}

void StudentWorld::RemoveDeadGameObjects()
{
	
	for (int i = 0; i < m_stars.size();) {
		if (!m_stars[i]->getStatus()) {
			delete m_stars[i];
			m_stars.erase(m_stars.begin() + i);
		}
		else i++;
	}   //remove dead stars

	for (int i = 0; i < m_aliens.size();) {
		if (!m_aliens[i]->getStatus()) {
			delete m_aliens[i];
			m_aliens.erase(m_aliens.begin() + i);
		}
		else i++;
	}   //remove dead aliens

	for (int i = 0; i < m_explosions.size();) {
		if (!m_explosions[i]->getStatus()) {
			delete m_explosions[i];
			m_explosions.erase(m_explosions.begin() + i);
		}
		else i++;
	} //remove dead explosions

	for (int i = 0; i < m_projectiles.size();) {
		if (!m_projectiles[i]->getStatus()) {
			delete m_projectiles[i];
			m_projectiles.erase(m_projectiles.begin() + i);
		}
		else i++;
	} //remove dead projectiles

	for (int i = 0; i < m_goodies.size();) {
		if (!m_goodies[i]->getStatus()) {
			delete  m_goodies[i];
			m_goodies.erase(m_goodies.begin() + i);
		}
		else i++;
	} //remove dead goodies
}

void StudentWorld::setDisplay()
{
	ostringstream oss;
	oss << "Lives: " << getLives() << "  Health: " << m_Nachen->gethealth() * 100 / 50 << "%  Score: " << getScore() << "  Level: " << getLevel() << "  Cabbages: " << m_Nachen->getcabbage() * 100 / 30 << "%  Torpedoes: " << m_Nachen->gettorpedo();
	string s = oss.str();
	setGameStatText(s);
}

void StudentWorld::generateStar()
{
	double random_size;
	int random_y;
	random_size = randInt(5, 50) / 100.0;
	random_y = randInt(0, VIEW_HEIGHT - 1);
	m_stars.push_back(new Star(VIEW_WIDTH - 1, random_y, random_size));
}

int StudentWorld::init()
{
	double random_size;
	int random_x;
	int random_y;
	int rand;
	int total = 4 + (0.5 * getLevel());

	for (int i = 0; i < 30; i++)
	{
		random_size = randInt(5, 50) / 100.0;
		random_x = randInt(0, VIEW_WIDTH - 1);
		random_y = randInt(0, VIEW_HEIGHT - 1);
		m_stars.push_back(new Star(random_x, random_y, random_size));
	}
	
	while (m_aliens.size() < total)
	{
		rand = randInt(1, 85 + 15 * getLevel());
		if (rand <= 60) generateSmallgon();
		else if (rand <= 80 + 5 * getLevel()) generateSmoregon();
		else generateSnagglegon();
	}
	m_Nachen = new NachenBlaster(this);
	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	int rand;
	int total = 4 + (0.5 * getLevel());
	//Stars move
	for (int i = 0; i < m_stars.size(); i++)
	{
		if (m_stars[i]->getStatus()) m_stars[i]->doSomething();
	}

	//NachenBlaster move
	if (m_Nachen->getStatus()) m_Nachen->doSomething();
	if (checkDeath()) {
	    decLives();
		return GWSTATUS_PLAYER_DIED;
	}
	if (checkComplete()) return GWSTATUS_FINISHED_LEVEL;

	//Aliens move
	for (int i = 0; i < m_aliens.size(); i++)
	{
		if (m_aliens[i]->getStatus()) m_aliens[i]->doSomething();
		if (checkDeath()) {
			decLives();
			return GWSTATUS_PLAYER_DIED;
		}
		if (checkComplete()) {
			playSound(SOUND_FINISHED_LEVEL);
			return GWSTATUS_FINISHED_LEVEL;
		}
	}

	//Projectiles move
	for (int i = 0; i < m_projectiles.size(); i++)
	{
		if (m_projectiles[i]->getStatus()) m_projectiles[i]->doSomething();
		if (checkDeath()) {
			decLives();
			return GWSTATUS_PLAYER_DIED;
		}
		if (checkComplete()) {
			playSound(SOUND_FINISHED_LEVEL);
			return GWSTATUS_FINISHED_LEVEL;
		}
	}

	//Goodies move
	for (int i = 0; i < m_goodies.size(); i++)
	{
		if (m_goodies[i]->getStatus()) m_goodies[i]->doSomething();
	}

	//Explosions move
	for (int i = 0; i < m_explosions.size(); i++)
	{
		if (m_explosions[i]->getStatus()) m_explosions[i]->doSomething();
	}

	//introduce star
	if (randInt(0, 14) == 0) generateStar();
	
	//introduce new aliens
	while (m_aliens.size() < total)
	{
		rand = randInt(1, 85 + 15 * getLevel());
		if (rand <= 60) generateSmallgon();
		else if (rand <= 80 + 5 * getLevel()) generateSmoregon();
		else generateSnagglegon();
	}
	RemoveDeadGameObjects();
	setDisplay();
	return GWSTATUS_CONTINUE_GAME;
	//decLives();
    //return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
	for (vector<Star*>::iterator p = m_stars.begin(); p != m_stars.end(); p++)
		delete *p;
	m_stars.clear(); //clear stars

	for (vector<Aliens*>::iterator p = m_aliens.begin(); p != m_aliens.end(); p++)
		delete *p;
	m_aliens.clear(); //clear aliens


	for (vector<Explosion*>::iterator p = m_explosions.begin(); p != m_explosions.end(); p++)
		delete *p;
	m_explosions.clear(); //clear explosions

	for (vector<Projectile*>::iterator p = m_projectiles.begin(); p != m_projectiles.end(); p++)
		delete *p;
	m_projectiles.clear(); //clear projectiles

	for (vector<Goodie*>::iterator p = m_goodies.begin(); p != m_goodies.end(); p++)
		delete *p;
	m_goodies.clear(); //delete 

	delete m_Nachen;
	m_Nachen = nullptr;
	totalDestroyed = 0;
}

void StudentWorld::decNachenhealth(int value)
{
	m_Nachen->decHealth(value); 
	if (m_Nachen->gethealth() <= 0) m_Nachen->setdead();
}

bool StudentWorld::checkCollision(double ax, double ay, double ar, double bx, double by, double br)
{
	double xdis = fabs(ax - bx);
	double ydis = fabs(ay - by);
	return (sqrt(xdis*xdis + ydis*ydis) < (0.75 * (ar + br)));
}

void StudentWorld::collideAliens(Aliens* alien)
{
	if (checkCollision(alien->getX(), alien->getY(), alien->getRadius(), m_Nachen->getX(), m_Nachen->getY(), m_Nachen->getRadius()))
	{
		alien->incScore();
		alien->dechealth();
		alien->setdead();
		playSound(SOUND_DEATH);
		alien->dropGoodie();
		generateExplosion(alien->getX(), alien->getY());
		incDestroyed();
	}//check with NahcenBlaster

	for (int i = 0; i < m_projectiles.size(); i++)
	{
		if (!m_projectiles[i]->getStatus()) continue;
		if (m_projectiles[i]->getSide() == NACHEN)
			if (checkCollision(alien->getX(), alien->getY(), alien->getRadius(), m_projectiles[i]->getX(), m_projectiles[i]->getY(), m_projectiles[i]->getRadius()))
			{
				alien->getDamaged(m_projectiles[i]->getDamage());
				if (!alien->getStatus()) {
					playSound(SOUND_DEATH);
					alien->incScore();
					alien->dropGoodie();
					generateExplosion(alien->getX(), alien->getY());
					incDestroyed();
					return;
				}
				else playSound(SOUND_BLAST);
				m_projectiles[i]->setdead();
			}
	} //check with projectiles
}

void StudentWorld::collideNachen() 
{
	for (int i = 0; i < m_aliens.size(); i++)
	{
		if (!m_aliens[i]->getStatus()) continue;
		if (checkCollision(m_aliens[i]->getX(), m_aliens[i]->getY(), m_aliens[i]->getRadius(), m_Nachen->getX(), m_Nachen->getY(), m_Nachen->getRadius()))
		{
			if (!m_aliens[i]->getStatus()) continue;
			m_aliens[i]->incScore();
			m_aliens[i]->dechealth();
			m_aliens[i]->setdead();
			playSound(SOUND_DEATH);
			incDestroyed();
			m_aliens[i]->dropGoodie();
			generateExplosion(m_aliens[i]->getX(), m_aliens[i]->getY());
		}
	} //check with aliens


	for (int i = 0; i < m_projectiles.size(); i++)
	{
		if (!m_projectiles[i]->getStatus()) continue;
		if (m_projectiles[i]->getSide() == ALIENS)
			if (checkCollision(m_Nachen->getX(), m_Nachen->getY(), m_Nachen->getRadius(), m_projectiles[i]->getX(), m_projectiles[i]->getY(), m_projectiles[i]->getRadius()))
			{
				m_Nachen->decHealth(m_projectiles[i]->getDamage());
				if (!m_Nachen->getStatus()) return;
				else playSound(SOUND_BLAST);
				m_projectiles[i]->setdead();
			}
	} //check with projectiles

	for (int i = 0; i < m_goodies.size(); i++)
	{
		if (!m_goodies[i]->getStatus()) continue;
		if (checkCollision(m_Nachen->getX(), m_Nachen->getY(), m_Nachen->getRadius(), m_goodies[i]->getX(), m_goodies[i]->getY(), m_goodies[i]->getRadius()))
		{
			m_goodies[i]->setdead();
			playSound(SOUND_GOODIE);
			increaseScore(100);
			m_goodies[i]->benefit();
		}
	} //check with goodies
} 


bool StudentWorld::CollideProjectile(Projectile* proj)
{
	if (proj->getSide() == ALIENS) 
		if (checkCollision(proj->getX(), proj->getY(), proj->getRadius(), m_Nachen->getX(), m_Nachen->getY(), m_Nachen->getRadius()))
		{
			m_Nachen->decHealth(proj->getDamage());
			playSound(SOUND_BLAST);
			proj->setdead();
			return true;
		}//check with NachenBlaster

	if (proj->getSide() == NACHEN)
		for (int i = 0; i < m_aliens.size(); i++)
		{
			if (!m_aliens[i]->getStatus()) continue;
			if (checkCollision(proj->getX(), proj->getY(), proj->getRadius(), m_aliens[i]->getX(), m_aliens[i]->getY(), m_aliens[i]->getRadius()))
			{
				m_aliens[i]->getDamaged(proj->getDamage());
				if (!m_aliens[i]->getStatus()) {
					playSound(SOUND_DEATH);
					m_aliens[i]->incScore();
					m_aliens[i]->dropGoodie();
					generateExplosion(m_aliens[i]->getX(), m_aliens[i]->getY());
					incDestroyed();
				}
				else playSound(SOUND_BLAST);
				proj->setdead();
				return true;
			}
		}//check with aliens
	return false;
}

void StudentWorld::collideGoodie(Goodie* good)
{
	if (checkCollision(good->getX(), good->getY(), good->getRadius(), m_Nachen->getX(), m_Nachen->getY(), m_Nachen->getRadius()))
	{
		good->setdead();
		playSound(SOUND_GOODIE);
		increaseScore(100);
		good->benefit();
	}
}


bool StudentWorld::checkFire(Aliens* alien) 
{ 
	return (fabs(m_Nachen->getY() - alien->getY()) <= 4); 
}

void StudentWorld::generateSmallgon()
{
	double hitpoints = 5 * (1 + (getLevel() - 1)*0.1);
	int random_y = randInt(0, VIEW_HEIGHT - 1);
	m_aliens.push_back(new Smallgon(VIEW_WIDTH - 1, random_y, hitpoints, this));
}

void StudentWorld::generateSmoregon()
{
	double hitpoints = 5 * (1 + (getLevel() - 1)*0.1);
	int random_y = randInt(0, VIEW_HEIGHT - 1);
	m_aliens.push_back(new Smoregon(VIEW_WIDTH - 1, random_y, hitpoints, this));
}

void StudentWorld::generateSnagglegon()
{
	double hitpoints = 10 * (1 + (getLevel() - 1)*0.1);
	int random_y = randInt(0, VIEW_HEIGHT - 1);
	m_aliens.push_back(new Snagglegon(VIEW_WIDTH - 1, random_y, hitpoints, this));
}

void StudentWorld::generateExplosion(double sx, double sy)
{
	m_explosions.push_back(new Explosion(sx, sy));
}

void StudentWorld::generateCabbage(double sx, double sy)
{
	m_projectiles.push_back(new Cabbage(sx, sy,this));
}

void StudentWorld::generateTurnip(double sx, double sy)
{
	m_projectiles.push_back(new Turnip(sx, sy, this));
}

void StudentWorld::generateTorpedo(double sx, double sy, int side)
{
	int dir;
	if (side == ALIENS) dir = 180;
	else if (side == NACHEN) dir = 0;
	m_projectiles.push_back(new Torpedo(sx, sy, side, dir, this));
}

void StudentWorld::generateRepair(double sx, double sy)
{
	m_goodies.push_back(new RepairGoodie(sx, sy, this));
}

void StudentWorld::generateTorpedoGoodie(double sx, double sy)
{
	m_goodies.push_back(new TorpedoGoodie(sx, sy, this));
}

void StudentWorld::generateExtraLife(double sx, double sy)
{
	m_goodies.push_back(new ExtraLifeGoodie(sx, sy, this));
}

StudentWorld::~StudentWorld()
{
	cleanUp();
}



