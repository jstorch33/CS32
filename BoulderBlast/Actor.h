

#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <string>
using namespace std;

class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY,  StudentWorld* gg, Direction dir = none,
          double b = -1, bool a = true)
    :GraphObject(imageID, startX, startY, dir), m_world(gg), life(a), m_health(b)
    {}
    
    virtual void doSomething() = 0;
    
    StudentWorld* getWorld()
    {return m_world;}
    
    virtual ~Actor()
    {}

    virtual void shoot();
    
    virtual void damage();
    
    virtual bool blocksPath()
    {return false;}
    
    virtual bool blocksPath(int a)
    {return true;}
    
    void setDead()
    {life = false;}
    
    bool isAlive()
    {return life;}
    
    void setHealth(double health)
    {m_health = health;}
    
    double getHealth()
    {return m_health;}
    
    
private:
    StudentWorld* m_world;
    bool life;
    double m_health;
    
};

class Wall: public Actor
{
public:
    Wall(int x, int y, StudentWorld* gg)
    :Actor(IID_WALL,x,y, gg)
    {setVisible(true);}

    virtual void shoot()
    {}

    virtual void doSomething()
    {}
    
    virtual ~Wall()
    {}
    
    virtual bool blocksPath()
    {return true;}
};

class Player: public Actor
{
public:
    Player(int startX, int startY, StudentWorld* gg)
    :Actor(IID_PLAYER, startX, startY, gg, right, 20), m_ammo(20)
    {setVisible(true);}
    
    virtual void doSomething();
    
    
    virtual ~Player()
    {}

    virtual bool blocksPath()
    {return true;}
    
    virtual void damage();
    
    int getAmmo()
    {return m_ammo;}
    
    void incAmmo()
    {m_ammo += 20;}
    
private:
    int m_ammo;
    
};

class Boulder: public Actor
{
public:
    Boulder(int x, int y, StudentWorld* gg)
    :Actor(IID_BOULDER,x,y, gg, none, 10)
    {setVisible(true);}
    
    virtual void shoot()
    {}
    
    virtual void doSomething()
    {}
    
    virtual ~Boulder()
    {}
        
    virtual bool blocksPath()
    {return true;}
    
    virtual bool blocksPath(int key);

};

class Hole: public Actor
{
public:
    Hole(int x, int y, StudentWorld* gg)
    :Actor(IID_HOLE,x,y, gg)
    {setVisible(true);}
    
    virtual void doSomething();
    
    virtual void shoot()
    {}
    
    virtual ~Hole()
    {}
    
    virtual bool blocksPath()
    {return true;}
};

class Goodie: public Actor
{
public:
    Goodie(int imageId, int x, int y,StudentWorld* gg)
    :Actor(imageId,x,y,gg)
    {}
    
    virtual void doSomething() = 0;
    
    virtual void shoot()
    {}
    
    virtual ~Goodie()
    {}
    
    virtual bool blocksPath()
    {return false;}
    
    bool isPlayerHere();
};

class Jewel: public Goodie
{
public:
    Jewel(int x, int y, StudentWorld* gg)
    :Goodie(IID_JEWEL, x,y,gg)
    {setVisible(true);}
    
    virtual void shoot()
    {}
    
    virtual ~Jewel()
    {}
    
    virtual void doSomething();
};

class ExtraLife: public Goodie
{
public:
    ExtraLife(int x, int y, StudentWorld* gg)
    :Goodie(IID_EXTRA_LIFE, x,y,gg)
    {setVisible(true);}
    
    virtual void shoot()
    {}
    
    virtual ~ExtraLife()
    {}
    
    virtual void doSomething();
};

class RestoreHealth: public Goodie
{
public:
    RestoreHealth(int x, int y, StudentWorld* gg)
    :Goodie(IID_RESTORE_HEALTH, x,y,gg)
    {setVisible(true);}
    
    virtual void shoot()
    {}
    
    virtual ~RestoreHealth()
    {}
    
    virtual void doSomething();
};

class Ammo: public Goodie
{
public:
    Ammo(int x, int y, StudentWorld* gg)
    :Goodie(IID_AMMO, x,y,gg)
    {setVisible(true);}
    
    virtual void shoot()
    {}
    
    virtual ~Ammo()
    {}
    
    virtual void doSomething();
};

class Exit: public Goodie
{
public:
    Exit(int x, int y, StudentWorld* gg)
    :Goodie(IID_EXIT, x,y,gg)
    {setVisible(false);}
    
    virtual void shoot()
    {}
    
    virtual ~Exit()
    {}
    
    virtual void doSomething();

};

class Bullet: public Actor
{
public:
    Bullet(int x, int y, StudentWorld* gg,Direction dir)
    :Actor(IID_BULLET, x,y,gg,dir)
    {setVisible(true);}
    
    virtual void shoot()
    {}
    
    virtual ~Bullet()
    {}
    
    virtual void doSomething();
    
    void didItHit();
};

class Robot: public Actor
{
public:
    Robot(int imageID, int x, int y, StudentWorld* gg, Direction dir = right, int health = 0)
    :Actor(imageID, x, y, gg, dir, health), m_ticks(0)
    {}
    
    virtual void doSomething() = 0;
    
    virtual ~Robot()
    {}
        
    bool wait();
    
    virtual bool blocksPath()
    {return true;}
    
    void incTicks()
    {m_ticks++;}
    
    bool isPlayerInLineOfSight();
private:
    int m_ticks;
};

class SnarlBot: public Robot
{
public:
    SnarlBot(int x, int y, StudentWorld* gg, Direction dir)
    :Robot(IID_SNARLBOT, x, y, gg, dir, 10)
    {setVisible(true);}
    
    virtual void doSomething();
    
    virtual ~SnarlBot()
    {}
};

class KleptoBot: public Robot
{
public:
    KleptoBot(int x, int y, StudentWorld* gg, int imageID = IID_KLEPTOBOT, int health = 5)
    :Robot(imageID, x, y, gg, right, health), m_dis(0), keepGoing(true), m_goodieID(0)
    {setVisible(true);}
    
    virtual ~KleptoBot()
    {}
        
    virtual void doSomething();
    
    void setNewDir();
    
    void setNewDis();
    
    bool eatGoodie();
    
    void walk();
    
    virtual void damage();
    
    bool blockedIn(char letter);
    
    void resetBlocked()
    {blocked = "";}
    
    int getGoodieID()
    {return m_goodieID;}
    
private:
    int m_goodieID;
    int m_dis;
    bool keepGoing;
    string blocked;
};

class AngryKleptoBot: public KleptoBot
{
public:
    AngryKleptoBot(int x, int y, StudentWorld* gg)
    :KleptoBot(x, y, gg, IID_ANGRY_KLEPTOBOT, 8)
    {setVisible(true);}
    
    virtual ~AngryKleptoBot()
    {}
    
    virtual void doSomething();
    
};

class KleptoBotFactory: public Actor
{
public:
    KleptoBotFactory(int x, int y, StudentWorld* gg, bool a)
    :Actor(IID_ROBOT_FACTORY, x,y,gg), m_angry(a)
    {setVisible(true);}
    
    virtual void shoot()
    {}
    
    virtual void doSomething();
    
    void createRobot(bool a);
    
    virtual bool blocksPath()
    {return true;}
    
private:
    bool m_angry;
};


#endif // ACTOR_H_
