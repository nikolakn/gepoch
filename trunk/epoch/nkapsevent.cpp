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

#include "nkapsevent.h"
#include <QPainter>
NKApsEvent::NKApsEvent(  ) 
	: NKhron()
{
	startDate=0;
	endDate=0;
	name="caption";
	desc="";
	posY=100;
	apsEpoch=0;
	textColor.black();
	lineColor.black();
	beckColor.black();
	zoom=0;
	renderType=0;
	eventType=0;
	relLinkDraw=true;
	isSelect=false;
	treeItem=new QTreeWidgetItem(0);
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
NKApsEvent::~NKApsEvent()
{
}
//
void NKApsEvent::rebuidTree(){
	treeItem=new QTreeWidgetItem(0);
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
void NKApsEvent::Draw(QPainter* painter,NKSkala* skala,int ,int YY) 
{
	NKJD d1(startDate);
	int x=skala->PolozajZaDatum(d1);
	if(x>=0 ){
		if(renderType==0){
			if(isSelect){
					QColor ss=lineColor;
					ss.setBlue(255);
					painter->setPen(ss);
			}
			else{
					painter->setPen(lineColor);
			}

			painter->drawRect(x-5,(posY+YY)-5,10,10);
			QFont m_Font;
	   		m_Font=QFont("Times", 10);
	   		painter->setFont(m_Font);
			painter->drawText(x+8,(posY+YY+4),name);

			QPoint pq(x,posY+YY+14);
			painter->drawImage(pq,getImage());
		}
		if(renderType==1){
			if(isSelect){
					QColor ss=lineColor;
					ss.setBlue(255);
					painter->setPen(ss);
			}
			else{
					painter->setPen(lineColor);
			}

			painter->drawRect(x-5,(posY+YY)-5,10,10);
			QFont m_Font;
	   		m_Font=QFont("Times", 10);
	   		painter->setFont(m_Font);
			painter->drawText(x+8,(posY+YY+4),name);
			QPoint pq(x,posY+YY+14);
			painter->drawImage(pq,getImage());
		}
		if(renderType==2){
			if(isSelect){
					QColor ss=lineColor;
					ss.setBlue(255);
					painter->setPen(ss);
			}
			else{
					painter->setPen(lineColor);
			}
			
			painter->drawRect(x-6,(posY+YY)-6,12,12);
			QFont m_Font;
	   		m_Font=QFont("Times", 11);
	   		painter->setFont(m_Font);
			painter->drawText(x+8,(posY+YY+4),name);

			QPoint pq(x,posY+YY+14);
			painter->drawImage(pq,getImage());
		}
		if(renderType==3){
			if(isSelect){
					QColor ss=lineColor;
					ss.setBlue(255);
					painter->setPen(ss);
			}
			else{
					painter->setPen(lineColor);
			}

			painter->drawRect(x-8,(posY+YY)-8,16,16);
			QFont m_Font;
	   		m_Font=QFont("Times", 12);
	   		painter->setFont(m_Font);
			painter->drawText(x+12,(posY+YY+4),name);
			QPoint pq(x,posY+YY+14);
			painter->drawImage(pq,getImage());
		}
		if(renderType==4){
			if(isSelect){
					QColor ss=lineColor;
					ss.setBlue(255);
					painter->setPen(ss);
			}
			else{
					painter->setPen(lineColor);
			}

			painter->drawRect(x-9,(posY+YY)-9,18,18);
			QFont m_Font;
	   		m_Font=QFont("Times", 13);
	   		painter->setFont(m_Font);
			painter->drawText(x+14,(posY+YY+4),name);
			QPoint pq(x,posY+YY+14);
			painter->drawImage(pq,getImage());
		}
	}
}
bool NKApsEvent::Select(NKSkala *skala,int x,int y){
		NKJD d1(startDate);
		int poc=skala->PolozajZaDatum(d1);
		if(poc>=0){
			if(renderType==0){
			if((x>=(poc-5)) && (x<=poc+5)){
	 			if(y>=(posY-5) && y<=(posY+5)){
					isSelect=true;
					return true;
				}
			}
			}
			if(renderType==1){
			if((x>=(poc-5)) && (x<=poc+5)){
	 			if(y>=(posY-5) && y<=(posY+5)){
					isSelect=true;
					return true;	
				}					
			}
			}
			if(renderType==2){
			if((x>=(poc-6)) && (x<=poc+6)){
	 			if(y>=(posY-6) && y<=(posY+6)){
					isSelect=true;
					return true;
				}
			}
			}
			if(renderType==3){
			if((x>=(poc-8)) && (x<=poc+8)){
	 			if(y>=(posY-8) && y<=(posY+8)){
					isSelect=true;
					return true;
				}
			}
			}
			if(renderType==4){
			if((x>=(poc-9)) && (x<=poc+9)){
	 			if(y>=(posY-9) && y<=(posY+9)){
					isSelect=true;
					return true;
				}
			}
			}
		}
	return false;
}
