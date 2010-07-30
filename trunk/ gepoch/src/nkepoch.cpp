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
class NKRelEpoch;
NKEpoch::NKEpoch() {
	m_YY = 0;
	isSelect = false;
	select = 0;
}
bool NKEpoch::AddEpohu(NKhron *ep) {
	try {
		if (GetBrojEpoha() > 0) {
			NKJD dd(ep->GetApStart());
			for (int i = 0; i < vhron.size(); ++i) {
				NKJD tren = vhron.at(i)->GetApStart();
				if (tren.VeceE(dd)) {
					vhron.insert(i, ep);
					return true;
				}
			}
		}

		vhron.push_back(ep);
	} catch (const std::exception& e) {
		return false;
	}

	return true;
}

int NKEpoch::GetBrojEpoha(void) {
	return (vhron.size());
}

void NKEpoch::Draw(QPainter *painter, NKSkala *skala, int Y, short kateg,
		int zoom) {
	if (GetBrojEpoha() > 0) {
		for (QVector<NKhron*>::const_iterator qq = vhron.begin(); qq
				!= vhron.end(); ++qq) {

			//filtering event type all=0, war, art....
			if ((*qq)->getEventType() == kateg || kateg == 0) {
				//show always
				if ((*qq)->getZoom() == 0) {
					(*qq)->Draw(painter, skala, 0, Y);
				}
				//here+
				if ((*qq)->getZoom() == 1 && (*qq)->getDozoom() >= zoom) {
					(*qq)->Draw(painter, skala, 0, Y);
				}
				//here
				if ((*qq)->getZoom() == 2 && (*qq)->getDozoom() == zoom) {
					(*qq)->Draw(painter, skala, 0, Y);
				}
				//here-
				if ((*qq)->getZoom() == 3 && (*qq)->getDozoom() <= zoom) {
					(*qq)->Draw(painter, skala, 0, Y);
				}

			}
		}
	}

}
bool NKEpoch::Select(NKSkala *skala, int x, int y) {
	if (GetBrojEpoha() > 0) {
		select = 0;
		for (QVector<NKhron*>::iterator qq = vhron.begin(); qq != vhron.end(); ++qq) {
			if ((*qq)->Select(skala, x, y)) {
				isSelect = true;
				select = (*qq);
				return true;
			}

		}
	}
	return false;
}
bool NKEpoch::SelectID(int id) {
	if (GetBrojEpoha() > 0) {
		select = 0;
		for (int i = 0; i < vhron.size(); ++i) {
			if (i == id) {
				isSelect = true;
				select = vhron.at(i);
				select->SetIsSel(true);

				return true;
			}

		}
	}
	return false;
}
void NKEpoch::ClearSelection(QTreeWidget *tree, QTreeWidget *pp,
		QTreeWidget *tl) {
	isSelect = false;
	if (select)
		select->SetIsSel(false);
	select = 0;

}

NKhron* NKEpoch::GetSelHro() {
	return select;
}
void NKEpoch::Cut(QTreeWidget *tree, QTreeWidget *pp, QTreeWidget *tl) {
	if (select) {
		JD st = select->GetApStart();
		NKRelPerson* rp = NULL;
		rp = dynamic_cast<NKRelPerson*> (select);
		if (rp) {

			NKApsPerson* aph = new NKApsPerson;
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
			aph->setIsMale(rp->getIsMale());
			aph->setPindex(-1);
			aph->setDozoom(rp->getDozoom());
			aph->setImage(rp->getImage());
			Odvezi();
			vhron.replace(GetIndex(select), aph);
			Zavezi();
			tree->clear();
			pp->clear();
			tl->clear();
			for (int i = 0; i < vhron.size(); ++i) {
				vhron.at(i)->rebuidTree();
			}
			if (select)
				delete (select);
			select = aph;
		} else {
			NKRelEpoch* re = NULL;
			re = dynamic_cast<NKRelEpoch*> (select);
			NKRelEvent* rev = NULL;
			rev = dynamic_cast<NKRelEvent*> (select);
			if (re) {

				NKApsEpoch* aph = new NKApsEpoch;
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
				aph->setDozoom(select->getDozoom());
				aph->setImage(select->getImage());
				Odvezi();
				vhron.replace(GetIndex(select), aph);
				Zavezi();
				tree->clear();
				pp->clear();
				tl->clear();
				for (int i = 0; i < vhron.size(); ++i) {
					vhron.at(i)->rebuidTree();
				}
				if (select)
					delete (select);
				select = aph;
			}
			if (rev) {

				NKApsEvent* aph = new NKApsEvent;
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
				aph->setDozoom(select->getDozoom());
				aph->setImage(select->getImage());
				Odvezi();
				vhron.replace(GetIndex(select), aph);
				Zavezi();
				tree->clear();
				pp->clear();
				tl->clear();
				for (int i = 0; i < vhron.size(); ++i) {
					vhron.at(i)->rebuidTree();
				}
				if (select)
					delete (select);
				select = aph;
			}

		}
	}
}
//pravi timeline, people i tree stabla za sta je preduslov da hronologije
//budu sortirane po darumu
void NKEpoch::UpdateTree(QTreeWidget* tree, QTreeWidget *pp, QTreeWidget *tl) {
	tree->setColumnCount(2);
	tree->hideColumn(1);
	pp->setColumnCount(2);
	pp->hideColumn(1);
	tl->setColumnCount(3);
	tl->setColumnWidth(0, 100);
	tl->hideColumn(2);

	if (GetBrojEpoha() > 0) {
		int i;
		for (int n = 0; n < vhron.size(); ++n) {
			NKhron *hh = vhron.at(n);
			i = n;

			NKRelEvent* epr = NULL;
			epr = dynamic_cast<NKRelEvent*> (hh);
			if (!epr) {
				NKApsPerson* epr = NULL;
				NKRelPerson* eprr = NULL;
				epr = dynamic_cast<NKApsPerson*> (hh);
				eprr = dynamic_cast<NKRelPerson*> (hh);
				if (epr || eprr) {
					vhron.at(i)->getTreeppItem()->setData(1, 0, i);
					vhron.at(i)->getTreeppItem()->setData(0, 0,
							vhron.at(i)->getName());
					pp->insertTopLevelItem(0, vhron.at(i)->getTreeppItem());

				}
			}

			vhron.at(i)->getTreeItem()->setData(1, 0, i);
			vhron.at(i)->getTreeItem()->setData(0, 0, vhron.at(i)->getName());
			tree->insertTopLevelItem(0, vhron.at(i)->getTreeItem());

			NKJD temp(vhron.at(i)->GetApStart());
			QString da;
			da.setNum(abs(temp.GetGregDay()));
			da = da.rightJustified(2, '0');
			QString mm;
			mm.setNum(abs(temp.GetGregMonth()));
			mm = mm.rightJustified(2, '0');
			QString dd = QString("%1.%2.%3").arg(da).arg(mm).arg(
					temp.GetGregYear());
			vhron.at(i)->getTreetlItem()->setData(0, 0, dd);
			vhron.at(i)->getTreetlItem()->setData(1, 0, vhron.at(i)->getName());
			vhron.at(i)->getTreetlItem()->setData(2, 0, i);
			tl->insertTopLevelItem(0, vhron.at(i)->getTreetlItem());

		}
	}
	tree->sortByColumn(1, Qt::AscendingOrder);
	pp->sortByColumn(1, Qt::AscendingOrder);
	tl->sortByColumn(2, Qt::AscendingOrder);
}
int NKEpoch::GetIndex(NKhron* hh) {
	for (int i = 0; i < vhron.size(); ++i) {
		if (vhron.at(i) == hh)
			return i;
	}
	return -1;
}
//cuva indexe hronologija koje zauzimaju u vhron i indexe apsolutnih hron
//kako bi se one mogle sacuvati u fajlu ili u slucaju editovalja ponovo povezati
void NKEpoch::Odvezi() {
	for (int i = 0; i < vhron.size(); ++i) {
		vhron.at(i)->setIndex(i);
	}
	for (int i = 0; i < vhron.size(); ++i) {
		NKhron* ap = vhron.at(i)->GetApsolute();
		if (ap) {
			vhron.at(i)->setPindex(ap->getIndex());
		} else {
			vhron.at(i)->setPindex(-1);
		}
	}
}
//suprotno od odvezivanja Zavezi koristi indexe da bi postavio pokazivace
//na apsolutne hronologije
void NKEpoch::Zavezi() {
	for (int i = 0; i < vhron.size(); ++i) {
		int ap = vhron.at(i)->getPindex();
		if (ap != -1) {
			vhron.at(i)->setApsEpoch(vhron.at(ap));
		} else {
			vhron.at(i)->setApsEpoch(0);
		}
	}
}
void NKEpoch::Del(QTreeWidget *tree, QTreeWidget *pp, QTreeWidget *tl) {
	//prekini sve veze na select zatim ga ugloni i updatuj stabla
	if (select) {
		NKhron* temp = select;
		for (int i = 0; i < vhron.size(); ++i) {
			if (vhron.at(i)->GetApsolute() == select) {
				select = vhron.at(i);
				Cut(tree, pp, tl);
				select = temp;
			}
		}

		vhron.remove(GetIndex(temp));
		if (GetIndex(temp) != -1)
			vhron.remove(GetIndex(temp));

		tree->clear();
		pp->clear();
		tl->clear();
		for (int i = 0; i < vhron.size(); ++i) {
			vhron.at(i)->rebuidTree();
		}

	}
	select = 0;
	isSelect = false;
}
void NKEpoch::Link(NKhron* pre, QTreeWidget *tree, QTreeWidget *pp,
		QTreeWidget *tl) {
	//dodaj relativni posavi osobine apsolutnog, premesti druge linkove na njega
	//obrisi stari apsolutni
	if (pre) {
		if (select != pre) {
			JD stp = pre->GetApStart();
			NKRelEpoch* re1 = NULL;
			re1 = dynamic_cast<NKRelEpoch*> (select);
			NKApsEpoch* ae1 = NULL;
			ae1 = dynamic_cast<NKApsEpoch*> (select);
			if (ae1 || re1) {
				JD st = select->GetApStart();
				NKApsPerson* rp = NULL;
				rp = dynamic_cast<NKApsPerson*> (pre);
				if (rp) {

					NKRelPerson* aph = new NKRelPerson(select);
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
					aph->setIsMale(rp->getIsMale());
					aph->setDozoom(pre->getDozoom());
					aph->setImage(pre->getImage());
					AddEpohu(aph);
					for (int i = 0; i < vhron.size(); ++i) {
						if (vhron.at(i)->GetApsolute() == pre) {
							vhron.at(i)->setApsEpoch(aph);
						}
					}
					select->SetIsSel(false);
					select = pre;
					Del(tree, pp, tl);
					tree->clear();
					pp->clear();
					tl->clear();
					for (int i = 0; i < vhron.size(); ++i) {
						vhron.at(i)->rebuidTree();
					}
				} else {
					NKApsEpoch* re = NULL;
					re = dynamic_cast<NKApsEpoch*> (pre);
					NKApsEvent* rev = NULL;
					rev = dynamic_cast<NKApsEvent*> (pre);
					if (re) {

						NKRelEpoch* aph = new NKRelEpoch(select);
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
						aph->setDozoom(pre->getDozoom());
						aph->setImage(pre->getImage());
						AddEpohu(aph);
						for (int i = 0; i < vhron.size(); ++i) {
							if (vhron.at(i)->GetApsolute() == pre) {
								vhron.at(i)->setApsEpoch(aph);
							}
						}
						select->SetIsSel(false);
						select = pre;
						Del(tree, pp, tl);
						tree->clear();
						pp->clear();
						tl->clear();
						for (int i = 0; i < vhron.size(); ++i) {
							vhron.at(i)->rebuidTree();
						}

					}
					if (rev) {

						NKRelEvent* aph = new NKRelEvent(select);
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
						aph->setDozoom(pre->getDozoom());
						aph->setImage(pre->getImage());
						Odvezi();

						AddEpohu(aph);
						for (int i = 0; i < vhron.size(); ++i) {
							if (vhron.at(i)->GetApsolute() == pre) {
								vhron.at(i)->setApsEpoch(aph);
							}
						}
						select->SetIsSel(false);
						select = pre;
						Del(tree, pp, tl);
						tree->clear();
						pp->clear();
						tl->clear();
						for (int i = 0; i < vhron.size(); ++i) {
							vhron.at(i)->rebuidTree();
						}
					}

				}
				//////////////
			}
		}
	}
}
void NKEpoch::ocisti() {
	m_YY = 0;
	isSelect = false;
	select = 0;
	vhron.clear();
	vhron.empty();
}
void NKEpoch::save(QDataStream &o) {
	if (GetBrojEpoha() > 0) {
		o << (int) vhron.size();
		Odvezi();
		//prodji kroz sve
		for (QVector<NKhron*>::iterator qq = vhron.begin(); qq != vhron.end(); ++qq) {

			NKhron *tren = (*qq);
			if (tren) {
				NKApsPerson* ap = NULL;
				ap = dynamic_cast<NKApsPerson*> (tren);
				if (ap) {
					//apsolutna osoba
					o << (int) 1;
					o << (bool) ap->getIsMale();
				} else {
					NKRelPerson* rp = NULL;
					rp = dynamic_cast<NKRelPerson*> (tren);
					if (rp) {
						//relativna osoba
						o << (int) 2;
						o << (bool) rp->getIsMale();
					} else {
						//moze osve ostalo
						NKApsEpoch* ae = NULL;
						ae = dynamic_cast<NKApsEpoch*> (tren);
						if (ae) {
							o << (int) 3;
						}
						NKRelEpoch* re = NULL;
						re = dynamic_cast<NKRelEpoch*> (tren);
						if (re) {
							o << (int) 4;
						}
						NKApsEvent* aee = NULL;
						aee = dynamic_cast<NKApsEvent*> (tren);
						if (aee) {
							o << (int) 5;
						}
						NKRelEvent* ree = NULL;
						ree = dynamic_cast<NKRelEvent*> (tren);
						if (ree) {
							o << (int) 6;
						}
					}
				}
				//zajednicko

				o << (QString) tren->getName();
				o << (double) tren->GetStartDate();
				o << (double) tren->GetEndDate();
				o << (QString) tren->getName();
				o << (QString) tren->getDesc();
				o << (int) tren->GetPozY();
				o << (QColor) tren->getTextColor();
				o << (QColor) tren->getLineColor();
				o << (QColor) tren->getBeckColor();
				o << (bool) tren->GetIsSel();
				o << (int) tren->getIndex();
				o << (int) tren->getPindex();
				o << (int) tren->getZoom();
				o << (int) tren->getDozoom();
				o << (short) tren->getRenderType();
				o << (short) tren->getEventType();
				o << (bool) tren->getRelLinkDraw();
				o << (QImage) tren->getImage();
			}
		}
	}
}
void NKEpoch::open(QDataStream &o) {
	int bepo;
	QString i1;
	double i2;
	double i3;
	QString i4;
	QString i5;
	int i6;
	QColor i7;
	QColor i8;
	QColor i9;
	bool i10;
	int i11, i12, i13, i14;
	short i15, i16;
	bool i17;
	bool male;
	QImage image;
	o >> bepo;
	if (bepo > 0) {
		vhron.empty();
		vhron.clear();
		int vrsta;
		for (int i = 0; i < bepo; i++) {
			o >> vrsta;
			if (vrsta == 1) {
				o >> male;
				o >> i1;
				o >> i2;
				o >> i3;
				o >> i4;
				o >> i5;
				o >> i6;
				o >> i7;
				o >> i8;
				o >> i9;
				o >> i10;
				o >> i11;
				o >> i12;
				o >> i13;
				o >> i14;
				o >> i15;
				o >> i16;
				o >> i17;
				o >> image;
				NKhron *htemp = new NKApsPerson();
				htemp->setName(i1);
				htemp->SetStartDate(i2);
				htemp->SetEndDate(i3);
				htemp->setName(i4);
				htemp->setDesc(i5);
				htemp->SetPozY(i6);
				htemp->setTextColor(i7);
				htemp->setLineColor(i8);
				htemp->setBeckColor(i9);
				htemp->SetIsSel(i10);
				htemp->setIndex(i11);
				htemp->setPindex(i12);
				htemp->setZoom(i13);
				htemp->setDozoom(i14);
				htemp->setRenderType(i15);
				htemp->setEventType(i16);
				htemp->setRelLinkDraw(i17);
				htemp->setImage(image);
				vhron.push_back(htemp);
			}
			if (vrsta == 2) {

				o >> male;
				o >> i1;
				o >> i2;
				o >> i3;
				o >> i4;
				o >> i5;
				o >> i6;
				o >> i7;
				o >> i8;
				o >> i9;
				o >> i10;
				o >> i11;
				o >> i12;
				o >> i13;
				o >> i14;
				o >> i15;
				o >> i16;
				o >> i17;
				o >> image;
				NKhron *htemp = new NKRelPerson(0);
				htemp->setName(i1);
				htemp->SetStartDate(i2);
				htemp->SetEndDate(i3);
				htemp->setName(i4);
				htemp->setDesc(i5);
				htemp->SetPozY(i6);
				htemp->setTextColor(i7);
				htemp->setLineColor(i8);
				htemp->setBeckColor(i9);
				htemp->SetIsSel(i10);
				htemp->setIndex(i11);
				htemp->setPindex(i12);
				htemp->setZoom(i13);
				htemp->setDozoom(i14);
				htemp->setRenderType(i15);
				htemp->setEventType(i16);
				htemp->setRelLinkDraw(i17);
				htemp->setImage(image);
				vhron.push_back(htemp);
			}
			if (vrsta == 3) {

				o >> i1;
				o >> i2;
				o >> i3;
				o >> i4;
				o >> i5;
				o >> i6;
				o >> i7;
				o >> i8;
				o >> i9;
				o >> i10;
				o >> i11;
				o >> i12;
				o >> i13;
				o >> i14;
				o >> i15;
				o >> i16;
				o >> i17;
				o >> image;
				NKhron *htemp = new NKApsEpoch();
				htemp->setName(i1);
				htemp->SetStartDate(i2);
				htemp->SetEndDate(i3);
				htemp->setName(i4);
				htemp->setDesc(i5);
				htemp->SetPozY(i6);
				htemp->setTextColor(i7);
				htemp->setLineColor(i8);
				htemp->setBeckColor(i9);
				htemp->SetIsSel(i10);
				htemp->setIndex(i11);
				htemp->setPindex(i12);
				htemp->setZoom(i13);
				htemp->setDozoom(i14);
				htemp->setRenderType(i15);
				htemp->setEventType(i16);
				htemp->setRelLinkDraw(i17);
				htemp->setImage(image);
				vhron.push_back(htemp);
			}
			if (vrsta == 4) {

				o >> i1;
				o >> i2;
				o >> i3;
				o >> i4;
				o >> i5;
				o >> i6;
				o >> i7;
				o >> i8;
				o >> i9;
				o >> i10;
				o >> i11;
				o >> i12;
				o >> i13;
				o >> i14;
				o >> i15;
				o >> i16;
				o >> i17;
				o >> image;
				NKhron *htemp = new NKRelEpoch();

				htemp->setName(i1);
				htemp->SetStartDate(i2);
				htemp->SetEndDate(i3);
				htemp->setName(i4);
				htemp->setDesc(i5);
				htemp->SetPozY(i6);
				htemp->setTextColor(i7);
				htemp->setLineColor(i8);
				htemp->setBeckColor(i9);
				htemp->SetIsSel(i10);
				htemp->setIndex(i11);
				htemp->setPindex(i12);
				htemp->setZoom(i13);
				htemp->setDozoom(i14);
				htemp->setRenderType(i15);
				htemp->setEventType(i16);
				htemp->setRelLinkDraw(i17);
				htemp->setImage(image);
				vhron.push_back(htemp);

			}
			if (vrsta == 5) {
				o >> i1;
				o >> i2;
				o >> i3;
				o >> i4;
				o >> i5;
				o >> i6;
				o >> i7;
				o >> i8;
				o >> i9;
				o >> i10;
				o >> i11;
				o >> i12;
				o >> i13;
				o >> i14;
				o >> i15;
				o >> i16;
				o >> i17;
				o >> image;
				NKhron *htemp = new NKApsEvent();
				htemp->setName(i1);
				htemp->SetStartDate(i2);
				htemp->SetEndDate(i3);
				htemp->setName(i4);
				htemp->setDesc(i5);
				htemp->SetPozY(i6);
				htemp->setTextColor(i7);
				htemp->setLineColor(i8);
				htemp->setBeckColor(i9);
				htemp->SetIsSel(i10);
				htemp->setIndex(i11);
				htemp->setPindex(i12);
				htemp->setZoom(i13);
				htemp->setDozoom(i14);
				htemp->setRenderType(i15);
				htemp->setEventType(i16);
				htemp->setRelLinkDraw(i17);
				htemp->setImage(image);
				vhron.push_back(htemp);

			}
			if (vrsta == 6) {
				o >> i1;
				o >> i2;
				o >> i3;
				o >> i4;
				o >> i5;
				o >> i6;
				o >> i7;
				o >> i8;
				o >> i9;
				o >> i10;
				o >> i11;
				o >> i12;
				o >> i13;
				o >> i14;
				o >> i15;
				o >> i16;
				o >> i17;
				o >> image;
				NKhron *htemp = new NKRelEvent(0);
				htemp->setName(i1);
				htemp->SetStartDate(i2);
				htemp->SetEndDate(i3);
				htemp->setName(i4);
				htemp->setDesc(i5);
				htemp->SetPozY(i6);
				htemp->setTextColor(i7);
				htemp->setLineColor(i8);
				htemp->setBeckColor(i9);
				htemp->SetIsSel(i10);
				htemp->setIndex(i11);
				htemp->setPindex(i12);
				htemp->setZoom(i13);
				htemp->setDozoom(i14);
				htemp->setRenderType(i15);
				htemp->setEventType(i16);
				htemp->setRelLinkDraw(i17);
				htemp->setImage(image);
				vhron.push_back(htemp);
			}

		}

	}

	Zavezi();

	for (int i = 0; i < vhron.size(); ++i) {
		vhron.at(i)->rebuidTree();
	}

}
void NKEpoch::import(QDataStream &o) {

	int realo = vhron.size();
	this->Odvezi();
	int bepo;
	QString i1;
	double i2;
	double i3;
	QString i4;
	QString i5;
	int i6;
	QColor i7;
	QColor i8;
	QColor i9;
	bool i10;
	int i11, i12, i13, i14;
	short i15, i16;
	bool i17;
	QImage image;
	bool male;
	o >> bepo;
	if (bepo > 0) {
		int vrsta;
		for (int i = 0; i < bepo; i++) {
			o >> vrsta;
			if (vrsta == 1) {
				o >> male;
				o >> i1;
				o >> i2;
				o >> i3;
				o >> i4;
				o >> i5;
				o >> i6;
				o >> i7;
				o >> i8;
				o >> i9;
				o >> i10;
				o >> i11;
				o >> i12;
				o >> i13;
				o >> i14;
				o >> i15;
				o >> i16;
				o >> i17;
				o >> image;
				NKhron *htemp = new NKApsPerson();
				htemp->setName(i1);
				htemp->SetStartDate(i2);
				htemp->SetEndDate(i3);
				htemp->setName(i4);
				htemp->setDesc(i5);
				htemp->SetPozY(i6);
				htemp->setTextColor(i7);
				htemp->setLineColor(i8);
				htemp->setBeckColor(i9);
				htemp->SetIsSel(i10);
				htemp->setIndex(i11 + realo);
				htemp->setPindex(i12 + realo);
				htemp->setZoom(i13);
				htemp->setDozoom(i14);
				htemp->setRenderType(i15);
				htemp->setEventType(i16);
				htemp->setRelLinkDraw(i17);
				htemp->setImage(image);
				vhron.push_back(htemp);
			}
			if (vrsta == 2) {

				o >> male;
				o >> i1;
				o >> i2;
				o >> i3;
				o >> i4;
				o >> i5;
				o >> i6;
				o >> i7;
				o >> i8;
				o >> i9;
				o >> i10;
				o >> i11;
				o >> i12;
				o >> i13;
				o >> i14;
				o >> i15;
				o >> i16;
				o >> i17;
				o >> image;
				NKhron *htemp = new NKRelPerson(0);
				htemp->setName(i1);
				htemp->SetStartDate(i2);
				htemp->SetEndDate(i3);
				htemp->setName(i4);
				htemp->setDesc(i5);
				htemp->SetPozY(i6);
				htemp->setTextColor(i7);
				htemp->setLineColor(i8);
				htemp->setBeckColor(i9);
				htemp->SetIsSel(i10);
				htemp->setIndex(i11 + realo);
				htemp->setPindex(i12 + realo);
				htemp->setZoom(i13);
				htemp->setDozoom(i14);
				htemp->setRenderType(i15);
				htemp->setEventType(i16);
				htemp->setRelLinkDraw(i17);
				htemp->setImage(image);
				vhron.push_back(htemp);
			}
			if (vrsta == 3) {

				o >> i1;
				o >> i2;
				o >> i3;
				o >> i4;
				o >> i5;
				o >> i6;
				o >> i7;
				o >> i8;
				o >> i9;
				o >> i10;
				o >> i11;
				o >> i12;
				o >> i13;
				o >> i14;
				o >> i15;
				o >> i16;
				o >> i17;
				o >> image;
				NKhron *htemp = new NKApsEpoch();
				htemp->setName(i1);
				htemp->SetStartDate(i2);
				htemp->SetEndDate(i3);
				htemp->setName(i4);
				htemp->setDesc(i5);
				htemp->SetPozY(i6);
				htemp->setTextColor(i7);
				htemp->setLineColor(i8);
				htemp->setBeckColor(i9);
				htemp->SetIsSel(i10);
				htemp->setIndex(i11 + realo);
				htemp->setPindex(i12 + realo);
				htemp->setZoom(i13);
				htemp->setDozoom(i14);
				htemp->setRenderType(i15);
				htemp->setEventType(i16);
				htemp->setRelLinkDraw(i17);
				htemp->setImage(image);
				vhron.push_back(htemp);
			}
			if (vrsta == 4) {

				o >> i1;
				o >> i2;
				o >> i3;
				o >> i4;
				o >> i5;
				o >> i6;
				o >> i7;
				o >> i8;
				o >> i9;
				o >> i10;
				o >> i11;
				o >> i12;
				o >> i13;
				o >> i14;
				o >> i15;
				o >> i16;
				o >> i17;
				o >> image;
				NKhron *htemp = new NKRelEpoch();

				htemp->setName(i1);
				htemp->SetStartDate(i2);
				htemp->SetEndDate(i3);
				htemp->setName(i4);
				htemp->setDesc(i5);
				htemp->SetPozY(i6);
				htemp->setTextColor(i7);
				htemp->setLineColor(i8);
				htemp->setBeckColor(i9);
				htemp->SetIsSel(i10);
				htemp->setIndex(i11 + realo);
				htemp->setPindex(i12 + realo);
				htemp->setZoom(i13);
				htemp->setDozoom(i14);
				htemp->setRenderType(i15);
				htemp->setEventType(i16);
				htemp->setRelLinkDraw(i17);
				htemp->setImage(image);
				vhron.push_back(htemp);

			}
			if (vrsta == 5) {
				o >> i1;
				o >> i2;
				o >> i3;
				o >> i4;
				o >> i5;
				o >> i6;
				o >> i7;
				o >> i8;
				o >> i9;
				o >> i10;
				o >> i11;
				o >> i12;
				o >> i13;
				o >> i14;
				o >> i15;
				o >> i16;
				o >> i17;
				o >> image;
				NKhron *htemp = new NKApsEvent();
				htemp->setName(i1);
				htemp->SetStartDate(i2);
				htemp->SetEndDate(i3);
				htemp->setName(i4);
				htemp->setDesc(i5);
				htemp->SetPozY(i6);
				htemp->setTextColor(i7);
				htemp->setLineColor(i8);
				htemp->setBeckColor(i9);
				htemp->SetIsSel(i10);
				htemp->setIndex(i11 + realo);
				htemp->setPindex(i12 + realo);
				htemp->setZoom(i13);
				htemp->setDozoom(i14);
				htemp->setRenderType(i15);
				htemp->setEventType(i16);
				htemp->setRelLinkDraw(i17);
				htemp->setImage(image);
				vhron.push_back(htemp);

			}
			if (vrsta == 6) {
				o >> i1;
				o >> i2;
				o >> i3;
				o >> i4;
				o >> i5;
				o >> i6;
				o >> i7;
				o >> i8;
				o >> i9;
				o >> i10;
				o >> i11;
				o >> i12;
				o >> i13;
				o >> i14;
				o >> i15;
				o >> i16;
				o >> i17;
				o >> image;
				NKhron *htemp = new NKRelEvent(0);
				htemp->setName(i1);
				htemp->SetStartDate(i2);
				htemp->SetEndDate(i3);
				htemp->setName(i4);
				htemp->setDesc(i5);
				htemp->SetPozY(i6);
				htemp->setTextColor(i7);
				htemp->setLineColor(i8);
				htemp->setBeckColor(i9);
				htemp->SetIsSel(i10);
				htemp->setIndex(i11 + realo);
				htemp->setPindex(i12 + realo);
				htemp->setZoom(i13);
				htemp->setDozoom(i14);
				htemp->setRenderType(i15);
				htemp->setEventType(i16);
				htemp->setRelLinkDraw(i17);
				htemp->setImage(image);
				vhron.push_back(htemp);
			}

		}

	}

	Zavezi();

	for (int i = 0; i < vhron.size(); ++i) {
		vhron.at(i)->rebuidTree();
	}

}
//sortira hronologije po datumu tako sto ih premesti u privremeni vektor
//zatim ih po redu vraca u vhron i ponovo uspostavlja  veze
void NKEpoch::Realocate(QTreeWidget *tree, QTreeWidget *pp, QTreeWidget *tl) {

	if (select) {
		select->SetIsSel(false);
	}
	this->select = 0;
	this->isSelect = false;
	this->Odvezi();

	QVector<NKhron*> temp;
	for (int i = 0; i < vhron.size(); ++i) {
		temp.push_back(vhron.at(i));

	}

	vhron.clear();
	vhron.empty();
	for (int i = 0; i < temp.size(); ++i) {
		this->AddEpohu(temp.at(i));
	}
	temp.clear();
	temp.empty();
	for (int i = 0; i < vhron.size(); ++i) {
		int index = vhron.at(i)->getPindex();
		if (index != -1) {
			for (int jj = 0; jj < vhron.size(); ++jj) {
				if (vhron.at(jj)->getIndex() == index) {
					vhron.at(i)->setPindex(jj);
					break;
				}
			}
		}
	}

	this->Zavezi();
	UpdateTree(tree, pp, tl);
}
