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
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LostWindow
{
public:
    QLabel *returnmenulabel;
    QPushButton *pushButton;

    void setupUi(QDialog *LostWindow)
    {
        if (LostWindow->objectName().isEmpty())
            LostWindow->setObjectName("LostWindow");
        LostWindow->resize(1125, 750);
        returnmenulabel = new QLabel(LostWindow);
        returnmenulabel->setObjectName("returnmenulabel");
        returnmenulabel->setGeometry(QRect(0, 0, 1121, 751));
        pushButton = new QPushButton(LostWindow);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(440, 660, 201, 41));
        QPalette palette;
        QBrush brush(QColor(0, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        pushButton->setPalette(palette);
        pushButton->setStyleSheet(QString::fromUtf8("font: 12pt \"Times New Roman\";"));

        retranslateUi(LostWindow);

        QMetaObject::connectSlotsByName(LostWindow);
    } // setupUi

    void retranslateUi(QDialog *LostWindow)
    {
        LostWindow->setWindowTitle(QCoreApplication::translate("LostWindow", "Dialog", nullptr));
        returnmenulabel->setText(QString());
        pushButton->setText(QCoreApplication::translate("LostWindow", "Return to Main Menue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LostWindow: public Ui_LostWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOSTWINDOW_H
