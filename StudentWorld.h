#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include <string>


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

//added
#include "Actor.h"
#include <list>

class StudentWorld : public GameWorld

//GameWorld has these functions:
/*void setGameStatText(string text);
bool getAction(int playerNum);
void playSound(int soundID);
int getBoardNumber() const;
void setFinalScore(int stars, int coins);
void startCountDownTimer(int numSeconds);
int timeRemaining() const;
string assetPath() const;*/

{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();

  //Used for checking is valid position in Actor
  bool isEmpty(int chkX, int chkY);

  //Find player
  //void findPeach(/*Actor* player, */int& playerX, int& playerY);
  //void findPlayer(int player_num, int& playerX, int& playerY);
  //void findYoshi(/*Actor* player, */int& playerX, int& playerY);
  
  Actor* getPeach()
  {
      return m_peach;
  }
  Actor* getYoshi()
  {
      return m_yoshi;
  }

  //Player Coins
  void deductPlayerCoins(int player_num, int coins)
  {
      if (player_num == 1)
      {
          m_peach->deductCoins(coins);
      }
      else
          m_yoshi->deductCoins(coins);
  }
  void addPlayerCoins(int player_num, int coins)
  {
      if (player_num == 1)
      {
          m_peach->addCoins(coins);
      }
      else
      {
          m_yoshi->addCoins(coins);
      }
  }
  int getPlayerCoins(int player_num)
  {
      if (player_num == 1)
      {
          return m_peach->getCoins();
      }
      else
      {
          return m_yoshi->getCoins();
      }
  }
  void setPlayerCoins(int player_num, int coins)
  {
      if (player_num == 1)
      {
          m_peach->setCoins(coins);
      }
      else
      {
          m_yoshi->setCoins(coins);
      }
  }
  //Stars
  void addPlayerStars(int player_num, int stars)
  {
      if (player_num == 1)
      {
          m_peach->addStars(stars);
      }
      else
      {
          m_yoshi->addStars(stars);
      }
  }
  void deductPlayerStars(int player_num, int stars)
  {
      if (player_num == 1)
      {
          m_peach->deductStars(stars);
      }
      else
      {
          m_yoshi->deductStars(stars);
      }
  }
  int getPlayerStars(int player_num)
  {
      if (player_num == 1)
      {
          return m_peach->getStars();
      }
      else
      {
          return m_yoshi->getStars();
      }
  }
  void setPlayerStars(int player_num, int stars)
  {
      if (player_num == 1)
      {
          m_peach->setStars(stars);
      }
      else
      {
          m_yoshi->setStars(stars);
      }
  }

  //Teleport in Event Square
  void teleportPlayer(int playerNum)
  {
      bool isOn = false;
      while (isOn == false)
      {
     /* for (;;)
      {*/
          int newX, newY;

          newX = randInt(0, BOARD_WIDTH - 1);
          newY = randInt(0, BOARD_HEIGHT - 1);
          std::list<Actor*>::iterator p;
          for (p = actor.begin(); p != actor.end(); p++)
          {
              Actor* temp = *p;
              if (temp->getIsImpactable() == false && gameBoard.getContentsOf(newX, newY) != Board::empty)
              {
                  if (playerNum == 1)
                  {
                      m_peach->moveTo(newX * SPRITE_HEIGHT, newY * SPRITE_WIDTH);
                      //m_peach->setNewLocationY(newY);
                  }
                  else
                  {
                      m_yoshi->moveTo(newX * SPRITE_HEIGHT, newY * SPRITE_WIDTH);
                  }
                  isOn = true;
              }
          }
      }   
      isOn = false;
  }
  //Teleport Player
  //void movePlayer(int player_num, int playerX, int playerY)
  //{
  //    if (player_num == 1)
  //    {
  //        m_peach->moveTo(playerX, playerY);
  //    }
  //    else
  //    {
  //        m_yoshi->moveTo(playerX, playerY);
  //    }
  //}

  //Is a Square
  bool isOnASquare(int objectX, int objectY)
  {
      std::list<Actor*>::iterator p;
      for (p = actor.begin(); p != actor.end(); p++)
      {
          Actor* temp = *p;
          if (temp->getX() == objectX && temp->getY() == objectY)
          {
              if (temp->getIsImpactable() == false) //if not impactable, == square
              {
                  //std::cerr << " on a square " << std::endl;
                  return true;
              }
              //return true;
          }
      }
      return false;
  }
  

  //waitingToRoll
  bool getPlayerWaitingToRoll(int player_num)
  {
      if (player_num == 1)
      {
          return m_peach->getWaitingToRoll();
      }
      else
      {
          return m_yoshi->getWaitingToRoll();
      }
  }
  void setPlayerWaitingToRoll(int player_num, bool value)
  {
      if (player_num == 1)
      {
          return m_peach->setWaitingToRoll(value);
      }
      else
      {
          return m_yoshi->setWaitingToRoll(value);
      }
  }
  //Player Ticks
  int getPlayerTicks(int player_num)
  {
      if (player_num == 1)
      {
          return m_peach->getTicks();

      }
      else
      {
          return m_yoshi->getTicks();
      }
  }
  void changePlayerTicks(int player_num, int ticks)
  {
      if (player_num == 1)
      {
          m_peach->setPlayerTicks(ticks);
      }
      else
      {
          m_yoshi->setPlayerTicks(ticks);
      }
  }
  //Moving Direction of Player
  int getPlayerDirection(int player_num)
  {
      if (player_num == 1)
      {
          return m_peach->getMovingDirection();
      }
      else
      {
          return m_yoshi->getMovingDirection();
      }
  }
  void setPlayerDirection(int player_num, int dir)
  {
      if (player_num == 1)
      {
          m_peach->setMovingDirection(dir);
      }
      else
      {
          m_yoshi->setMovingDirection(dir);
      }
  }
  //Sprite Direction of Player
  void setSpriteDirection(int player_num, int dir)
  {
      if (player_num == 1)
      {
          m_peach->setDirection(dir);
      }
      else
      {
          m_yoshi->setDirection(dir);
      }
  }
  int getSpriteDirection(int player_num)
  {
      if (player_num == 1)
      {
          return m_peach->getDirection();
      }
      else
      {
          return m_yoshi->getDirection();
      }
  }
  
  //Make Teleport
 /* void setTeleport(int player_num, bool state)
  {
      if (player_num == 1)
      {
          m_peach->setTeleportStatus(state);
      }
      else
      {
          m_yoshi->setTeleportStatus(state);
      }
  }*/

  //Destructor
  virtual ~StudentWorld()
  {
      cleanUp();
  }

  //Bank Coins
  void changeBankCoins(int change, int coins)
  {
      if (change == 1)
      {
          m_bankCoins += coins;
      }
      else
      {
          m_bankCoins -= coins;
      }
  }
  int getBankCoins()
  {
      if (m_bankCoins <= 0)
      {
          m_bankCoins = 0;
      }
      return m_bankCoins;
  }

private:
   //It is required that you keep track of all of the actor
   //objects in a single STL collection(e.g., a list, set, or vector).To do so, we recommend
   //using a container of pointers to the actors.
    std::list<Actor*> actor;
    
    //Bank Coins
    int m_bankCoins;
    
    //create seperate pointers for peach and yoshi
    Peach* m_peach;
    Yoshi* m_yoshi;

    //a member of Board so we can access Board information
    Board gameBoard;

    int m_peachCoins;
    int m_yoshiCoins;

    //bool waiting_to_roll;
    //int m_dieRoll;
};

#endif // STUDENTWORLD_H_
