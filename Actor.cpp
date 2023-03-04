#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
#include <list>

//Actor
Actor::Actor(StudentWorld* world, const int imageID, int startX, int startY, int startDirection, int depth, double size)
    : GraphObject(imageID, startX, startY, startDirection, depth, 1), m_dieRoll(0), ticks_to_move(0), waiting_to_roll(true)
        , m_alive(true), m_playerCoins(0), m_playerStars(0), m_goTeleport(false), justSwapped(false) //, ticks_to_move(ticks)
{
    m_world = world;
}
Actor::~Actor()	//always have it
{	}
StudentWorld* Actor::getWorld()
{
    return m_world;
}

bool Actor::isValidPos(int dir) //, int xDir, int yDir)
{
    int xNew, yNew;
    getPositionInThisDirection(dir, SPRITE_WIDTH, xNew, yNew);	//returns pixel location
    //std::cerr << xNew << " " << yNew << std::endl;

    //pass in grid x, y for isEmpty()
    if (m_world->isEmpty(xNew / SPRITE_WIDTH, yNew / SPRITE_HEIGHT) == true)	
    {
        //std::cerr << "Next pos is empty, valid pos is false" << std::endl;
        //if it's empty, then you can't keep moving.  Meaning, false valid position
        return false;
    }
    else
    {
        //std::cerr << "Next pos is not empty, valid pos is true " << std::endl;
        return true;
    }

}
void Actor::swap()
{
    //swap position (x, y)
    //int peachX, peachY, yoshiX, yoshiY;
    //getWorld()->findPeach(peachX, peachY);
    //getWorld()->findYoshi(yoshiX, yoshiY);
    //getWorld()->movePlayer(1, yoshiX, yoshiY);
    //getWorld()->movePlayer(2, peachX, peachY);
  

    //get coins getx gety to make it dropping squares' getx gety before destryoing coin
    //getWorld()->movePlayer(2, peachX, peachY);
    int peachX = getWorld()->getPeach()->getX();
    int peachY = getWorld()->getPeach()->getY();
    int yoshiX = getWorld()->getYoshi()->getX();
    int yoshiY = getWorld()->getYoshi()->getY();
    getWorld()->getPeach()->moveTo(yoshiX, yoshiY);
    getWorld()->getYoshi()->moveTo(peachX, peachY);
    //Avatar* peach = getWorld()->getpeach()
    //return m_plaer
    //swap ticks
    int tempTicks = getWorld()->getPlayerTicks(1);
    getWorld()->changePlayerTicks(1, getWorld()->getPlayerTicks(2));
    getWorld()->changePlayerTicks(2, tempTicks);
    //swap moving direction
    int movingDir = getWorld()->getPlayerDirection(1);
    getWorld()->setPlayerDirection(1, getWorld()->getPlayerDirection(2));
    getWorld()->setPlayerDirection(2, movingDir);
    //swap sprite direction
    int spriteDir = getWorld()->getSpriteDirection(1);
    getWorld()->setSpriteDirection(1, getWorld()->getSpriteDirection(2));
    getWorld()->setSpriteDirection(2, spriteDir);
    //swap state
    bool rollState = getWorld()->getPlayerWaitingToRoll(1);
    getWorld()->setPlayerWaitingToRoll(1, getWorld()->getPlayerWaitingToRoll(2));
    getWorld()->setPlayerWaitingToRoll(2, rollState);
    //swap:
        /*
        i. x, y coordinates
        ii.the number of ticks left that the player has to move before
        completing their roll
        iii.the player's walk direction
        iv.the player's sprite direction
        v.the player's roll/walk state*/
 
}
//void Actor::swapPosition()
//{
//
//}
void Actor::swapStars()
{
    //swap stars
    int tempStars = 0;
    tempStars = getWorld()->getPlayerStars(1);
    getWorld()->setPlayerStars(1, getWorld()->getPlayerStars(2));
    getWorld()->setPlayerStars(2, tempStars);
}
void Actor::swapCoins()
{
    //swap coins
    int tempCoins = 0;
    tempCoins = getWorld()->getPlayerCoins(1);
    getWorld()->setPlayerCoins(1, getWorld()->getPlayerCoins(2));
    getWorld()->setPlayerCoins(2, tempCoins);
}

/*
void Actor::setTeleportStatus(bool teleportStatus)
{
    m_goTeleport = teleportStatus;
}
bool Actor::getTeleportStatus()
{
    return m_goTeleport;
}*/


Players::Players(StudentWorld* world, const int imageID, int startX, int startY, int ticks) 
//, int startDirection, int depth, double size)
    : Actor(world, imageID, startX, startY)// startDirection, depth, size),
    , /*ticks_to_move(ticks)*/ movingDirection(right) //, m_vortex(nullptr)
{
    //ticks_to_move = 0;
    //waiting_to_roll = true;
    //player_coins = 0;
    //m_dieRoll = 0;
    //movingDirection = right;
}
int Players::getMovingDirection()
{
    return movingDirection;
}
void Players::setMovingDirection(int dir)
{
    movingDirection = dir;
}

//void Players::setVortex(Vortex* vortex)
//{
//    //m_vortex = vortex;
//}

void Players::doSomething()
{
    if (getWaitingToRoll() == false)	//since waiting to roll is false, walking state is active
    {

        //C. if avatar can't coitinue moving in current direction
        //update avatar's walk direction so it can turn to face a new direction perpendicular to walking direction.

        //c.
        //do a is valid position function, in actor class, or do a is valid position in student world only
        //check if position is empty using studentworld's getContentsOF
        //only studentworld has access to board, so is empty should be in that

        //getX() provides pixels, so divide by 16 to get grid space!
        int gridX = getX() / SPRITE_WIDTH;
        int gridY = getY() / SPRITE_HEIGHT;
        //every tick you move 2 pixels, so 8 ticks you move 16 pixels, which is one square
        //each block is 16 pixels by 16 pixels
        if (getTicks() % 8 == 0)
            //if (getX() % 16 == 0 && getY() % 16 == 0)
        {
            setDieRoll(0);
            if (getMovingDirection() == right || getMovingDirection() == left)
            {
                if (isValidPos(getMovingDirection()) == false)
                {
                    //std::cerr << "Enter checking dir for up and down!" << std::endl;
                    std::cerr << gridX << " " << gridY << std::endl;

                    //code for preferred setDirection()
                    if (isValidPos(down) == true && isValidPos(up) == true)
                    {
                        //std::cerr << "change dir up!" << std::endl;
                        setMovingDirection(up);
                        setDirection(right);	//changes sprite direction
                    }
                    else if (isValidPos(up) == true)
                    {
                        //std::cerr << "change dir!" << std::endl;
                        setMovingDirection(up);
                        setDirection(right);
                    }
                    else if (isValidPos(down) == true)
                    {
                        //std::cerr << "change dir!" << std::endl;
                        setMovingDirection(down);
                        setDirection(right);
                    }

                }
            }
            //if going up or down
            else if (getMovingDirection() == up || getMovingDirection() == down)
            {
                if (isValidPos(getMovingDirection()) == false)
                {
                    //std::cerr << "Enter checking dir for right and left!" << std::endl;
                    std::cerr << gridX << " " << gridY << std::endl;

                    //code for preferred setDirection()
                    if (isValidPos(right) == true && isValidPos(left) == true)
                    {
                        //std::cerr << "change dir!" << std::endl;
                        setMovingDirection(right);
                        setDirection(right);
                    }
                    else if (isValidPos(right) == true)
                    {
                        //std::cerr << "change dir!" << std::endl;
                        setMovingDirection(right);
                        setDirection(right);
                    }
                    else if (isValidPos(left) == true)
                    {
                        //std::cerr << "change dir!" << std::endl;
                        setMovingDirection(left);
                        setDirection(left);
                    }
                }
            }
        }

        //moving in 2 pixels in direction
        moveAtAngle(getMovingDirection(), 2);
        //decrementing ticks, each iteration
        setTicks(0);

        if (getTicks() <= 0)
        {
            setWaitingToRoll(true);
        }
        return;
    }
}

Peach::Peach(StudentWorld* world, int startX, int startY)
    : Players(world, IID_PEACH, startX, startY, 0)
{    }
void Peach::doSomething()
{
    //should always pass in 1 to get action
    //int action = ->getAction(1)
    
    /*if (alive == true)
    {*/

    if (getWaitingToRoll() == true)
    {
        int die_roll;
        int action = getWorld()->getAction(1);
        switch (action)
        {
        case ACTION_RIGHT:
            //std::cerr << "move?" << std::endl;
            //change direction to right!
            setDirection(right);
            setMovingDirection(right);
            break;
        case ACTION_LEFT:
            setMovingDirection(left);
            break;
        case ACTION_UP:
            //setDirection(up);
            setMovingDirection(up);
            break;
        case ACTION_DOWN:
            //setDirection(down);
            setMovingDirection(down);
            break;
        case ACTION_ROLL:
            //1. change ticks_to_move = die_roll * 8;
            die_roll = randInt(1, 10);
            setDieRoll(die_roll);
            setTicks(die_roll);
            std::cerr << "Rolled " << die_roll << std::endl;
            //2. change avatar's state to walking state;
            setWaitingToRoll(false);	//sets waiting to roll to false, meaning move to walking state
            break;

        case ACTION_FIRE:
            //if (m_vortex == nullptr)
            //vortex = new vortex(this, getX, getY)
            
            ///Vortex* newVortex = new Vortex(this, getX(), getY());
            //getworld() -> add actor() ??
            break;

        default:
            return;	//nothing pressed, return?
        }
    }
    
    //Allows you to exeucte code from derived class
    Players::doSomething();
    getWorld()->getPeach()->setJustSwappedStatus(false);

    //KeyMap
    /*{ 'a', { 1, ACTION_LEFT } },
    { 'd',             { 1, ACTION_RIGHT } },
    { 'w',             { 1, ACTION_UP } },
    { 's',             { 1, ACTION_DOWN } },
    { KEY_PRESS_TAB,   { 1, ACTION_ROLL } },
    { '`',             { 1, ACTION_FIRE } },
    { KEY_PRESS_LEFT,  { 2, ACTION_LEFT } },
    { KEY_PRESS_RIGHT, { 2, ACTION_RIGHT } },
    { KEY_PRESS_UP,    { 2, ACTION_UP } },
    { KEY_PRESS_DOWN,  { 2, ACTION_DOWN } },
    { KEY_PRESS_ENTER, { 2, ACTION_ROLL } },
    { '\\',            { 2, ACTION_FIRE } },*/
    
    //if teleport flag is true, set player's flag in event square, teleport
}

Yoshi::Yoshi(StudentWorld* world, int startX, int startY)
    : Players(world, IID_YOSHI, startX, startY, 0)
{   }
void Yoshi::doSomething()
{
    if (getWaitingToRoll() == true)
    {
        int die_roll;
        int action = getWorld()->getAction(2);
        switch (action)
        {
        case ACTION_RIGHT:
            //std::cerr << "move?" << std::endl;
            //change direction to right!
            setDirection(right);
            setMovingDirection(right);
            break;
        case ACTION_LEFT:
            setMovingDirection(left);
            break;
        case ACTION_UP:
            //setDirection(up);
            setMovingDirection(up);
            break;
        case ACTION_DOWN:
            //setDirection(down);
            setMovingDirection(down);
            break;
        case ACTION_ROLL:
            //1. change ticks_to_move = die_roll * 8;
            die_roll = randInt(1, 10);
            setDieRoll(die_roll);
            setTicks(die_roll);
            std::cerr << "Rolled " << die_roll << std::endl;
            //2. change avatar's state to walking state;
            setWaitingToRoll(false);	//sets waiting to roll to false, meaning move to walking state
            break;

        case ACTION_FIRE:

        default:
            return;	//nothing pressed, return?
        }
    }
    Players::doSomething();
    //getWorld()->getYoshi()->setJustSwappedStatus(false);

}

Squares::Squares(StudentWorld* world, const int imageID, int startX, int startY, int startDirection, int depth)
    :Actor(world, imageID, startX, startY, startDirection, 1)
{   
    isPeachOnSquare = false;
    isYoshiOnSquare = false;
}
bool Squares::isOverlappingPeach(int& peachX, int& peachY, int objectX, int objectY)
{
    getWorld()->findPlayer(1, peachX, peachY);
    if (peachX == objectX && peachY == objectY)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//actor a actor b
//check overlap for vortex
//overlap(Actor* a, Actor* b){
 //if getxa==getxb && getya!=getyb
    //or/and? opposite

    //calling in another function
    //overlap(this, getPeach())     //"this" would be the class
    //a->getX();
//if callign this in vortex: this, bowser?

bool Squares::isOverlappingYoshi(int& yoshiX, int& yoshiY, int objectX, int objectY)
{
    getWorld()->findYoshi(yoshiX, yoshiY);
    if (yoshiX == objectX && yoshiY == objectY)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Squares::getIsImpactable()
{
    return false;
}
void Squares::setPeachOn(bool state)
{
    isPeachOnSquare = state;
}
void Squares::setYoshiOn(bool state)
{
    isYoshiOnSquare = state;
}
bool Squares::getPeachOn()
{
    return isPeachOnSquare;
}
bool Squares::getYoshiOn()
{
    return isYoshiOnSquare;
}

CoinSquare::CoinSquare(StudentWorld* world, const int imageID, int startX, int startY, std::string color)
    : Actor(world, imageID, startX, startY, 0, 1, 1.00), color(color) //, m_alive(true)
{
    m_PeachOnSquare = false;
    m_YoshiOnSquare = false;
}
void CoinSquare::deactivate()
{
    setAlive(false);
}
void CoinSquare::activate()
{
    setAlive(true);
}
void CoinSquare::doSomething()
{
    if (getColor() == "blue")
    {
        getBlueSquare();
    }
    if (getColor() == "red")
    {
        getRedSquare();
    }
}
void CoinSquare::getRedSquare()
{
    if (getAlive() == false)
    {
        return;
    }
    int peachX, peachY, yoshiX, yoshiY;

    getWorld()->findPeach(peachX, peachY);
    getWorld()->findYoshi(yoshiX, yoshiY);

    if (peachX == getX() && peachY == getY())
    {
        if (!m_PeachOnSquare)
        {
            if (getWorld()->getPlayerWaitingToRoll(1) == true)
            {
                getWorld()->deductPlayerCoins(1, 3);
                //std::cerr << peachX / 16 << " " << peachY / 16 << std::endl;
                std::cerr << "deduct coins " << std::endl;
                getWorld()->playSound(SOUND_TAKE_COIN);
            }
        }
        m_PeachOnSquare = true;
    }
    else
    {
        m_PeachOnSquare = false;
    }
    if (yoshiX == getX() && yoshiY == getY())
    {
        if (!m_YoshiOnSquare)
        {
            if (getWorld()->getPlayerWaitingToRoll(2) == true)
            {
                getWorld()->deductPlayerCoins(2, 3);
                std::cerr << "deduct coins " << std::endl;
                getWorld()->playSound(SOUND_TAKE_COIN);
            }
        }
        m_YoshiOnSquare = true;
    }
    else
    {
        m_YoshiOnSquare = false;
    }

    return;
}
void CoinSquare::getBlueSquare()
{
    //1. check if square is active
    if (getAlive() == false)
    {
        return;
    }
    int peachX, peachY, yoshiX, yoshiY;

    getWorld()->findPeach(peachX, peachY);
    getWorld()->findYoshi(yoshiX, yoshiY);

    if (peachX == getX() && peachY == getY())
    {
        if (!m_PeachOnSquare)
        {
            if (getWorld()->getPlayerWaitingToRoll(1) == true)
            {
                getWorld()->addPlayerCoins(1, 3);
                //std::cerr << peachX / 16 << " " << peachY / 16 << std::endl;
                //std::cerr << "add peach coins " << std::endl;
                getWorld()->playSound(SOUND_GIVE_COIN);
            }
        }
        m_PeachOnSquare = true;
    }
    else
    {
        m_PeachOnSquare = false;
    }

    if (yoshiX == getX() && yoshiY == getY())
    {
        if (!m_YoshiOnSquare)
        {
            if (getWorld()->getPlayerWaitingToRoll(2) == true)
            {
                getWorld()->addPlayerCoins(2, 3);
                //std::cerr << "add yoshi coins " << std::endl;
                getWorld()->playSound(SOUND_GIVE_COIN);
            }
        }
        m_YoshiOnSquare = true;
    }
    else
    {
        m_YoshiOnSquare = false;
    }

    return;
   
}

StarSquare::StarSquare(StudentWorld* world, int startX, int startY)
    : Squares(world, IID_STAR_SQUARE, startX, startY, 0, 1)
{   }
void StarSquare::doSomething()
{
    //Checking Peach
    int peachX, peachY, yoshiX, yoshiY;
    if (isOverlappingPeach(peachX, peachY, getX(), getY()))
    {
        if (!getPeachOn())
        {
            if (getWorld()->getPlayerCoins(1) < 20)
            {
                //return; do nothing
            }
            else
            {
                getWorld()->deductPlayerCoins(1, 20);
                getWorld()->addPlayerStars(1, 1);
                getWorld()->playSound(SOUND_GIVE_STAR);
            }
        }
        setPeachOn(true);
    }
    else
    {
        setPeachOn(false);
    }

    //Checking Yoshi
    if (isOverlappingYoshi(yoshiX, yoshiY, getX(), getY()))
    {
        if (!getYoshiOn())
        {
            if (getWorld()->getPlayerCoins(2) < 20)
            {
                //return; do nothing
            }
            else
            {
                getWorld()->deductPlayerCoins(2, 20);
                getWorld()->addPlayerStars(2, 1);
                getWorld()->playSound(SOUND_GIVE_STAR);

            }
        }
        setYoshiOn(true);
    }
    else
    {
        setYoshiOn(false);
    }
    return;
}

DirectionalSquares::DirectionalSquares(StudentWorld* world, int startX, int startY, int startdirection, int direction)// std::string direction)
    :Squares(world, IID_DIR_SQUARE, startX, startY, startdirection, 1), direction(direction)
{
    direction = 0;
}
void DirectionalSquares::forceDirection(int playerNum, int goDir)
{
    if (playerNum == 1)
    {
        getWorld()->setPlayerDirection(playerNum, goDir);

    }
    else
    {
        getWorld()->setPlayerDirection(playerNum, goDir);
    }
}
void DirectionalSquares::doSomething()
    {
    //
    int theDirection = getDirectionSquare();
    int peachX, peachY, yoshiX, yoshiY;
    if (isOverlappingPeach(peachX, peachY, getX(), getY()))
    {
        switch (theDirection)
        {
        case 1: //up
            forceDirection(1, 90);
            getWorld()->setSpriteDirection(1, 0);
            break;
        case 2: //right
            forceDirection(1, 0);
            getWorld()->setSpriteDirection(1, 0);
            break;
        case 3: //down
            forceDirection(1, 270);
            getWorld()->setSpriteDirection(1, 0);
            break;
        case 4: //left
            forceDirection(1, 180);
            getWorld()->setSpriteDirection(1, 180);
            break;
        default:
            break;
        }
    }

    if (isOverlappingYoshi(yoshiX, yoshiY, getX(), getY()))
    {

        //std::cerr << "yoshi check";
        switch (theDirection)
        {
        case 1: //up
            forceDirection(2, 90);
            getWorld()->setSpriteDirection(2, 0);
            break;
        case 2: //right
            forceDirection(2, 0);
            getWorld()->setSpriteDirection(2, 0);
            break;
        case 3: //down
            forceDirection(2, 270);
            getWorld()->setSpriteDirection(2, 0);
            break;
        case 4: //left
            forceDirection(2, 180);
            getWorld()->setSpriteDirection(2, 180);
            break;
        default:
            break;
        }
    }
}

BankSquares::BankSquares(StudentWorld* world, int startX, int startY)
    :Squares(world, IID_BANK_SQUARE, startX, startY, 0, 1)
{

}
void BankSquares::doSomething()
{
    //std::cerr << getWorld()->getBankCoins();
    int peachX, peachY, yoshiX, yoshiY;
    //Peach
    if (isOverlappingPeach(peachX, peachY, getX(), getY()) && getWorld()->getPlayerWaitingToRoll(1) == false)
    {
        int deductedCoins = 0;
        //check if player will go broke when deducting 5 coins
        if (getWorld()->getPlayerCoins(1) - 5 <= 0)
        {
            //std::cerr << "player is going broke" << std::endl;
            deductedCoins = getWorld()->getPlayerCoins(1);
            getWorld()->deductPlayerCoins(1, deductedCoins);
            getWorld()->changeBankCoins(1, deductedCoins);
            //std::cerr << "new bank total: " << getWorld()->getBankCoins() << std::endl;
            getWorld()->playSound(SOUND_DEPOSIT_BANK);
        }
        else
        {
            //std::cerr << "before added bank: " << getWorld()->getBankCoins() << std::endl;
            getWorld()->deductPlayerCoins(1, 5);
            //For bank function, 1 means add, any other number means deduct
            getWorld()->changeBankCoins(1, 5);
            //std::cerr << "added bank: " << getWorld()->getBankCoins() << std::endl;
            getWorld()->playSound(SOUND_DEPOSIT_BANK);
        }
    }
    else if (isOverlappingPeach(peachX, peachY, getX(), getY()))    //player landed on
    {
        if (!getPeachOn())
        {
            //std::cerr << "before deducted bank: " << getWorld()->getBankCoins() << std::endl;
            getWorld()->addPlayerCoins(1, getWorld()->getBankCoins());
            getWorld()->changeBankCoins(2, getWorld()->getBankCoins());
            //std::cerr << "deducted bank: " << getWorld()->getBankCoins() << std::endl;
            getWorld()->playSound(SOUND_WITHDRAW_BANK);
        }
        setPeachOn(true);
    }
    else
    {
        setPeachOn(false);
    }

    //Yoshi
    if (isOverlappingYoshi(yoshiX, yoshiY, getX(), getY()) && getWorld()->getPlayerWaitingToRoll(2) == false)
    {
        int deductedCoins = 0;
        if (getWorld()->getPlayerCoins(2) - 5 <= 0)
        {
            //std::cerr << "player is going broke" << std::endl;
            deductedCoins = getWorld()->getPlayerCoins(2);
            getWorld()->deductPlayerCoins(2, deductedCoins);
            getWorld()->changeBankCoins(1, deductedCoins);
            //std::cerr << "new bank total: " << getWorld()->getBankCoins() << std::endl;
            getWorld()->playSound(SOUND_DEPOSIT_BANK);
        }
        else
        {
            //std::cerr << "before added bank: " << getWorld()->getBankCoins() << std::endl;
            getWorld()->deductPlayerCoins(2, 5);
            //For bank function, 1 means add, any other number means deduct
            getWorld()->changeBankCoins(1, 5);
            //std::cerr << "added bank: " << getWorld()->getBankCoins() << std::endl;
            getWorld()->playSound(SOUND_DEPOSIT_BANK);
        }
    }
    else if (isOverlappingYoshi(yoshiX, yoshiY, getX(), getY()))
    {
        if (!getYoshiOn())
        {
            //std::cerr << "Yoshi coins: " << getWorld()->getPlayerCoins(2) << std::endl;
            //std::cerr << "before yoshi deducted bank: " << getWorld()->getBankCoins() << std::endl;
            //Deduct from bank, add to player
            getWorld()->addPlayerCoins(2, getWorld()->getBankCoins());
            getWorld()->changeBankCoins(2, getWorld()->getBankCoins());
            //std::cerr << "Yoshi new coins: " << getWorld()->getPlayerCoins(2) << std::endl;
            //std::cerr << "after yoshi stole bank: " << getWorld()->getBankCoins() << std::endl;
            getWorld()->playSound(SOUND_WITHDRAW_BANK);
        }
        setYoshiOn(true);
    }
    else
    {
        setYoshiOn(false);
    }
}
//reusing code?
//maybe create another function that is called in dosometing, that recerives player number


EventSquares::EventSquares(StudentWorld* world, int startX, int startY)
    :Squares(world, IID_EVENT_SQUARE, startX, startY, 0, 1)
{

}
void EventSquares::doSomething()
{
    //int randomAction = randInt(1, 2);

    int randomAction = 2;
    int peachX, peachY, yoshiX, yoshiY;
    if (isOverlappingPeach(peachX, peachY, getX(), getY()) && getWorld()->getPlayerWaitingToRoll(1) == true)
    {
        
        if (!getPeachOn() && getWorld()->getPeach()->getJustSwapped() == false)
        {
            std::cerr << "in event: " << std::endl;
            //int randomAction = randInt(1, 1);
            std::cerr << randomAction << std::endl;
                //option 1: teleported to random spot on board
            if (randomAction == 1)
            {
                std::cerr << "teleport " << std::endl;
                //getWorld()->setTeleport(1, true);
                getWorld()->teleportPlayer(1);
                getWorld()->playSound(SOUND_PLAYER_TELEPORT);
            }
            if (randomAction == 2)
            {
                std::cerr << "swap" << std::endl;
                swap();
            }
            if (randomAction == 3)
            {

            }
        }
        setPeachOn(true);
        getWorld()->getPeach()->setJustSwappedStatus(true);
    }
    else
    {
        getWorld()->getPeach()->setJustSwappedStatus(false);
        setPeachOn(false);
    }
    if (isOverlappingYoshi(yoshiX, yoshiY, getX(), getY()) && getWorld()->getPlayerWaitingToRoll(2) == true)
    {
        if (!getYoshiOn() && getWorld()->getYoshi()->getJustSwapped() == false)
        {
            if (randomAction == 1)
            {
                std::cerr << "teleport yoshi" << std::endl;
                //getWorld()->setTeleport(1, true);
                getWorld()->teleportPlayer(2);
                getWorld()->playSound(SOUND_PLAYER_TELEPORT);
            }
            if (randomAction == 2)
            {
                swap();
                std::cerr << "swap " << std::endl;
            }
            if (randomAction == 3)
            {

            }
        }
        
        setYoshiOn(true);
        getWorld()->getYoshi()->setJustSwappedStatus(true);
    }
    else
    {
        setYoshiOn(false);
        getWorld()->getYoshi()->setJustSwappedStatus(false);
    }

    //option 2: swap position and movement state with another player.
    //option 3: give player a vortex projectile
}

DroppingSquares::DroppingSquares(StudentWorld* world, int startX, int startY)
    :Squares(world, IID_DROPPING_SQUARE, startX, startY, 0, 1)
{   }
//Bowser creates this dropping square, and passes in the x and y when constructing this.
void DroppingSquares::doSomething()
{
    int randomAction = randInt(1, 2);
    int peachX, peachY, yoshiX, yoshiY;
    //Peach
    if (isOverlappingPeach(peachX, peachY, getX(), getY()) && getWorld()->getPlayerWaitingToRoll(1) == false)
    {
        if (randomAction == 1)
        {
            //option 1: deduct 10 coins
            if (getWorld()->getPlayerCoins(1) - 10 <= 0)
            {
                //std::cerr << "player is going broke" << std::endl;
                getWorld()->deductPlayerCoins(1, getWorld()->getPlayerCoins(1));
                getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
            }
            else
            {
                getWorld()->deductPlayerCoins(1, 10);
                getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
            }
        }
        else
        {
            if (getWorld()->getPlayerStars(1) - 10 <= 0)
            {
                getWorld()->deductPlayerStars(1, getWorld()->getPlayerStars(1));
                getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
            }
            else
            {
                getWorld()->deductPlayerStars(1, 1);
                getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
            }
        }
    }

    if (isOverlappingYoshi(yoshiX, yoshiY, getX(), getY()) && getWorld()->getPlayerWaitingToRoll(1) == false)
    {
        if (randomAction == 1)
        {
            //option 1: deduct 10 coins
            if (getWorld()->getPlayerCoins(2) - 10 <= 0)
            {
                //std::cerr << "player is going broke" << std::endl;
                getWorld()->deductPlayerCoins(2, getWorld()->getPlayerCoins(2));
                getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
            }
            else
            {
                getWorld()->deductPlayerCoins(2, 10);
                getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
            }
        }
        else
        {
            if (getWorld()->getPlayerStars(2) - 10 <= 0)
            {
                getWorld()->deductPlayerStars(2, getWorld()->getPlayerStars(2));
                getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
            }
            else
            {
                getWorld()->deductPlayerStars(2, 1);
                getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
            }
        }
    }
}


Vortex::Vortex(StudentWorld* world, int startX, int startY)
    :Actor(world, IID_VORTEX, startX, startY, 0, 0)
{
    //starts out in active state?
    activeState = true;
}
//vector<Actor*> Vortex::activate();
bool Vortex::isActiveState()
{
    return activeState;
}
void Vortex::doSomething()
{

}