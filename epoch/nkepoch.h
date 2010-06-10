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

#ifndef NKEPOCH_H
#define NKEPOCH_H
#include <QTreeWidget>
#include <QVector>
#include "nkskala.h"
#include "nkhron.h"
#include "nkapsepoch.h"
#include "nkrelepoch.h"
#include "nkapsevent.h"
#include "nkrelevent.h"
#include "nkapsperson.h"
#include "nkrelperson.h"

class NKEpoch  
{

public:
	NKEpoch();
	bool AddEpohu(NKhron *ep);
	int GetBrojEpoha(void);
	void Draw(QPainter *painter,NKSkala *skala,int Y,short kateg,int zoom);
	bool Select(NKSkala *skala,int x,int y);
	void ClearSelection();
	NKhron* GetSelHro();
	void UpdateTree(QTreeWidget *tree,QTreeWidget *pp,QTreeWidget *tl);
	bool SelectID(int id);
	void Cut(QTreeWidget *tree,QTreeWidget *pp,QTreeWidget *tl);
	void Del(QTreeWidget *tree,QTreeWidget *pp,QTreeWidget *tl);
	void Link(NKhron* pre,QTreeWidget *tree,QTreeWidget *pp,QTreeWidget *tl);
	void ocisti();
private:
	NKhron* Getvhron(int aa) {return(vhron[aa]);};
	int GetIndex(NKhron* hh);
	void Odvezi();
	void Zavezi();
	QVector<NKhron*> vhron;
	int m_YY;
	NKhron* select;
	bool isSelect;	
};
#endif
