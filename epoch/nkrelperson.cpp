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

#include "nkrelperson.h"
#include "nkapsperson.h"

class NKApsPerson;
NKRelPerson::NKRelPerson(NKhron *root) 
	: NKRelEpoch(root,true)
{
		name="name";
		isSelect=false;
		male=true;
		zoom=0;
		renderType=0;
		eventType=0;
		relLinkDraw=true;
		treeItem->setText(0,name);
		treeItem->setTextColor(0,Qt::blue);

		treeppItem->setText(0,name);
		treeppItem->setTextColor(0,Qt::blue);

		treetlItem->setText(1,name);
		treetlItem->setTextColor(1,Qt::blue);
}
//
NKRelPerson::~NKRelPerson()
{
}
void NKRelPerson::rebuidTree(){

	treeItem=new QTreeWidgetItem(apsEpoch->getTreeItem());
	treeItem->setText(0,name);
	treeItem->setFlags(Qt::ItemIsEnabled);

	NKRelEpoch* re = NULL;
	re = dynamic_cast<NKRelEpoch*> (apsEpoch);
	NKApsEpoch* ae = NULL;
	ae = dynamic_cast<NKApsEpoch*> (apsEpoch);

	NKApsPerson* ap = NULL;
	ap = dynamic_cast<NKApsPerson*> (apsEpoch);
	NKRelPerson* rp = NULL;
	rp = dynamic_cast<NKRelPerson*> (apsEpoch);
	if(((ae || re) && !ap) && !rp){
		treeppItem=new QTreeWidgetItem(0);
		treeppItem->setText(0,name);
		treeppItem->setFlags(Qt::ItemIsEnabled);
	}
	else{
	treeppItem=new QTreeWidgetItem(apsEpoch->getTreeppItem());
	treeppItem->setText(0,name);
	treeppItem->setFlags(Qt::ItemIsEnabled);
	}
	treetlItem=new QTreeWidgetItem(0);
	treetlItem->setText(1,name);
	treetlItem->setFlags(Qt::ItemIsEnabled);
	treeItem->setText(0,name);
	treeItem->setTextColor(0,Qt::blue);

	treeppItem->setText(0,name);
	treeppItem->setTextColor(0,Qt::blue);

	treetlItem->setText(1,name);
	treetlItem->setTextColor(1,Qt::blue);
}
