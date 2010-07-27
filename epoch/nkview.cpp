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

#include "nkview.h"
#include "nkjd.h"
#include <QMessageBox>
#include <QImage>
NKView::NKView(QWidget *parent, NKSkala *skala, NKEpoch *document,
		QTreeWidget *Tree) :
	QWidget(parent) {
	setMouseTracking(true);
	m_skala = skala;
	status = "";
	grid = true;
	doc = document;
	menuAc = 0;
	isSelect = false;
	isMove = false;
	mTree = Tree;
	islink = false;
	pre = 0;
	dy = 0;
	pomeri = false;
	kateg = 0;
}
void NKView::ocisti() {
	status = "";
	grid = true;
	menuAc = 0;
	isSelect = false;
	isMove = false;
	islink = false;
	pre = 0;
	dy = 0;
	pomeri = false;
	kateg = 0;
}
void NKView::ocistisel() {

}
void NKView::save(QDataStream &o) {
	o << (bool) grid;
	o << (short) menuAc;
	o << (bool) isSelect;
	o << (bool) isMove;
	o << (bool) islink;
	o << (int) dy;
	o << (bool) pomeri;
	o << (short) kateg;
}
void NKView::open(QDataStream &o) {
	o >> grid;
	o >> menuAc;
	o >> isSelect;
	o >> isMove;
	o >> islink;
	o >> dy;
	o >> pomeri;
	o >> kateg;
}
void NKView::import(QDataStream &o) {
	o >> grid;
	o >> menuAc;
	o >> isSelect;
	o >> isMove;
	o >> islink;
	o >> dy;
	o >> pomeri;
	o >> kateg;
}
void NKView::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.fillRect(this->rect(), QBrush(Qt::white));
	painter.drawRect(0, 0, width(), height());

	//grid
	if (grid) {
		NKJD ff;

		double rr3 = m_skala->GetRazmera();
		zoom = rr3;
		int raz = 1;
		if (rr3 >= ((60 * 24 * 365) * 0.02)) {
			raz = 10;
		}
		if (rr3 >= ((60 * 24 * 365) * 0.2)) {
			raz = 50;
		}
		if (rr3 >= ((60 * 24 * 365) * 1)) {
			raz = 100;
		}
		if (rr3 >= ((60 * 24 * 365) * 4)) {
			raz = 1000;
		}
		if (rr3 >= ((60 * 24 * 365) * 34)) {
			raz = 10000;
		}

		ff = m_skala->DatumZaPolozaj(0);
		int godina = ff.GetGregYear();
		int ostatak = godina % raz;
		godina = godina - ostatak;
		godina = godina - raz;
		NKJD rr;
		for (int gg = 1; gg < 50; gg++) {
			rr.SetShortDate(1, 1, godina + (raz * gg));
			int pol = m_skala->PolozajZaDatum(rr);
			QPen o2(QColor(80, 80, 255, 100));
			painter.setPen(o2);
			painter.drawLine(pol, 0, pol, height());
			QString hhss = QString("%1").arg((godina + (raz * gg)));
			if (hhss.compare("0")) {
				QFont m_Font = QFont("Times", 8);
				painter.setFont(m_Font);
				painter.save();
				painter.rotate(-90);
				int xx = pol + 12;
				if (xx < width() && xx > 20)
					painter.drawText(-35, xx, hhss);

				painter.restore();
			}
		}
	}
	if (pomeri) {
		painter.drawLine(clik, clik2);
	}
	doc->Draw(&painter, m_skala, dy, kateg, zoom);
	//update statusbar
	NKJD jd1 = m_skala->DatumZaPolozaj(m_skala->GetPolozaj());
	status = jd1.getString(jd1);
	emit statusSig();
}
void NKView::mouseMoveEvent(QMouseEvent * event) {
	if (isSelect && isMove) {
		NKhron* sel = doc->GetSelHro();
		if (sel)
			sel->SetPozY(event->pos().y() - dy);
		update();
	}
	if (pomeri) {
		clik2 = event->pos();
		update();
	}
	m_skala->SetPolozajPokazivaca(event->pos().x());
	m_skala->update();
	NKJD jd1 = m_skala->DatumZaPolozaj(event->pos().x());
	status = jd1.getString(jd1);
	emit statusSig();
}
void NKView::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		if (menuAc > 0) {
			if (menuAc == 1) {
				menuAc = 0;
				NKJD start = m_skala->DatumZaPolozaj(event->pos().x());
				NKJD end = m_skala->DatumZaPolozaj(event->pos().x() + 200);
				end.SubDay(start.GetJD());
				start.SetTime(12, 0, 0);
				end.SetTime(12, 0, 0);
				NKhron *htemp = new NKApsEpoch();
				htemp->SetPozY(event->pos().y() - dy);
				htemp->SetStartDate(start.GetJD());
				htemp->SetEndDate(end.GetJD());
				doc->AddEpohu(htemp);
				doc->UpdateTree(mTree, mTreepp, mTreetl);
				update();
			}
			if (menuAc == 2) {
				///aps event
				menuAc = 0;
				NKJD start = m_skala->DatumZaPolozaj(event->pos().x());
				NKhron *htemp = new NKApsEvent();
				htemp->SetPozY(event->pos().y() - dy);
				start.SetTime(12, 0, 0);
				htemp->SetStartDate(start.GetJD());
				htemp->SetEndDate(0);
				doc->AddEpohu(htemp);
				doc->UpdateTree(mTree, mTreepp, mTreetl);
				update();
			}
			if (menuAc == 3) {
				///aps person
				menuAc = 0;
				NKJD start = m_skala->DatumZaPolozaj(event->pos().x());
				NKJD end = m_skala->DatumZaPolozaj(event->pos().x() + 200);
				end.SubDay(start.GetJD());
				start.SetTime(12, 0, 0);
				end.SetTime(12, 0, 0);
				NKhron *htemp = new NKApsPerson();
				htemp->SetPozY(event->pos().y() - dy);
				htemp->SetStartDate(start.GetJD());
				htemp->SetEndDate(end.GetJD());
				doc->AddEpohu(htemp);
				doc->UpdateTree(mTree, mTreepp, mTreetl);
				update();
			}

			if (menuAc == 4) {
				///rel epoch
				menuAc = 0;
				NKhron* sel = doc->GetSelHro();
				if (sel) {
					NKApsPerson* epr = NULL;
					epr = dynamic_cast<NKApsPerson*> (sel);
					if (!epr) {
						NKRelPerson* eprr = NULL;
						eprr = dynamic_cast<NKRelPerson*> (sel);
						if (!eprr) {

							NKApsEpoch* ep1 = NULL;
							ep1 = dynamic_cast<NKApsEpoch*> (sel);
							if (ep1) {
								NKJD start = m_skala->DatumZaPolozaj(
										event->pos().x());
								NKJD end = m_skala->DatumZaPolozaj(
										event->pos().x() + 200);
								JD aae = sel->GetApStart();
								end.SubDay(start.GetJD());
								start.SubDay(aae);
								start.SetTime(12, 0, 0);
								end.SetTime(12, 0, 0);
								NKhron *htemp = new NKRelEpoch(sel);
								htemp->SetPozY(event->pos().y() - dy);
								htemp->SetStartDate(start.GetJD());
								htemp->SetEndDate(end.GetJD());
								doc->AddEpohu(htemp);
								doc->UpdateTree(mTree, mTreepp, mTreetl);
								update();
							}
							NKRelEpoch* ep2 = NULL;
							ep2 = dynamic_cast<NKRelEpoch*> (sel);
							if (ep2) {
								NKJD start = m_skala->DatumZaPolozaj(
										event->pos().x());
								NKJD end = m_skala->DatumZaPolozaj(
										event->pos().x() + 200);
								JD aae = sel->GetApStart();
								end.SubDay(start.GetJD());
								start.SubDay(aae);
								start.SetTime(12, 0, 0);
								end.SetTime(12, 0, 0);
								NKhron *htemp = new NKRelEpoch(sel);
								htemp->SetPozY(event->pos().y() - dy);
								htemp->SetStartDate(start.GetJD());
								htemp->SetEndDate(end.GetJD());
								doc->AddEpohu(htemp);
								doc->UpdateTree(mTree, mTreepp, mTreetl);
								update();
							}
						}
					}
				}
			}
			//////
			if (menuAc == 5) {

				menuAc = 0;
				NKhron* sel = doc->GetSelHro();
				if (sel) {

					NKRelEvent* epr = NULL;
					epr = dynamic_cast<NKRelEvent*> (sel);
					if (!epr) {
						NKApsEvent* epr22 = NULL;
						epr22 = dynamic_cast<NKApsEvent*> (sel);
						if (!epr22) {
							NKJD start = m_skala->DatumZaPolozaj(
									event->pos().x());
							JD aae = sel->GetApStart();
							start.SubDay(aae);
							start.SetTime(12, 0, 0);

							NKhron *htemp = new NKRelEvent(sel);
							htemp->SetPozY(event->pos().y() - dy);
							htemp->SetStartDate(start.GetJD());
							doc->AddEpohu(htemp);
							doc->UpdateTree(mTree, mTreepp, mTreetl);
							update();
						}
					}
				}
			}
			//////
			if (menuAc == 6) {
				///rel epoch
				menuAc = 0;
				NKhron* sel = doc->GetSelHro();
				if (sel) {
					NKApsEpoch* ep1 = NULL;
					ep1 = dynamic_cast<NKApsEpoch*> (sel);
					if (ep1) {
						NKJD start = m_skala->DatumZaPolozaj(event->pos().x());
						NKJD end = m_skala->DatumZaPolozaj(event->pos().x()
								+ 200);
						JD aae = sel->GetApStart();
						end.SubDay(start.GetJD());
						start.SubDay(aae);
						start.SetTime(12, 0, 0);
						end.SetTime(12, 0, 0);
						NKhron *htemp = new NKRelPerson(sel);
						htemp->SetPozY(event->pos().y() - dy);
						htemp->SetStartDate(start.GetJD());
						htemp->SetEndDate(end.GetJD());
						doc->AddEpohu(htemp);
						doc->UpdateTree(mTree, mTreepp, mTreetl);
						update();
					}
					NKRelEpoch* ep2 = NULL;
					ep2 = dynamic_cast<NKRelEpoch*> (sel);
					if (ep2) {
						NKJD start = m_skala->DatumZaPolozaj(event->pos().x());
						NKJD end = m_skala->DatumZaPolozaj(event->pos().x()
								+ 200);
						JD aae = sel->GetApStart();
						end.SubDay(start.GetJD());
						start.SubDay(aae);
						start.SetTime(12, 0, 0);
						end.SetTime(12, 0, 0);
						NKhron *htemp = new NKRelPerson(sel);
						htemp->SetPozY(event->pos().y() - dy);
						htemp->SetStartDate(start.GetJD());
						htemp->SetEndDate(end.GetJD());
						doc->AddEpohu(htemp);
						doc->UpdateTree(mTree, mTreepp, mTreetl);
						update();
					}
				}
			}
		} else {

			doc->ClearSelection(mTree, mTreepp, mTreetl);
			doc->Realocate(mTree, mTreepp, mTreetl);

			emit
			itemClicked();
			if (doc->Select(m_skala, event->pos().x(), event->pos().y() - dy)) {

				if (islink) {
					islink = false;
					doc->Link(pre, mTree, mTreepp, mTreetl);
					doc->UpdateTree(mTree, mTreepp, mTreetl);
					pre = 0;

				} else {
					emit itemClicked();
					isMove = true;
					isSelect = true;
				}
			}

			update();

		}

	}
	if (event->button() == Qt::RightButton) {
		pomeri = true;
		clik = event->pos();
	}

}
void NKView::aepoha() {
	menuAc = 1;
}
void NKView::adog() {
	menuAc = 2;
}
void NKView::aPer() {
	menuAc = 3;
}
void NKView::rPer() {
	menuAc = 6;
}
void NKView::repoha() {
	menuAc = 4;
}
void NKView::rdog() {
	menuAc = 5;
}
void NKView::mouseReleaseEvent(QMouseEvent * event) {
	if (event->button() == Qt::LeftButton) {
		isMove = false;

	}
	if (event->button() == Qt::RightButton) {
		if (pomeri) {
			pomeri = false;
			dy += (event->pos().y() - clik.y());
			NKJD p1;
			p1 = m_skala->DatumZaPolozaj(clik.x());
			NKJD p2;
			p2 = m_skala->DatumZaPolozaj(event->pos().x());
			p1.SubDay(p2.GetJD());
			p2 = m_skala->GetPocetak();
			p2.AddDay(p1.GetJD());
			m_skala->SetPocetak(p2);
			update();
		}
	}

}
void NKView::selectFromTree(QTreeWidgetItem * item, int column) {
	QString tex = item->text(1);
	int it = tex.toInt();
	doc->ClearSelection(mTree, mTreepp, mTreetl);
	if (doc->SelectID(it)) {
		emit itemClicked();
		isSelect = true;
		NKhron* sel = doc->GetSelHro();
		dy = (height() / 2) - sel->GetPozY();
		if (sel) {
			JD ds = sel->GetApStart();
			m_skala->CentrirajDatum(ds);
		}
		update();
	}
}
void NKView::selectFromppTree(QTreeWidgetItem * item, int column) {
	QString tex = item->text(1);
	int it = tex.toInt();
	doc->ClearSelection(mTree, mTreepp, mTreetl);
	if (doc->SelectID(it)) {
		emit itemClicked();
		isSelect = true;
		NKhron* sel = doc->GetSelHro();
		dy = (height() / 2) - sel->GetPozY();
		if (sel) {
			JD ds = sel->GetApStart();
			m_skala->CentrirajDatum(ds);
		}
		update();
	}
}
void NKView::selectFromtlTree(QTreeWidgetItem * item, int column) {
	QString tex = item->text(2);
	int it = tex.toInt();
	doc->ClearSelection(mTree, mTreepp, mTreetl);
	if (doc->SelectID(it)) {
		emit itemClicked();
		isSelect = true;
		NKhron* sel = doc->GetSelHro();
		dy = (height() / 2) - sel->GetPozY();
		if (sel) {
			JD ds = sel->GetApStart();
			m_skala->CentrirajDatum(ds);
		}
		update();
	}
}
void NKView::adel() {
	NKhron* sel = doc->GetSelHro();
	if (sel) {
		doc->Del(mTree, mTreepp, mTreetl);
		isSelect = false;
		doc->UpdateTree(mTree, mTreepp, mTreetl);
		update();
	}
}
void NKView::acut() {
	NKhron* sel = doc->GetSelHro();
	if (sel) {
		doc->Cut(mTree, mTreepp, mTreetl);
		doc->UpdateTree(mTree, mTreepp, mTreetl);
		update();
	}
}
void NKView::alink() {
	NKhron* sel = doc->GetSelHro();
	if (sel) {
		islink = true;
		pre = sel;
	}
}
void NKView::mouseDoubleClickEvent(QMouseEvent * event) {
	if (event->button() == Qt::LeftButton) {
		if (menuAc > 0) {
			if (menuAc == 1) {
				menuAc = 0;
				NKJD start = m_skala->DatumZaPolozaj(event->pos().x());
				NKJD end = m_skala->DatumZaPolozaj(event->pos().x() + 200);
				end.SubDay(start.GetJD());
				start.SetTime(12, 0, 0);
				end.SetTime(12, 0, 0);
				NKhron *htemp = new NKApsEpoch();
				htemp->SetPozY(event->pos().y() - dy);
				htemp->SetStartDate(start.GetJD());
				htemp->SetEndDate(end.GetJD());
				doc->AddEpohu(htemp);
				doc->UpdateTree(mTree, mTreepp, mTreetl);
				update();
			}
			if (menuAc == 2) {
				///aps event
				menuAc = 0;
				NKJD start = m_skala->DatumZaPolozaj(event->pos().x());
				NKhron *htemp = new NKApsEvent();
				htemp->SetPozY(event->pos().y() - dy);
				start.SetTime(12, 0, 0);
				htemp->SetStartDate(start.GetJD());
				htemp->SetEndDate(0);
				doc->AddEpohu(htemp);
				doc->UpdateTree(mTree, mTreepp, mTreetl);
				update();
			}
			if (menuAc == 3) {
				///aps person
				menuAc = 0;
				NKJD start = m_skala->DatumZaPolozaj(event->pos().x());
				NKJD end = m_skala->DatumZaPolozaj(event->pos().x() + 200);
				end.SubDay(start.GetJD());
				start.SetTime(12, 0, 0);
				end.SetTime(12, 0, 0);
				NKhron *htemp = new NKApsPerson();
				htemp->SetPozY(event->pos().y() - dy);
				htemp->SetStartDate(start.GetJD());
				htemp->SetEndDate(end.GetJD());
				doc->AddEpohu(htemp);
				doc->UpdateTree(mTree, mTreepp, mTreetl);
				update();
			}

			if (menuAc == 4) {
				///rel epoch
				menuAc = 0;
				NKhron* sel = doc->GetSelHro();
				if (sel) {
					NKApsPerson* epr = NULL;
					epr = dynamic_cast<NKApsPerson*> (sel);
					if (!epr) {
						NKRelPerson* eprr = NULL;
						eprr = dynamic_cast<NKRelPerson*> (sel);
						if (!eprr) {

							NKApsEpoch* ep1 = NULL;
							ep1 = dynamic_cast<NKApsEpoch*> (sel);
							if (ep1) {
								NKJD start = m_skala->DatumZaPolozaj(
										event->pos().x());
								NKJD end = m_skala->DatumZaPolozaj(
										event->pos().x() + 200);
								JD aae = sel->GetApStart();
								end.SubDay(start.GetJD());
								start.SubDay(aae);
								start.SetTime(12, 0, 0);
								end.SetTime(12, 0, 0);
								NKhron *htemp = new NKRelEpoch(sel);
								htemp->SetPozY(event->pos().y() - dy);
								htemp->SetStartDate(start.GetJD());
								htemp->SetEndDate(end.GetJD());
								doc->AddEpohu(htemp);
								doc->UpdateTree(mTree, mTreepp, mTreetl);
								update();
							}
							NKRelEpoch* ep2 = NULL;
							ep2 = dynamic_cast<NKRelEpoch*> (sel);
							if (ep2) {
								NKJD start = m_skala->DatumZaPolozaj(
										event->pos().x());
								NKJD end = m_skala->DatumZaPolozaj(
										event->pos().x() + 200);
								JD aae = sel->GetApStart();
								end.SubDay(start.GetJD());
								start.SubDay(aae);
								start.SetTime(12, 0, 0);
								end.SetTime(12, 0, 0);
								NKhron *htemp = new NKRelEpoch(sel);
								htemp->SetPozY(event->pos().y() - dy);
								htemp->SetStartDate(start.GetJD());
								htemp->SetEndDate(end.GetJD());
								doc->AddEpohu(htemp);
								doc->UpdateTree(mTree, mTreepp, mTreetl);
								update();
							}
						}
					}
				}
			}
			//////
			if (menuAc == 5) {

				menuAc = 0;
				NKhron* sel = doc->GetSelHro();
				if (sel) {

					NKRelEvent* epr = NULL;
					epr = dynamic_cast<NKRelEvent*> (sel);
					if (!epr) {
						NKApsEvent* epr22 = NULL;
						epr22 = dynamic_cast<NKApsEvent*> (sel);
						if (!epr22) {
							NKJD start = m_skala->DatumZaPolozaj(
									event->pos().x());
							JD aae = sel->GetApStart();
							start.SubDay(aae);
							start.SetTime(12, 0, 0);

							NKhron *htemp = new NKRelEvent(sel);
							htemp->SetPozY(event->pos().y() - dy);
							htemp->SetStartDate(start.GetJD());
							doc->AddEpohu(htemp);
							doc->UpdateTree(mTree, mTreepp, mTreetl);
							update();
						}
					}
				}
			}
			//////
			if (menuAc == 6) {
				///rel epoch
				menuAc = 0;
				NKhron* sel = doc->GetSelHro();
				if (sel) {
					NKApsEpoch* ep1 = NULL;
					ep1 = dynamic_cast<NKApsEpoch*> (sel);
					if (ep1) {
						NKJD start = m_skala->DatumZaPolozaj(event->pos().x());
						NKJD end = m_skala->DatumZaPolozaj(event->pos().x()
								+ 200);
						JD aae = sel->GetApStart();
						end.SubDay(start.GetJD());
						start.SubDay(aae);
						start.SetTime(12, 0, 0);
						end.SetTime(12, 0, 0);
						NKhron *htemp = new NKRelPerson(sel);
						htemp->SetPozY(event->pos().y() - dy);
						htemp->SetStartDate(start.GetJD());
						htemp->SetEndDate(end.GetJD());
						doc->AddEpohu(htemp);
						doc->UpdateTree(mTree, mTreepp, mTreetl);
						update();
					}
					NKRelEpoch* ep2 = NULL;
					ep2 = dynamic_cast<NKRelEpoch*> (sel);
					if (ep2) {
						NKJD start = m_skala->DatumZaPolozaj(event->pos().x());
						NKJD end = m_skala->DatumZaPolozaj(event->pos().x()
								+ 200);
						JD aae = sel->GetApStart();
						end.SubDay(start.GetJD());
						start.SubDay(aae);
						start.SetTime(12, 0, 0);
						end.SetTime(12, 0, 0);
						NKhron *htemp = new NKRelPerson(sel);
						htemp->SetPozY(event->pos().y() - dy);
						htemp->SetStartDate(start.GetJD());
						htemp->SetEndDate(end.GetJD());
						doc->AddEpohu(htemp);
						doc->UpdateTree(mTree, mTreepp, mTreetl);
						update();
					}
				}
			}
		} else {
			doc->ClearSelection(mTree, mTreepp, mTreetl);
			emit
			itemClicked();
			if (doc->Select(m_skala, event->pos().x(), event->pos().y() - dy)) {
				if (islink) {
					islink = false;
					doc->Link(pre, mTree, mTreepp, mTreetl);
					doc->UpdateTree(mTree, mTreepp, mTreetl);
					pre = 0;
				} else {
					emit itemClicked();
					emit
					itemDoubleClicked();
					isMove = true;
					isSelect = true;
				}
			}
			update();
		}

	}
}
void NKView::aImage() {
	NKhron* sel = doc->GetSelHro();
	if (sel) {

		QString fileName = QFileDialog::getOpenFileName(this, tr(
				"Choose a file name"), "", tr(
				"image (*.jpg | *.bmp | *.png | *.gif)"));
		if (fileName.isEmpty())
			return;
		QImage slika(fileName);

		sel->setImage(slika.scaled(64, 64));
		update();
	}

}
