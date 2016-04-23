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
    :GameWorld(assetDir)
	{}

    virtual int init();

    virtual int move();
    
    virtual ~StudentWorld()
    {cleanUp();}
    
	virtual void cleanUp()
	{
        vector<Actor*>::iterator p = m_actor.begin();
        for(;p < m_actor.end() ; p++)
        {delete  (*p);}
        delete m_player;
	}
    
    Actor* whatsHere(int x, int y);
    
private:
    vector<Actor*> m_actor;
    Player* m_player;
};

#endif // STUDENTWORLD_H_
