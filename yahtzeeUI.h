#ifndef YAHTZEEUI_H
#define YAHTZEEUI_H

#include "YahtzeeGame.h"
#include "YahtzeeUiSetup.h"
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class YahtzeeUI; }
QT_END_NAMESPACE

class YahtzeeUI : public QWidget
{
    Q_OBJECT

public:
    YahtzeeUI(QWidget *parent = nullptr);
    ~YahtzeeUI();
    void setDiePixmap(int slot);
    void refreshTable ();
    void paintEvent(QPaintEvent *event);
    void getInitials();
    void displayTopTen();

private slots:
    void on_rollButton_clicked();
    void on_DieButton_1_clicked();
    void on_DieButton_0_clicked();
    void on_DieButton_2_clicked();
    void on_DieButton_3_clicked();
    void on_DieButton_4_clicked();
    void on_tableUpper_cellClicked(int row, int col); 
    void on_tableLower_cellClicked(int row, int col); 
    void on_leftArrow_clicked();
    void on_rightArrow_clicked();
    void on_enter_clicked();

private:
    Ui::YahtzeeUI *ui;
    QPixmap dice0;
    QPixmap dice1;
    QPixmap dice2;
    QPixmap dice3;
    QPixmap dice4;
    QPixmap dice5;
    QPixmap dice6;
    QPixmap dice1b;
    QPixmap dice2b;
    QPixmap dice3b;
    QPixmap dice4b;
    QPixmap dice5b;
    QPixmap dice6b;
    QPixmap background;
    QPixmap pixmaps[13];
    QList<QTableWidget*> tables;
    int lastRowClicked = 0;
    int lastColumnClicked = 0;
    YahtzeeGame* m_pYahtzeeGame;
    std::vector<std::pair<QString,int>> topTen;
    QString scores[10];
    QString inits[10];
    char initial = 'A';
    QString entryInitials = "_ _ _";
    QString assetPath;
    bool newGame = true;
    bool newCell = true;
};
#endif // YahtzeeUI_H
