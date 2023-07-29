#ifndef WIDGETWINDOW_H
#define WIDGETWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "yahtzeeGame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WidgetWindow; }
QT_END_NAMESPACE

class WidgetWindow : public QWidget
{
    Q_OBJECT

public:
    WidgetWindow(QWidget *parent = nullptr);
    ~WidgetWindow();
    void setDiePixmap(int slot);
    void refreshTable ();

private slots:
    void on_rollButton_clicked();

    void on_DieButton_1_clicked();

    void on_DieButton_0_clicked();

    void on_DieButton_2_clicked();

    void on_DieButton_3_clicked();

    void on_DieButton_4_clicked();

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::WidgetWindow *ui;
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
    QPushButton* dicePB[5];
    QPixmap pixmaps[13];
    int lastRowClicked = 0;
    int lastColumnClicked = 0;

    //YahtzeeGame m_Yahtzee;
    YahtzeeGame* m_pYahtzee;
};
#endif // WIDGETWINDOW_H
