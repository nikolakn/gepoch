/*
 * This file is part of Epoch, a timeline program
 *
 * Copyright (C) 2008-2010 Nikola Knezevic <nkcodeplus@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui/QMainWindow>
#include <QtCore/QMap>
#include "nkview.h"
#include "nkskala.h"
#include "nkepoch.h"
#include "nkhron.h"
class QtVariantProperty;
class QtProperty;
class QtBrowserIndex;
class QTextEdit;
class QComboBox;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private slots:
    void newEpoch();
    void save();
    void print();
    void undo();
    void about();
    void mleft();
    void mright();
    void status();
    void zoomin();
    void zoomout();
    void cut();
    void del();
    void link();
    void valueChanged(QtProperty *property, const QVariant &value);
    void itemClicked();
    void kategorijaChanged(const QString &size);
    void godinaChanged();
private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWindows();
    void addProperty(QtVariantProperty *property, const QString &id);
    void updateExpandState();
    NKView *view;
    NKSkala *skala;
    class QtVariantPropertyManager *variantManager;
    class QtTreePropertyBrowser *propertyEditor;
    QMap<QtProperty *, QString> propertyToId;
    QMap<QString, QtVariantProperty *> idToProperty;
    QMap<QString, bool> idToExpanded;

    QTreeWidget *timelineList;
    QTreeWidget *peopleList;
    QTreeWidget *Tree;
    QTextEdit *decW;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *posToolBar;
    QToolBar *addEpochToolBar;	    
    
    QTextEdit *godina;
    QComboBox *kategorija;

    QAction *newEpochAct;
    QAction *saveAct;
    QAction *printAct;
    QAction *undoAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *quitAct;
    QAction *moveLeft;
    QAction *moveRight;
    QAction *zoomIn;
    QAction *zoomOut;
    QAction *aEpoha;
    QAction *rEpoha;
    QAction *aDog;
    QAction *rDog;
    QAction *aPer;
    QAction *rPer;
    QAction *cutAct;
    QAction *linkAct;
    QAction *delAct;
    QAction *deleteAction;

    NKEpoch Doc;


};

#endif
