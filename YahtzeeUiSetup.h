
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
    QPushButton* m_dieButton[5];
    QPushButton* m_rollButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QTableWidget* m_tableWidget;
    QTableWidgetItem* m_cell[22][4];
    QFrame *line;
    QFrame *line_2;
    QTableWidget* m_tableWidgetTotal;
    

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
            m_dieButton[i] = new QPushButton(YahtzeeUI);
            m_dieButton[i]->setObjectName(QString::fromStdString(buttonName));
            m_dieButton[i]->setGeometry(QRect(20+(i*100), 40, 100, 100));
            m_dieButton[i]->setStyleSheet(QString::fromUtf8("border: none"));
            m_dieButton[i]->setIcon(icon);
            m_dieButton[i]->setIconSize(QSize(100, 100));
            m_dieButton[i]->setCheckable(false);
            m_dieButton[i]->setEnabled(false);
            horizontalLayout->addWidget(m_dieButton[i]);
        }

        m_rollButton = new QPushButton("Roll", YahtzeeUI);
        m_rollButton->setObjectName("rollButton");
        m_rollButton->setGeometry(QRect(270, 110, 100, 50));
        
        m_tableWidget = new QTableWidget(YahtzeeUI);
        m_tableWidget->setColumnCount(4);
        m_tableWidget->setRowCount(22);
        m_tableWidget->setObjectName("tableWidget");
        m_tableWidget->setGeometry(QRect(90, 160, 451, 661));
        m_tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_tableWidget->setRowCount(22);
        m_tableWidget->setColumnCount(4);
        m_tableWidget->horizontalHeader()->setVisible(false);
        m_tableWidget->horizontalHeader()->setHighlightSections(false);
        m_tableWidget->verticalHeader()->setVisible(false);
        m_tableWidget->verticalHeader()->setHighlightSections(false);

        std::vector<QString> names = {"x1", "x2", "x3", "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", "Top Subtotal",
        "Bonus", "Top Total", "LOWER SECTION", "Three of a Kind", "Four of a Kind", "Full House", "Small Straight", "Large Straight",
        "Yahtzee", "Chance", "Yahtzee Bonus", "Lower Total", "Grand Total", "Final Score"};

        for(int i=0; i<22; i++)
        {
            for(int j=0; j<4; j++)
            {
                m_cell[i][j] = new QTableWidgetItem();
                QColor transparentColor;
                if(i==0 && j>0)
                {
                    m_cell[i][j]->setText(names[j-1]);
                }
                if(i>0 && i<22 && j==0)
                {
                    m_cell[i][j]->setText(names[i+2]);
                }
                if(i==0 || (i>6 && i<11) || i>17 || j==0)
                {
                    m_cell[i][j]->setFlags(m_cell[i][j]->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEnabled);     // non-clickable
                    m_cell[i][j]->setForeground(QBrush(QColor(Qt::black)));   // makes text not be greyed out even though non-clickable
                }
                if(j==0)
                {
                    transparentColor = QColor(255, 239, 219, 127); 
                }
                if(j==1)
                {
                    transparentColor = QColor(210, 180, 140, 127);  
                }
                if(j==2)
                {
                    transparentColor =  QColor(198, 150, 94, 127);  
                }
                if(j==3)
                {  
                    transparentColor =  QColor(184, 134, 11, 127);   
                }
                m_cell[i][j]->setBackground(transparentColor);
                m_tableWidget->setItem(i, j, m_cell[i][j]);     // this makes the m_cell a part of m_tableWidget
            }
        }

        

        m_tableWidgetTotal = new QTableWidget(YahtzeeUI);
        if (m_tableWidgetTotal->columnCount() < 2)
            m_tableWidgetTotal->setColumnCount(2);
        if (m_tableWidgetTotal->rowCount() < 1)
            m_tableWidgetTotal->setRowCount(1);

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
        m_tableWidgetTotal->setItem(0, 0, grandTotal);
        m_tableWidgetTotal->setObjectName("m_tableWidgetTotal");
        m_tableWidgetTotal->setGeometry(QRect(220, 830, 201, 31));
        m_tableWidgetTotal->setFont(font);
        m_tableWidgetTotal->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_tableWidgetTotal->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        m_tableWidgetTotal->setShowGrid(false);
        m_tableWidgetTotal->setRowCount(1);
        m_tableWidgetTotal->setColumnCount(2);
        m_tableWidgetTotal->horizontalHeader()->setVisible(false);
        m_tableWidgetTotal->horizontalHeader()->setHighlightSections(false);
        m_tableWidgetTotal->verticalHeader()->setVisible(false);
        m_tableWidgetTotal->verticalHeader()->setHighlightSections(false);

        QMetaObject::connectSlotsByName(YahtzeeUI);
    } // setupUi


};


namespace Ui {
    class YahtzeeUI: public YahtzeeUiSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // YAHTZEEUISETUP_H
