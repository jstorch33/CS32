#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include "stdlib.h"
#include <iostream>
#include <string>

using namespace std;
void Actor::shoot()
{
    if(this->getID() == IID_PLAYER)
       getWorld()->playSound(SOUND_PLAYER_FIRE);
    else
        getWorld()->playSound(SOUND_ENEMY_FIRE);

    if(getDirection() == up)
    {
        getWorld()->makeItem(getX(), getY()+1, IID_BULLET, up);
    }
    if(getDirection() == down)
    {
        getWorld()->makeItem(getX(), getY()-1, IID_BULLET, down);
    }
    if(getDirection() == right)
    {
        getWorld()->makeItem(getX()+1, getY(), IID_BULLET, right);
    }
    if(getDirection() == left)
    {
        getWorld()->makeItem(getX()-1, getY(), IID_BULLET, left);
    }
}

void Actor::damage()
{
    setHealth(getHealth()-2);
    if(getHealth() <= 0)
    {
        setDead();
    }
    
    if(getID() == IID_SNARLBOT && !isAlive())
        getWorld()->increaseScore(100);
    
    if(getID() == IID_ANGRY_KLEPTOBOT ||getID() == IID_KLEPTOBOT ||getID() == IID_SNARLBOT)
    {
        if(!isAlive())
            getWorld()->playSound(SOUND_ROBOT_DIE);
        else
            getWorld()->playSound(SOUND_ROBOT_IMPACT);
    }
}

void Player::doSomething()
{
    int keyValue = 0;
    if(getWorld()->getKey(keyValue))
    {
        switch(keyValue)
        {
            case KEY_PRESS_UP:
                setDirection(up);
                if(getWorld()->whatsHere(getX(),getY()+1) != nullptr)
                {
                    if (getWorld()->whatsHere(getX(),getY()+1)->getID()== IID_BOULDER)
                    {
                        if(getWorld()->whatsHere(getX(),getY()+1)->blocksPath(keyValue))
                        {
                            break;
                        }
                    }
                    else if(getWorld()->whatsHere(getX(),getY()+1)->blocksPath())
                    {
                        break;
                    }
                    else if(getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_AMMO ||
                       getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_EXTRA_LIFE ||
                       getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_JEWEL ||
                       getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_RESTORE_HEALTH ||
                       getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_EXIT)
                    {
                        if(getWorld()->whatDoYouNeed(getX(), getY()+1, IID_KLEPTOBOT) != nullptr ||
                           getWorld()->whatDoYouNeed(getX(), getY()+1, IID_SNARLBOT) != nullptr ||
                           getWorld()->whatDoYouNeed(getX(), getY()+1, IID_ANGRY_KLEPTOBOT) != nullptr)
                            
                        {
                            break;
                        }
                    }
                }
                moveTo(getX(),getY()+1);
                break;
                
            case KEY_PRESS_DOWN:
                setDirection(down);
                if(getWorld()->whatsHere(getX(),getY()-1) != nullptr)
                {
                    if (getWorld()->whatsHere(getX(),getY()-1)->getID()== IID_BOULDER)
                    {
                        if(getWorld()->whatsHere(getX(),getY()-1)->blocksPath(keyValue))
                        {
                            break;
                        }
                    }
                    else if(getWorld()->whatsHere(getX(),getY()-1)->blocksPath())
                    {
                        break;
                    }
                    else if(getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_AMMO ||
                            getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_EXTRA_LIFE ||
                            getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_JEWEL ||
                            getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_RESTORE_HEALTH ||
                            getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_EXIT)
                    {
                        if(getWorld()->whatDoYouNeed(getX(), getY()-1, IID_KLEPTOBOT) != nullptr ||
                           getWorld()->whatDoYouNeed(getX(), getY()-1, IID_SNARLBOT) != nullptr ||
                           getWorld()->whatDoYouNeed(getX(), getY()-1, IID_ANGRY_KLEPTOBOT) != nullptr)
                            
                        {
                            break;
                        }
                    }

                }
                moveTo(getX(),getY()-1);
                break;
                
            case KEY_PRESS_RIGHT:
                setDirection(right);
                if(getWorld()->whatsHere(getX()+1,getY()) != nullptr)
                {
                    if (getWorld()->whatsHere(getX()+1,getY())->getID()== IID_BOULDER)
                    {
                        if(getWorld()->whatsHere(getX()+1,getY())->blocksPath(keyValue))
                        {
                            break;
                        }
                    }
                    else if(getWorld()->whatsHere(getX()+1,getY())->blocksPath())
                    {
                        break;
                    }
                    else if(getWorld()->whatsHere(getX()+1, getY())->getID() == IID_AMMO ||
                            getWorld()->whatsHere(getX()+1, getY())->getID() == IID_EXTRA_LIFE ||
                            getWorld()->whatsHere(getX()+1, getY())->getID() == IID_JEWEL ||
                            getWorld()->whatsHere(getX()+1, getY())->getID() == IID_RESTORE_HEALTH ||
                            getWorld()->whatsHere(getX()+1, getY())->getID() == IID_EXIT)
                    {
                        if(getWorld()->whatDoYouNeed(getX()+1, getY(), IID_KLEPTOBOT) != nullptr ||
                           getWorld()->whatDoYouNeed(getX()+1, getY(), IID_SNARLBOT) != nullptr ||
                           getWorld()->whatDoYouNeed(getX()+1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
                            
                        {
                            break;
                        }
                    }
                }
                moveTo(getX()+1,getY());
                break;
                
            case KEY_PRESS_LEFT:
                setDirection(left);
                if(getWorld()->whatsHere(getX()-1,getY()) != nullptr)
                {
                    if (getWorld()->whatsHere(getX()-1,getY())->getID()== IID_BOULDER)
                    {
                        if(getWorld()->whatsHere(getX()-1,getY())->blocksPath(keyValue))
                        {
                            break;
                        }
                    }
                    else if(getWorld()->whatsHere(getX()-1,getY())->blocksPath())
                    {
                        break;
                    }
                    else if(getWorld()->whatsHere(getX()-1, getY())->getID() == IID_AMMO ||
                            getWorld()->whatsHere(getX()-1, getY())->getID() == IID_EXTRA_LIFE ||
                            getWorld()->whatsHere(getX()-1, getY())->getID() == IID_JEWEL ||
                            getWorld()->whatsHere(getX()-1, getY())->getID() == IID_RESTORE_HEALTH ||
                            getWorld()->whatsHere(getX()-1, getY())->getID() == IID_EXIT)
                    {
                        if(getWorld()->whatDoYouNeed(getX()-1, getY(), IID_KLEPTOBOT) != nullptr ||
                           getWorld()->whatDoYouNeed(getX()-1, getY(), IID_SNARLBOT) != nullptr ||
                           getWorld()->whatDoYouNeed(getX()-1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
                            
                        {
                            break;
                        }
                    }
                }
                moveTo(getX()-1,getY());
                break;
                
            case KEY_PRESS_SPACE:
                if(m_ammo > 0)
                {
                    shoot();
                    m_ammo--;
                }
                break;
            case KEY_PRESS_ESCAPE:
                setDead();
                break;
        }
    }
}

void Player::damage()
{
    setHealth(getHealth()-2);
    if(getHealth() <= 0)
    {
        getWorld()->playSound(SOUND_PLAYER_DIE);
        setDead();
    }
    if(isAlive())
        getWorld()->playSound(SOUND_PLAYER_IMPACT);
}

bool Boulder::blocksPath(int keyValue)
{
    if(getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY()+1 == getY())
    {
        if(keyValue == KEY_PRESS_UP)
        {
            if(getWorld()->whatsHere(getX(),getY()+1) == nullptr || getWorld()->whatsHere(getX(),getY()+1)->getID() == IID_HOLE)
            {
                moveTo(getX(), getY()+1);
                return false;
            }
        }
    }
    
    if(getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY()-1 == getY())
    {
        if(keyValue == KEY_PRESS_DOWN)
        {
            if(getWorld()->whatsHere(getX(),getY()-1) == nullptr || getWorld()->whatsHere(getX(),getY()-1)->getID() == IID_HOLE)
            {
                moveTo(getX(), getY()-1);
                return false;
            }
        }
    }
    
    if(getWorld()->getPlayer()->getX()-1 == getX() && getWorld()->getPlayer()->getY() == getY())
    {
        if(keyValue == KEY_PRESS_LEFT)
        {
            if(getWorld()->whatsHere(getX()-1,getY()) == nullptr || getWorld()->whatsHere(getX()-1,getY())->getID() == IID_HOLE)
            {
                moveTo(getX()-1, getY());
                return false;
            }
        }
    }
    
    if(getWorld()->getPlayer()->getX()+1 == getX() && getWorld()->getPlayer()->getY() == getY())
    {
        if(keyValue == KEY_PRESS_RIGHT)
        {
            if(getWorld()->whatsHere(getX()+1,getY()) == nullptr || getWorld()->whatsHere(getX()+1,getY())->getID() == IID_HOLE)
            {
                moveTo(getX()+1, getY());
                return false;
            }
        }
    }
    return true;
}

void Hole::doSomething()
{
    if(!isAlive())
    {
        return;
    }
    
    if(getWorld()->whatDoYouNeed(getX(),getY(),IID_BOULDER) != nullptr)
    {
        setDead();
        getWorld()->whatDoYouNeed(getX(), getY(), IID_BOULDER)->setDead();
    }
}

bool Goodie::isPlayerHere()
{
    if(getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY())
    {
        setDead();
        return true;
    }
    return false;
}

void Jewel::doSomething()
{
    if(!isAlive())
        return;
    
    if(isPlayerHere())
    {
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(50);
    }
}

void ExtraLife::doSomething()
{
    if(!isAlive())
        return;
    
    if(isPlayerHere())
    {
        getWorld()->playSound(SOUND_GOT_GOODIE);

        getWorld()->increaseScore(1000);
        getWorld()->incLives();
    }

}

void RestoreHealth::doSomething()
{
    if(!isAlive())
        return;
    
    if(isPlayerHere())
    {
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(500);
        getWorld()->getPlayer()->setHealth(20);
    }
    
}

void Ammo::doSomething()
{
    if(!isAlive())
        return;
    
    if(isPlayerHere())
    {
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(100);
        getWorld()->getPlayer()->incAmmo();
    }
}

void Exit::doSomething()
{
    if (!getWorld()->anyLeft(IID_JEWEL) && !isVisible())
    {
        getWorld()->playSound(SOUND_REVEAL_EXIT);
        setVisible(true);
    }
    
    if(!getWorld()->anyLeft(IID_JEWEL) && isPlayerHere())
    {
        getWorld()->playSound(SOUND_FINISHED_LEVEL);
        getWorld()->increaseScore(2000);
        getWorld()->levelFinished();
    }
}

void Bullet::doSomething()
{
    if(!isAlive())
        return;
    
    didItHit();
    
    if(!isAlive())
        return;
    
    if(getDirection() == up)
        moveTo(getX(), getY()+1);
    if(getDirection() == down)
        moveTo(getX(), getY()-1);
    if(getDirection() == right)
        moveTo(getX()+1, getY());
    if(getDirection() == left)
        moveTo(getX()-1, getY());
    
    didItHit();
}

void Bullet::didItHit()
{
    Actor* klepto = getWorld()->whatDoYouNeed(getX(), getY(), IID_KLEPTOBOT);
    Actor* angryKlepto = getWorld()->whatDoYouNeed(getX(), getY(), IID_ANGRY_KLEPTOBOT);
    Actor* snarl = getWorld()->whatDoYouNeed(getX(), getY(), IID_SNARLBOT);
    

    int image2 = getWorld()->whatsHere(getX(), getY())->getID();
    if(getX()==getWorld()->getPlayer()->getX() && getY()==getWorld()->getPlayer()->getY())
    {
        getWorld()->getPlayer()->damage();
        setDead();
        return;
    }
    if(image2 == IID_ANGRY_KLEPTOBOT ||image2 == IID_BOULDER ||image2 == IID_KLEPTOBOT || image2 == IID_SNARLBOT)
    {
        getWorld()->whatsHere(getX(), getY())->damage();
        setDead();
        return;
    }
    else if(image2 == IID_WALL)
    {
        setDead();
        return;
    }
    else if(image2 == IID_ROBOT_FACTORY || image2 == IID_JEWEL || image2 == IID_EXTRA_LIFE
            || image2 == IID_RESTORE_HEALTH || image2 == IID_AMMO || image2 == IID_EXIT)
    {
        if(klepto != nullptr && klepto->getID() == IID_KLEPTOBOT )
        {
            klepto->damage();
            setDead();
        }
        if(angryKlepto != nullptr && angryKlepto->getID() == IID_ANGRY_KLEPTOBOT)
        {
            angryKlepto->damage();
            setDead();
        }
        if(snarl != nullptr && snarl->getID() == IID_SNARLBOT)
        {
            snarl->damage();
            setDead();
        }
        if(image2 == IID_ROBOT_FACTORY)
            setDead();
        
        return;
    }
    


    if(getWorld()->whatsNext(getX(), getY(), getDirection()) == nullptr)
    {return;}
    int image = getWorld()->whatsNext(getX(), getY(), getDirection())->getID();
    if(image == IID_PLAYER || image == IID_ANGRY_KLEPTOBOT ||image == IID_BOULDER
       || image == IID_KLEPTOBOT || image == IID_SNARLBOT)
    {
        getWorld()->whatsNext(getX(), getY(), getDirection())->damage();
        setDead();
        return;
    }
    else if(image == IID_WALL)
    {
        setDead();
        return;
    }
    
}

bool Robot::wait()
{
    int ticks = getWorld()->getLevel();
    ticks = (28 - ticks) / 4;
    if (ticks < 3)
        ticks = 3;
    
    if(m_ticks == ticks)
    {
        m_ticks = 0;
        return true;
    }
    return false;
}

bool Robot::isPlayerInLineOfSight()
{
    int dir = getDirection();
    switch (dir)
    {
        case up:
            if(getWorld()->getPlayer()->getX() != getX())
                break;
            for(int y = getY()+1;y < VIEW_HEIGHT; y++)
            {
                if(getWorld()->getPlayer()->getY() == y)
                    return true;
                if(getWorld()->whatsHere(getX(), y) == nullptr)
                    continue;
                if(getWorld()->whatsHere(getX(), y)->getID() == IID_HOLE)
                    continue;
                if(getWorld()->whatsHere(getX(), y)->blocksPath())
                    return false;
            }
            break;
            
        case down:
            if(getWorld()->getPlayer()->getX() != getX())
                break;
            for(int y = getY()-1;y > 0; y--)
            {
                if(getWorld()->getPlayer()->getY() == y)
                    return true;
                if(getWorld()->whatsHere(getX(), y) == nullptr)
                    continue;
                if(getWorld()->whatsHere(getX(), y)->getID() == IID_HOLE)
                    continue;
                if(getWorld()->whatsHere(getX(), y)->blocksPath())
                    return false;
            }
            break;
            
        case right:
            if(getWorld()->getPlayer()->getY() != getY())
                break;
            for(int x = getX()+1;x < VIEW_WIDTH; x++)
            {
                if(getWorld()->getPlayer()->getX() == x)
                    return true;
                if(getWorld()->whatsHere(x, getY()) == nullptr)
                    continue;
                if(getWorld()->whatsHere(x, getY())->getID() == IID_HOLE)
                    continue;
                if(getWorld()->whatsHere(x, getY())->blocksPath())
                    return false;
            }
            break;
            
        case left:
            if(getWorld()->getPlayer()->getY() != getY())
                break;
            for(int x = getX()-1;x > 0; x--)
            {
                if(getWorld()->getPlayer()->getX() == x)
                    return true;
                if(getWorld()->whatsHere(x, getY()) == nullptr)
                    continue;
                if(getWorld()->whatsHere(x, getY())->getID() == IID_HOLE)
                    continue;
                if(getWorld()->whatsHere(x, getY())->blocksPath())
                    return false;
            }
            break;
    }
    return false;
}

void SnarlBot::doSomething()
{
    if(!isAlive())
        return;
    
    if(!wait())
    {
        incTicks();
        return;
    }
    
    if(isPlayerInLineOfSight())
    {
        shoot();
        return;
    }
    
    Direction dir = getDirection();
    switch (dir)
    {
        case up:
            if(getWorld()->getPlayer()->getX()== getX() &&
                    getWorld()->getPlayer()->getY() == getY()+1)
            {
                setDirection(down);
                break;
            }

            if(getWorld()->whatsHere(getX(), getY()+1)!=nullptr)
            {
                if(getWorld()->whatsHere(getX(), getY()+1)->blocksPath())
                {
                    setDirection(down);
                    break;
                }
            }
            moveTo(getX(), getY()+1);
            break;
            
        case down:
            if(getWorld()->getPlayer()->getX() == getX() &&
                    getWorld()->getPlayer()->getY() == getY()-1)
            {
                setDirection(up);
                break;
            }
            if(getWorld()->whatsHere(getX(), getY()-1)!=nullptr)
            {
                if(getWorld()->whatsHere(getX(), getY()-1)->blocksPath())
                {
                    setDirection(up);
                    break;
                }
            }
            moveTo(getX(), getY()-1);
            break;
            
        case right:
            if(getWorld()->getPlayer()->getX()== getX()+1 &&
               getWorld()->getPlayer()->getY() == getY())
            {
                setDirection(left);
                break;
            }
            if(getWorld()->whatsHere(getX()+1, getY()) != nullptr)
            {
                if(getWorld()->whatsHere(getX()+1, getY())->blocksPath())
                {
                    setDirection(left);
                    break;
                }
            }
            moveTo(getX()+1, getY());
            break;
            
        case left:
            if(getWorld()->getPlayer()->getX() == getX()-1 &&
                    getWorld()->getPlayer()->getY() == getY())
            {
                setDirection(right);
                break;
            }
            if(getWorld()->whatsHere(getX()-1, getY())!=nullptr)
            {
                if(getWorld()->whatsHere(getX()-1, getY())->blocksPath())
                {
                    setDirection(right);
                    break;
                }
            }
            moveTo(getX()-1, getY());
            break;
            
        default:
            break;
    }
}

void KleptoBot::setNewDis()
{
    switch(rand()%6 + 1)
    {
        case 1:
            m_dis = 1;
            break;
        case 2:
            m_dis = 2;
            break;
        case 3:
            m_dis = 3;
            break;
        case 4:
            m_dis = 4;
            break;
        case 5:
            m_dis = 5;
            break;
        case 6:
            m_dis = 6;
            break;
    }
}
bool KleptoBot::blockedIn(char letter)
{
    if(letter == 'e')
        return true;
    for(int a = 0; a< blocked.length(); a++)
    {
        if(blocked[a] == letter)
        {
           if(blockedIn(letter+1))
               return true;
        }
    }
    return false;
}

void KleptoBot::setNewDir()
{
    if(blockedIn('a'))
        return;
    switch(rand()%4 + 1)
    {
        case 1:
            blocked += 'a';
            if(getWorld()->getPlayer()->getX()== getX() &&
               getWorld()->getPlayer()->getY() == getY()+1)
            {
                setNewDir();
                break;
            }
            
            if(getWorld()->whatsHere(getX(), getY()+1)!=nullptr)
            {
                if(getWorld()->whatsHere(getX(), getY()+1)->blocksPath())
                {
                    setNewDir();
                    break;
                }
                if(getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_AMMO ||
                   getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_EXTRA_LIFE ||
                   getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_JEWEL ||
                   getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_RESTORE_HEALTH ||
                   getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_EXIT)
                {
                    if(getWorld()->whatDoYouNeed(getX(), getY()+1, IID_KLEPTOBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX(), getY()+1, IID_SNARLBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX(), getY()+1, IID_ANGRY_KLEPTOBOT) != nullptr)
                        
                    {
                        setNewDir();
                        break;
                    }
                }
            }
            blocked = "";
            setDirection(up);
            break;
        case 2:
            blocked += 'b';

            if(getWorld()->getPlayer()->getX()== getX() &&
               getWorld()->getPlayer()->getY() == getY()-1)
            {
                setNewDir();
                break;
            }
            
            if(getWorld()->whatsHere(getX(), getY()-1)!=nullptr)
            {
                if(getWorld()->whatsHere(getX(), getY()-1)->blocksPath())
                {
                    setNewDir();
                    break;
                }
                if(getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_AMMO ||
                   getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_EXTRA_LIFE ||
                   getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_JEWEL ||
                   getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_RESTORE_HEALTH ||
                   getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_EXIT)
                {
                    if(getWorld()->whatDoYouNeed(getX(), getY()-1, IID_KLEPTOBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX(), getY()-1, IID_SNARLBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX(), getY()-1, IID_ANGRY_KLEPTOBOT) != nullptr)
                        
                    {
                        setNewDir();
                        break;
                    }
                }
            }
            blocked = "";
            setDirection(down);
            break;
        case 3:
            blocked += 'c';
            if(getWorld()->getPlayer()->getX()== getX()+1 &&
               getWorld()->getPlayer()->getY() == getY())
            {
                setNewDir();
                break;
            }
            
            if(getWorld()->whatsHere(getX()+1, getY())!=nullptr)
            {
                if(getWorld()->whatsHere(getX()+1, getY())->blocksPath())
                {
                    setNewDir();
                    break;
                }
                if(getWorld()->whatsHere(getX()+1, getY())->getID() == IID_AMMO ||
                   getWorld()->whatsHere(getX()+1, getY())->getID() == IID_EXTRA_LIFE ||
                   getWorld()->whatsHere(getX()+1, getY())->getID() == IID_JEWEL ||
                   getWorld()->whatsHere(getX()+1, getY())->getID() == IID_RESTORE_HEALTH ||
                   getWorld()->whatsHere(getX()+1, getY())->getID() == IID_EXIT)
                {
                    if(getWorld()->whatDoYouNeed(getX()+1, getY(), IID_KLEPTOBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX()+1, getY(), IID_SNARLBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX()+1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
                        
                    {
                        setNewDir();
                        break;
                    }
                }
            }
            blocked = "";
            setDirection(right);
            break;
        case 4:
            blocked += 'd';
            if(getWorld()->getPlayer()->getX()== getX()-1 &&
               getWorld()->getPlayer()->getY() == getY())
            {
                setNewDir();
                break;
            }
            
            if(getWorld()->whatsHere(getX()-1, getY())!=nullptr)
            {
                if(getWorld()->whatsHere(getX()-1, getY())->blocksPath())
                {
                    setNewDir();
                    break;
                }
                if(getWorld()->whatsHere(getX()-1, getY())->getID() == IID_AMMO ||
                   getWorld()->whatsHere(getX()-1, getY())->getID() == IID_EXTRA_LIFE ||
                   getWorld()->whatsHere(getX()-1, getY())->getID() == IID_JEWEL ||
                   getWorld()->whatsHere(getX()-1, getY())->getID() == IID_RESTORE_HEALTH ||
                   getWorld()->whatsHere(getX()-1, getY())->getID() == IID_EXIT)
                {
                    if(getWorld()->whatDoYouNeed(getX()-1, getY(), IID_KLEPTOBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX()-1, getY(), IID_SNARLBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX()-1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
                        
                    {
                        setNewDir();
                        break;
                    }
                }
            }
            blocked = "";
            setDirection(left);
            break;
    }
}

void KleptoBot::damage()
{
    setHealth(getHealth()-2);
    if(getHealth() <= 0)
    {
        setDead();
    }
    
    if(getID() == IID_KLEPTOBOT && !isAlive())
        getWorld()->increaseScore(10);
    
    if(getID() == IID_ANGRY_KLEPTOBOT && !isAlive())
        getWorld()->increaseScore(20);
    
    if(!isAlive())
        getWorld()->playSound(SOUND_ROBOT_DIE);
    else
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    
    
    if(!isAlive())
    {
        if(m_goodieID != 0)
        {
            if(m_goodieID == IID_AMMO)
            {
                getWorld()->makeItem(getX(), getY(), IID_AMMO);
            }
            if(m_goodieID == IID_EXTRA_LIFE)
            {
                getWorld()->makeItem(getX(), getY(), IID_EXTRA_LIFE);
            }
            if(m_goodieID == IID_RESTORE_HEALTH)
            {
                getWorld()->makeItem(getX(), getY(), IID_RESTORE_HEALTH);
            }
            if(m_goodieID == IID_JEWEL)
            {
                getWorld()->makeItem(getX(), getY(), IID_JEWEL);
            }
        }
    }
   
}

bool KleptoBot::eatGoodie()
{
    if(getWorld()->whatDoYouNeed(getX(), getY(), IID_EXTRA_LIFE) == nullptr &&
       getWorld()->whatDoYouNeed(getX(), getY(), IID_JEWEL) == nullptr &&
       getWorld()->whatDoYouNeed(getX(), getY(), IID_RESTORE_HEALTH) == nullptr &&
       getWorld()->whatDoYouNeed(getX(), getY(), IID_AMMO) == nullptr)
    {
        return false;
    }
    
    if(m_goodieID == 0 && rand()%10 +1 == 5)
    {
        getWorld()->playSound(SOUND_ROBOT_MUNCH);
        getWorld()->whatsHere(getX(), getY())->setDead();
        m_goodieID = getWorld()->whatsHere(getX(), getY())->getID();
        return true;
    }
    return false;
}

void KleptoBot::walk()
{
    int dir = getDirection();
    switch (dir)
    {
        case up:
            if(getWorld()->getPlayer()->getX()== getX() &&
               getWorld()->getPlayer()->getY() == getY()+1)
            {
                setNewDir();
                setNewDis();
                break;
            }
            
            if(getWorld()->whatsHere(getX(), getY()+1)!=nullptr)
            {
                if(getWorld()->whatsHere(getX(), getY()+1)->blocksPath())
                {
                    setNewDis();
                    setNewDir();
                    break;
                }
                if(getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_AMMO ||
                   getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_EXTRA_LIFE ||
                   getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_JEWEL ||
                   getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_RESTORE_HEALTH ||
                   getWorld()->whatsHere(getX(), getY()+1)->getID() == IID_EXIT)
                {
                    if(getWorld()->whatDoYouNeed(getX(), getY()+1, IID_KLEPTOBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX(), getY()+1, IID_SNARLBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX(), getY()+1, IID_ANGRY_KLEPTOBOT) != nullptr)
                        
                    {
                        setNewDis();
                        setNewDir();
                        break;
                    }
                }
            }

            if(m_dis == 0)
            {
                setNewDis();
                setNewDir();
                break;
            }
            moveTo(getX(), getY()+1);
            m_dis--;
            break;
            
        case down:
            if(getWorld()->getPlayer()->getX() == getX() &&
               getWorld()->getPlayer()->getY() == getY()-1)
            {
                setNewDis();
                setNewDir();
                break;
            }
            if(getWorld()->whatsHere(getX(), getY()-1)!=nullptr)
            {
                if(getWorld()->whatsHere(getX(), getY()-1)->blocksPath())
                {
                    setNewDis();
                    setNewDir();
                    break;
                }
                if(getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_AMMO ||
                   getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_EXTRA_LIFE ||
                   getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_JEWEL ||
                   getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_RESTORE_HEALTH||
                   getWorld()->whatsHere(getX(), getY()-1)->getID() == IID_EXIT)
                {
                    if(getWorld()->whatDoYouNeed(getX(), getY()-1, IID_KLEPTOBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX(), getY()-1, IID_SNARLBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX(), getY()-1, IID_ANGRY_KLEPTOBOT) != nullptr)
                        
                    {
                        setNewDis();
                        setNewDir();
                        break;
                    }
                }
            }
            
                
            if(m_dis == 0)
            {
                setNewDis();
                setNewDir();
                break;
            }
            moveTo(getX(), getY()-1);
            m_dis--;
            break;
            
        case right:
            if(getWorld()->getPlayer()->getX()== getX()+1 &&
               getWorld()->getPlayer()->getY() == getY())
            {
                setNewDis();
                setNewDir();
                break;
            }
            if(getWorld()->whatsHere(getX()+1, getY()) != nullptr)
            {
                if(getWorld()->whatsHere(getX()+1, getY())->blocksPath())
                {
                    setNewDis();
                    setNewDir();
                    break;
                }
                if(getWorld()->whatsHere(getX()+1, getY())->getID() == IID_AMMO ||
                   getWorld()->whatsHere(getX()+1, getY())->getID() == IID_EXTRA_LIFE ||
                   getWorld()->whatsHere(getX()+1, getY())->getID() == IID_JEWEL ||
                   getWorld()->whatsHere(getX()+1, getY())->getID() == IID_RESTORE_HEALTH ||
                   getWorld()->whatsHere(getX()+1, getY())->getID() == IID_EXIT)
                {
                    if(getWorld()->whatDoYouNeed(getX()+1, getY(), IID_KLEPTOBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX()+1, getY(), IID_SNARLBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX()+1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
                        
                    {
                        setNewDis();
                        setNewDir();
                        break;
                    }
                }
            }
            
            
            if(m_dis == 0)
            {
                setNewDis();
                setNewDir();
                break;
            }
            moveTo(getX()+1, getY());
            m_dis--;
            break;
            
        case left:
            if(getWorld()->getPlayer()->getX() == getX()-1 &&
               getWorld()->getPlayer()->getY() == getY())
            {
                setNewDis();
                setNewDir();
                break;
            }
            if(getWorld()->whatsHere(getX()-1, getY())!=nullptr)
            {
                if(getWorld()->whatsHere(getX()-1, getY())->blocksPath())
                {
                    setNewDis();
                    setNewDir();
                    break;
                }
                if(getWorld()->whatsHere(getX()-1, getY())->getID() == IID_AMMO ||
                   getWorld()->whatsHere(getX()-1, getY())->getID() == IID_EXTRA_LIFE ||
                   getWorld()->whatsHere(getX()-1, getY())->getID() == IID_JEWEL ||
                   getWorld()->whatsHere(getX()-1, getY())->getID() == IID_RESTORE_HEALTH ||
                   getWorld()->whatsHere(getX()-1, getY())->getID() == IID_EXIT)
                {
                    if(getWorld()->whatDoYouNeed(getX()-1, getY(), IID_KLEPTOBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX()-1, getY(), IID_SNARLBOT) != nullptr ||
                       getWorld()->whatDoYouNeed(getX()-1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
                        
                    {
                        setNewDis();
                        setNewDir();
                        break;
                    }
                }
            }
            
            
            if(m_dis == 0)
            {
                setNewDis();
                setNewDir();
                break;
            }
            moveTo(getX()-1, getY());
            m_dis--;
            break;
            
        default:
            break;
    }
}

void KleptoBot::doSomething()
{
    resetBlocked();
    if(!isAlive())
        return;
    if(!wait())
    {
        incTicks();
        return;
    }
   if(eatGoodie())
        return;
    walk();
}

void AngryKleptoBot::doSomething()
{
    resetBlocked();
    if(!isAlive())
        return;
    if(!wait())
    {
        incTicks();
        return;
    }
    if(isPlayerInLineOfSight())
    {
        shoot();
        return;
    }
    if(eatGoodie())
        return;
    walk();
}

void KleptoBotFactory::doSomething()
{
    int count = 0;
    if(getWorld()-> whatDoYouNeed(getX(), getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
    {
        return;
    }
    if(getWorld()-> whatDoYouNeed(getX(), getY(), IID_KLEPTOBOT) != nullptr)
    {
        return;
    }

    for(int x = getX(); x < VIEW_WIDTH && x <= getX()+3; x++)
    {
        for(int y = getY(); y < VIEW_HEIGHT && y <= getY()+3; y++)
        {
            if(getWorld()->whatDoYouNeed(x, y, IID_KLEPTOBOT))
            {
                count++;
            }
            if(getWorld()->whatDoYouNeed(x, y, IID_ANGRY_KLEPTOBOT))
            {
                count++;
            }

        }
        for(int y = getY()-1; y > 0 && y >= getY()-3; y--)
        {
            if(getWorld()->whatDoYouNeed(x, y, IID_KLEPTOBOT))
            {
                count++;
            }
            if(getWorld()->whatDoYouNeed(x, y, IID_ANGRY_KLEPTOBOT))
            {
                count++;
            }
        }
    }
    for(int x = getX()-1; x > 0 && x >= getX()-3; x--)
    {
        for(int y = getY(); y < VIEW_HEIGHT && y <= getY()+3; y++)
        {
            if(getWorld()->whatDoYouNeed(x, y, IID_KLEPTOBOT))
            {
                count++;
            }
            if(getWorld()->whatDoYouNeed(x, y, IID_ANGRY_KLEPTOBOT))
            {
                count++;
            }
            
        }
        for(int y = getY()-1; y > 0 && y >= getY()-3; y--)
        {
            if(getWorld()->whatDoYouNeed(x, y, IID_KLEPTOBOT))
            {
                count++;
            }
            if(getWorld()->whatDoYouNeed(x, y, IID_ANGRY_KLEPTOBOT))
            {
                count++;
            }
        }
    }
    if(count < 3)
    {
        if((rand()%50 +1) == 25)
        {
            createRobot(m_angry);
        }
    }
}

void KleptoBotFactory::createRobot(bool angry)
{
    getWorld()->playSound(SOUND_ROBOT_BORN);
    if(angry)
    {
        getWorld()->makeItem(getX(), getY(), IID_ANGRY_KLEPTOBOT);
    }
    else
    {
        getWorld()->makeItem(getX(), getY(), IID_KLEPTOBOT);
    }
}