#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY,  StudentWorld* gg, Direction dir = none)
    :GraphObject(imageID, startX, startY, dir), m_world(gg)
    {}
    virtual void doSomething() = 0;
    StudentWorld* getWorld()
    {return m_world;}
    
    virtual ~Actor()
    {}

    virtual bool blocksPlayer()
    {
        return false;
    }
private:
    StudentWorld* m_world;
};

class Wall: public Actor
{
public:
    Wall(int x, int y, StudentWorld* gg)
    :Actor(IID_WALL,x,y, gg)
    {setVisible(true);}

    virtual void doSomething()
    {}
    
    virtual ~Wall()
    {}
    
    virtual bool blocksPlayer()
    {return true;}
};

class Player: public Actor
{
public:
    Player(int startX, int startY, StudentWorld* gg)
    :Actor(IID_PLAYER, startX, startY, gg, right), m_hitPoints(20), m_ammo(20)
    {setVisible(true);}
    
    virtual void doSomething();
    
    bool isValidMove(int x, int y);
    
    virtual ~Player()
    {}

private:
    int m_hitPoints;
    int m_ammo;
    
};


#endif // ACTOR_H_
