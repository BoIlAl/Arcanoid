/********************************************************************************
** Form generated from reading UI file 'Arcanoid.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARCANOID_H
#define UI_ARCANOID_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ArcanoidClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ArcanoidClass)
    {
        if (ArcanoidClass->objectName().isEmpty())
            ArcanoidClass->setObjectName(QString::fromUtf8("ArcanoidClass"));
        ArcanoidClass->resize(600, 400);
        menuBar = new QMenuBar(ArcanoidClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ArcanoidClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ArcanoidClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ArcanoidClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ArcanoidClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ArcanoidClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ArcanoidClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ArcanoidClass->setStatusBar(statusBar);

        retranslateUi(ArcanoidClass);

        QMetaObject::connectSlotsByName(ArcanoidClass);
    } // setupUi

    void retranslateUi(QMainWindow *ArcanoidClass)
    {
        ArcanoidClass->setWindowTitle(QCoreApplication::translate("ArcanoidClass", "Arcanoid", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ArcanoidClass: public Ui_ArcanoidClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARCANOID_H
