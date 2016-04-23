
#include "StudentWorld.h"
#include "Level.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
    string	curLevel = "level";
    if(getLevel() < 10)
    {
        curLevel += "0";
        curLevel += ('0' + getLevel());
    }
    else
    {
        curLevel += ('0' + getLevel());
    }
    curLevel += ".dat";
    
    finishedLevel = false;
    
    if(getLevel()>99)
        return GWSTATUS_PLAYER_WON;
    
    Level lev(assetDirectory());
    Level::LoadResult result = lev.loadLevel(curLevel);
    
    if(result == Level:: load_fail_file_not_found)
        return GWSTATUS_PLAYER_WON;
    
    if (result	==	Level:: load_fail_bad_format)
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
            if(item == Level::boulder)
            {
                m_actor.push_back(new Boulder(x,y,this));
            }
            if(item == Level::hole)
            {
                m_actor.push_back(new Hole(x,y,this));
            }
            if(item == Level::jewel)
            {
                m_actor.push_back(new Jewel(x,y,this));
            }
            if(item == Level::extra_life)
            {
                m_actor.push_back(new ExtraLife(x,y,this));
            }
            if(item == Level::restore_health)
            {
                m_actor.push_back(new RestoreHealth(x,y,this));
            }
            if(item == Level::ammo)
            {
                m_actor.push_back(new Ammo(x,y,this));
            }
            if(item == Level::exit)
            {
                m_actor.push_back(new Exit(x,y,this));
            }
            if(item == Level::vert_snarlbot)
            {
                m_actor.push_back(new SnarlBot(x,y,this,Actor::down));
            }
            if(item == Level::horiz_snarlbot)
            {
                m_actor.push_back(new SnarlBot(x,y,this, Actor::right));
            }
            if(item == Level::kleptobot_factory)
            {
                m_actor.push_back(new KleptoBotFactory(x,y,this, false));
            }
            if(item == Level::angry_kleptobot_factory)
            {
                m_actor.push_back(new KleptoBotFactory(x,y,this, true));
            }
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    setDisplayText();
    
    if(playerDead())
    {
        playSound(SOUND_PLAYER_DIE);
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    m_player->doSomething();
    vector<Actor*>::iterator p = m_actor.begin();
    for(;p < m_actor.end() ; p++)
    {
        if((*p)->isAlive())
            (*p)->doSomething();
        else
        {
            delete (*p);
            m_actor.erase(p);
        }
    }
    if(m_bonus!=0)
    {
        m_bonus--;
    }
    
    if(finishedLevel == true)
    {
        increaseScore(m_bonus);
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    vector<Actor*>::iterator p = m_actor.begin();
    for(;p < m_actor.end() ; p++)
    {delete  (*p);}
    
    m_actor.clear();
    delete m_player;
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

Actor* StudentWorld::whatDoYouNeed(int x, int y , int id)
{
    vector<Actor*>::iterator p = m_actor.begin();
    for( ; p < m_actor.end(); p++)
    {
        if((*p)->getX() == x && (*p)->getY() == y && (*p)->getID() == id)
            return (*p);
    }

    return nullptr;
}

Actor* StudentWorld::whatsNext(int x, int y, Actor::Direction dir)
{
    vector<Actor*>::iterator p = m_actor.begin();
    switch(dir)
    {
        case GraphObject::up:
            if(m_player->getX() == x && m_player->getY() == y+1)
                return m_player;
            for( ; p < m_actor.end(); p++)
            {
                if((*p)->getX() == x && (*p)->getY() == y+1)
                    return (*p);
            }
            break;
            
        case GraphObject::down:
            if(m_player->getX() == x && m_player->getY() == y-1)
                return m_player;
            for( ; p < m_actor.end(); p++)
            {
                if((*p)->getX() == x && (*p)->getY() == y-1)
                    return (*p);
            }
            break;
            
        case GraphObject::right:
            if(m_player->getX() == x+1 && m_player->getY() == y)
                return m_player;
            for( ; p < m_actor.end(); p++)
            {
                if((*p)->getX() == x+1 && (*p)->getY() == y)
                    return (*p);
            }
            break;
            
        case GraphObject::left:
            if(m_player->getX() == x-1 && m_player->getY() == y)
                return m_player;
            for( ; p < m_actor.end(); p++)
            {
                if((*p)->getX() == x-1 && (*p)->getY() == y)
                    return (*p);
            }
            break;
            
        default:
            break;
    }
    return nullptr;
}

bool StudentWorld::playerDead()
{
    if(!m_player->isAlive())
        return true;
    return false;
}

void StudentWorld::setDisplayText()
{
    int score = getScore();
    int level = getLevel();
    unsigned int bonus = m_bonus;
    int livesLeft = getLives();

    string s = formatInfo(score, level, livesLeft, m_player->getHealth(), m_player->getAmmo(), bonus);
    
    setGameStatText(s);
}

bool StudentWorld::anyLeft(int image)
{
    vector<Actor*>::iterator p = m_actor.begin();
    for( ; p < m_actor.end(); p++)
    {
        if((*p)->getID() == IID_KLEPTOBOT || (*p)->getID() == IID_ANGRY_KLEPTOBOT)
        {
            KleptoBot* kp = dynamic_cast<KleptoBot*>(*p);
            if(kp != nullptr && (kp)->getGoodieID() == IID_JEWEL)
                return false;
            AngryKleptoBot* akp = dynamic_cast<AngryKleptoBot*>(*p);
            if(akp != nullptr && (akp)->getGoodieID() == IID_JEWEL)
                return false;
        }
        if(image == (*p)->getID())
            return true;
    }
    return false;
}

void StudentWorld::makeItem(int x, int y, int imageID, Actor::Direction dir)
{
    if(imageID == IID_BULLET)
        m_actor.push_back(new Bullet(x,y,this,dir));
    
    if(imageID == IID_ANGRY_KLEPTOBOT)
        m_actor.push_back(new AngryKleptoBot(x,y,this));
    
    if(imageID == IID_KLEPTOBOT)
        m_actor.push_back(new KleptoBot(x,y,this));
    
    if(imageID == IID_AMMO)
        m_actor.push_back(new Ammo(x,y,this));
    
    if(imageID == IID_EXTRA_LIFE)
        m_actor.push_back(new ExtraLife(x,y,this));
    
    if(imageID == IID_RESTORE_HEALTH)
        m_actor.push_back(new RestoreHealth(x,y,this));
    
    if(imageID == IID_JEWEL)
        m_actor.push_back(new Jewel(x,y,this));
}

string formatInfo(int score, int level, int lives, double health, int ammo, int bonus)
{
    string s;
    ostringstream oss, oss1, oss2, oss3, oss4, oss5, oss6;

    s += "Score: ";
    oss.fill('0');
    oss << setw(7) << score;
    s += oss.str();
    
    oss1.fill('0');
    s += "  Level: ";
    oss1 << setw(2) << level;
    s += oss1.str();
    
    s += "  Lives: ";
    oss3 << setw(2) << lives;
    s += oss3.str();

    s += "  Health: ";
    oss4 << setw(3) << (health/20)*100;
    s += oss4.str();
    s += "%";
    
    s += "  Ammo: ";
    oss5 << setw(3) << ammo;
    s += oss5.str();

    s += "  Bonus: ";
    oss6 << setw(4) << bonus;
    s += oss6.str();

    return s;
}

