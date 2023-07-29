#include "dice.h"
#include <memory> // Include the memory header for shared_ptr

class YahtzeeGame
{

    public:
        YahtzeeGame();
        ~YahtzeeGame();
        void rollDice(int i);
        void clickDie(int i);
        bool checkGameOver();
        int  getRolls();
        void setRolls(int inputRolls);
        int* bubbleSort();
        int* bubbleSort2(int* values);
        bool enterScore(int row, int col);

        bool checkTopSection(int row, int col);
        bool checkThreeOfaKind(int col);
        bool checkFourOfaKind(int col);
        bool checkFullHouse(int col);
        bool checkSmallStraight(int col);
        bool checkLargeStraight(int col);
        bool checkChance(int col);
        bool checkYahtzee(int col);
        void checkYahtzeeBonus(int col);
        bool checkTopFill ();
        void clearPad();

        void totalUp();
        int  getGrandTotal();

        Dice* getDiceArrayPtr(int slot);
        int   getYahtzeePad(int row, int col);

        

        //void newGame();
        //int totalUpTop();
        //int totalUpBottom();
        //int checkBonus();
        //std::shared_ptr<Dice> getDice(int index); // Return shared_ptr to Dice

    private:
        int  rolls;
        int  yahtzeePad[3][21];
        bool gameOver;
        bool diceCanRoll;
        int  lastEntry[2];
        Dice diceArray[5];
        int  grandTotal = 0;
        int  cellsFilled = 0;
        bool yahtzeeBonusFlag = false;
        bool yahtzeeOn = false;
        bool yahtzeeCheck = false;
        
        /*
        int upperSection[4][7];
        int upperTotal[4];
        int lowerSection[4][7];
        int yahtzeeBonus[4];
        int lowerTotal[4];       
        int grandTotal;
        */
        //std::shared_ptr<Dice> diceArray[5]; // Array of shared pointers to Dice
};