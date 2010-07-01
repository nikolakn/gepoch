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

#include "nkapsepoch.h"
#include <QPainter>
NKApsEpoch::NKApsEpoch(  ) 
	: NKhron()
{
	startDate=0;
	endDate=0;
	name="caption";
	desc="";
	posY=100;
	apsEpoch=0;
	zoom=0;
	renderType=0;
	eventType=0;
	relLinkDraw=true;

	textColor.black();
	lineColor.black();
	beckColor.black();
	isSelect=false;
	treeItem=new QTreeWidgetItem(0);
	treeItem->setText(0,name);
	treeItem->setFlags(Qt::ItemIsEnabled);

	treeppItem=new QTreeWidgetItem(0);
	treeppItem->setText(0,name);
	treeppItem->setFlags(Qt::ItemIsEnabled);

	treetlItem=new QTreeWidgetItem(0);
	treetlItem->setText(1,name);
	treetlItem->setFlags(Qt::ItemIsEnabled);
}
//
NKApsEpoch::~NKApsEpoch()
{
}
//
void NKApsEpoch::rebuidTree(){
	treeItem=new QTreeWidgetItem(0);
	treeItem->setText(0,name);
	treeItem->setFlags(Qt::ItemIsEnabled);

	treeppItem=new QTreeWidgetItem(0);
	treeppItem->setText(0,name);
	treeppItem->setFlags(Qt::ItemIsEnabled);

	treetlItem=new QTreeWidgetItem(0);
	treetlItem->setText(1,name);
	treetlItem->setFlags(Qt::ItemIsEnabled);
}
void NKApsEpoch::Draw(QPainter* painter,NKSkala* skala,int ,int YY) 
{
	NKJD d1(startDate);
	int x=skala->PolozajZaDatum(d1);
	if(x>=(-1)){
		NKJD d2(endDate);
		d2.AddDay(d1.GetJD());
		int x2=skala->PolozajZaDatum(d2);
		if(x2!=-1) {
			if(x2<-1)
				x2=x2*-1;
			if(isSelect){
					QColor ss=lineColor;
					ss.setBlue(255);
					painter->setPen(ss);
			}
			else{
					painter->setPen(lineColor);
			}
		    int xt=x;
		    if(x==-1)
		    	xt=5;
		    if(renderType==0 || renderType==2 || renderType==3 || renderType==4){
				painter->drawLine(x,posY+YY,x2,posY+YY);
				QFont m_Font;
				m_Font=QFont("Times", 10);
				painter->setFont(m_Font);
				painter->drawText(xt+2,(posY+YY+12),name);
		    }
		    if(renderType==1){
				//painter->drawLine(x,posY+YY,x2,posY+YY);
				painter->drawRect(x,posY+YY,x2-x,15);
				//painter->fillRect(x,posY+YY,x2,15,Qt::white);
				QFont m_Font;
				m_Font=QFont("Times", 10);
				painter->setFont(m_Font);
				painter->drawText(xt+2,(posY+YY+12),name);
		    }
	}
	}
};
bool NKApsEpoch::Select(NKSkala *skala,int x,int y){
    if(renderType==0  || renderType==2 || renderType==3 || renderType==4){
		NKJD d1(startDate);
		int poc=skala->PolozajZaDatum(d1);
		NKJD d2(endDate);
		d2.AddDay(d1.GetJD());
		int kraj=skala->PolozajZaDatum(d2);
	    if(kraj<-1)
	    	kraj=kraj*-1;
		if(x>=poc && x<=kraj){
			if(y>=(posY-4) && y<=(posY+4)){
				isSelect=true;
				return true;
			}
		}
    }
    if(renderType==1){
		NKJD d1(startDate);
		int poc=skala->PolozajZaDatum(d1);
		NKJD d2(endDate);
		d2.AddDay(d1.GetJD());
		int kraj=skala->PolozajZaDatum(d2);
	    if(kraj<-1)
	    	kraj=kraj*-1;
		if(x>=poc && x<=kraj){
			if(y>=(posY-4) && y<=(posY+19)){
				isSelect=true;
				return true;	
			}
		}
    }
	return false;
}
