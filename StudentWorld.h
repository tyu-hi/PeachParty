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

  //added:
  bool isEmpty(int dir, int chkX, int chkY);

  void findPeach(/*Actor* player, */int& playerX, int& playerY);
  void findYoshi(/*Actor* player, */int& playerX, int& playerY);
  //PeachCoins
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
          m_yoshi->addCoins(3);
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
  //Direction of Player
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

  //Destructor
  virtual ~StudentWorld()
  {
      cleanUp();
  }

  /*std::list<Actor*> getActors() const
  {
      std::list<Actor*> getActors;
      for (auto p = actor.begin(); p != actor.end(); p++)
      {
          if ((*p)->getAlive())
          {
              getActors.push_back(*p);
          }
         
      }
      return getActors;
  }*/


private:
   //It is required that you keep track of all of the actor
   //objects in a single STL collection(e.g., a list, set, or vector).To do so, we recommend
   //using a container of pointers to the actors.
    std::list<Actor*> actor;
    
    
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
