#include "YahtzeeUI.h"
#include "YahtzeeUiSetup.h"
#include <iostream>
#include <QTimer>
#include <QPainter>
#include <QDir>

YahtzeeUI::YahtzeeUI(QWidget *parent)
    : QWidget(parent), ui(new Ui::YahtzeeUI)
{
    ui->setupUi(this);

    QString appDir = QCoreApplication::applicationDirPath();
    QString assetPath = QDir::cleanPath(appDir + QDir::separator() + "pngs") + QDir::separator();

    for(int i=0; i<13; i++)
    {
        QString pathway = assetPath + "dice" + QString::number(i) + ".png";
        std::cout << pathway.toStdString() << std::endl;
        pixmaps[i] = QPixmap(pathway);
    }

    background = QPixmap(QString(assetPath + "green.png"));
   
    for(int i=0; i<5; i++)
    {
        dicePB[i] = ui->dieButton[i];
    }

    for (int i=0; i<5; i++) {dicePB[i]->setIcon(pixmaps[0]);}
    int lastRowClicked = 0;
    int lastColumnClicked = 0;
    ui->tableWidget->setColumnWidth(0, 150);   
    ui->tableWidget->setEnabled(false);
    std::cout << "Asset Path" << assetPath.toStdString() << std::endl;
    m_pYahtzee = new YahtzeeGame();
}


YahtzeeUI::~YahtzeeUI()
{
    delete ui;
}


void YahtzeeUI::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    // Paint the green background image
    painter.drawPixmap(0, 0, width(), height(), background);
}


void YahtzeeUI::on_rollButton_clicked()
{
    bool gameOver = m_pYahtzee->checkGameOver();
 
    if (gameOver == true)
    {
        ui->tableWidget_2->setItem(0,1,nullptr);
        ui->rollButton->setText("Roll");
        m_pYahtzee-> clearPad();
        refreshTable();
    }
    for(int i=0; i<6; i++)
    {
        ui->dieButton[i]->setEnabled(true);
    }
    ui->tableWidget->setEnabled(true);
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


void YahtzeeUI::on_DieButton_0_clicked()
{
    m_pYahtzee->clickDie(0);
    setDiePixmap(0);
}


void YahtzeeUI::on_DieButton_1_clicked()
{
    m_pYahtzee->clickDie(1);
    setDiePixmap(1);       
}


void YahtzeeUI::on_DieButton_2_clicked()
{
    m_pYahtzee->clickDie(2);
    setDiePixmap(2);
}


void YahtzeeUI::on_DieButton_3_clicked()
{
    m_pYahtzee->clickDie(3);
    setDiePixmap(3);
}


void YahtzeeUI::on_DieButton_4_clicked()
{
    m_pYahtzee->clickDie(4);
    setDiePixmap(4);
}


void YahtzeeUI::setDiePixmap(int slot)
{
    Dice* dicePtr = m_pYahtzee->getDiceArrayPtr(slot);

    int value = dicePtr->getValue();   
    bool clicked = dicePtr->getClicked();  
    
    if (clicked == false)
    {
        dicePB[slot]->setIcon(QIcon(pixmaps[value]));
    }
    else
    {
        dicePB[slot]->setIcon(QIcon(pixmaps[value+6]));
    }
}


void YahtzeeUI::on_tableWidget_cellClicked(int row, int col)
{
    m_pYahtzee->setRolls(0);
    ui->rollButton->setText("Roll");
    bool done = false;
    done = m_pYahtzee->enterScore(row, col);
    refreshTable();
    done = m_pYahtzee->checkGameOver();
    if (done == true) {ui->rollButton->setText("New Game?");}

}


void YahtzeeUI::refreshTable()
{
    for (int col=0; col<3; col++)
    {
        for (int row=0; row<21; row++)
        {
            if(row != 19)
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
    }
    
    QTableWidgetItem *item6 = new QTableWidgetItem(QString::number(m_pYahtzee->getGrandTotal()));
     ui->tableWidget_2->setItem(0, 1, item6);
}
