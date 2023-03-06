#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>

using namespace std;
#include <list>
#include "Actor.h"
#include <sstream>

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
    : GameWorld(assetPath), m_peachCoins(0), m_yoshiCoins(0)
{
    //if i initailize this, i crash!
    /*m_peach = nullptr;
    m_yoshi = nullptr;*/


    //actor.clear();
}
int StudentWorld::init()
{
	//startCountdownTimer(5);  // this placeholder causes timeout after 5 seconds
    //return GWSTATUS_CONTINUE_GAME;

    //It is required that you keep track of all of the actor
    //objects in a single STL collection(e.g., a list, set, or vector).To do so, we recommend
    //using a container of pointers to the actors.

    //load the board data file in using
    //    the Board class, and then determine where each "actor" (player, square and baddie) is
    //    supposed to be on the board.Then you'll create objects corresponding to each of these
    //    actors indicated in the board data files
    string board_file;
    int boardNum = getBoardNumber();
    switch (boardNum)
    {
    case 1:
        board_file = assetPath() + "board01.txt";
        break;
    case 2:
        board_file = assetPath() + "board02.txt";
        break;
    case 3:
        board_file = assetPath() + "board03.txt";
        break;
    case 4:
        board_file = assetPath() + "board04.txt";
        break;
    case 5:
        board_file = assetPath() + "board05.txt";
        break;
    case 6:
        board_file = assetPath() + "board06.txt";
        break;
    case 7:
        board_file = assetPath() + "board07.txt";
        break;
    case 8:
        board_file = assetPath() + "board08.txt";
        break;
    case 9:
        board_file = assetPath() + "board09.txt";
        break;
    default:
        break;
    }

   // string board_file = assetPath() + "board01.txt";        //board 1 right now!!
    //+ "board0" << number << ".txt"        //get boardnumber -> using GameWorld function
    Board::LoadResult result = gameBoard.loadBoard(board_file);
    std::cerr << result << std::endl;

    if (result == Board::load_fail_file_not_found)
        cerr << "Could not find board01.txt data file\n";
    else if (result == Board::load_fail_bad_format)
        cerr << "Your board was improperly formatted\n";
    else if (result == Board::load_success) {
        cerr << "Successfully loaded board\n";
        
        //board info
        //x is rows, y is columns
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            for (int y = 0; y < BOARD_HEIGHT; y++)
            {
                Board::GridEntry ge = gameBoard.getContentsOf(x, y);    //get what symbol is at that position
                int boardY = SPRITE_HEIGHT * y;
                int boardX = SPRITE_WIDTH * x;
                // update grid data structure by dynamically allocating each class object
                switch (ge)
                {
                case Board::empty:
                {
                    break;
                }
                case Board::player:
                {
                    //cerr << "Peach Location: " << x << ", " << y << endl;
                    if (m_peach != nullptr)
                        m_peach = new Peach(this, boardX, boardY);

                   
                    if (m_yoshi != nullptr)
                        m_yoshi = new Yoshi(this, boardX, boardY);
                    
                    //The starting position of players has a blue square
                    //actor.push_back(new BlueSquare(this, boardX, boardY));
                    actor.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, boardX, boardY, "blue"));
                    break;
                }
                case Board::blue_coin_square:
                {
                    //cerr << "Blue Square Location: " << x << ", " << y << endl;
                    actor.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, boardX, boardY, "blue"));
                    //actor.push_back(new BlueSquare(this, boardX, boardY));
                    break;
                }
                case Board::red_coin_square:
                {
                    //actor.push_back(new RedSquare(this, boardX, boardY));
                    actor.push_back(new CoinSquare(this, IID_RED_COIN_SQUARE, boardX, boardY, "red"));
                    break;
                }
                case Board::left_dir_square:
                {
                    actor.push_back(new DirectionalSquares(this, boardX, boardY, 180, 4));
                    break;
                }
                case Board::right_dir_square:
                {
                    actor.push_back(new DirectionalSquares(this, boardX, boardY, 0, 2));
                    break;
                }
                case Board::up_dir_square:
                {
                    actor.push_back(new DirectionalSquares(this, boardX, boardY, 90, 1));
                    break;
                }
                case Board::down_dir_square:
                {
                    actor.push_back(new DirectionalSquares(this, boardX, boardY, 270, 3));
                    break;
                }
                case Board::event_square:
                {
                    actor.push_back(new EventSquares(this, boardX, boardY));
                    break;
                }
                case Board::star_square:
                {
                    actor.push_back(new StarSquare(this, boardX, boardY));
                    break;
                }
                case Board::bank_square:
                {
                    actor.push_back(new BankSquares(this, boardX, boardY));
                    break;
                }
                case Board::bowser:
                {
                    actor.push_back(new Bowser(this, boardX, boardY));
                    actor.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, boardX, boardY, "blue"));
                    break;
                }
                case Board::boo:
                {
                    actor.push_back(new Boo(this, boardX, boardY));
                    actor.push_back(new CoinSquare(this, IID_BLUE_COIN_SQUARE, boardX, boardY, "blue"));
                    break;
                }
               
                }
            }
        }
    }
   
    startCountdownTimer(99);
    return GWSTATUS_CONTINUE_GAME;

    //Board::corresponding object

}

int StudentWorld::move()
{
    //2. ask actors currently active in game world to do something
    m_peach->doSomething();
    m_yoshi->doSomething();

    //use iterators to traverse using for loop, for list template, for each object
    list<Actor*>::iterator p;
    p = actor.begin();
    for (p = actor.begin(); p != actor.end(); p++)
    {
        Actor* temp = *p;
        temp->doSomething();
    }


    //3. delete any actors that have become inactive/dead during this tick


    //4. update status text on top of screen with latest information
    ostringstream statsBoard;
    statsBoard.fill('0');
    statsBoard  << "P1 Roll: " << m_peach->getDieRoll() << " Stars: " << m_peach->getStars() << " $$: " << m_peach->getCoins() 
                << " VOR"
                << " | Time: " << timeRemaining()
                << " | Bank: " << getBankCoins() << " | "
                << "P2 Roll: " << m_yoshi->getDieRoll() << " Stars: " << m_yoshi->getStars() << " $$: " << m_yoshi->getCoins() 
                << " VOR";     //check if there is VOR!!!!!!

    string stats = statsBoard.str();
    setGameStatText(stats);
    
    //1. if time is run out, return winner                      THIS DOES NOT WORK???  --> works!
    if (timeRemaining() <= 0)
    {
        playSound(SOUND_GAME_FINISHED);
        //If based on more stars
        if (m_yoshi->getStars() > m_peach->getStars())
        {
            //Yoshi Won

            std::cerr << "yoshi stars " << std::endl;
            setFinalScore(m_yoshi->getStars(), m_yoshi->getCoins());
            return GWSTATUS_YOSHI_WON;
        }
        else if (m_peach->getStars() > m_yoshi->getStars())
        {
            //Peach Won
            setFinalScore(m_peach->getStars(), m_peach->getCoins());
            return GWSTATUS_PEACH_WON;
        }
        //If based on more coins
        if (m_yoshi->getStars() == m_peach->getStars())
        {
            if (m_yoshi->getCoins() > m_peach->getCoins())
            {

                std::cerr << "yoshi coins " << std::endl;
                //Yoshi Won
                setFinalScore(m_yoshi->getStars(), m_yoshi->getCoins());
                return GWSTATUS_YOSHI_WON;
            }
            else
            {
                //Peach Won
                setFinalScore(m_peach->getStars(), m_peach->getCoins());
                return GWSTATUS_PEACH_WON;
            }   
        }
        //If game was tie with both players having equal coins and stars, pick winner randomly
        else
        {
            int randomWinner = randInt(1, 2);
            if (randomWinner == 1)
            {
                std::cerr << "yoshi tie" << std::endl;
                setFinalScore(m_peach->getStars(), m_peach->getCoins());
                return GWSTATUS_PEACH_WON;
            }
            else
            {
                setFinalScore(m_yoshi->getStars(), m_yoshi->getCoins());
                return GWSTATUS_YOSHI_WON;
            }
        }
    }
    
  
    //5. if game is not over, return this, which calls move() again
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    //use iterator to loop through list and delete

    list<Actor*>::iterator p;
    for (p = actor.begin(); p != actor.end(); p++)
    {
        Actor* temp = *p;
        delete temp;
    }
    //what does this do?
    actor.clear();

    //what does erase do?
    //actor.erase(actor.begin(), actor.end());

    //should i create one variable for players, rather than m_peach, m_yoshi?
    delete m_peach; //check!
    m_peach = nullptr;

    delete m_yoshi;
    m_yoshi = nullptr;
}

bool StudentWorld::isEmpty(int chkX, int chkY)
{
    //create board object in student world
    //getContentsOf is in grid form
    if (gameBoard.getContentsOf(chkX, chkY) == Board::empty)
    {
        //if contents in that position is empty, then isEmpty returns true;
        return true;
    }
    else
    {
        return false;
    }

}

//void StudentWorld::findPeach(/*Actor* player, */int& playerX, int& playerY)
//{
//    playerX = m_peach->getX();
//    playerY = m_peach->getY();
//    
//}
//void StudentWorld::findPlayer(int player_num, int& playerX, int& playerY)
//{
//    if (player_num == 1)
//    {
//        playerX = m_peach->getX();
//        playerY = m_peach->getY();
//    }
//    else
//    {
//        playerX = m_yoshi->getX();
//        playerY = m_yoshi->getY();
//    }
//}
//void StudentWorld::findYoshi(/*Actor* player, */int& playerX, int& playerY)
//{
//    playerX = m_yoshi->getX();
//    playerY = m_yoshi->getY();
//}
