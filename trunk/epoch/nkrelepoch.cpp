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

#include "nkrelepoch.h"
#include "nkjd.h"
#include <QPainter>
#include "nkapsepoch.h"
#include "nkapsperson.h"
#include "nkrelperson.h"
class NKApsPerson;
class NKRelPerson;

NKRelEpoch::NKRelEpoch(NKhron *root,bool relper)
	: NKhron()
{
	startDate=0;
	endDate=0;
	name="caption";
	desc="";
	posY=100;
	apsEpoch=root;
	textColor.black();
	lineColor.black();
	beckColor.black();
	isSelect=false;

	treeItem=new QTreeWidgetItem(apsEpoch->getTreeItem());
	treeItem->setText(0,name);
	treeItem->setFlags(Qt::ItemIsEnabled);

	if(relper){
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

	}
	else{
		treeppItem=new QTreeWidgetItem(apsEpoch->getTreeppItem());
		treeppItem->setText(0,name);
		treeppItem->setFlags(Qt::ItemIsEnabled);
	}


	treetlItem=new QTreeWidgetItem(0);
	treetlItem->setText(1,name);
	treetlItem->setFlags(Qt::ItemIsEnabled);

}
//
NKRelEpoch::~NKRelEpoch()
{
}
void NKRelEpoch::rebuidTree(){

	treeItem=new QTreeWidgetItem(apsEpoch->getTreeItem());
	treeItem->setText(0,name);
	treeItem->setFlags(Qt::ItemIsEnabled);


	treeppItem=new QTreeWidgetItem(apsEpoch->getTreeppItem());
	treeppItem->setText(0,name);
	treeppItem->setFlags(Qt::ItemIsEnabled);

	treetlItem=new QTreeWidgetItem(0);
	treetlItem->setText(1,name);
	treetlItem->setFlags(Qt::ItemIsEnabled);


}
JD NKRelEpoch::GetApStart()
{
	NKApsEpoch* ep1 = NULL;
	ep1 = dynamic_cast<NKApsEpoch*> (apsEpoch);
	if(ep1){
	 	JD d1=ep1->GetApStart();
		NKJD temp;
	 	temp.SetJD(d1);
		temp.AddDay(startDate);
		return temp.GetJD();
	}
	NKRelEpoch *rel=NULL;
	rel=dynamic_cast<NKRelEpoch*> (apsEpoch);
	if(!rel)
		return 0;
	JD d1=rel->GetApStart();
 	NKJD temp;
	temp.SetJD(d1);
 	temp.AddDay(startDate);
	return temp.GetJD();
}
void NKRelEpoch::Draw(QPainter* painter,NKSkala* skala,int ,int YY) 
{
	NKJD d1(GetApStart());
	int x=skala->PolozajZaDatum(d1);
	if(x>=(-1)){
		NKJD d2(endDate);
		d2.AddDay(d1.GetJD());
		int x2=skala->PolozajZaDatum(d2);
		if(x2!=-1) {
			if(x2<-1)
				x2=x2*-1;
			QColor ss=lineColor;	
			if(isSelect){
					
					ss.setBlue(255);
					painter->setPen(ss);
			}
			else{
					painter->setPen(lineColor);
			}
		    int xt=x;
		    if(x==-1)
		    	xt=5;
		    int ay=apsEpoch->GetPozY();
			painter->drawLine(x,posY+YY,x2,posY+YY);
			QFont m_Font;
	   		m_Font=QFont("Times", 10);
	   		painter->setFont(m_Font);
			painter->drawText(xt,(posY+YY+10),name);
		    QPen ol1(ss,1,Qt::DashLine);
    		painter->setPen(ol1);
			painter->drawLine(x,posY+YY,x,ay+YY);
	}
	}
};
bool NKRelEpoch::Select(NKSkala *skala,int x,int y){
		NKJD d1(GetApStart());
		int poc=skala->PolozajZaDatum(d1);
		NKJD d2(endDate);
		d2.AddDay(d1.GetJD());
		int kraj=skala->PolozajZaDatum(d2);
	    if(kraj<-1)
	    	kraj=kraj*-1;
		if(x>=poc && x<=kraj){
			if(y>=(posY-3) && y<=(posY+3)){
				isSelect=true;
				return true;	
			}
							
			
		}
	return false;
}