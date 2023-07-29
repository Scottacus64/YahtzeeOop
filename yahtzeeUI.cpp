#include "yahtzeeUI.h"
#include "ui_widgetwindow.h"
#include <iostream>
#include <QTimer>

WidgetWindow::WidgetWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetWindow)
{
    ui->setupUi(this);

    dice0.load("/Users/scottmiller/VSC/CPP/Yahtzee/resources/dice0.png");
   
    pixmaps[1] = QPixmap("/Users/scottmiller/VSC/CPP/Yahtzee/resources/dice1.png");
    pixmaps[2] = QPixmap("/Users/scottmiller/VSC/CPP/Yahtzee/resources/dice2.png");
    pixmaps[3] = QPixmap("/Users/scottmiller/VSC/CPP/Yahtzee/resources/dice3.png");
    pixmaps[4] = QPixmap("/Users/scottmiller/VSC/CPP/Yahtzee/resources/dice4.png");
    pixmaps[5] = QPixmap("/Users/scottmiller/VSC/CPP/Yahtzee/resources/dice5.png");
    pixmaps[6] = QPixmap("/Users/scottmiller/VSC/CPP/Yahtzee/resources/dice6.png");

    pixmaps[7] = QPixmap("/Users/scottmiller/VSC/CPP/Yahtzee/resources/dice1b.png");
    pixmaps[8] = QPixmap("/Users/scottmiller/VSC/CPP/Yahtzee/resources/dice2b.png");
    pixmaps[9] = QPixmap("/Users/scottmiller/VSC/CPP/Yahtzee/resources/dice3b.png");
    pixmaps[10] = QPixmap("/Users/scottmiller/VSC/CPP/Yahtzee/resources/dice4b.png");
    pixmaps[11] = QPixmap("/Users/scottmiller/VSC/CPP/Yahtzee/resources/dice5b.png");
    pixmaps[12] = QPixmap("/Users/scottmiller/VSC/CPP/Yahtzee/resources/dice6b.png");

    dicePB[0] = ui->DieButton_0;
    dicePB[1] = ui->DieButton_1;
    dicePB[2] = ui->DieButton_2;
    dicePB[3] = ui->DieButton_3;
    dicePB[4] = ui->DieButton_4;

    for (int i=0; i<5; i++) {dicePB[i]->setIcon(dice0);}
    int lastRowClicked = 0;
    int lastColumnClicked = 0;
    ui->tableWidget->setColumnWidth(0, 150);   

    m_pYahtzee = new YahtzeeGame();
}

WidgetWindow::~WidgetWindow()
{
    delete ui;
}


void WidgetWindow::on_rollButton_clicked()
{
    bool gameOver = m_pYahtzee->checkGameOver();
    //m_pYahtzee->newGame();
 
    if (gameOver == true)
    {
        ui->tableWidget_2->setItem(0,1,nullptr);
        ui->rollButton->setText("Roll");
        m_pYahtzee-> clearPad();
        refreshTable();
    }

    lastRowClicked = 0;
    lastColumnClicked = 0;
    int rolls = m_pYahtzee->getRolls();

    if (rolls == 0)
    {
        for (int i=0; i<5; i++)
        {
            Dice* dicePtr = m_pYahtzee->getDiceArrayPtr(i);
            dicePtr->setClicked();
        }
    }

    rolls +=1;
    m_pYahtzee->setRolls(rolls);

    switch(rolls)
    {
    case 0:
        ui->rollButton->setText("Roll");
        break;        
    case 1:
        ui->rollButton->setText("2 Rolls Left");
        break;
    case 2:
        ui->rollButton->setText("1 Roll Left");
        break;
    default:
        ui->rollButton->setText("Click Below");
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
                m_pYahtzee->rollDice(i);
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


void WidgetWindow::on_DieButton_0_clicked()
{
    m_pYahtzee->clickDie(0);
    setDiePixmap(0);
}


void WidgetWindow::on_DieButton_1_clicked()
{
    m_pYahtzee->clickDie(1);
    setDiePixmap(1);       
}


void WidgetWindow::on_DieButton_2_clicked()
{
    m_pYahtzee->clickDie(2);
    setDiePixmap(2);
}


void WidgetWindow::on_DieButton_3_clicked()
{
    m_pYahtzee->clickDie(3);
    setDiePixmap(3);
}


void WidgetWindow::on_DieButton_4_clicked()
{
    m_pYahtzee->clickDie(4);
    setDiePixmap(4);
}

void WidgetWindow::setDiePixmap(int slot)
{
    Dice* dicePtr = m_pYahtzee->getDiceArrayPtr(slot);

    int value = dicePtr->getValue();   //getDice(slot)->getValue();
    bool clicked = dicePtr->getClicked();  //getDice(slot)->getClicked();
    
    if (clicked == false)
    {
        dicePB[slot]->setIcon(QIcon(pixmaps[value]));
    }
    else
    {
        dicePB[slot]->setIcon(QIcon(pixmaps[value+6]));
    }
}

void WidgetWindow::on_tableWidget_cellClicked(int row, int col)
{
    m_pYahtzee->setRolls(0);
    ui->rollButton->setText("Roll");
    bool done = false;
    done = m_pYahtzee->enterScore(row, col);
    refreshTable();
    done = m_pYahtzee->checkGameOver();
    if (done == true) {ui->rollButton->setText("New Game?");}

}

void WidgetWindow::refreshTable()
{
    for (int col=0; col<3; col++)
    {
        for (int row=0; row<21; row++)
        {
            int value = m_pYahtzee->getYahtzeePad(row, col);
            if (value < 10000)
            {
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(value));
                ui->tableWidget->setItem(row+1, col+1, item);
            }
            else
            {          
                ui->tableWidget->setItem(row+1, col+1, nullptr);
            }
        }
    }
    
    QTableWidgetItem *item6 = new QTableWidgetItem(QString::number(m_pYahtzee->getGrandTotal()));
     ui->tableWidget_2->setItem(0, 1, item6);
}