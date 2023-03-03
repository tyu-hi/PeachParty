#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

//reference STudentWorld
class StudentWorld;

//Peach, Yoshi, Coin Square, Star Squares, Directional Squares, Bank Squares
//Event Squares, Dropping Squares, Boo, Bowser, Vortexes
class Actor : public GraphObject
{
	//constructor
	//doSomething()
	//etc... as you see fit
	
	//GraphObject(int imageID, double startX, double startY, int startDirection = right, int depth = 0, double size = 1.0);
	//int getX() const; // in pixels (0-255)
	//int getY() const; // in pixels (0-255)
	//void moveTo(int x, int y); // in pixels (0-255)
	//int getDirection() const; // sprite angle in degrees (0-359)
	//void setDirection(Direction d); // sprite angle in degrees (0-359)
	//void getPositionInThisDirection(int angle, int distance, int& newX, int& newY) const;
	//void moveAtAngle(int angle, int distance);

	//what player avatar object must do when it is created
	//what player avatar must do during a tick
	//what player avatar must do in other circusmtances


public:
	Actor(StudentWorld* world, const int imageID, int startX, int startY, int startDirection = right, int depth = 0, double size = 1);
	virtual ~Actor();
	virtual void doSomething() = 0;
	virtual bool isValidPos(int dir); 
	//, int xDir, int yDir);
	//void addPCoins(int coins)
	//{
	//	m_peachCoins += coins;
	//}
	//void deductPeachCoins(int coins)
	//{
	//	m_peachCoins -= coins;
	//}
	//int getPeachCoins()
	//{
	//	return m_peachCoins;
	//}
	////Yoshi
	//void addYoshiCoins(int coins)
	//{
	//	m_yoshiCoins += coins;
	//}
	//void deductYoshiCoins(int coins)
	//{
	//	m_yoshiCoins -= coins;
	//}
	//int getYoshiCoins()
	//{
	//	return m_yoshiCoins;
	//}
	//int getCoins()
	//{
	//	return m_playerCoins;
	//}

	//Coins
	void addCoins(int coins)
	{
		m_playerCoins += coins;
	}
	void deductCoins(int coins)
	{
		m_playerCoins -= coins;
	}
	int getCoins()
	{
		if (m_playerCoins <= 0)
		{
			m_playerCoins = 0;
		}
		return m_playerCoins;
	}
	int setCoins(int coins)
	{
		m_playerCoins = coins;
	}

	//Stars
	int getStars()
	{
		if (m_playerStars <= 0)
		{
			m_playerStars = 0;
		}
		return m_playerStars;
	}
	void addStars(int stars)
	{
		m_playerStars += stars;
	}

	//Ticks
	int getTicks()
	{
		return ticks_to_move;
	}
	void setTicks(int dieRoll)
	{
		if (dieRoll > 0)
		{
			ticks_to_move = dieRoll * 8;
			//std::cerr << "new ticks: " << ticks_to_move << std::endl;
			//return ticks_to_move;
		}
		else if (dieRoll == 0 && ticks_to_move > 0)
		{
			//std::cerr << "new decremented ticks: " << ticks_to_move << std::endl;
			ticks_to_move--;
		}
		else
		{
			ticks_to_move = 0;
		}
	}
	
	//Alive Status
	void setAlive(bool state)
	{
		m_alive = state;
	}
	bool getAlive() const
	{
		return m_alive;
	}

	//WaitingToRoll State
	bool getWaitingToRoll()
	{
		return waiting_to_roll;
	}
	void setWaitingToRoll(bool value)
	{
		waiting_to_roll = value;
	}

	//DieRoll
	void setDieRoll(int die_roll)
	{
		if (die_roll > 0)
		{
			m_dieRoll = die_roll;
		}
		else
		{
			m_dieRoll--;
		}
	}
	int getDieRoll()
	{
		//std::cerr << m_dieRoll << std::endl;
		return m_dieRoll;
	}


	//Pointer to StudentWorld
	StudentWorld* getWorld();


	//make listoof common stuff
	//print blue coin square first on board

private:
	StudentWorld* m_world;
	bool m_alive;
	int ticks_to_move;
	bool waiting_to_roll;
	int m_dieRoll;

	int m_playerCoins;
	int m_playerStars;
};


//Players //-> perhaps create another base class here - done
class Players : public Actor
{
public:
	Players(StudentWorld* world, const int imageID, int startX, int startY, int ticks);

	virtual int getMovingDirection();
	virtual void setMovingDirection(int dir);

	virtual void doSomething();
	
private:
	int movingDirection; //right = 0 from graphobject
	
};

class Peach : public Players	
{
public:
	Peach(StudentWorld* world, int startX, int startY);
	virtual void doSomething();

private:
	
};
class Yoshi : public Players
{
public:
	Yoshi(StudentWorld* world, int startX, int startY);
	virtual void doSomething();
};

//Baddies -> perhaps create another base class here
class Baddie :public Actor
{
public:
	Baddie(StudentWorld* world, const int imageID, int startX, int startY)
		:Actor(world, imageID, startX, startY)
	{

	}
	virtual void walkingState() {};
	virtual void pausedState() {};
};
class Bowser : public Baddie
{
public:
	Bowser(StudentWorld* world, int startX, int startY)
		:Baddie(world, IID_BOWSER, startX, startY)
	{

	}
	virtual void doSomething() {};
};
class Boo : public Baddie
{
public:
	Boo(StudentWorld* world, int startX, int startY)
		:Baddie(world, IID_BOO, startX, startY)
	{

	}
	virtual void doSomething() {};
};

//Squares
class CoinSquare : public Actor	///change to squares subclass later?
{
	//use good object-oriented programming style!
public:
	CoinSquare(StudentWorld* world, const int imageID, int startX, int startY, std::string color);
	//Hint: You may want your Coin Square, or one of its base classes, to have an
	/*"alive" flag that indicates whether it's still capable of being activated (since
	Bowser can convert a Coin Square into a Dropping Square, necessitating
	destruction of the Coin Squareand removal from the StudentWorld's actor
	container).*/

	std::string getColor()
	{
		return color;
	}
	virtual void deactivate();
	virtual void activate();
	void getBlueSquare();
	void getRedSquare();
	virtual void doSomething();

private:
	std::string color;
	bool m_PeachOnSquare;
	bool m_YoshiOnSquare;
};

class Squares :public Actor
{
public:
	Squares(StudentWorld* world, const int imageID, int startX, int startY, int startDirection, int depth);
	bool isOverlappinggPeach(int& peachX, int& peachY, int objectX, int objectY);
	bool isOverLappingYoshi(int& yoshiX, int& yoshiY, int objectX, int objectY);
	void setPeachOn(bool state);
	bool getPeachOn();
	void setYoshiOn(bool state);
	bool getYoshiOn();
private:
	bool isPeachOnSquare;
	bool isYoshiOnSquare;
};
class StarSquare : public Squares
{
public:
	StarSquare(StudentWorld* world, int startX, int startY);
	virtual void doSomething();
	//bool isOverlapping(int& peachX, int& peachY, int x, int y);
};
class DirectionalSquares : public Squares
{
public:
	DirectionalSquares(StudentWorld* world, int startX, int startY, int startdirection, int direction);
	int getDirectionSquare()
	{
		return direction;
		//1 == up, 2 == right, 3 == down, 4 == left
	}
	void forceDirection(int playerNum, int goDir);
	virtual void doSomething();
private:
	int direction;

};


class BankSquares : public Squares
{
public:
	BankSquares(StudentWorld* world, int startX, int startY)
		:Squares(world, IID_BANK_SQUARE, startX, startY, 0, 1)
	{

	}
	virtual void doSomething() {};
};
class EventSquares : public Squares
{
	public:
		EventSquares(StudentWorld* world, int startX, int startY)
			:Squares(world, IID_EVENT_SQUARE, startX, startY, 0, 1)
		{

		}
		virtual void doSomething() {};
};
class DroppingSquares : public Squares
{
public:
	DroppingSquares(StudentWorld* world, int startX, int startY)
		:Squares(world, IID_DROPPING_SQUARE, startX, startY, 0, 1)
	{

	}
	virtual void doSomething() {};

};
class Vortexes : public Actor
{

};

#endif // ACTOR_H
