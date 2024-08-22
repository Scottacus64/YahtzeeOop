#ifndef YAHTZEEUI_H
#define YAHTZEEUI_H

#include <QWidget>
#include <QPushButton>
#include "YahtzeeGame.h"
#include "YahtzeeUiSetup.h"

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

private slots:
    void on_rollButton_clicked();
    void on_DieButton_1_clicked();
    void on_DieButton_0_clicked();
    void on_DieButton_2_clicked();
    void on_DieButton_3_clicked();
    void on_DieButton_4_clicked();
    void on_tableWidget_cellClicked(int row, int column);

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
    QPushButton* dicePB[5];
    QPixmap pixmaps[13];
    int lastRowClicked = 0;
    int lastColumnClicked = 0;
    YahtzeeGame* m_pYahtzeeGame;
};
#endif // YahtzeeUI_H
