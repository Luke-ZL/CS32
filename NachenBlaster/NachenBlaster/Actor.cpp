#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>

using namespace std;

void Star::doSomething()
{
	moveTo(getX() - 1, getY());
	if (getX() < 0) setdead();
}

void NachenBlaster::doSomething()
{
	if (m_health <= 0) setdead();
	if (!getStatus()) return;
	int ch;
	if (getWorld()->getKey(ch))
	{
		switch (ch) {
		case KEY_PRESS_LEFT:
			if (getX() >= 0) moveTo(getX() - 6, getY());
			//else moveTo(0, getY());
			break;
		case KEY_PRESS_RIGHT:
			if (getX() < VIEW_WIDTH) moveTo(getX() + 6, getY());
			//else moveTo(VIEW_WIDTH-1, getY());
			break;
		case KEY_PRESS_DOWN:
			if (getY()>= 0) moveTo(getX(), getY() - 6);
			//else moveTo(getX(), 0);
			break;
		case KEY_PRESS_UP:
			if (getY() < VIEW_HEIGHT) moveTo(getX(), getY() + 6);
			//else moveTo(getX(), VIEW_HEIGHT-1);
			break;
		case KEY_PRESS_TAB:
			if (m_torpedo_count > 0) {
				m_world->generateTorpedo(getX() + 12, getY(), NACHEN);
				m_world->playSound(SOUND_TORPEDO);
				m_torpedo_count--;
			}
			break;
		case KEY_PRESS_SPACE:
			if (m_cabbage_count >= 5) {
				m_world->generateCabbage(getX() + 12, getY());
				m_world->playSound(SOUND_PLAYER_SHOOT);
				m_cabbage_count -= 5;
			}
			break;
		default:
			break;
		}
	}
	m_world->collideNachen();

	if (m_cabbage_count < 30) m_cabbage_count++;
}


void Explosion::doSomething()
{
	setSize(1.5*getSize());
	m_tick_count++;
	if (m_tick_count >= 4) setdead();
}

void Projectile::doSomething()
{
	if (!getStatus()) return;
	if (getX() < 0) {
		setdead();
		return;
	}
	if (getWorld()->CollideProjectile(this)) return;
	if (m_side == ALIENS) moveTo(getX() - m_speed, getY());
	else moveTo(getX() + m_speed, getY());
	rotate();
	getWorld()->CollideProjectile(this);
}

void Goodie::doSomething()
{
	if (!getStatus()) return;
	if ((getX() < 0) || (getY() < 0)) {
		setdead();
		return;
	}
	getWorld()->collideGoodie(this);
	if (!getStatus()) return;
	moveTo(getX() - 0.75, getY() - 0.75);
	getWorld()->collideGoodie(this);
}

void ExtraLifeGoodie::benefit() 
{
	getWorld()->incLives(); 
}

void RepairGoodie::benefit()
{
	getWorld()->benefitRepair();
}

void TorpedoGoodie::benefit()
{
	getWorld()->benefitTorpedo();
}

void Aliens::newFlightPlan()
{
	double y = getY();
    double x = getX();
	if (y >= VIEW_HEIGHT - 1) {
		m_dir = DOWN_LEFT;
		m_plan = randInt(1, 32);
	}
	else if (y <= 0) {
		m_dir = UP_LEFT;
		m_plan = randInt(1, 32);
	}
	else if (m_plan <= 0) {
		m_dir = randInt(0, 2);
		m_plan = randInt(1, 32);
	}
}

void Aliens::fly()
{
	if ((m_dir == UP_LEFT)&&(getY() <= VIEW_HEIGHT-1)) moveTo(getX() - m_speed, getY() + m_speed);
	else if ((m_dir == DOWN_LEFT) && (getY() >= 0)) moveTo(getX() - m_speed, getY() - m_speed);
	else if (m_dir == LEFT) moveTo(getX() - m_speed, getY());
	m_plan--;
}

void Aliens::incScore()
{
	m_world->increaseScore(250); 
}

void Aliens::dechealth() 
{ 
	m_world->decNachenhealth(m_clashDamage); 
}

void Aliens::doSomething()
{
	if (!getStatus()) return;
	if (getX() < 0) {
		setdead();
		return;
	}
	getWorld()->collideAliens(this);
	if (!getStatus()) return;
	newFlightPlan();
	if (fire()) return;
	fly();
	getWorld()->collideAliens(this);

}

void Smallgon::dropGoodie()
{
	return;
}

bool Smallgon::fire()
{
	if (getWorld()->checkFire(this)) {
		int a = getWorld()->getLevel();
		int b = 10 * a + 15;
		if (randInt(a, b) <= a) {
			getWorld()->generateTurnip(getX() - 14, getY());
			getWorld()->playSound(SOUND_ALIEN_SHOOT);
			return true;
		}
	}
	return false;
}



bool Smoregon::fire()
{
	int a = getWorld()->getLevel();
	int b = 5 * a + 20;
	if (getWorld()->checkFire(this)) {
		if (randInt(a, b) <= a) {
			getWorld()->generateTurnip(getX() - 14, getY());
			getWorld()->playSound(SOUND_ALIEN_SHOOT);
			return true;
		}
		if (randInt(a, b) <= a) {
			changeDir(LEFT);
			changeSpeed(5.0);
			changePlan(VIEW_WIDTH);
		}
	}
    return false;
}

void Smoregon::dropGoodie()
{
	if (randInt(1, 3) == 1) {
		if (randInt(1, 2 == 1)) getWorld()->generateRepair(getX(),getY());
		else getWorld()->generateTorpedoGoodie(getX(), getY());
	}
}

void Snagglegon::newFlightPlan()
{
	double y = getY();
	double x = getX();
	if (y >= VIEW_HEIGHT - 1) changeDir(DOWN_LEFT);
	else if (y <= 0) changeDir(UP_LEFT);
}

bool Snagglegon::fire()
{
	if (getWorld()->checkFire(this)) {
		int a = getWorld()->getLevel();
		int b = 10 * a + 15;
		if (randInt(a, b) <= a) {
			getWorld()->generateTorpedo(getX() - 14, getY(), ALIENS);
			getWorld()->playSound(SOUND_TORPEDO);
			return true;
		}
	}
	return false;
}

void Snagglegon::incScore()
{
	getWorld()->increaseScore(1000);
}

void Snagglegon::dropGoodie()
{
	if (randInt(1, 6) == 1) getWorld()->generateExtraLife(getX(), getY());
}

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
