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

#ifndef NKAPSPERSON_H
#define NKAPSPERSON_H
//
#include "nkapsepoch.h"
//
class NKApsPerson : public NKApsEpoch
{

public:
	NKApsPerson();
	virtual ~NKApsPerson();
	virtual void rebuidTree();
        bool getIsMale() {return male;}
	void setIsMale(bool m) {
		male=m;
		if(male)
			treeppItem->setTextColor(0,Qt::blue);
		else
			treeppItem->setTextColor(0,Qt::magenta);

	};
private:
	bool male;
};
#endif
