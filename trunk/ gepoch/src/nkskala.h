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

// glavna uloga skale jeste pretvaranja koordinata na ekranu u odgovarajuci
// datum i obrnuto. Glavna karakteristika skale je njen pocetak to je datum
// koju se nalazi na nultoj koordinati ekrana i razmera na osnovu koje se
// racunaju ostali datumi.

//u planu je da se skala generalizuje i omoguci dodavalje drugih kalendara
//kao i mogucnost prikazivanja dve ili vise skala koje bi prikazivale datume
//razlcitih kalendara za datu koordinatu ekrana.
#ifndef NKSKALA_H
#define NKSKALA_H

#include <QWidget>
#include "nkjd.h"
class NKSkala : public QWidget
{
public:
   NKSkala(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
private:
    void NacrtajDatum(QPainter *p1,QPoint gde,QString datum,QString vreme);    
private:
    NKJD m_pocetak;           //datum na pocetku skale
    QRect m_rc;
    double m_razmera;         //minuta po pikselu  (minuti/piksel)
    int m_korak;              //razmak izmedu dva datuma
    bool m_stampajvreme;      //dali se prikazuje vreme pored datuma
    int m_offset;             //udaljenost pocetka iscrtavanja od 0
    int m_polozaj;
    QFont  m_Font;
    QColor m_C1;
    QColor m_C2;
public:
    //set
    void SetPolozajPokazivaca(int pol);
    //datum na pocetku skale odnosno na nultoj koordinati ekrana
    void SetPocetak(NKJD poc) {m_pocetak=poc;};
    void SetRazmera(double raz) {m_razmera=raz;};
    void SetKorak(int kor) {m_korak=kor;};
    void SetStampajVreme(bool v) {m_stampajvreme=v;};
    //Get
    NKJD GetPocetak(void) {return m_pocetak;};
    double GetRazmera(void) {return m_razmera;};
    int GetKorak(void) {return m_korak;};
    bool GetStampajVreme(void) {return m_stampajvreme;};
    //razmera, polozaj i zoom skale
    void Osvezi(void) {this->update();};
    void PomeriDesno(int p);
    void PomeriLevo(int p);
    void uvecaj(int raz);
    void smanji(int raz);
    void RastojanjePlus(void);
    void RastojanjeMinus(void);
    //komunikacija sa epohom
    //vraca -1 za levu stranu i -2 za desnu a pozitivnu
    //vrednost ak je na vidljivom delu
    int PolozajZaDatum(NKJD datum);
    NKJD DatumZaPolozaj(int polozaj);
    int GetPolozaj() {return m_polozaj;};
    void CentrirajDatum(JD datum);
};

#endif
