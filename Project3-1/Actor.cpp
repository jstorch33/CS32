#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

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
                    if(getWorld()->whatsHere(getX(),getY()+1)->blocksPlayer())
                    {
                        break;
                    }
                }
                moveTo(getX(),getY()+1);
                break;
                
            case KEY_PRESS_DOWN:
                setDirection(down);
                if(getWorld()->whatsHere(getX(),getY()-1) != nullptr)
                {
                    if(getWorld()->whatsHere(getX(),getY()-1)->blocksPlayer())
                    {
                        break;
                    }
                }
                moveTo(getX(),getY()-1);
                break;
                
            case KEY_PRESS_RIGHT:
                setDirection(right);
                if(getWorld()->whatsHere(getX()+1,getY()) != nullptr)
                {
                    if(getWorld()->whatsHere(getX()+1,getY())->blocksPlayer())
                    {
                        break;
                    }
                }
                moveTo(getX()+1,getY());
                break;
                
            case KEY_PRESS_LEFT:
                setDirection(left);
                if(getWorld()->whatsHere(getX()-1,getY()) != nullptr)
                {
                    if(getWorld()->whatsHere(getX()-1,getY())->blocksPlayer())
                    {
                        break;
                    }
                }
                moveTo(getX()-1,getY());
                break;
                
            case KEY_PRESS_SPACE:
                break;
        }
    }
}

bool Player::isValidMove(int x, int y)
{
    Actor* ap = getWorld()->whatsHere(x,y);
    if (ap != nullptr)
    {
        Wall* wp = dynamic_cast<Wall*>(ap);
        if (wp != nullptr)
        {
            return false;
        }
    }
    return true;
}