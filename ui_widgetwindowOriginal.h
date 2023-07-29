/********************************************************************************
** Form generated from reading UI file 'widgetwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETWINDOW_H
#define UI_WIDGETWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetWindow
{
public:
    QPushButton *DieButton_0;
    QPushButton *DieButton_1;
    QPushButton *DieButton_2;
    QPushButton *DieButton_3;
    QPushButton *DieButton_4;
    QPushButton *rollButton;

    void setupUi(QWidget *WidgetWindow)
    {
        if (WidgetWindow->objectName().isEmpty())
            WidgetWindow->setObjectName("WidgetWindow");
        WidgetWindow->resize(545, 317);
        DieButton_0 = new QPushButton(WidgetWindow);
        DieButton_0->setObjectName("DieButton_0");
        DieButton_0->setGeometry(QRect(20, 40, 100, 100));
        DieButton_0->setStyleSheet(QString::fromUtf8("border: none"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../VSC/CPP/Dice/resources/dice0.png"), QSize(), QIcon::Normal, QIcon::Off);
        DieButton_0->setIcon(icon);
        DieButton_0->setIconSize(QSize(100, 100));
        DieButton_1 = new QPushButton(WidgetWindow);
        DieButton_1->setObjectName("DieButton_1");
        DieButton_1->setGeometry(QRect(120, 40, 100, 100));
        DieButton_1->setStyleSheet(QString::fromUtf8("border: none"));
        DieButton_1->setIcon(icon);
        DieButton_1->setIconSize(QSize(100, 100));
        DieButton_2 = new QPushButton(WidgetWindow);
        DieButton_2->setObjectName("DieButton_2");
        DieButton_2->setGeometry(QRect(220, 40, 100, 100));
        DieButton_2->setStyleSheet(QString::fromUtf8("border: none"));
        DieButton_2->setIcon(icon);
        DieButton_2->setIconSize(QSize(100, 100));
        DieButton_3 = new QPushButton(WidgetWindow);
        DieButton_3->setObjectName("DieButton_3");
        DieButton_3->setGeometry(QRect(320, 40, 100, 100));
        DieButton_3->setStyleSheet(QString::fromUtf8("border: none"));
        DieButton_3->setIcon(icon);
        DieButton_3->setIconSize(QSize(100, 100));
        DieButton_4 = new QPushButton(WidgetWindow);
        DieButton_4->setObjectName("DieButton_4");
        DieButton_4->setGeometry(QRect(420, 40, 100, 100));
        DieButton_4->setStyleSheet(QString::fromUtf8("border: none"));
        DieButton_4->setIcon(icon);
        DieButton_4->setIconSize(QSize(100, 100));
        rollButton = new QPushButton(WidgetWindow);
        rollButton->setObjectName("rollButton");
        rollButton->setGeometry(QRect(190, 160, 161, 61));

        retranslateUi(WidgetWindow);

        QMetaObject::connectSlotsByName(WidgetWindow);
    } // setupUi

    void retranslateUi(QWidget *WidgetWindow)
    {
        WidgetWindow->setWindowTitle(QCoreApplication::translate("WidgetWindow", "Yahtzee", nullptr));
        DieButton_0->setText(QString());
        DieButton_1->setText(QString());
        DieButton_2->setText(QString());
        DieButton_3->setText(QString());
        DieButton_4->setText(QString());
        rollButton->setText(QCoreApplication::translate("WidgetWindow", "Roll", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetWindow: public Ui_WidgetWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETWINDOW_H
