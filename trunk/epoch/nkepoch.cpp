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

#include "nkepoch.h"
#include <iostream>
#include <stdexcept> 
#include <QMessageBox>

NKEpoch::NKEpoch(  ) 
{
	m_YY=0;
	isSelect=false;
	select=0;
}
bool NKEpoch::AddEpohu(NKhron *ep){
	try{
		if(GetBrojEpoha()>0){
			NKJD dd(ep->GetApStart());
			for(int i = 0; i < vhron.size(); ++i){
				NKJD tren=vhron.at(i)->GetApStart();
				if(tren.VeceE(dd)){
					vhron.insert(i,ep);
					return true;
				}
			}
		}
		else{
			vhron.prepend(ep);
		}
		vhron.push_back(ep);
	}
	catch (const std::exception& e){
		return false;
	}

	return true;
}

int NKEpoch::GetBrojEpoha(void){
	return (vhron.size());
}

void NKEpoch::Draw(QPainter *painter,NKSkala *skala,int Y)
{
	if(GetBrojEpoha()>0){
		for(QVector<NKhron*>::const_iterator qq = vhron.begin(); qq != vhron.end(); ++qq){
			(*qq)->Draw(painter,skala,0,Y);
		}
	}
	
}
bool  NKEpoch::Select(NKSkala *skala,int x,int y){
	if(GetBrojEpoha()>0){
		select=0;
		for(QVector<NKhron*>::iterator qq = vhron.begin(); qq != vhron.end(); ++qq){
			if((*qq)->Select(skala,x,y)){
				isSelect=true;
				select=(*qq);
				return true;
			}
			
		}
	}
	return false;
}
bool  NKEpoch::SelectID(int id){
	if(GetBrojEpoha()>0){
		select=0;
		for(int i = 0; i < vhron.size(); ++i){
			if(i==id){
				isSelect=true;
				select=vhron.at(i);
				select->SetIsSel(true);

				return true;
			}

		}
	}
	return false;
}
void  NKEpoch::ClearSelection(){
	isSelect=false;
	if(select)
		select->SetIsSel(false);
	select=0;
}

NKhron* NKEpoch::GetSelHro() {
		return select;
}
void  NKEpoch::Cut(QTreeWidget *tree,QTreeWidget *pp,QTreeWidget *tl){
	if(select){
		JD st=select->GetApStart();
		NKRelPerson* rp = NULL;
		rp = dynamic_cast<NKRelPerson*> (select);
		if(rp){

			NKApsPerson* aph=new NKApsPerson;
			aph->SetStartDate(st);
			aph->SetEndDate(select->GetEndDate());
			aph->SetPozY(select->GetPozY());
			aph->setIndex(select->getIndex());
			aph->setLineColor(select->getLineColor());
			aph->setName(select->getName());
			aph->setDesc(select->getDesc());
			aph->setZoom(select->getZoom());
			aph->setRenderType(select->getRenderType());
			aph->setEventType(select->getEventType());
			aph->setRelLinkDraw(select->getRelLinkDraw());
			aph->setPindex(-1);

			Odvezi();
			vhron.replace(GetIndex(select),aph);
			Zavezi();
			tree->clear();
			pp->clear();
			tl->clear();
			for(int i = 0; i < vhron.size(); ++i){
				vhron.at(i)->rebuidTree();
			}
			if(select)
				delete(select);
			select=aph;
		}
		else{
			NKRelEpoch* re = NULL;
			re = dynamic_cast<NKRelEpoch*> (select);
			NKRelEvent* rev = NULL;
			rev = dynamic_cast<NKRelEvent*> (select);
			if(re){

				NKApsEpoch* aph=new NKApsEpoch;
				aph->SetStartDate(st);
				aph->SetEndDate(select->GetEndDate());
				aph->SetPozY(select->GetPozY());
				aph->setIndex(select->getIndex());
				aph->setLineColor(select->getLineColor());
				aph->setName(select->getName());
				aph->setDesc(select->getDesc());
				aph->setZoom(select->getZoom());
				aph->setRenderType(select->getRenderType());
				aph->setEventType(select->getEventType());
				aph->setRelLinkDraw(select->getRelLinkDraw());
				aph->setPindex(-1);

				Odvezi();
				vhron.replace(GetIndex(select),aph);
				Zavezi();
				tree->clear();
				pp->clear();
				tl->clear();
				for(int i = 0; i < vhron.size(); ++i){
					vhron.at(i)->rebuidTree();
				}
				if(select)
					delete(select);
				select=aph;
			}
			if(rev){

				NKApsEvent* aph=new NKApsEvent;
				aph->SetStartDate(st);
				aph->SetEndDate(0);
				aph->SetPozY(select->GetPozY());
				aph->setIndex(select->getIndex());
				aph->setLineColor(select->getLineColor());
				aph->setName(select->getName());
				aph->setDesc(select->getDesc());
				aph->setZoom(select->getZoom());
				aph->setRenderType(select->getRenderType());
				aph->setEventType(select->getEventType());
				aph->setRelLinkDraw(select->getRelLinkDraw());
				aph->setPindex(-1);

				Odvezi();
				vhron.replace(GetIndex(select),aph);
				Zavezi();
				tree->clear();
				pp->clear();
				tl->clear();
				for(int i = 0; i < vhron.size(); ++i){
					vhron.at(i)->rebuidTree();
				}
				if(select)
					delete(select);
				select=aph;
			}

		}
	}
}
void NKEpoch::UpdateTree(QTreeWidget* tree,QTreeWidget *pp,QTreeWidget *tl)
{
	tree->setColumnCount(2);
	tree->hideColumn(1);
	pp->setColumnCount(2);
	pp->hideColumn(1);
	tl->setColumnCount(3);
	tl->setColumnWidth(0,100);
	tl->hideColumn(2);
	if(GetBrojEpoha()>0){
		for(int i = 0; i < vhron.size(); ++i){
			NKhron *hh=vhron.at(i);
         	NKRelEvent* epr = NULL;
			epr = dynamic_cast<NKRelEvent*> (hh);
			if(!epr){
		    NKApsPerson* epr = NULL;
		    NKRelPerson* eprr = NULL;
			epr = dynamic_cast<NKApsPerson*> (hh);
			eprr = dynamic_cast<NKRelPerson*> (hh);
			if(epr || eprr){
					vhron.at(i)->getTreeppItem()->setData(1,0,i);
					vhron.at(i)->getTreeppItem()->setData(0,0,vhron.at(i)->getName());
					pp->insertTopLevelItem(0,vhron.at(i)->getTreeppItem());

			}
			}

			vhron.at(i)->getTreeItem()->setData(1,0,i);
			vhron.at(i)->getTreeItem()->setData(0,0,vhron.at(i)->getName());
			tree->insertTopLevelItem(0,vhron.at(i)->getTreeItem());

			NKJD temp(vhron.at(i)->GetApStart());
			QString da;
			da.setNum(abs(temp.GetGregDay()));
			da=da.rightJustified(2,'0');
			QString mm;
			mm.setNum(abs(temp.GetGregMonth()));
			mm=mm.rightJustified(2,'0');
		    QString dd=QString("%1.%2.%3").arg(da).arg(mm).arg(temp.GetGregYear());
			vhron.at(i)->getTreetlItem()->setData(0,0,dd);
			vhron.at(i)->getTreetlItem()->setData(1,0,vhron.at(i)->getName());
			vhron.at(i)->getTreetlItem()->setData(2,0,i);
			tl->insertTopLevelItem(0,vhron.at(i)->getTreetlItem());

		}
	}
	tree->sortByColumn(1,Qt::AscendingOrder);
	pp->sortByColumn(1,Qt::AscendingOrder);
	tl->sortByColumn(2,Qt::AscendingOrder);
}
int  NKEpoch::GetIndex(NKhron* hh){
	for(int i = 0; i <vhron.size(); ++i){
		if(vhron.at(i)==hh)
			return i;
	}
	return -1;
}
void NKEpoch::Odvezi(){
	for(int i = 0; i <vhron.size(); ++i){
		vhron.at(i)->setIndex(i);
	}
	for(int i = 0; i <vhron.size(); ++i){
		NKhron* ap=vhron.at(i)->GetApsolute();
		if(ap){
			vhron.at(i)->setPindex(ap->getIndex());
		}
		else{
			vhron.at(i)->setPindex(-1);
		}
	}
}
void NKEpoch::Zavezi(){
	for(int i = 0; i <vhron.size(); ++i){
		int ap=vhron.at(i)->getPindex();
		if(ap!=-1){
			vhron.at(i)->setApsEpoch(vhron.at(ap));
		}
		else{
			vhron.at(i)->setApsEpoch(0);
		}
	}
}
void  NKEpoch::Del(QTreeWidget *tree,QTreeWidget *pp,QTreeWidget *tl){
	//prekini sve veze na select zatim ga ugloni i updatuj stabla
	if(select){
			NKhron* temp=select;
			for(int i = 0; i <vhron.size(); ++i){
			  if(vhron.at(i)->GetApsolute()==select){
				  select=vhron.at(i);
				  Cut(tree,pp,tl);
				  select=temp;
			  }
			}

			vhron.remove(GetIndex(temp));
			if(GetIndex(temp)!=-1)
				vhron.remove(GetIndex(temp));

			tree->clear();
			pp->clear();
			tl->clear();
			for(int i = 0; i < vhron.size(); ++i){
				vhron.at(i)->rebuidTree();
			}

		}
		select=0;
		isSelect=false;
}
void NKEpoch::Link(NKhron* pre,QTreeWidget *tree,QTreeWidget *pp,QTreeWidget *tl){
	//dodaj relativni posavi osobine apsolutnog, premesti druge linkove na njega
	//obrisi stari apsolutni
	if(pre){
		if(select!=pre){
		JD stp=pre->GetApStart();
		NKRelEpoch* re1 = NULL;
		re1 = dynamic_cast<NKRelEpoch*> (select);
		NKApsEpoch* ae1 = NULL;
		ae1 = dynamic_cast<NKApsEpoch*> (select);
		if(ae1 || re1){
				JD st=select->GetApStart();
				NKApsPerson* rp = NULL;
				rp = dynamic_cast<NKApsPerson*> (pre);
				if(rp){

					NKRelPerson* aph=new NKRelPerson(select);
					NKJD start(stp);
					start.SubDay(st);
					aph->SetStartDate(start.GetJD());
					aph->SetEndDate(pre->GetEndDate());
					aph->SetPozY(pre->GetPozY());
					aph->setLineColor(pre->getLineColor());
					aph->setName(pre->getName());
					aph->setDesc(pre->getDesc());
					aph->setZoom(pre->getZoom());
					aph->setRenderType(pre->getRenderType());
					aph->setEventType(pre->getEventType());
					aph->setRelLinkDraw(pre->getRelLinkDraw());
					aph->setIndex(pre->getIndex());
					aph->setPindex(pre->getPindex());

					AddEpohu(aph);
					for(int i = 0; i < vhron.size(); ++i){
						if(vhron.at(i)->GetApsolute()==pre){
							vhron.at(i)->setApsEpoch(aph);
						}
					}
					select->SetIsSel(false);
					select=pre;
					Del(tree,pp,tl);
					tree->clear();
					pp->clear();
					tl->clear();
					for(int i = 0; i < vhron.size(); ++i){
						vhron.at(i)->rebuidTree();
					}
				}
				else{
					NKApsEpoch* re = NULL;
					re = dynamic_cast<NKApsEpoch*> (pre);
					NKApsEvent* rev = NULL;
					rev = dynamic_cast<NKApsEvent*> (pre);
					if(re){

						NKRelEpoch* aph=new NKRelEpoch(select);
						NKJD start(stp);
						start.SubDay(st);
						aph->SetStartDate(start.GetJD());
						aph->SetEndDate(pre->GetEndDate());
						aph->SetPozY(pre->GetPozY());
						aph->setLineColor(pre->getLineColor());
						aph->setName(pre->getName());
						aph->setDesc(pre->getDesc());
						aph->setZoom(pre->getZoom());
						aph->setRenderType(pre->getRenderType());
						aph->setEventType(pre->getEventType());
						aph->setRelLinkDraw(pre->getRelLinkDraw());
						aph->setIndex(pre->getIndex());
						aph->setPindex(pre->getPindex());

						AddEpohu(aph);
						for(int i = 0; i < vhron.size(); ++i){
							if(vhron.at(i)->GetApsolute()==pre){
								vhron.at(i)->setApsEpoch(aph);
							}
						}
						select->SetIsSel(false);
						select=pre;
						Del(tree,pp,tl);
						tree->clear();
						pp->clear();
						tl->clear();
						for(int i = 0; i < vhron.size(); ++i){
							vhron.at(i)->rebuidTree();
						}

					}
					if(rev){

						NKRelEvent* aph=new NKRelEvent(select);
						NKJD start(stp);
						start.SubDay(st);
						aph->SetStartDate(start.GetJD());
						aph->SetEndDate(0);
						aph->SetPozY(pre->GetPozY());
						aph->setLineColor(pre->getLineColor());
						aph->setName(pre->getName());
						aph->setDesc(pre->getDesc());
						aph->setZoom(pre->getZoom());
						aph->setRenderType(pre->getRenderType());
						aph->setEventType(pre->getEventType());
						aph->setRelLinkDraw(pre->getRelLinkDraw());
						aph->setIndex(pre->getIndex());
						aph->setPindex(pre->getPindex());
						Odvezi();

						AddEpohu(aph);
						for(int i = 0; i < vhron.size(); ++i){
							if(vhron.at(i)->GetApsolute()==pre){
								vhron.at(i)->setApsEpoch(aph);
							}
						}
						select->SetIsSel(false);
						select=pre;
						Del(tree,pp,tl);
						tree->clear();
						pp->clear();
						tl->clear();
						for(int i = 0; i < vhron.size(); ++i){
							vhron.at(i)->rebuidTree();
						}
					}

				}
			//////////////
		}
	}}
}
