#include "StudentWorld.h"
#include "Level.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
    string	curLevel = "level0";
    curLevel += ('0'+getLevel());
    curLevel += ".dat";
    
    Level lev(assetDirectory());
    Level::LoadResult result = lev.loadLevel(curLevel);
    
    if (result	==	Level::load_fail_file_not_found	||
        result	==	Level:: load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR;
    
    for(int x = 0; x < VIEW_WIDTH; x++)
    {
        for(int y = 0; y < VIEW_HEIGHT; y++)
        {
            Level::MazeEntry item = lev.getContentsOf(x, y);
            if(item == Level::player)
            {
                m_player = new Player(x, y, this);
            }
            if(item == Level::wall)
            {
                m_actor.push_back(new Wall(x,y,this));
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_player->doSomething();
    vector<Actor*>::iterator p = m_actor.begin();
    for(;p < m_actor.end() ; p++)
    {
        (*p)->doSomething();
    }
    return GWSTATUS_CONTINUE_GAME;
}

Actor* StudentWorld::whatsHere(int x, int y)
{
    vector<Actor*>::iterator p = m_actor.begin();
    for( ; p < m_actor.end(); p++)
    {
        if((*p)->getX() == x && (*p)->getY() == y)
            return *p;
    }

    return nullptr;
}





