
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

 //dodat je engleski i srpski jezik
#include <QtGui/QApplication>
#include <QTranslator>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator myappTranslator;
      	if (myappTranslator.load(":/translations/Epoch_en.qm")) {
      		app.installTranslator(&myappTranslator);
      	}
	app.setApplicationName("gEpoch");
	app.setApplicationVersion("1.5");
	app.setOrganizationName("Nikola Knezevic");
	app.setOrganizationDomain("http://code.google.com/p/gepoch/");
    Q_INIT_RESOURCE(epoch);
    MainWindow mainWin;

    mainWin.resize(800,600);
    mainWin.show();
    return app.exec();

}
