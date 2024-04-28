/********************************************************************************
** Form generated from reading UI file 'lostwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOSTWINDOW_H
#define UI_LOSTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_LostWindow
{
public:
    QLabel *returnmenulabel;

    void setupUi(QDialog *LostWindow)
    {
        if (LostWindow->objectName().isEmpty())
            LostWindow->setObjectName("LostWindow");
        LostWindow->resize(769, 508);
        returnmenulabel = new QLabel(LostWindow);
        returnmenulabel->setObjectName("returnmenulabel");
        returnmenulabel->setGeometry(QRect(0, 0, 771, 511));

        retranslateUi(LostWindow);

        QMetaObject::connectSlotsByName(LostWindow);
    } // setupUi

    void retranslateUi(QDialog *LostWindow)
    {
        LostWindow->setWindowTitle(QCoreApplication::translate("LostWindow", "Dialog", nullptr));
        returnmenulabel->setText(QCoreApplication::translate("LostWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LostWindow: public Ui_LostWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOSTWINDOW_H
