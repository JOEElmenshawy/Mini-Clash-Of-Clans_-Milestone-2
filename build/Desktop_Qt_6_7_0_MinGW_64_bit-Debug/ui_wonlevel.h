/********************************************************************************
** Form generated from reading UI file 'wonlevel.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WONLEVEL_H
#define UI_WONLEVEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WonLevel
{
public:
    QLabel *nextlevellabel;
    QPushButton *pushButton;

    void setupUi(QDialog *WonLevel)
    {
        if (WonLevel->objectName().isEmpty())
            WonLevel->setObjectName("WonLevel");
        WonLevel->resize(1125, 750);
        nextlevellabel = new QLabel(WonLevel);
        nextlevellabel->setObjectName("nextlevellabel");
        nextlevellabel->setGeometry(QRect(0, 0, 1121, 751));
        pushButton = new QPushButton(WonLevel);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(500, 620, 131, 41));
        QPalette palette;
        QBrush brush(QColor(255, 0, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        pushButton->setPalette(palette);
        pushButton->setStyleSheet(QString::fromUtf8("font: 12pt \"Times New Roman\";"));

        retranslateUi(WonLevel);

        QMetaObject::connectSlotsByName(WonLevel);
    } // setupUi

    void retranslateUi(QDialog *WonLevel)
    {
        WonLevel->setWindowTitle(QCoreApplication::translate("WonLevel", "Dialog", nullptr));
        nextlevellabel->setText(QString());
        pushButton->setText(QCoreApplication::translate("WonLevel", "Next Level", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WonLevel: public Ui_WonLevel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WONLEVEL_H
