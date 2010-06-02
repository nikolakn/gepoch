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

#include <QtGui>

#include "nkskala.h"
#define L_DUZ 15

NKSkala::NKSkala(QWidget *parent)
    : QWidget(parent)
{
    m_pocetak.SetJD(0);
    m_razmera=2628;
    m_korak=200;
    m_stampajvreme=true;
    m_offset=0;
    m_polozaj=0;
    m_C1 = Qt::red;
    m_C2 = Qt::blue;
    setFixedHeight(22);
    m_Font=QFont("Times", 7);
    setMouseTracking(true);

}
void NKSkala::NacrtajDatum(QPainter *p1,QPoint gde,QString datum,QString vreme){
    QLine line1(gde.x(), gde.y(),gde.x(),(gde.y()+L_DUZ));
    p1->drawLine(line1);
    if(m_stampajvreme){
        p1->drawText(gde.x()+4,gde.y(),vreme);
        p1->drawText(gde.x()+4,gde.y()+11,datum);
    }
    else{
        p1->drawText(gde.x()+4,gde.y()+11,datum);
    }
}
void NKSkala::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    m_rc.setHeight(height());
    m_rc.setWidth(width());
    painter.setRenderHint(QPainter::Antialiasing);
    QPoint topLeft(width(),0);
    QPoint bottomRight(0,height());
    QLinearGradient backgroundGradient(topLeft, bottomRight);
    backgroundGradient.setColorAt(0.0, QColor(Qt::blue).lighter(180));
    backgroundGradient.setColorAt(1.0, QColor(Qt::green).lighter(140));
    painter.fillRect(this->rect(), QBrush(backgroundGradient));
    QPoint t1;
    t1.setY(10);
    painter.setPen(m_C2);
    painter.setFont(m_Font);
    NKJD temp=m_pocetak;
    for(int i=m_offset;i<=width();i+=m_korak){
        t1.setX(i);
        QString vv=QString("UT %1:%2:%3").arg(abs(temp.GetHour())).arg(abs(temp.GetMin())).arg(abs(temp.GetSec()));
        QString dd=QString("%1.%2.%3").arg(abs(temp.GetGregDay())).arg(abs(temp.GetGregMonth())).arg(temp.GetGregYear());
        NacrtajDatum(&painter,t1,dd,vv);
        temp.AddMin(m_korak*m_razmera);
    }
    QPen ol1(m_C1,1,Qt::DashLine);
    painter.setPen(ol1);
    QLine line1(m_polozaj,0,m_polozaj,30);
    painter.drawLine(line1);
}
void NKSkala::mouseMoveEvent(QMouseEvent * event){
    m_polozaj=event->pos().x();
    this->update();
}
void NKSkala::PomeriDesno(int pp)
{
        //u plusu <
    int pomak=pp+m_offset;  //gde ce biti novi offset
    int kolikokoraka=pomak/m_korak;
    pomak=pomak%m_korak;
    m_offset=pomak;
    if(kolikokoraka>0){
        m_pocetak.SubMin(m_razmera*kolikokoraka*m_korak);
    }
    this->update();
}
//ako ide u minus offset je takoce pozitivan ali se oduzima od koraka
void NKSkala::PomeriLevo(int pk)
{
    //u minusu >
    int pomak=abs(m_offset)-pk;
    if (pomak>0){
        m_offset=pomak;
    }
    else{
        pomak=abs(m_offset)+abs(pk);
        int kolikokoraka=pomak/m_korak;
        pomak=pomak%m_korak;
        m_offset=m_korak-pomak;
        kolikokoraka+=1;
        m_pocetak.AddMin(m_razmera*kolikokoraka*m_korak);
    }
    this->update();
}
void NKSkala::uvecaj(int raz){
    m_razmera=m_razmera*raz;
    this->update();
}
void NKSkala::smanji(int raz){
    m_razmera=m_razmera/raz;
    this->update();
}
int NKSkala::PolozajZaDatum(NKJD datum){
   int rez;
   double razlika=datum.RoundDifferInMin(m_pocetak);
   double duzina=(razlika/m_razmera)+m_offset;
   if(duzina<0)
           return -1;
   if(duzina>m_rc.width())
           return (-m_rc.width());
   rez=duzina;
   return rez;
}
NKJD NKSkala::DatumZaPolozaj(int polozaj){
   NKJD rez;
   double duzina=polozaj-m_offset;
   double min=duzina*m_razmera;
   rez=m_pocetak;
   rez.AddMin(min);
   return rez;
}
void NKSkala::SetPolozajPokazivaca(int pol){
        m_polozaj=pol;
       this->update();
}
void  NKSkala::RastojanjePlus(void){
    if(m_korak<800){
        m_korak+=100;
    }
}
void  NKSkala::RastojanjeMinus(void){
    if(m_korak>100){
        m_korak-=100;
    }
}
void  NKSkala::CentrirajDatum(JD datum){
    int w=width()/2;
    this->SetPocetak(datum);
    NKJD temp(datum);
    NKJD sred=this->DatumZaPolozaj(w);
    sred.SubDay(temp.GetJD());
    temp.SubDay(sred.GetJD());

    this->SetPocetak(temp);
}
