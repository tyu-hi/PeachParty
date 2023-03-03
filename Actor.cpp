#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
#include <list>

//Actor
Actor::Actor(StudentWorld* world, const int imageID, int startX, int startY, int startDirection, int depth, double size)
    : GraphObject(imageID, startX, startY, startDirection, depth, 1), m_dieRoll(0), ticks_to_move(0), waiting_to_roll(true)
        , m_alive(true), m_playerCoins(0), m_playerStars(0)//, ticks_to_move(ticks)
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
    if (m_world->isEmpty(dir, xNew / SPRITE_WIDTH, yNew / SPRITE_HEIGHT) == true)	
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

Players::Players(StudentWorld* world, const int imageID, int startX, int startY, int ticks) 
//, int startDirection, int depth, double size)
    : Actor(world, imageID, startX, startY)// startDirection, depth, size),
    , /*ticks_to_move(ticks)*/ movingDirection(right)
{
    //ticks_to_move = 0;
    //waiting_to_roll = true;
    //player_coins = 0;
    //m_dieRoll = 0;
    //movingDirection = right;
}
//bool Players::getWaitingToRoll()
//{
//    return waiting_to_roll;
//}

//int Players::getTicks()
//{
//    //std::cerr << "ticks: " << ticks_to_move << std::endl;
//    return ticks_to_move;
//}
//void Players::setTicks(int dieRoll)
//{
//    if (dieRoll > 0)
//    {
//        ticks_to_move = dieRoll * 8;
//        //std::cerr << "new ticks: " << ticks_to_move << std::endl;
//        //return ticks_to_move;
//    }
//    else if (dieRoll == 0 && ticks_to_move > 0)
//    {
//        //std::cerr << "new decremented ticks: " << ticks_to_move << std::endl;
//        ticks_to_move--;
//    }
//    else
//    {
//        ticks_to_move = 0;
//    }
//}
//void Players::setWaitingToRoll(bool value)
//{
//    waiting_to_roll = value;
//}
int Players::getMovingDirection()
{
    return movingDirection;
}
void Players::setMovingDirection(int dir)
{
    movingDirection = dir;
}
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

        default:
            return;	//nothing pressed, return?
        }
    }
    
    //Allows you to exeucte code from derived class
    Players::doSomething();

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
    else if (isOverlappingPeach(peachX, peachY, getX(), getY()))
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
            std::cerr << "Yoshi coins: " << getWorld()->getPlayerCoins(2) << std::endl;
            std::cerr << "before yoshi deducted bank: " << getWorld()->getBankCoins() << std::endl;
            //Deduct from bank, add to player
            getWorld()->addPlayerCoins(2, getWorld()->getBankCoins());
            getWorld()->changeBankCoins(2, getWorld()->getBankCoins());
            //std::cerr << "deducted bank: " << getWorld()->getBankCoins() << std::endl;
            std::cerr << "Yoshi new coins: " << getWorld()->getPlayerCoins(2) << std::endl;
            std::cerr << "after yoshi stole bank: " << getWorld()->getBankCoins() << std::endl;
            getWorld()->playSound(SOUND_WITHDRAW_BANK);
        }
        setYoshiOn(true);
    }
    else
    {
        setYoshiOn(false);
    }
}
