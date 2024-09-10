
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
    QTableWidget* m_tableLowerTotal;
    QTableWidget* m_tableTotal;
    QTableWidget* m_tableTopTen;
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
        YahtzeeUI->move(500,0);

        QString appDir = QCoreApplication::applicationDirPath();
        assetPath = QDir::cleanPath(appDir + QDir::separator() + "pngs") + QDir::separator();

        int hsFontId = QFontDatabase::addApplicationFont(assetPath + "Cookbook.ttf");
        QString hsFontFamily;
        hsFontFamily = QFontDatabase::applicationFontFamilies(hsFontId).at(0);
        QFont hsFont(hsFontFamily);

        m_cup = new QLabel(YahtzeeUI);
        m_cup->setGeometry(QRect(0,0,180,200));
        QPixmap cupPix = QPixmap(QString(assetPath + "cup.png"));
        m_cup->resize(180, 200);
        QPixmap scaledCup = cupPix.scaled(m_cup->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_cup->setPixmap(scaledCup);

        m_pad = new QLabel(YahtzeeUI);
        m_pad->setGeometry(QRect(25,230,770,780));
        QPixmap padPix = QPixmap(QString(assetPath + "pad.png"));
        QPixmap scaledPad = padPix.scaled(m_pad->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_pad->setPixmap(scaledPad);
        

        m_topTen = new QLabel(YahtzeeUI);
        m_topTen->setGeometry(QRect(190,-50,500,1000));
        QPixmap sheetPix = QPixmap(QString(assetPath + "highScoreSheet.png"));
        QPixmap scaledSheet = sheetPix.scaled(m_topTen->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_topTen->setPixmap(scaledSheet);
        m_topTen->setStyleSheet("QLabel { color: black; font-size: 32px; text-align: center; }");
        //m_topTen->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        m_topTen->setVisible(false);

        m_initials = new QLabel(YahtzeeUI);
        m_initials->setGeometry(QRect(320,790,100,75));
        m_initials->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        m_initials->setFont(hsFont);
        m_initials->setStyleSheet("QLabel {color: white; font-size: 52px; text-align: center; }");
        m_initials->setText("_ _ _");
        m_initials->setVisible(false);

        m_letter = new QLabel(YahtzeeUI);
        m_letter->setGeometry(QRect(360,840,75,75));
        m_letter->setFont(hsFont);
        m_letter->setStyleSheet("QLabel {color: white; font-size: 52px; text-align: center; }");
        m_letter->setVisible(false);

        m_leftArrow = new QPushButton(YahtzeeUI);
        m_leftArrow->setGeometry(QRect(200,900,100,100));
        m_leftArrow->setObjectName("leftArrow");
        m_leftArrow->setStyleSheet(QString::fromUtf8("border: none"));
        m_leftArrow->setEnabled(false);
        m_leftArrow->setVisible(false);

        m_rightArrow = new QPushButton(YahtzeeUI);
        m_rightArrow->setGeometry(QRect (450,900,100,100));
        m_rightArrow->setObjectName("rightArrow");
        m_rightArrow->setStyleSheet(QString::fromUtf8("border: none"));
        m_rightArrow->setEnabled(false);
        m_rightArrow->setVisible(false);

        m_enter = new QPushButton(YahtzeeUI);
        m_enter->setGeometry(QRect(325,900,100,100));
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
        QIcon rollButton = QPixmap(QString(assetPath + "rollDice.png"));
        m_rollButton->setIcon(rollButton);

        m_tableTopTen = createTableWidget(YahtzeeUI, 2, 10, QRect(225, 340, 300, 500), false);
        m_tableUpper = createTableWidget(YahtzeeUI, 3, 6, QRect(413, 293, 270, 170), true);
        m_tableUpperTotal = createTableWidget(YahtzeeUI, 3, 3, QRect(413, 465, 270, 86), true);
        m_tableLower = createTableWidget(YahtzeeUI, 3, 11, QRect(413, 578, 270, 200), true);
        m_tableLowerTotal = createTableWidget(YahtzeeUI, 3, 4, QRect(413, 780, 270, 103), true);
        m_tableTotal = createTableWidget(YahtzeeUI, 3, 2, QRect(413, 905, 270, 78), true);
        
        QMetaObject::connectSlotsByName(YahtzeeUI);
    } 

    QTableWidget* createTableWidget(QWidget* parent, int columns, int rows, const QRect& geometry, bool scorePad) 
    {
        int tableFontId = QFontDatabase::addApplicationFont(assetPath + "Cookbook.ttf");
        QString tableFontFamily;
        tableFontFamily = QFontDatabase::applicationFontFamilies(tableFontId).at(0);
        QFont tableFont(tableFontFamily);
        tableFont.setPointSize(21);

        QTableWidget* table = new QTableWidget(parent);
        table->setFont(tableFont); 
        if(rows==6){table->setObjectName("tableUpper");}
        if(rows==11){table->setObjectName("tableLower");}
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
        table->setShowGrid(false);
        table->setEnabled(false);
        table->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->setSelectionMode(QAbstractItemView::SingleSelection);
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
            "QTableWidget { "
            "    color: black; "  
            "} "
            "QTableWidget::item:disabled { "
            "    color: black; "  
            "}"
        );

        if(scorePad ==  true){
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
        }
        else{
            table->setEnabled(false);
            for (int i = 0; i < columns; i++) {
                table->setColumnWidth(i, 300/2);
            }
            for (int i=0;i<rows;i++){
                table->setRowHeight(i, 40);
            }
            tableFont.setPointSize(42);
            for(int i=0;i<10;i++){
                for (int j = 0; j < columns; j++) {
                        QTableWidgetItem* item = new QTableWidgetItem();
                        item->setBackground(Qt::transparent);
                        QFont itemFont = item->font();
                        itemFont.setPointSize(42);
                        item->setFont(itemFont);
                        item->setTextAlignment(Qt::AlignCenter);
                        table->setItem(i, j, item);
                    }
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
