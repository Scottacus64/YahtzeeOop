
#ifndef YAHTZEEUISETUP_H
#define YAHTZEEUISETUP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QApplication>
#include <QFrame>
#include <QWidget>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QTableWidget>
#include <QDir>
#include <QLabel>
#include <QWidget>
#include <QString>
#include <vector>
#include <string>
#include <QFont>
#include <QFontDatabase>


QT_BEGIN_NAMESPACE

class YahtzeeUiSetup
{
public:
    QPushButton* m_dieButton[5];
    QPushButton* m_rollButton;
    QPushButton* m_rightArrow;
    QPushButton* m_leftArrow;
    QPushButton* m_enter;
    QTableWidget* m_tableUpper;
    QTableWidget* m_tableUpperTotal;
    QTableWidget* m_tableLower;
    QTableWidget* m_tableTotal;
    QTableWidgetItem* m_cell[22][4];
    QString assetPath;
    QLabel* m_cup;
    QLabel* m_pad;
    QLabel* m_topTen;
    QLabel* m_letter;
    QLabel* m_initials;
    

    void setupUi(QWidget *YahtzeeUI)
    {
        if (YahtzeeUI->objectName().isEmpty())
            YahtzeeUI->setObjectName("Yahtzee");
        YahtzeeUI->resize(750, 1000);

        QString appDir = QCoreApplication::applicationDirPath();
        assetPath = QDir::cleanPath(appDir + QDir::separator() + "pngs") + QDir::separator();

        m_cup = new QLabel(YahtzeeUI);
        m_cup->setGeometry(QRect(0,0,180,200));
        QPixmap cupPix = QPixmap(QString(assetPath + "cup.png"));
        m_cup->resize(180, 200);
        QPixmap scaledCup = cupPix.scaled(m_cup->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_cup->setPixmap(scaledCup);

        m_pad = new QLabel(YahtzeeUI);
        m_pad->setGeometry(QRect(25,230,770,780));
        QPixmap padPix = QPixmap(QString(assetPath + "background.png"));
        QPixmap scaledPad = padPix.scaled(m_pad->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_pad->setPixmap(scaledPad);
        

        m_topTen = new QLabel(YahtzeeUI);
        m_topTen->setGeometry(QRect(100,240,450,400));

        m_initials = new QLabel(YahtzeeUI);
        m_initials->setGeometry(QRect(275,650,100,75));
        QFont iFont = m_initials->font();
        iFont.setPointSize(42);
        m_initials->setFont(iFont);

        m_letter = new QLabel(YahtzeeUI);
        m_letter->setGeometry(QRect(300,700,75,75));
        QFont lFont = m_letter->font();
        lFont.setPointSize(42);
        m_letter->setFont(lFont);

        m_leftArrow = new QPushButton(YahtzeeUI);
        m_leftArrow->setGeometry(QRect(150,775,100,100));
        m_leftArrow->setObjectName("leftArrow");
        m_leftArrow->setStyleSheet(QString::fromUtf8("border: none"));
        m_leftArrow->setEnabled(false);
        m_leftArrow->setVisible(false);

        m_rightArrow = new QPushButton(YahtzeeUI);
        m_rightArrow->setGeometry(QRect (400,775,100,100));
        m_rightArrow->setObjectName("rightArrow");
        m_rightArrow->setStyleSheet(QString::fromUtf8("border: none"));
        m_rightArrow->setEnabled(false);
        m_rightArrow->setVisible(false);

        m_enter = new QPushButton(YahtzeeUI);
        m_enter->setGeometry(QRect(275,775,100,100));
        m_enter->setObjectName("enter");
        m_enter->setStyleSheet(QString::fromUtf8("border: none"));
        m_enter->setEnabled(false);
        m_enter->setVisible(false);
        
        for(int i=0; i<5; i++)
        {
            std::string buttonName = "DieButton_" + std::to_string(i);
            m_dieButton[i] = new QPushButton(YahtzeeUI);
            m_dieButton[i]->setObjectName(QString::fromStdString(buttonName));
            m_dieButton[i]->setGeometry(QRect(190+(i*100), 90, 100, 100));
            m_dieButton[i]->setStyleSheet(QString::fromUtf8("border: none"));
            m_dieButton[i]->setIconSize(QSize(100, 100));
            m_dieButton[i]->setCheckable(false);
            m_dieButton[i]->setEnabled(false);
        }

        m_rollButton = new QPushButton(YahtzeeUI);
        m_rollButton->setObjectName("rollButton");
        m_rollButton->setGeometry(QRect(300, 190, 200, 60));
        m_rollButton->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
        m_rollButton->setIconSize(QSize(200, 60));
        QIcon rollButton = QPixmap(QString(assetPath + "newGame.png"));
        m_rollButton->setIcon(rollButton);

        m_tableUpper = createTableWidget(YahtzeeUI, 3, 6, QRect(413, 293, 270, 170));
        m_tableUpperTotal = createTableWidget(YahtzeeUI, 3, 3, QRect(413, 465, 270, 86));
        m_tableLower = createTableWidget(YahtzeeUI, 3, 10, QRect(413, 579, 270, 285));
        m_tableTotal = createTableWidget(YahtzeeUI, 3, 2, QRect(413, 905, 270, 78));

        QMetaObject::connectSlotsByName(YahtzeeUI);
    } 

    QTableWidget* createTableWidget(QWidget* parent, int columns, int rows, const QRect& geometry) 
    {
        int tableFontId = QFontDatabase::addApplicationFont(assetPath + "Cookbook.ttf");
        QString tableFontFamily;
        tableFontFamily = QFontDatabase::applicationFontFamilies(tableFontId).at(0);
        QFont tableFont(tableFontFamily);
        tableFont.setPointSize(21);

        QTableWidget* table = new QTableWidget(parent);
        table->setFont(tableFont); 
        table->setColumnCount(columns);
        table->setRowCount(rows);
        table->setGeometry(geometry);
        table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        table->horizontalHeader()->setVisible(false);
        table->horizontalHeader()->setHighlightSections(false);
        table->verticalHeader()->setVisible(false);
        table->verticalHeader()->setHighlightSections(false);
        table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        //table->setStyleSheet("QTableWidget::item { background-color: transparent; border: none; }");
        table->setStyleSheet(
            "QTableWidget { "
            "    background-color: transparent; "
            "    border: none; "
            "} "
            "QHeaderView::section { "
            "    background-color: transparent; "
            "    border: none; "
            "} "
            "QTableWidget::item { "
            "    border: none; "
            "}"
        );
        
        if(rows<6){table->setEnabled(false);}

        for (int i = 0; i < columns; i++) {
            table->setColumnWidth(i, 270 / 3);
        }

        for (int i = 0; i < rows; i++) {
            if(rows < 3) {
                if(i==0){
                    table->setRowHeight(i, 34);
                }
                else {
                    table->setRowHeight(i, 40);
                }
            }
            else {
                table->setRowHeight(i, 28);
            }
            

            for (int j = 0; j < columns; j++) {
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setBackground(Qt::transparent);
                item->setTextAlignment(Qt::AlignCenter);
                if(rows < 3) {
                    QFont itemFont = item->font();
                    if(i==0){
                        itemFont.setPointSize(28);
                        item->setFont(itemFont);
                    }
                    else {
                        itemFont.setPointSize(34);
                        item->setFont(itemFont);
                    }
                }
                table->setItem(i, j, item);
            }
        }

        return table;
    }

};


namespace Ui {
    class YahtzeeUI: public YahtzeeUiSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // YAHTZEEUISETUP_H
