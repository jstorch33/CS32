#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>
using namespace std;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir)
    :GameWorld(assetDir),m_bonus(1000), finishedLevel(false)
	{}

    virtual int init();

    virtual int move();
    
    virtual ~StudentWorld()
    {cleanUp();}
    
    virtual void cleanUp();
    
    Player* getPlayer()
    {return m_player;}
    
    Actor* whatsHere(int x, int y);
    
    Actor* whatDoYouNeed(int x, int y, int ID);
    
    Actor* whatsNext(int x, int y, Actor::Direction dir);
    
    bool playerDead();
    
    void setDisplayText();
    
    bool anyLeft(int image);
    
    void levelFinished()
    {finishedLevel = true;}
    
    void makeItem(int x, int y, int imageID, Actor::Direction dir = Actor::right);
    
private:
    vector<Actor*> m_actor;
    Player* m_player;
    int m_bonus;
    bool finishedLevel;
};

string formatInfo(int score, int level, int lives, double health, int ammo, int bonus);

#endif // STUDENTWORLD_H_
