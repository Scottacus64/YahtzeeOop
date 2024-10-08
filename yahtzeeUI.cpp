#include "YahtzeeUI.h"
#include "YahtzeeUiSetup.h"
#include <iostream>
#include <QTimer>
#include <QPainter>
#include <QDir>
#include <utility>


YahtzeeUI::YahtzeeUI(QWidget *parent)
    : QWidget(parent), ui(new Ui::YahtzeeUI)
{
    ui->setupUi(this);
    background = QPixmap(QString(ui->assetPath + "felt.png"));

    for(int i=0; i<13; i++)
    {
        QString pathway = ui->assetPath + "dice" + QString::number(i) + ".png";
        pixmaps[i] = QPixmap(pathway);
    }

    for (int i=0; i<5; i++) {ui->m_dieButton[i]->setIcon(pixmaps[0]);}
    int lastRowClicked = 0;
    int lastColumnClicked = 0;

    QIcon leftIcon = QPixmap(QString(ui->assetPath + "LeftArrow.png"));
    ui->m_leftArrow->setIcon(leftIcon);
    QIcon rightIcon = QPixmap(QString(ui->assetPath + "RightArrow.png"));
    ui->m_leftArrow->setIconSize(ui->m_leftArrow->size());
    ui->m_rightArrow->setIcon(rightIcon);
    ui->m_rightArrow->setIconSize(ui->m_rightArrow->size());
    QIcon enterIcon = QPixmap(QString(ui->assetPath + "EnterButton.png"));
    ui->m_enter->setIcon(enterIcon);
    ui->m_enter->setIconSize(ui->m_enter->size());
    m_pYahtzeeGame = new YahtzeeGame();
    QList<QTableWidget*> tables = {
        ui->m_tableUpper,
        ui->m_tableUpperTotal,
        ui->m_tableLower,
        ui->m_tableLowerTotal,
        ui->m_tableTotal
    };
}


YahtzeeUI::~YahtzeeUI()
{
    delete ui;
}


void YahtzeeUI::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), background);
}


void YahtzeeUI::on_rollButton_clicked()
{
    if(isRolling == true){return;}
    isRolling = true;
    ui->m_rollButton->setEnabled(false);
    QTimer::singleShot(500, this, [this]() {
        ui->m_rollButton->setEnabled(true); 
        isRolling = false;
    });
    bool gameOver = m_pYahtzeeGame->checkGameOver();
    if (gameOver == true)
    {
        m_pYahtzeeGame-> clearPad();
        m_pYahtzeeGame->clearHighScore();

        for (QTableWidget* table : tables) {
            table->setVisible(true);
            table->clearFocus();
            table->setCurrentItem(nullptr);
            table->setCurrentCell(-1, -1);
            table->clearSelection();
        }
        refreshTable();
        ui->m_tableUpper->setVisible(true);
        ui->m_tableLower->setVisible(true);
        ui->m_tableUpperTotal->setVisible(true);
        ui->m_tableLowerTotal->setVisible(true);
        ui->m_tableTotal->setVisible(true);
        ui->m_tableUpper->setEnabled(true);
        ui->m_tableLower->setEnabled(true);
        ui->m_pad->setVisible(true);

        ui->m_topTen->setVisible(false);
        ui->m_leftArrow->setVisible(false);
        ui->m_rightArrow->setVisible(false);
        ui->m_enter->setVisible(false);
        ui->m_initials->setVisible(false);
        ui->m_letter->setVisible(false);
        refreshTable();
        newGame = false;
    }

    if(newCell == true){
        for(int i=0; i<6; i++)
        {
            ui->m_dieButton[i]->setEnabled(true);
        }

        lastRowClicked = 0;
        lastColumnClicked = 0;
        int rolls = m_pYahtzeeGame->getRolls();

        if (rolls == 0)
        {
            for (int i=0; i<5; i++)
            {
                Dice* dicePtr = m_pYahtzeeGame->getDiceArrayPtr(i);
                dicePtr->setClicked();
            }
        }

        rolls +=1;
        m_pYahtzeeGame->setRolls(rolls);
        //QString out = "ABC 2000 BCD 1800 CDE 1700 DEF 1600 EFG 1500 FGH 1400 GHI 1300 HIJ 1200 IJK 1100 JKH 1000";
        switch(rolls)
        {
            case 0:
                ui->m_rollButton->setIcon(QIcon(QPixmap(ui->assetPath + "enterRoll.png")));
                break;        
            case 1:
                ui->m_rollButton->setIcon(QIcon(QPixmap(ui->assetPath + "twoRollsLeft.png")));
                break;       
            case 2:
                ui->m_rollButton->setIcon(QIcon(QPixmap(ui->assetPath + "oneRollLeft.png")));          
                break;
            default:
                ui->m_rollButton->setIcon(QIcon(QPixmap(ui->assetPath + "enterRoll.png")));
                break;
        }

        if (rolls < 4)
        {
            QTimer timer;
            timer.setInterval(25);
            for (int j=0; j<10; j++)
            {
                for (int i=0; i<5; i++)
                {
                    m_pYahtzeeGame->rollDice(i);
                    setDiePixmap(i);
                }
                timer.start();
                // Use a loop to wait until the QTimer times out (25ms)
                QEventLoop loop;
                QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
                loop.exec();
            }
        }
    }
}


void YahtzeeUI::on_DieButton_0_clicked()
{
    m_pYahtzeeGame->clickDie(0);
    setDiePixmap(0);
}


void YahtzeeUI::on_DieButton_1_clicked()
{
    m_pYahtzeeGame->clickDie(1);
    setDiePixmap(1);       
}


void YahtzeeUI::on_DieButton_2_clicked()
{
    m_pYahtzeeGame->clickDie(2);
    setDiePixmap(2);
}


void YahtzeeUI::on_DieButton_3_clicked()
{
    m_pYahtzeeGame->clickDie(3);
    setDiePixmap(3);
}


void YahtzeeUI::on_DieButton_4_clicked()
{
    m_pYahtzeeGame->clickDie(4);
    setDiePixmap(4);
}


void YahtzeeUI::setDiePixmap(int slot)
{
    Dice* dicePtr = m_pYahtzeeGame->getDiceArrayPtr(slot);

    int value = dicePtr->getValue();   
    bool clicked = dicePtr->getClicked();  
    
    if (clicked == false)
    {
        ui->m_dieButton[slot]->setIcon(QIcon(pixmaps[value]));
    }
    else
    {
        ui->m_dieButton[slot]->setIcon(QIcon(pixmaps[value+6]));
    }
}


void YahtzeeUI::on_tableUpper_cellClicked(int row, int col)
{
    bool gameOver = m_pYahtzeeGame->checkGameOver();
    if (gameOver == false)
    {
        m_pYahtzeeGame->setRolls(0);
        bool done = false;
        newCell = m_pYahtzeeGame->enterScore(row, col);
        if(newCell == true){
            ui->m_rollButton->setIcon(QIcon(QPixmap(ui->assetPath + "rollDice.png")));
        }
        refreshTable();
        ui->m_tableUpper->clearSelection();
        done = m_pYahtzeeGame->checkGameOver();
        if (done == true) {
           displayTopTen();
        }
    }
}

void YahtzeeUI::on_tableLower_cellClicked(int row, int col)
{
    bool gameOver = m_pYahtzeeGame->checkGameOver();
    if (gameOver == false)
    {
        m_pYahtzeeGame->setRolls(0);
        bool done = false;
        newCell = m_pYahtzeeGame->enterScore(row+9, col);
        if(newCell == true){
            ui->m_rollButton->setIcon(QIcon(QPixmap(ui->assetPath + "rollDice.png")));
        }
        refreshTable();
        ui->m_tableLower->clearSelection();
        done = m_pYahtzeeGame->checkGameOver();
        if (done == true) {
            displayTopTen();
        }
    }
}


void YahtzeeUI::refreshTable()
{
    for (int row = 0; row < 22; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int value = m_pYahtzeeGame->getYahtzeePad(row, col);
            if (value < 10000)
            {
                if(row<6){
                    QTableWidgetItem* pItem = ui->m_tableUpper->item(row, col);
                    pItem->setText(QString::number(value));
                }
                if(row>5 && row<9){
                    QTableWidgetItem* pItem = ui->m_tableUpperTotal->item(row-6, col);
                    pItem->setText(QString::number(value));
                }
                if(row>8 && row<16){
                    QTableWidgetItem* pItem = ui->m_tableLower->item(row-9, col);
                    pItem->setText(QString::number(value));
                }
                 if(row>15 && row<20){
                    QTableWidgetItem* pItem = ui->m_tableLowerTotal->item(row-16, col);
                    pItem->setText(QString::number(value));
                }
                if(row>19){
                    QTableWidgetItem* pItem = ui->m_tableTotal->item(row-20, col);
                    pItem->setText(QString::number(value));
                }
            }
            else
            {
                if(row<6){
                    QTableWidgetItem* pItem = ui->m_tableUpper->item(row, col);
                    pItem->setText(QString());
                }
                if(row>5 && row<9){
                    QTableWidgetItem* pItem = ui->m_tableUpperTotal->item(row-6, col);
                    pItem->setText(QString());
                }
                if(row>8 && row<16){
                    QTableWidgetItem* pItem = ui->m_tableLower->item(row-9, col);
                    pItem->setText(QString());
                }
                if(row>15 && row<20){
                    QTableWidgetItem* pItem = ui->m_tableLowerTotal->item(row-16, col);
                    pItem->setText(QString());
                }
                if(row>19){
                    QTableWidgetItem* pItem = ui->m_tableTotal->item(row-20, col);
                    pItem->setText(QString());
                }
            }
        }
    }
}


void YahtzeeUI::on_leftArrow_clicked()
{
    initial --;
    if (initial < 'A') {initial = 'Z';}
    ui->m_letter->setText(QString(QChar(initial)));
}


void YahtzeeUI::on_rightArrow_clicked()
{
    initial ++;
    if(initial > 'Z'){initial = 'A';}
    ui->m_letter->setText(QString(QChar(initial)));
}


void YahtzeeUI::on_enter_clicked()
{
    if(newGame == true){
        m_pYahtzeeGame->clearPad();
        m_pYahtzeeGame->clearHighScore();

        for (QTableWidget* table : tables) {
            table->setVisible(true);
            table->clearFocus();
            table->setCurrentItem(nullptr);
            table->setCurrentCell(-1, -1);
            table->clearSelection();
            table->setEnabled(true);
        }
        refreshTable();

        ui->m_topTen->setVisible(false);
        ui->m_tableTopTen->setVisible(false);
        ui->m_leftArrow->setVisible(false);
        ui->m_rightArrow->setVisible(false);
        ui->m_enter->setVisible(false);
        ui->m_initials->setVisible(false);
        ui->m_letter->setVisible(false);

        ui->m_rollButton->setVisible(true);
        ui->m_pad->setVisible(true);
        newCell = true;
        refreshTable();
        newGame = false;
    }
    else{
        int firstUnderscore = entryInitials.indexOf('_');
        if (firstUnderscore != -1) {
            entryInitials.replace(firstUnderscore, 1, initial);  
        }
        ui->m_initials->setText(entryInitials);

        if (!entryInitials.contains('_')) {
            ui->m_letter->setVisible(false);
            ui->m_leftArrow->setVisible(false);
            ui->m_rightArrow->setVisible(false);

            for(int i=0;i<10;i++){
                if(inits[i]=="999"){inits[i]= entryInitials.remove(' ');}
            }
            QString output;
            for(int i=0;i<10;i++){
                output = output + inits[i] + " " + scores[i] + " ";
            }
            m_pYahtzeeGame->writeTopTen(output);
            QIcon enterIcon = QPixmap(QString(ui->assetPath + "newGameRound.png"));
            ui->m_enter->setIcon(enterIcon);
            ui->m_enter->setIconSize(ui->m_enter->size());

            std::vector<std::pair<QString, int>> topTenVec = m_pYahtzeeGame->checkTopTen(10);
            int counter = 0;
            for (const auto& pair : topTenVec) {
                QString init = pair.first;
                QString score = QString::number(pair.second);
                inits[counter] = init;
                scores[counter] = score;
                QTableWidgetItem* initItem = ui->m_tableTopTen->item(counter, 0);
                QTableWidgetItem* scoreItem = ui->m_tableTopTen->item(counter, 1);
                if (initItem) {initItem->setText(init);}
                if (scoreItem) {scoreItem->setText(score);} 
                counter++;
            }
            newGame = true;
        }  
    }
}


void YahtzeeUI::getInitials()
{
    for (int i=0; i<5; i++) {ui->m_dieButton[i]->setIcon(pixmaps[0]);}
    ui->m_topTen->setVisible(true);
    ui->m_leftArrow->setVisible(true);
    ui->m_rightArrow->setVisible(true);
    ui->m_enter->setVisible(true);
    ui->m_leftArrow->setEnabled(true);
    ui->m_rightArrow->setEnabled(true);
    ui->m_enter->setEnabled(true);
    ui->m_initials->setVisible(true);
    ui->m_letter->setVisible(true);
    ui->m_letter->setText("A");
    entryInitials = "_ _ _";
    ui->m_initials->setText(entryInitials);
}


void YahtzeeUI::displayTopTen()
{
    QTimer::singleShot(2000, [this]() {
        // Hide game components and show Top Ten table and initials
        for (int i = 0; i < 5; i++) {
            ui->m_dieButton[i]->setIcon(pixmaps[0]);
        }
        ui->m_tableUpper->setVisible(false);
        ui->m_tableUpperTotal->setVisible(false);
        ui->m_tableLower->setVisible(false);
        ui->m_tableLowerTotal->setVisible(false);
        ui->m_tableTotal->setVisible(false);
        ui->m_pad->setVisible(false);
        ui->m_tableUpper->setEnabled(false);
        ui->m_tableLower->setEnabled(false);
        ui->m_rollButton->setVisible(false);
        ui->m_topTen->setVisible(true);
        ui->m_tableTopTen->setVisible(true);

        // Retrieve and display top ten scores
        int total = m_pYahtzeeGame->getGrandTotal();
        std::vector<std::pair<QString, int>> topTenVec = m_pYahtzeeGame->checkTopTen(total);
        int counter = 0;

        for (const auto& pair : topTenVec) {
            QString init = pair.first;
            QString score = QString::number(pair.second);
            inits[counter] = init;
            scores[counter] = score;

            // Retrieve the existing items in the table and set their values
            QTableWidgetItem* initItem = ui->m_tableTopTen->item(counter, 0);
            QTableWidgetItem* scoreItem = ui->m_tableTopTen->item(counter, 1);
            
            if (initItem) {
                if(init!="999"){
                    initItem->setText(init);
                }
                else{
                    initItem->setText(QString());
                }
            } 

            if (scoreItem) {
                scoreItem->setText(score);
            } 
            counter++;
        }

        // Check for high score and prompt initials entry if applicable
        if (m_pYahtzeeGame->highScore()) {
            getInitials();
            newGame = false;
        }
        else{
            ui->m_enter->setEnabled(true);
            ui->m_enter->setVisible(true);
            QIcon enterIcon = QPixmap(QString(ui->assetPath + "newGameRound.png"));
            ui->m_enter->setIcon(enterIcon);
            ui->m_enter->setIconSize(ui->m_enter->size());
            newGame = true;
        }
    });
}


            

