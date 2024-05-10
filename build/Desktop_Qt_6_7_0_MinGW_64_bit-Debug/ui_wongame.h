/********************************************************************************
** Form generated from reading UI file 'wongame.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WONGAME_H
#define UI_WONGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_wongame
{
public:
    QLabel *returnmenulabel;
    QPushButton *pushButton;

    void setupUi(QDialog *wongame)
    {
        if (wongame->objectName().isEmpty())
            wongame->setObjectName("wongame");
        wongame->resize(1125, 750);
        returnmenulabel = new QLabel(wongame);
        returnmenulabel->setObjectName("returnmenulabel");
        returnmenulabel->setGeometry(QRect(0, 0, 1121, 751));
        pushButton = new QPushButton(wongame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(460, 660, 201, 41));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        pushButton->setPalette(palette);
        pushButton->setStyleSheet(QString::fromUtf8("font: 12pt \"Times New Roman\";"));

        retranslateUi(wongame);

        QMetaObject::connectSlotsByName(wongame);
    } // setupUi

    void retranslateUi(QDialog *wongame)
    {
        wongame->setWindowTitle(QCoreApplication::translate("wongame", "Dialog", nullptr));
        returnmenulabel->setText(QString());
        pushButton->setText(QCoreApplication::translate("wongame", "Return to Main Menue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wongame: public Ui_wongame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WONGAME_H
