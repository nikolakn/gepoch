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
#ifndef NKVIEW_H
#define NKVIEW_H
#include <QtGui>

#include "nkskala.h"
#include "nkepoch.h"
#include "nkhron.h"
#include "nkapsepoch.h"
#include "nkrelepoch.h"
#include "nkapsevent.h"
#include "nkrelevent.h"
#include "nkapsperson.h"
#include "nkrelperson.h"
class NKView  : public QWidget
{
    Q_OBJECT
public:
   NKView(QWidget *parent = 0, NKSkala *skala=0, NKEpoch *document=0,QTreeWidget *Tree=0);
   QString getStatus() {return status;};
   void setTree(QTreeWidget *Tree,QTreeWidget *Treepp,QTreeWidget *Treetl) {mTree=Tree;mTreepp=Treepp;mTreetl=Treetl;};
   void setKat(short kk) {kateg=kk;};
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent (QMouseEvent * event);
    void mouseDoubleClickEvent ( QMouseEvent * event );
public:
signals:
    void statusSig();
    void itemClicked();
    void itemDoubleClicked();
private slots:
    void selectFromTree( QTreeWidgetItem  * item, int column );
    void selectFromppTree( QTreeWidgetItem  * item, int column );
    void selectFromtlTree( QTreeWidgetItem  * item, int column );
        void aepoha();
        void adog();
        void aPer();
        void rPer();
        void repoha();
    void rdog();

        void adel();
        void acut();
    void alink();
private:
    NKSkala *m_skala;
    NKEpoch *doc;
    QTreeWidget *mTree;
    QTreeWidget *mTreepp;
    QTreeWidget *mTreetl;
    QString status;
    bool grid;  
    short menuAc;
    QPoint clik;
    QPoint clik2;
    bool isSelect;
    bool isMove;
    bool islink;
    NKhron *pre;
    int dy;
    bool pomeri;
    short kateg;
};

#endif // NKVIEW_H
