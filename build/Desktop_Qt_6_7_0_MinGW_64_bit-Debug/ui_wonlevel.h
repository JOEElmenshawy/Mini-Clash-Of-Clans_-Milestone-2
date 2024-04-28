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

QT_BEGIN_NAMESPACE

class Ui_WonLevel
{
public:
    QLabel *nextlevellabel;

    void setupUi(QDialog *WonLevel)
    {
        if (WonLevel->objectName().isEmpty())
            WonLevel->setObjectName("WonLevel");
        WonLevel->resize(852, 485);
        nextlevellabel = new QLabel(WonLevel);
        nextlevellabel->setObjectName("nextlevellabel");
        nextlevellabel->setGeometry(QRect(20, 19, 821, 541));

        retranslateUi(WonLevel);

        QMetaObject::connectSlotsByName(WonLevel);
    } // setupUi

    void retranslateUi(QDialog *WonLevel)
    {
        WonLevel->setWindowTitle(QCoreApplication::translate("WonLevel", "Dialog", nullptr));
        nextlevellabel->setText(QCoreApplication::translate("WonLevel", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WonLevel: public Ui_WonLevel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WONLEVEL_H
