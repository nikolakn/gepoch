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

#include "nkrelevent.h"
#include <QPainter>
NKRelEvent::NKRelEvent(NKhron *root) 
	: NKhron()
{
	startDate=0;
	endDate=0;
	name="caption";
	desc="";
	posY=100;
	apsEpoch=root;
	isSelect=false;
	zoom=0;
	renderType=0;
	eventType=0;
	relLinkDraw=true;
	treeItem=new QTreeWidgetItem(apsEpoch->getTreeItem());
	treeItem->setText(0,name);
	treeItem->setFlags(Qt::ItemIsEnabled);
	treeItem->setTextColor(0,Qt::green);


	treeppItem=new QTreeWidgetItem(0);
	treeppItem->setText(0,name);
	treeppItem->setFlags(Qt::ItemIsEnabled);
	treeppItem->setTextColor(0,Qt::green);

	treetlItem=new QTreeWidgetItem(0);
	treetlItem->setText(1,name);
	treetlItem->setFlags(Qt::ItemIsEnabled);
	treetlItem->setTextColor(1,Qt::green);
}
//
NKRelEvent::~NKRelEvent()
{

}
void NKRelEvent::rebuidTree(){
	treeItem=new QTreeWidgetItem(apsEpoch->getTreeItem());
	treeItem->setText(0,name);
	treeItem->setFlags(Qt::ItemIsEnabled);
	treeItem->setTextColor(0,Qt::green);


	treeppItem=new QTreeWidgetItem(0);
	treeppItem->setText(0,name);
	treeppItem->setFlags(Qt::ItemIsEnabled);
	treeppItem->setTextColor(0,Qt::green);

	treetlItem=new QTreeWidgetItem(0);
	treetlItem->setText(1,name);
	treetlItem->setFlags(Qt::ItemIsEnabled);
	treetlItem->setTextColor(1,Qt::green);
}
JD NKRelEvent::GetApStart()
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
void NKRelEvent::Draw(QPainter* painter,NKSkala* skala,int ,int YY) 
{
	NKJD d1(GetApStart());
	int x=skala->PolozajZaDatum(d1);
	if(x>=(0)){
			QColor ss=lineColor;	
			if(isSelect){
					
					ss.setBlue(255);
					painter->setPen(ss);
			}
			else{
					painter->setPen(lineColor);
			}
		    
			int ay=apsEpoch->GetPozY();
			painter->drawRect(x-5,(posY+YY)-5,10,10);
			QFont m_Font;
	   		m_Font=QFont("Times", 10);
	   		painter->setFont(m_Font);
			painter->drawText(x+10,(posY+YY+2),name);
		    QPen ol1(ss,1,Qt::DashLine);
    		painter->setPen(ol1);
    		if(posY>=ay){
    			painter->drawLine(x,posY+YY-5,x,ay+YY);
   			}
   			else{
   				painter->drawLine(x,posY+YY+5,x,ay+YY);
  			}
			
	}
}
bool NKRelEvent::Select(NKSkala *skala,int x,int y){
		NKJD d1(GetApStart());
			int poc=skala->PolozajZaDatum(d1);
		if(poc>=0){
			if((x>=(poc-5)) && (x<=poc+5)){
	 			if(y>=(posY-5) && y<=(posY+5)){
					isSelect=true;
					return true;	
				}					
			}
			
		}
	return false;
}
