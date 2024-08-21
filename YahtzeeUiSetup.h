
#ifndef YAHTZEEUISETUP_H
#define YAHTZEEUISETUP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include <vector>
#include <string>

QT_BEGIN_NAMESPACE

class YahtzeeUiSetup
{
public:
    QPushButton* dieButton[5];
    QPushButton* rollButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QFrame *line;
    QFrame *line_2;
    QTableWidget *tableWidget_2;
    QTableWidgetItem* cell[22][4];

    void setupUi(QWidget *YahtzeeUI)
    {
        if (YahtzeeUI->objectName().isEmpty())
            YahtzeeUI->setObjectName("Yahtzee");
        YahtzeeUI->resize(648, 878);

        layoutWidget = new QWidget(YahtzeeUI);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(40, 10, 558, 112));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
    
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../VSC/CPP/Dice/resources/dice0.png"), QSize(), QIcon::Normal, QIcon::Off);

        std::string button = "DieButton_";

        for(int i=0; i<5; i++)
        {
            std::string buttonName = button + std::to_string(i);
            dieButton[i] = new QPushButton(YahtzeeUI);
            dieButton[i]->setObjectName(QString::fromStdString(buttonName));
            dieButton[i]->setGeometry(QRect(20+(i*100), 40, 100, 100));
            dieButton[i]->setStyleSheet(QString::fromUtf8("border: none"));
            dieButton[i]->setIcon(icon);
            dieButton[i]->setIconSize(QSize(100, 100));
            dieButton[i]->setCheckable(false);
            dieButton[i]->setEnabled(false);
            horizontalLayout->addWidget(dieButton[i]);
        }

        rollButton = new QPushButton("Roll", YahtzeeUI);
        rollButton->setObjectName("rollButton");
        rollButton->setGeometry(QRect(270, 110, 100, 50));
        
        tableWidget = new QTableWidget(YahtzeeUI);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        if (tableWidget->rowCount() < 22)
            tableWidget->setRowCount(22);

        std::vector<QString> names = {"x1", "x2", "x3", "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", "Top Subtotal",
        "Bonus", "Top Total", "LOWER SECTION", "Three of a Kind", "Four of a Kind", "Full House", "Small Straight", "Large Straight",
        "Yahtzee", "Chance", "Yahtzee Bonus", "Lower Total", "Grand Total", "Final Score"};

        for(int i=0; i<22; i++)
        {
            for(int j=0; j<4; j++)
            {
                cell[i][j] = new QTableWidgetItem();
                
                if(i==0 && j>0)
                {
                    cell[i][j]->setText(names[j-1]);
                }
                if(i>0 && i<22 && j==0)
                {
                    cell[i][j]->setText(names[i+2]);
                }
                if(i==0 || (i>6 && i<11) || i>17 || j==0)
                {
                    cell[i][j]->setFlags(cell[i][j]->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEnabled);     // non-clickable
                    cell[i][j]->setForeground(QBrush(QColor(Qt::black)));   // makes text not be greyed out even though non-clickable
                }
                tableWidget->setItem(i, j, cell[i][j]);    
            }
        }

        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(90, 160, 451, 661));
        tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        //tableWidget->setIconSize(QSize(10, 10));
        tableWidget->setRowCount(22);
        tableWidget->setColumnCount(4);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setHighlightSections(false);

        tableWidget_2 = new QTableWidget(YahtzeeUI);
        if (tableWidget_2->columnCount() < 2)
            tableWidget_2->setColumnCount(2);
        if (tableWidget_2->rowCount() < 1)
            tableWidget_2->setRowCount(1);

        line = new QFrame(YahtzeeUI);
        //line->setObjectName("line");
        line->setGeometry(QRect(90, 450, 451, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(YahtzeeUI);
        //line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(90, 480, 451, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        QFont font;
        font.setPointSize(18);
        QTableWidgetItem *grandTotal = new QTableWidgetItem();
        grandTotal->setFlags(Qt::ItemIsEnabled);
        tableWidget_2->setItem(0, 0, grandTotal);
        tableWidget_2->setObjectName("tableWidget_2");
        tableWidget_2->setGeometry(QRect(220, 830, 201, 31));
        tableWidget_2->setFont(font);
        tableWidget_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget_2->setShowGrid(false);
        tableWidget_2->setRowCount(1);
        tableWidget_2->setColumnCount(2);
        tableWidget_2->horizontalHeader()->setVisible(false);
        tableWidget_2->horizontalHeader()->setHighlightSections(false);
        tableWidget_2->verticalHeader()->setVisible(false);
        tableWidget_2->verticalHeader()->setHighlightSections(false);

        QMetaObject::connectSlotsByName(YahtzeeUI);
    } // setupUi


};

namespace Ui {
    class YahtzeeUI: public YahtzeeUiSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // YAHTZEEUISETUP_H
