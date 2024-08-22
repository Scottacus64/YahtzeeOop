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
        dicePB[i] = ui->m_dieButton[i];
    }

    for (int i=0; i<5; i++) {dicePB[i]->setIcon(pixmaps[0]);}
    int lastRowClicked = 0;
    int lastColumnClicked = 0;
    ui->m_tableWidget->setColumnWidth(0, 150);   
    ui->m_tableWidget->setEnabled(false);
    std::cout << "Asset Path" << assetPath.toStdString() << std::endl;
    m_pYahtzeeGame = new YahtzeeGame();
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
    bool gameOver = m_pYahtzeeGame->checkGameOver();
    if (gameOver == true)
    {
        ui->m_tableWidgetTotal->setItem(0,1,nullptr);
        ui->m_rollButton->setText("Roll");
        m_pYahtzeeGame-> clearPad();
        refreshTable();
    }
    else
    {
        m_pYahtzeeGame->newGame();
    }
    
    for(int i=0; i<6; i++)
    {
        ui->m_dieButton[i]->setEnabled(true);
    }
    ui->m_tableWidget->setEnabled(true);
    lastRowClicked = 0;
    lastColumnClicked = 0;
    int rolls = m_pYahtzeeGame->getRolls();

    // Clear focus from the table widget
    ui->m_tableWidget->clearFocus();
    ui->m_tableWidget->setCurrentItem(nullptr);

    // Deselect all cells
    ui->m_tableWidget->setCurrentCell(-1, -1);
    ui->m_tableWidget->clearSelection();

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

    switch(rolls)
    {
    case 0:
        ui->m_rollButton->setText("Roll");
        break;        
    case 1:
        ui->m_rollButton->setText("2 Rolls Left");
        break;
    case 2:
        ui->m_rollButton->setText("1 Roll Left");
        break;
    default:
        ui->m_rollButton->setText("Click Below");
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
        dicePB[slot]->setIcon(QIcon(pixmaps[value]));
    }
    else
    {
        dicePB[slot]->setIcon(QIcon(pixmaps[value+6]));
    }
}


void YahtzeeUI::on_tableWidget_cellClicked(int row, int col)
{
    bool gameOver = m_pYahtzeeGame->checkGameOver();
    if (gameOver == false)
    {
        m_pYahtzeeGame->setRolls(0);
        ui->m_rollButton->setText("Roll");
        bool done = false;
        m_pYahtzeeGame->enterScore(row, col);
        refreshTable();
        done = m_pYahtzeeGame->checkGameOver();
        if (done == true) {ui->m_rollButton->setText("New Game?");}
    }
}


void YahtzeeUI::refreshTable()
{
    for (int row = 0; row < 21; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int value = m_pYahtzeeGame->getYahtzeePad(row, col);
            std::cout << "value = " << value << " " << row << col <<std::endl;
            if (value < 10000)
            {
                QTableWidgetItem* pItem = ui->m_tableWidget->item(row+1, col+1);
                pItem->setText(QString::number(value));
                //ui->m_tableWidget->setItem(row+1, col+1, pItem);
            }
            else
            {
                QTableWidgetItem* pItem = ui->m_tableWidget->item(row+1, col+1);
                pItem->setText(QString());
            }
        }
    }
    std::cout << "\n" << std::endl;
    
    QTableWidgetItem *item6 = new QTableWidgetItem(QString::number(m_pYahtzeeGame->getGrandTotal()));
    ui->m_tableWidgetTotal->setItem(0, 1, item6);
}

