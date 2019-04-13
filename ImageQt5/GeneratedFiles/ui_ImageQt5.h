/********************************************************************************
** Form generated from reading UI file 'ImageQt5.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEQT5_H
#define UI_IMAGEQT5_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindow
{
public:
    QAction *actionOpenImage;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionClose;
    QAction *actionQuit;
    QAction *actionOpenRaw;
    QAction *actionAbout;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile_F;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;

    void setupUi(QMainWindow *mainwindow)
    {
        if (mainwindow->objectName().isEmpty())
            mainwindow->setObjectName(QString::fromUtf8("mainwindow"));
        mainwindow->resize(800, 600);
        mainwindow->setAutoFillBackground(true);
        actionOpenImage = new QAction(mainwindow);
        actionOpenImage->setObjectName(QString::fromUtf8("actionOpenImage"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ImageQt5/Resources/open.png"), QSize(), QIcon::Normal, QIcon::On);
        actionOpenImage->setIcon(icon);
        actionSave = new QAction(mainwindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ImageQt5/Resources/save.png"), QSize(), QIcon::Normal, QIcon::On);
        actionSave->setIcon(icon1);
        actionSaveAs = new QAction(mainwindow);
        actionSaveAs->setObjectName(QString::fromUtf8("actionSaveAs"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ImageQt5/Resources/save_as.png"), QSize(), QIcon::Normal, QIcon::On);
        actionSaveAs->setIcon(icon2);
        actionClose = new QAction(mainwindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionQuit = new QAction(mainwindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionOpenRaw = new QAction(mainwindow);
        actionOpenRaw->setObjectName(QString::fromUtf8("actionOpenRaw"));
        actionAbout = new QAction(mainwindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(mainwindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        mainwindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mainwindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile_F = new QMenu(menuBar);
        menuFile_F->setObjectName(QString::fromUtf8("menuFile_F"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        mainwindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mainwindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainwindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mainwindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        mainwindow->setStatusBar(statusBar);
        dockWidget_3 = new QDockWidget(mainwindow);
        dockWidget_3->setObjectName(QString::fromUtf8("dockWidget_3"));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        dockWidget_3->setWidget(dockWidgetContents_3);
        mainwindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_3);

        menuBar->addAction(menuFile_F->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile_F->addAction(actionOpenImage);
        menuFile_F->addAction(actionOpenRaw);
        menuFile_F->addSeparator();
        menuFile_F->addAction(actionSave);
        menuFile_F->addAction(actionSaveAs);
        menuFile_F->addSeparator();
        menuFile_F->addAction(actionClose);
        menuFile_F->addSeparator();
        menuFile_F->addAction(actionQuit);
        menuHelp->addAction(actionAbout);

        retranslateUi(mainwindow);

        QMetaObject::connectSlotsByName(mainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainwindow)
    {
        mainwindow->setWindowTitle(QApplication::translate("mainwindow", "ImageQt5", nullptr));
        actionOpenImage->setText(QApplication::translate("mainwindow", "Open Image...", nullptr));
#ifndef QT_NO_SHORTCUT
        actionOpenImage->setShortcut(QApplication::translate("mainwindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("mainwindow", "Save", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("mainwindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionSaveAs->setText(QApplication::translate("mainwindow", "Save as...", nullptr));
        actionClose->setText(QApplication::translate("mainwindow", "Close", nullptr));
#ifndef QT_NO_SHORTCUT
        actionClose->setShortcut(QApplication::translate("mainwindow", "Ctrl+W", nullptr));
#endif // QT_NO_SHORTCUT
        actionQuit->setText(QApplication::translate("mainwindow", "Quit", nullptr));
#ifndef QT_NO_SHORTCUT
        actionQuit->setShortcut(QApplication::translate("mainwindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        actionOpenRaw->setText(QApplication::translate("mainwindow", "Open Raw...", nullptr));
        actionAbout->setText(QApplication::translate("mainwindow", "About", nullptr));
        menuFile_F->setTitle(QApplication::translate("mainwindow", "File", nullptr));
        menuHelp->setTitle(QApplication::translate("mainwindow", "Help", nullptr));
        dockWidget_3->setWindowTitle(QApplication::translate("mainwindow", "Toolbox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwindow: public Ui_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEQT5_H
