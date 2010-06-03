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

#ifndef NKHRON_H
#define NKHRON_H

#include "nkskala.h"
#include <QTreeWidgetItem>
class NKhron
{
protected:
	JD startDate;
	JD endDate;
	QString name;
	QString desc;
	int posY;
	NKhron *apsEpoch; //absolute epoch for this
	QColor textColor;
	QColor lineColor;
	QColor beckColor;
	bool isSelect;
	QTreeWidgetItem* treeItem;
	QTreeWidgetItem* treeppItem;
	QTreeWidgetItem* treetlItem;
	int index;
	int pindex;
	int zoom;
	short renderType;
	short eventType;
	bool relLinkDraw;
public:
	NKhron();
	
	//virtual
	virtual ~NKhron();
	virtual void Draw(QPainter* ,NKSkala* ,int ,int )=0;
	virtual bool Select(NKSkala *skala,int x,int y)=0;
	virtual void rebuidTree()=0;
	//actual start of the epoch in absolute(real) date
	virtual JD GetApStart()=0;
    short getEventType() const
    {
        return eventType;
    }

    bool getRelLinkDraw() const
    {
        return relLinkDraw;
    }

    short getRenderType() const
    {
        return renderType;
    }

    void setEventType(short  eventType)
    {
        this->eventType = eventType;
    }

    void setRelLinkDraw(bool relLinkDraw)
    {
        this->relLinkDraw = relLinkDraw;
    }

    void setRenderType(short  renderType)
    {
        this->renderType = renderType;
    }

    QString getDesc() const
    {
        return desc;
    }

    void setDesc(QString desc)
    {
        this->desc = desc;
    }

    int getPindex() const
    {
        return pindex;
    }

    void setPindex(int pindex)
    {
        this->pindex = pindex;
    }

    int getIndex() const
    {
        return index;
    }

    void setIndex(int index)
    {
        this->index = index;
    }

    NKhron *getApsEpoch() const
    {
        return apsEpoch;
    }

    void setApsEpoch(NKhron *apsEpoch)
    {
        this->apsEpoch = apsEpoch;
    }

    QTreeWidgetItem *getTreetlItem() const
    {
        return treetlItem;
    }

    void setTreetlItem(QTreeWidgetItem *treetlItem)
    {
        this->treetlItem = treetlItem;
    }

    QTreeWidgetItem *getTreeppItem() const
    {
        return treeppItem;
    }

    void setTreeppItem(QTreeWidgetItem *treeppItem)
    {
        this->treeppItem = treeppItem;
    }

    QTreeWidgetItem *getTreeItem() const
    {
        return treeItem;
    }

    void setTreeItem(QTreeWidgetItem *treeItem)
    {
        this->treeItem = treeItem;
    }

    QColor getLineColor() const
    {
        return lineColor;
    }

    void setLineColor(QColor lineColor)
    {
        this->lineColor = lineColor;
    }

    QString getName() const
    {
        return name;
    }

    void setName(QString name)
    {
        this->name = name;
    }

    //set get
	void SetPozY(int Y) {posY=Y;};
	int GetPozY() {return posY;};
	JD GetStartDate() {return startDate;};
	JD GetEndDate() {return endDate;};	
	void SetStartDate(JD d1) {startDate=d1;};
	void SetEndDate(JD d2) {endDate=d2;};
	NKhron* GetApsolute() {return apsEpoch;};
	void SetIsSel(bool is) {isSelect=is;};
	bool GetIsSel() {return isSelect;};
};
#endif
