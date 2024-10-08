#include "YahtzeeGame.h"
#include <utility>
#include <vector>
#include <QString>
#include <QStandardPaths>
#include <QVector>
#include <QDir>
#include <QFile>


YahtzeeGame::YahtzeeGame()
{
    clearPad();
    gameOver = true;
    diceCanRoll = false;
 
    rolls = 0;
}


YahtzeeGame::~YahtzeeGame()
{}


void YahtzeeGame::clickDie(int i)
{
    diceArray[i].clickDie();
}


void YahtzeeGame::rollDice(int i)
{
    int value = diceArray[i].rollDie(6);
    diceCanRoll = true;
    yahtzeeBonusFlag = false;
    yahtzeeOn = false;
    yahtzeeCheck = false;
    gameOver = false;
}


bool YahtzeeGame::checkGameOver()
{
    return gameOver;
}


void YahtzeeGame::clearPad()
{
    for (int col=0; col<3; col++)
    {
        for (int row=0; row<22; row++)
        {
            yahtzeePad[col][row] = 10000;
        }
    }
}


bool YahtzeeGame::highScore()
{
    return newHighScore;
}


void YahtzeeGame:: clearHighScore()
{
    newHighScore = false;
}


Dice* YahtzeeGame::getDiceArrayPtr(int slot)
{
    return  &diceArray[slot];
}


int YahtzeeGame::getRolls()
{
    return rolls;
}


void YahtzeeGame::setRolls(int inputRolls)
{
    rolls = inputRolls;
}


bool YahtzeeGame::enterScore(int row, int col) 
{
    gameOver = false;
    bool done;
    row = row;
    col = col;
    if (yahtzeePad[col][row] > 9999)
    {
        if (diceCanRoll == false) 
        {
            int leCol = lastEntry[0];
            int leRow = lastEntry[1];
            yahtzeePad[leCol][leRow] = 10000;
        }

        diceCanRoll = false;
        if (row < 6) {done = checkTopSection(row, col);}
        if (row == 9) {done = checkThreeOfaKind(col);}
        if (row == 10) {done = checkFourOfaKind(col);}
        if (row == 11) {done = checkFullHouse(col);}
        if (row == 12) {done = checkSmallStraight(col);}
        if (row == 13) {done = checkLargeStraight(col);}
        if (row == 14) {done = checkYahtzee(col);}
        if (row == 15) {done = checkChance(col);}
        totalUp();
    }
    if(col==lastEntry[0]&&row==lastEntry[1]){
        done = true;
    }
    return done;
}


bool YahtzeeGame::checkTopSection(int row, int col)
{
    bool cellChanged;
    if (yahtzeePad[col][row] > 9999)
    {
        int total = 0;
    
        for (int i=0; i<5;i++)
        {
            int value = 0;
            value = diceArray[i].getValue();
            if (value == row+1)
            {
                total += value;
            }
        }

        yahtzeePad[col][row] = total;
        yahtzeeCheck = true;
        bool yBonus = checkYahtzee(col);
        int diceValue = diceArray[0].getValue();
        if (yBonus == true)
        {
            if (diceValue == row+1)
                {yahtzeeOn = true; checkYahtzeeBonus(col);}
            else 
                {yahtzeeOn = false; checkYahtzeeBonus(col);}
        }
        lastEntry[0] = col;
        lastEntry[1] = row;
        cellChanged = true;
    } 
    else{
        if(lastEntry[0]==col && lastEntry[1]==row){
            cellChanged = true;
        }
        else{
            cellChanged = false;
        }
    }  
    return cellChanged;
}


bool YahtzeeGame::checkThreeOfaKind(int col)
{
    int total = 0;
    bool cellChanged;
    int* values = bubbleSort(); 
    if (yahtzeePad[col][9] > 9999){
        if (values[0]==values[1]&&values[1]==values[2] || values[1]==values[2]&&values[2]==values[3] || values[2]==values[3]&&values[3]==values[4])
        {
            for (int i=0; i<5; i++)
            {
                total += values[i];
            }
        }
        else {total = 0;}
        yahtzeePad[col][9] = total;

        yahtzeeCheck = true;
        bool yBonus = checkYahtzee(col);
        bool topFill = checkTopFill();
        if (yBonus == true)
        {
            if (topFill == true)  {yahtzeeOn = true;}
            checkYahtzeeBonus(col);
        }
        
        lastEntry[0] = col;
        lastEntry[1] = 9;
        cellChanged = true;
    }
    else{
        cellChanged = false;
    }  
    return cellChanged;
}


bool YahtzeeGame::checkFourOfaKind(int col)
{
    int total = 0;
    int* values = bubbleSort();
    bool cellChanged;
    if (yahtzeePad[col][10] > 9999){
        if (values[0]==values[1]&&values[1]==values[2]&&values[2]==values[3] || values[1]==values[2]&&values[2]==values[3]&&values[3]==values[4])
            {
                for (int i=0; i<5; i++)
                {
                    total += values[i];
                }
            }
        else {total = 0;}
        yahtzeePad[col][10] = total;

        yahtzeeCheck = true;
        bool yBonus = checkYahtzee(col);
        bool topFill = checkTopFill();
        if (yBonus == true)
        {
            if (topFill == true)  {yahtzeeOn = true;}
            checkYahtzeeBonus(col);
        }

        lastEntry[0] = col;
        lastEntry[1] = 10;
        cellChanged = true;
    }
    else{
        cellChanged = false;
    }   
    return cellChanged;
}


bool YahtzeeGame::checkFullHouse(int col)
{
    int total = 0;
    int* values = bubbleSort();
    bool cellChanged;
    if (yahtzeePad[col][11] > 9999){
        if(values[0]==values[1]&&values[1]==values[2]&&values[3]==values[4] || values[0]==values[1]&&values[2]==values[3]&&values[3]==values[4]) 
            {total = 25;}
        else {total = 0;}
        yahtzeePad[col][11] = total;

        yahtzeeCheck = true;
        bool yBonus = checkYahtzee(col);
        bool topFill = checkTopFill();
        if (yBonus == true && topFill == true) 
        {
            yahtzeeOn = true; 
            checkYahtzeeBonus(col);
        }
        cellChanged = true;
        lastEntry[0] = col;
        lastEntry[1] = 11;
    }
    else{
        cellChanged = false;
    }       
    return cellChanged;
}


bool YahtzeeGame::checkSmallStraight(int col)
{
    int* values = bubbleSort();
    bool cellChanged;
    if (yahtzeePad[col][12] > 9999){
        for (int i=0; i<4; i++)
        {
            if (values[i]==values[i+1]) {values[i]=0;}
        }

        int* sortedValues = bubbleSort2(values);
        for (int i=0; i<5; i++) {values[i]=sortedValues[i];}

        if(values[0]+1==values[1]&&values[1]+1==values[2]&&values[2]+1==values[3]&&values[0]>0 ||
            values[1]+1==values[2]&&values[2]+1==values[3]&&values[3]+1==values[4]&&values[1]>0)
            {yahtzeePad[col][12] = 30;}
        else {yahtzeePad[col][12] = 0;}

        yahtzeeCheck = true;
        bool yBonus = checkYahtzee(col);
        bool topFill = checkTopFill();
        if (yBonus == true && topFill == true) 
        {
            yahtzeeOn = true; 
            checkYahtzeeBonus(col);
            yahtzeePad[col][12] = 30;
        }
        cellChanged = true;
        lastEntry[0] = col;
        lastEntry[1] = 12;
    }
    else{
        cellChanged = false;
    }       
    return cellChanged;
}


bool YahtzeeGame::checkLargeStraight(int col)
{
    int* values = bubbleSort();
    bool cellChanged;
    if (yahtzeePad[col][13] > 9999){
        if (values[0]+1==values[1]&&values[1]+1==values[2]&&values[2]+1==values[3]&&values[3]+1==values[4])
            {yahtzeePad[col][13] = 40;}
        else {yahtzeePad[col][13] = 0;}

        yahtzeeCheck = true;
        bool yBonus = checkYahtzee(col);
        bool topFill = checkTopFill();
        if (yBonus == true && topFill == true) 
        {
            yahtzeeOn = true; 
            checkYahtzeeBonus(col);
            yahtzeePad[col][13] = 40;
        }
        cellChanged = true;
        lastEntry[0] = col;
        lastEntry[1] = 13;
    }
    else{
        cellChanged = false;
    }      
    return cellChanged;
}


bool YahtzeeGame::checkYahtzee(int col)
{
    int array[5];
    bool yahtzee = true;                    // set to true and turn off if anything fails in the check
    for (int i=0; i<5; i++)
    {
        array[i] = diceArray[i].getValue();
    }
    for (int j=0; j<4; j++)
    {
        if (array[j] != array[j+1]) {yahtzee = false;}
    }
    if (yahtzeeCheck == false)              // yahtzeeCheck is set to true if we are checking for a yahtzeeBonus
    {                                       // this would be false if we are checking to fill in a yahtzee cell
        bool cellChanged;
        if (yahtzeePad[col][14] > 9999){
            if (yahtzee == true)            // this section lets both the yahtzee cell and yahtzee bonus use the same method
            {
                yahtzeePad[col][14] = 50;
            }
            else {yahtzeePad[col][14] = 0;}
            lastEntry[0] = col;
            lastEntry[1] = 14;
            yahtzee = true;   //cellChanged
        }
        else{
            yahtzee = false;
        }       
    }
    yahtzeeCheck = false;                   // reset yahtzee check here as a central place that all bounus' go through
    return yahtzee;
}


void YahtzeeGame::checkYahtzeeBonus(int col)
{
    if (yahtzeeBonusFlag == true)           // if a bonus has aleady been paid out this roll, clear last bonus
        {
            int bonus = yahtzeePad[lastEntry[0]][17];
            bonus = bonus - 100;
            yahtzeePad[lastEntry[0]][16] = bonus;
            yahtzeeBonusFlag = false;
        }

    int bonusCount = 0;                      // check if all three yahtzees are filled in
    for (int i=0; i<3; i++)
    {
        if (yahtzeePad[i][14] == 50) {bonusCount ++;}
    }

    if (bonusCount > 2 && yahtzeeOn == true) // if all three yahtzees are filled in and we have a legit yahtzee...
    {
        int bonus = yahtzeePad[col][16];     // get the bonus score
        if (bonus > 9999)                     // if it is blank (ie 10000)
        {
            yahtzeePad[col][16] = 100;
        }
        else                                 // otherwise add to old bonus score
        {
            yahtzeePad[col][16] = bonus + 100;
        }
        yahtzeeBonusFlag = true;             // set to true if a yahtzee bonus has been paid out
        yahtzeeOn = false;
    }
}


bool YahtzeeGame::checkChance(int col)
{
    int total = 0;
    bool cellChanged;
    if (yahtzeePad[col][15] > 9999){
        for (int i=0; i<5; i++)
        {
            total += diceArray[i].getValue();
        }

        yahtzeeCheck = true;
        bool yBonus = checkYahtzee(col);
        bool topFill = checkTopFill();
        if (yBonus == true && topFill == true) 
        {
            yahtzeeOn = true; 
            checkYahtzeeBonus(col);
        }
        lastEntry[0] = col;
        lastEntry[1] = 15;
        yahtzeePad[col][15] = total;
        cellChanged = true;
    }
    else{
        cellChanged = false;
    }       
    return cellChanged;        
}


int YahtzeeGame::getYahtzeePad(int row, int col)
{
    return yahtzeePad[col][row];
}


bool YahtzeeGame::checkTopFill()
{
    bool topFill = true;
    int value = diceArray[0].getValue();
    for (int i=0; i<3; i++)
    {
        if (yahtzeePad[i][value-1] > 9999)
        {
            topFill = false;
        }
        if (yahtzeePad[i][14] < 50)
        {
            topFill = false;
        }
    }
    return topFill;
}


int* YahtzeeGame::bubbleSort()
{
    int* pValues = new int[5];
    for (int i=0; i<5; i++)
    {
        pValues[i] = diceArray[i].getValue();
    }
    int j = 4;
    for (int i=0; i<4; i++)
    {
        for (int k=0; k<j; k++)
        {
            if (pValues[k] > pValues[k+1])
            {
                int temp = pValues[k+1];
                pValues[k+1] = pValues[k];
                pValues[k] = temp;
            }
        }
        j--;
    }
    return pValues;
}


int* YahtzeeGame::bubbleSort2(int* values)
{
    int j = 4;
    for (int i=0; i<4; i++)
    {
        for (int k=0; k<j; k++)
        {
            if (values[k] > values[k+1])
            {
                int temp = values[k+1];
                values[k+1] = values[k];
                values[k] = temp;
            }
        }
        j--;
    }

    return values;   
}


void YahtzeeGame::totalUp()
{
    grandTotal = 0;
    cellsFilled = 0;
    int tripleTotal[3];

    for (int col=0; col<3; col++)
    {
        int total = 0;
        int bottomTotal = 0;
        for (int row=0; row<6; row++)
        {
            if (yahtzeePad[col][row] < 10000) {total += yahtzeePad[col][row]; cellsFilled ++;}
        }
        yahtzeePad[col][6]= total;

        if (total > 62)
        {
            yahtzeePad[col][7] = 35;
            yahtzeePad[col][8] = total + 35;
        }
        else
        {
            yahtzeePad[col][7] = 0;
            yahtzeePad[col][8] = total; 
        }

        for (int row=9; row<17; row++)
        {
            if (yahtzeePad[col][row] < 10000) 
            {
                bottomTotal += yahtzeePad[col][row]; 
                if (row < 16) {cellsFilled ++;}
            }
        }
        yahtzeePad[col][17] = bottomTotal;
        yahtzeePad[col][18] = yahtzeePad[col][8];
        yahtzeePad[col][19] = yahtzeePad[col][8]+ bottomTotal;
        yahtzeePad[col][20] = yahtzeePad[col][19]*(col+1);
        tripleTotal[col] = yahtzeePad[col][20];
    }
    for(int i=0; i<3; i++){grandTotal=grandTotal+tripleTotal[i];}
    yahtzeePad[1][21] = grandTotal;
    if (cellsFilled > 38) {gameOver = true;}
}


int YahtzeeGame::getGrandTotal()
{
    return grandTotal;
}


void YahtzeeGame::writeTopTen(QString output)
{
    std::vector<std::pair<QString,int>> topTenVec(10);
    QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QString fileContent;
    if (!configDir.endsWith("Yahtzee")) 
    {
        configDir += QString(QDir::separator()) + "Yahtzee";
    }
    QDir().mkpath(configDir);
    QString filePath = configDir + QString(QDir::separator()) + "topTen.txt";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << output;
        file.close();
    } else {
        qWarning() << "Failed to create file" << filePath;
    }
}   


std::vector<std::pair<QString, int>> YahtzeeGame::checkTopTen(int currentScore)
{
    std::vector<std::pair<QString,int>> topTenVec(10);
    QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QString fileContent;
    if (!configDir.endsWith("Yahtzee")) 
    {
        configDir += QString(QDir::separator()) + "Yahtzee";
    }
    QDir().mkpath(configDir);
    QString filePath = configDir + QString(QDir::separator()) + "topTen.txt";
    QFile file(filePath);

    // if there is no file create a default file
    if (!file.exists()) 
    {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "ABC 2000 BCD 1800 CDE 1700 DEF 1600 EFG 1500 FGH 1400 GHI 1300 HIJ 1200 IJK 1100 JKH 1000" ;
            file.close();
        } 
    }

    // load the data
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        fileContent = in.readAll().trimmed();
        file.close(); 
        qDebug() << "File content:" << fileContent; 
    } 

    QStringList stringList = fileContent.split(' ', Qt::SkipEmptyParts);


    // make pairs of each two entries
    for(int i=0; i<10; i++)
    {
        QString initials = stringList.at(i*2);
        int value = stringList.at((i*2)+1).toInt();
        std::pair<QString, int> pair = std::make_pair(initials, value);
        topTenVec[i] = pair;
    }

    // check to see if the current score is in the top 10, if so add it with "999" as the initials
    for(int i=0; i<10; i++)
    {
        int value = topTenVec[i].second;
        if(currentScore > value)
        {
            topTenVec.pop_back();
            std::pair<QString, int> newPair = std::make_pair("999", currentScore);
            topTenVec.insert(topTenVec.begin()+i, newPair);
            newHighScore = true;
            break;
        }
    }

    return topTenVec;
}


