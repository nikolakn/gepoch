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
#include "mainwindow.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"
#include <QtGui/QMatrix>
#include <QtGui/QMouseEvent>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QAction>
#include <QtGui/QDockWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

	list.append(tr("All"));
	list.append(tr("War and Conflict"));
	list.append(tr("Religion"));
	list.append(tr("Science"));
	list.append(tr("Society"));
	list.append(tr("Technology"));
	list.append(tr("National"));
	list.append(tr("Historical outlines"));
	list.append(tr("Culture"));
	list.append(tr("Art"));
	list.append(tr("Exploration"));
	list.append(tr("Nature"));
	list.append(tr("Sports"));
    listRender.append(tr("Basic"));
    listRender.append(tr("Rect"));
    listRender.append(tr("Size1"));
    listRender.append(tr("Size2"));
    listRender.append(tr("Size3"));
    listAp.append(tr("Always"));
    listAp.append(tr("here+"));
    listAp.append(tr("only here"));
    listAp.append(tr("here-"));
	decEdit=false;
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    skala=new NKSkala();
    layout->addWidget(skala);
    view = new NKView(0,skala,&Doc,Tree);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    connect(view, SIGNAL(statusSig()), this, SLOT(status()));

    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    createDockWindows();
    setWindowIcon(QIcon(":/epoha.png"));
    setWindowTitle(tr("Epoch"));
    newEpoch();

    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::newEpoch()
{
	if(Doc.GetBrojEpoha()>0){
		if(QMessageBox::warning(this,tr("Epoch"), tr("Do you want to save document"), tr("Save"),tr("No")))
		{
			//nemoj da sacuvas
			NKJD poc;
			poc.SetShortDate(1,1,2010);
			skala->SetPocetak(poc);
		    timelineList->clear();
		    peopleList->clear();
		    Tree->clear();
		    decW->clear();
		    decEdit=false;
			Doc.ocisti();
			view->ocisti();
			kategorija->setCurrentIndex(0);
			godina->document()->setPlainText(tr(""));
		}
		else{
			//sacuvaj
			save();
		}
	}
	else{
		NKJD poc;
			poc.SetShortDate(1,1,2010);
			skala->SetPocetak(poc);
	}

}

void MainWindow::print()
{
#ifndef QT_NO_PRINTDIALOG
 
    QPrinter printer;

    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (dlg->exec() != QDialog::Accepted)
        return;

  //  document->print(&printer);

    statusBar()->showMessage(tr("Ready"), 2000);
#endif
}

void MainWindow::save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                        tr("Choose a file name"), "",
                        tr("epo (*.epo)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Dock Widgets"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
     QDataStream out(&file);
     out << (qint32)1; //verzija formata
	 out<< (double)(skala->GetPocetak().GetJD());
	 out<< (double)skala->GetRazmera();
     out<< (bool)decEdit;
	 out<< (int)kategorija->currentIndex();
	 view->save(out);
	 Doc.save(out);
    statusBar()->showMessage(tr("Saved '%1'").arg(fileName), 2000);
}


void MainWindow::undo()
{

}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About Epoch"),
            tr("The <b>Epoch</b>, simple timeline program.<br>"
               "Nikola Knezevic, <br>"
               "Serbia 2010 <br>"
               "nkcodeplus@gmail.com"));
}

void MainWindow::createActions()
{
    newEpochAct = new QAction(QIcon(":/images/new.png"), tr("&New"),this);
    newEpochAct->setShortcuts(QKeySequence::New);
    newEpochAct->setStatusTip(tr("Create a new document"));
    connect(newEpochAct, SIGNAL(triggered()), this, SLOT(newEpoch()));

    saveAct = new QAction(QIcon(":/images/save.png"), tr("&Save..."), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the current document"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    openAct = new QAction(QIcon(":/images/Folder.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open document"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    importAct = new QAction(QIcon(":/images/Folder.png"), tr("Import..."), this);
    importAct->setStatusTip(tr("Import document"));
    connect(importAct, SIGNAL(triggered()), this, SLOT(import()));

    moveLeft = new QAction(QIcon(":/images/Left.png"), tr("&Left"), this);
    moveLeft->setShortcuts(QKeySequence::MoveToNextChar);
    moveLeft->setStatusTip(tr("Move left"));
    connect(moveLeft, SIGNAL(triggered()), this, SLOT(mleft()));

    moveRight = new QAction(QIcon(":/images/Right.png"), tr("&Right"), this);
    moveRight->setShortcuts(QKeySequence::MoveToPreviousChar);
    moveRight->setStatusTip(tr("Move right"));
    connect(moveRight, SIGNAL(triggered()), this, SLOT(mright()));

    zoomIn = new QAction(QIcon(":/images/zoomin.png"), tr("&Zoom In"), this);
    zoomIn->setShortcuts(QKeySequence::ZoomIn);
    zoomIn->setStatusTip(tr("Zoom In Skale"));
    connect(zoomIn, SIGNAL(triggered()), this, SLOT(zoomin()));

    zoomOut = new QAction(QIcon(":/images/zoomout.png"), tr("&Zoom Out"), this);
    zoomOut->setShortcuts(QKeySequence::ZoomOut);
    zoomOut->setStatusTip(tr("Zoom Out Skale"));
    connect(zoomOut, SIGNAL(triggered()), this, SLOT(zoomout()));
 
  	aEpoha = new QAction(QIcon(":/images/aepoha.png"), tr("&add epoch"), this);
    aEpoha->setStatusTip(tr("Add Aps Epoch"));
    connect(aEpoha, SIGNAL(triggered()), view, SLOT(aepoha()));

    rEpoha = new QAction(QIcon(":/images/repoha.png"), tr("&add rel epoch"), this);
    rEpoha->setStatusTip(tr("Add relative Epoch"));
    connect(rEpoha, SIGNAL(triggered()), view, SLOT(repoha()));

    aDog = new QAction(QIcon(":/images/adog.png"), tr("&add event"), this);
    aDog->setStatusTip(tr("Add Aps event"));
    connect(aDog, SIGNAL(triggered()), view, SLOT(adog()));

    rDog = new QAction(QIcon(":/images/reldog.png"), tr("&add event"), this);
    rDog->setStatusTip(tr("Add rel event"));
    connect(rDog, SIGNAL(triggered()), view, SLOT(rdog()));

    aPer = new QAction(QIcon(":/images/Man.png"), tr("&add aps person"), this);
    aPer->setStatusTip(tr("Add Aps person"));
    connect(aPer, SIGNAL(triggered()), view, SLOT(aPer()));

    rPer = new QAction(QIcon(":/images/Users.png"), tr("&add rel person"), this);
    rPer->setStatusTip(tr("Add rel person"));
    connect(rPer, SIGNAL(triggered()), view, SLOT(rPer()));
    
    imageAction = new QAction(QIcon(":/images/Photo.png"), tr("&add image"), this);
    imageAction->setStatusTip(tr("Add Image"));
    connect(imageAction, SIGNAL(triggered()), view, SLOT(aImage()));

    cutAct = new QAction(QIcon(":/images/cut.png"), tr("&cut  relative link"), this);
    cutAct->setStatusTip(tr("cut relative link"));
    connect(cutAct, SIGNAL(triggered()), view, SLOT(acut()));

    linkAct = new QAction(QIcon(":/images/link.png"), tr("&make relative link"), this);
    linkAct->setStatusTip(tr("make relative link"));
    connect(linkAct, SIGNAL(triggered()),view, SLOT(alink()));

    delAct = new QAction(QIcon(":/images/Close.png"), tr("&delete"), this);
    delAct->setStatusTip(tr("delete select object"));
    connect(delAct, SIGNAL(triggered()),view, SLOT(adel()));

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newEpochAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(importAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);


    editMenu = menuBar()->addMenu(tr("&Edit"));
   // editMenu->addAction(undoAct);
    editMenu->addAction(cutAct);
    editMenu->addAction(delAct);
    editMenu->addAction(linkAct);
    viewMenu = menuBar()->addMenu(tr("&View"));

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newEpochAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(openAct);
    fileToolBar->setMaximumHeight(28);

    editToolBar = addToolBar(tr("Edit"));
  //  editToolBar->addAction(undoAct);
    editToolBar->addAction(cutAct);
    editToolBar->addAction(delAct);
    editToolBar->addAction(linkAct);

    editToolBar->setMaximumHeight(28);

    posToolBar=addToolBar(tr("Position"));
    posToolBar->setMaximumHeight(28);
    posToolBar->addAction(moveLeft);
    posToolBar->addAction(moveRight);
    posToolBar->addAction(zoomIn);
    posToolBar->addAction(zoomOut);
    godina=new QTextEdit();
    godina->setMaximumWidth(100);
    connect(godina, SIGNAL(textChanged ()),
              this, SLOT(godinaChanged()));
    posToolBar->addWidget(godina);
    kategorija=new QComboBox();
    kategorija->addItems(list);
    connect(kategorija, SIGNAL(currentIndexChanged(const QString)),
            this, SLOT(kategorijaChanged(const QString)));
    posToolBar->addWidget(kategorija);

    addEpochToolBar=addToolBar(tr("Add"));
    addEpochToolBar->setMaximumHeight(28);
    addEpochToolBar->addAction(aEpoha);
    addEpochToolBar->addAction(rEpoha);
    addEpochToolBar->addAction(aDog);
    addEpochToolBar->addAction(rDog);
    addEpochToolBar->addAction(aPer);
    addEpochToolBar->addAction(rPer);
    addEpochToolBar->addAction(imageAction);

}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget(tr("Timeline"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //dock->setFeatures(QDockWidget::DockWidgetMovable);
    timelineList = new QTreeWidget(dock);
    dock->setWidget(timelineList);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    QDockWidget *docktt=dock;
    dock = new QDockWidget(tr("People"), this);
    peopleList = new QTreeWidget(dock);
    dock->setWidget(peopleList);

    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());
    tabifyDockWidget(docktt,dock);

    dock = new QDockWidget(tr("description "), this);

    decW = new QTextBrowser(dock);
    decW->setOpenExternalLinks(true);
    dock->setWidget(decW);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());
    tabifyDockWidget(docktt,dock);
    connect(decW, SIGNAL(textChanged ()), this, SLOT(decChanged()));

    dock = new QDockWidget(tr("Tree"), this);
    Tree = new QTreeWidget(dock);

    dock->setWidget(Tree);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());
    tabifyDockWidget(docktt,dock);


    ///////////////
    view->setTree(Tree,peopleList,timelineList);
    connect(Tree,SIGNAL(itemDoubleClicked( QTreeWidgetItem  *, int)),
    		view,SLOT(selectFromTree( QTreeWidgetItem  *, int)));
    connect(peopleList,SIGNAL(itemDoubleClicked( QTreeWidgetItem  *, int)),
       		view,SLOT(selectFromppTree( QTreeWidgetItem  *, int)));
    connect(timelineList,SIGNAL(itemDoubleClicked( QTreeWidgetItem  *, int)),
       		view,SLOT(selectFromtlTree( QTreeWidgetItem  *, int)));
    variantManager = new QtVariantPropertyManager(this);

    connect(variantManager, SIGNAL(valueChanged(QtProperty *, const QVariant &)),
              this, SLOT(valueChanged(QtProperty *, const QVariant &)));

    dock = new QDockWidget(this);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    QtVariantEditorFactory *variantFactory = new QtVariantEditorFactory(this);
    propertyEditor = new QtTreePropertyBrowser(dock);
    propertyEditor->setFactoryForManager(variantManager, variantFactory);

    dock->setWidget(propertyEditor);

    viewMenu->addAction(dock->toggleViewAction());
    QMap<QtProperty *, QString>::ConstIterator itProp = propertyToId.constBegin();
    while (itProp != propertyToId.constEnd()) {
        delete itProp.key();
        itProp++;
    }
    connect(view, SIGNAL(itemClicked()),
             this, SLOT(itemClicked()));
    connect(view, SIGNAL(itemDoubleClicked()),
             this, SLOT(itemDoubleClicked()));
    itemClicked();
}

void MainWindow::mleft(){
    skala->PomeriDesno(20);
    skala->update();
    view->update();
}
void MainWindow::mright(){
    skala->PomeriLevo(20);
    skala->update();
    view->update();
}
void MainWindow::status(){
    statusBar()->clearMessage();
    statusBar()->showMessage(view->getStatus(),0);

}
void MainWindow::zoomin(){
    skala->smanji(2);
    skala->update();
    view->update();
}
void MainWindow::zoomout(){
    skala->uvecaj(2);
    skala->update();
    view->update();
}

void MainWindow::cut(){

    skala->update();
    view->update();
}
void MainWindow::del(){

    skala->update();
    view->update();
}
void MainWindow::link(){

    skala->update();
    view->update();
}

void MainWindow::valueChanged(QtProperty *property, const QVariant &value)
{
	 if (!propertyToId.contains(property))
	        return;

	 NKhron *sel=Doc.GetSelHro();
	 if(!sel)
		 return;
	 QString id = propertyToId[property];
	 NKApsEpoch* ep2 = NULL;
	 ep2 = dynamic_cast<NKApsEpoch*> (sel);
	 if(ep2){
		    if(id == QLatin1String("StartDate")) {
			    	NKJD st;
			    	if(st.ParsDatum(value.toString(),st))
			    		sel->SetStartDate(st.GetJD());
			}
			if(id == QLatin1String("StartTime")) {
				NKJD st(sel->GetApStart());
				if(st.ParsTime(value.toString(),st)){
					sel->SetStartDate(st.GetJD());
				}
			}
	    if(id == QLatin1String("EndDate")) {
	    	NKJD st;
	    	if(st.ParsDatum(value.toString(),st))
	    		st.SubDay(sel->GetApStart());
	    		sel->SetEndDate(st.GetJD());
	    }
	    if(id == QLatin1String("EndTime")) {
	    	NKJD st(sel->GetApStart());
	        NKJD st1(sel->GetEndDate());
	        st.AddDay(st1.GetJD());
			if(st.ParsTime(value.toString(),st)){
				st.SubDay(sel->GetApStart());
				sel->SetEndDate(st.GetJD());
			}
	    }
	    if(id == QLatin1String("Duration")) {
	    	if(value.toString().toDouble()>=0){
	    		sel->SetEndDate(value.toString().toDouble());
	    	}
	    }
	    if(id == QLatin1String("DurationYears")) {
	    	if(value.toString().toDouble()>=0){
	    		sel->SetEndDate(value.toString().toDouble()*365);
	    	}
	    }

        NKApsPerson* ap2 = NULL;
        ap2 = dynamic_cast<NKApsPerson*> (sel);
 		if(ap2){
            if (id == QLatin1String("Male")) {
          		 ap2->setIsMale(value.toBool());
          	}
 		}

	 }
    NKApsEvent* ae2 = NULL;
	ae2 = dynamic_cast<NKApsEvent*> (sel);
	if(ae2){
	    if(id == QLatin1String("StartDate")) {
			    	NKJD st;
			    	if(st.ParsDatum(value.toString(),st))
			    		sel->SetStartDate(st.GetJD());
			}
			if(id == QLatin1String("StartTime")) {
				NKJD st(sel->GetApStart());
				if(st.ParsTime(value.toString(),st)){
					sel->SetStartDate(st.GetJD());
				}
			}
	}
     NKRelEvent* re2 = NULL;
     re2 = dynamic_cast<NKRelEvent*> (sel);
		if(re2){
		    if(id == QLatin1String("StartDate")) {
		    	NKJD st;
			    	if(st.ParsDatum(value.toString(),st))
			    		st.SubDay(sel->GetApsolute()->GetApStart());
			    		sel->SetStartDate(st.GetJD());
			}
			if(id == QLatin1String("StartTime")) {
			    	NKJD st(sel->GetApsolute()->GetApStart());
			        NKJD st1(sel->GetStartDate());
			        st.AddDay(st1.GetJD());
					if(st.ParsTime(value.toString(),st)){
						st.SubDay(sel->GetApsolute()->GetApStart());
						sel->SetStartDate(st.GetJD());
					}
			}
			    if(id == QLatin1String("fromEpochdays")) {
			    	if(value.toString().toDouble()>=0){
			    		sel->SetStartDate(value.toString().toDouble());
			    	}
			    }
			    if(id == QLatin1String("fromEpochYars")) {
			    	if(value.toString().toDouble()>=0){
			    		sel->SetStartDate(value.toString().toDouble()*365);
			    	}
			    }
	            if (id == QLatin1String("Link")) {
	          		 sel->setRelLinkDraw(value.toBool());
	          	}
		}
	 //rel epoch
		 NKRelEpoch* rep2 = NULL;
			 rep2 = dynamic_cast<NKRelEpoch*> (sel);
			 if(rep2){
				if(id == QLatin1String("StartDate")) {
							NKJD st;
								if(st.ParsDatum(value.toString(),st))
									st.SubDay(sel->GetApsolute()->GetApStart());
									sel->SetStartDate(st.GetJD());
				}
				if(id == QLatin1String("StartTime")) {
						NKJD st(sel->GetApsolute()->GetApStart());
						NKJD st1(sel->GetStartDate());
						st.AddDay(st1.GetJD());
						if(st.ParsTime(value.toString(),st)){
							st.SubDay(sel->GetApsolute()->GetApStart());
							sel->SetStartDate(st.GetJD());
						}
				}
			    if(id == QLatin1String("EndDate")) {
			    	NKJD st;
			    	if(st.ParsDatum(value.toString(),st))
			    		st.SubDay(sel->GetApStart());
			    		sel->SetEndDate(st.GetJD());
			    }
			    if(id == QLatin1String("EndTime")) {
			    	NKJD st(sel->GetApStart());
			        NKJD st1(sel->GetEndDate());
			        st.AddDay(st1.GetJD());
					if(st.ParsTime(value.toString(),st)){
						st.SubDay(sel->GetApStart());
						sel->SetEndDate(st.GetJD());
					}
			    }
			    if(id == QLatin1String("Duration")) {
			    	if(value.toString().toDouble()>=0){
			    		sel->SetEndDate(value.toString().toDouble());
			    	}
			    }
			    if(id == QLatin1String("DurationYears")) {
			    	if(value.toString().toDouble()>=0){
			    		sel->SetEndDate(value.toString().toDouble()*365);
			    	}
			    }
			    if(id == QLatin1String("fromEpochdays")) {
			    	if(value.toString().toDouble()>=0){
			    		sel->SetStartDate(value.toString().toDouble());
			    	}
			    }
			    if(id == QLatin1String("fromEpochYars")) {
			    	if(value.toString().toDouble()>=0){
			    		sel->SetStartDate(value.toString().toDouble()*365);
			    	}
			    }
	            if (id == QLatin1String("Link")) {
	          		 sel->setRelLinkDraw(value.toBool());
	          	}
		        NKRelPerson* rap2 = NULL;
		        rap2 = dynamic_cast<NKRelPerson*> (sel);
		 		if(rap2){
		            if (id == QLatin1String("Male")) {
		          		 rap2->setIsMale(value.toBool());
		          	}
		 		}
			 }
	 //zajednicko

	    if (id == QLatin1String("Name")) {
	    	sel->setName(value.toString());
	    }
	    if (id == QLatin1String("category")) {
		    	sel->setEventType(value.toString().toInt());
		    }
	    if(id == QLatin1String("pen")) {
	        sel->setLineColor(qVariantValue<QColor>(value));
	    }
	    if (id == QLatin1String("Visibility")) {
			    	sel->setZoom(value.toString().toInt());
			    	sel->setDozoom(view->getZoom());
		   }
		if (id == QLatin1String("Render")) {
				sel->setRenderType(value.toString().toInt());
	   }
	 Doc.UpdateTree(Tree,peopleList,timelineList);
	 view->update();
}
void MainWindow::addProperty(QtVariantProperty *property, const QString &id)
{
    propertyToId[property] = id;
    idToProperty[id] = property;
    QtBrowserItem *item = propertyEditor->addProperty(property);
    if (idToExpanded.contains(id))
       propertyEditor->setExpanded(item, idToExpanded[id]);
}
void MainWindow::updateExpandState()
{
    QList<QtBrowserItem *> list = propertyEditor->topLevelItems();
    QListIterator<QtBrowserItem *> it(list);
    while (it.hasNext()) {
        QtBrowserItem *item = it.next();
        QtProperty *prop = item->property();
        idToExpanded[propertyToId[prop]] = propertyEditor->isExpanded(item);
    }
}
void MainWindow::itemClicked(){
    updateExpandState();

    QMap<QtProperty *, QString>::ConstIterator itProp = propertyToId.constBegin();
    while (itProp != propertyToId.constEnd()) {
        delete itProp.key();
        itProp++;
    }
    propertyToId.clear();
    idToProperty.clear();

    QtVariantProperty *property;


    NKhron *sel=Doc.GetSelHro();
    if(sel){
    	 decEdit=false;

    	decW->setHtml(sel->getDesc());

    	decW->setReadOnly(true);

    	//zajednicko
        property = variantManager->addProperty(QVariant::String, tr("Name"));
        property->setValue(sel->getName());
        addProperty(property, QLatin1String("Name"));



    	NKApsEpoch* ep2 = NULL;
    	ep2 = dynamic_cast<NKApsEpoch*> (sel);
    	if(ep2){
			NKJD st(sel->GetApStart());
			QString vv=QString("%1:%2").arg(abs(st.GetHour())).arg(abs(st.GetMin()));
			QString dd=QString("%1.%2.%3").arg(abs(st.GetGregDay())).arg(abs(st.GetGregMonth())).arg(st.GetGregYear());

			property = variantManager->addProperty(QVariant::String, tr("Start date"));
			property->setValue(dd);
			addProperty(property, QLatin1String("StartDate"));
			property = variantManager->addProperty(QVariant::String, tr("Start time"));
			property->setValue(vv);
			addProperty(property, QLatin1String("StartTime"));
            NKJD st1(sel->GetEndDate());
            st.AddDay(st1.GetJD());
            QString vv1=QString("%1:%2").arg(abs(st.GetHour())).arg(abs(st.GetMin()));
            QString dd1=QString("%1.%2.%3").arg(abs(st.GetGregDay())).arg(abs(st.GetGregMonth())).arg(st.GetGregYear());
            property = variantManager->addProperty(QVariant::String, tr("End date"));
            property->setValue(dd1);
            addProperty(property, QLatin1String("EndDate"));
            property = variantManager->addProperty(QVariant::String, tr("End time"));
            property->setValue(vv1);
            addProperty(property, QLatin1String("EndTime"));

            double trajanje=(double)(sel->GetEndDate());

            QString strtrajanje=QString("%1").arg(trajanje);

            property = variantManager->addProperty(QVariant::String, tr("Duration in days"));
            property->setValue(strtrajanje);
            addProperty(property, QLatin1String("Duration"));

            QString godinama=QString("%1").arg(trajanje/365.0);

            property = variantManager->addProperty(QVariant::String, tr("Duration in years"));
            property->setValue(godinama);
            addProperty(property, QLatin1String("DurationYears"));

            NKApsPerson* ap2 = NULL;
            ap2 = dynamic_cast<NKApsPerson*> (sel);
     		if(ap2){
                property = variantManager->addProperty(QVariant::Bool, tr("is male"));
                property->setValue(ap2->getIsMale());
                addProperty(property, QLatin1String("Male"));
     		}
    	}
		NKApsEvent* ae2 = NULL;
		ae2 = dynamic_cast<NKApsEvent*> (sel);
		if(ae2){
			    NKJD st(sel->GetApStart());
				QString vv=QString("%1:%2").arg(abs(st.GetHour())).arg(abs(st.GetMin()));
				QString dd=QString("%1.%2.%3").arg(abs(st.GetGregDay())).arg(abs(st.GetGregMonth())).arg(st.GetGregYear());

				property = variantManager->addProperty(QVariant::String, tr("Start date"));
				property->setValue(dd);
				addProperty(property, QLatin1String("StartDate"));
				property = variantManager->addProperty(QVariant::String, tr("Start time"));
				property->setValue(vv);
				addProperty(property, QLatin1String("StartTime"));
		}
        NKRelEvent* re2 = NULL;
        re2 = dynamic_cast<NKRelEvent*> (sel);
 		if(re2){
 			NKJD st(sel->GetApStart());
				QString vv=QString("%1:%2").arg(abs(st.GetHour())).arg(abs(st.GetMin()));
				QString dd=QString("%1.%2.%3").arg(abs(st.GetGregDay())).arg(abs(st.GetGregMonth())).arg(st.GetGregYear());

				property = variantManager->addProperty(QVariant::String, tr("Start date"));
				property->setValue(dd);
				addProperty(property, QLatin1String("StartDate"));
				property = variantManager->addProperty(QVariant::String, tr("Start time"));
				property->setValue(vv);
				addProperty(property, QLatin1String("StartTime"));
				double trajanje=(double)(sel->GetStartDate());

				QString strtrajanje=QString("%1").arg(trajanje);

				property = variantManager->addProperty(QVariant::String, tr("form epoch start(Days)"));
				property->setValue(strtrajanje);
				addProperty(property, QLatin1String("fromEpochdays"));

				QString godinama=QString("%1").arg(trajanje/365.0);

				property = variantManager->addProperty(QVariant::String, tr("from epoch start(years)"));
				property->setValue(godinama);
				addProperty(property, QLatin1String("fromEpochYars"));

	            property = variantManager->addProperty(QVariant::Bool, tr("Draw Link"));
	            property->setValue(sel->getRelLinkDraw());
	            addProperty(property, QLatin1String("Link"));
 		}
        NKRelEpoch* reep2 = NULL;
        reep2 = dynamic_cast<NKRelEpoch*> (sel);
 		if(reep2){
 			NKJD st(sel->GetApStart());
			QString vv=QString("%1:%2").arg(abs(st.GetHour())).arg(abs(st.GetMin()));
			QString dd=QString("%1.%2.%3").arg(abs(st.GetGregDay())).arg(abs(st.GetGregMonth())).arg(st.GetGregYear());

			property = variantManager->addProperty(QVariant::String, tr("Start date"));
			property->setValue(dd);
			addProperty(property, QLatin1String("StartDate"));
			property = variantManager->addProperty(QVariant::String, tr("Start time"));
			property->setValue(vv);
 			addProperty(property, QLatin1String("StartTime"));
 	        NKJD st1(sel->GetEndDate());
			st.AddDay(st1.GetJD());
			QString vv1=QString("%1:%2").arg(abs(st.GetHour())).arg(abs(st.GetMin()));
			QString dd1=QString("%1.%2.%3").arg(abs(st.GetGregDay())).arg(abs(st.GetGregMonth())).arg(st.GetGregYear());
			property = variantManager->addProperty(QVariant::String, tr("End date"));
			property->setValue(dd1);

			addProperty(property, QLatin1String("EndDate"));
			property = variantManager->addProperty(QVariant::String, tr("End time"));
			property->setValue(vv1);
			addProperty(property, QLatin1String("EndTime"));

		    double trajanje=(double)(sel->GetEndDate());
			QString strtrajanje=QString("%1").arg(trajanje);
			property = variantManager->addProperty(QVariant::String, tr("Duration in days"));
			property->setValue(strtrajanje);
			addProperty(property, QLatin1String("Duration"));
			QString godinama=QString("%1").arg(trajanje/365.0);
			property = variantManager->addProperty(QVariant::String, tr("Duration in years"));
			property->setValue(godinama);
			addProperty(property, QLatin1String("DurationYears"));

			trajanje=(double)(sel->GetStartDate());

			strtrajanje=QString("%1").arg(trajanje);

			property = variantManager->addProperty(QVariant::String, tr("form epoch start(Days)"));
			property->setValue(strtrajanje);
			addProperty(property, QLatin1String("fromEpochdays"));

			godinama=QString("%1").arg(trajanje/365.0);

			property = variantManager->addProperty(QVariant::String, tr("from epoch start(years)"));
			property->setValue(godinama);
			addProperty(property, QLatin1String("fromEpochYars"));

		    property = variantManager->addProperty(QVariant::Bool, tr("Draw Link"));
			property->setValue(sel->getRelLinkDraw());
			addProperty(property, QLatin1String("Link"));
			//rel person
            NKRelPerson* rp2 = NULL;
            rp2 = dynamic_cast<NKRelPerson*> (sel);
     		if(rp2){
                property = variantManager->addProperty(QVariant::Bool, tr("is male"));
                property->setValue(rp2->getIsMale());
                addProperty(property, QLatin1String("Male"));
     		}
 		}
        	//zajednicko na kraju
		    property = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(), tr("category"));
			property->setAttribute(QLatin1String("enumNames"),list);
			property->setValue(sel->getEventType());
			addProperty(property, QLatin1String("category"));

			property = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(), tr("Render"));
			property->setAttribute(QLatin1String("enumNames"),listRender);
			property->setValue(sel->getRenderType());
			addProperty(property, QLatin1String("Render"));

			property = variantManager->addProperty(QtVariantPropertyManager::enumTypeId(), tr("Visibility"));
			property->setAttribute(QLatin1String("enumNames"),listAp);
			property->setValue(sel->getZoom());
			addProperty(property, QLatin1String("Visibility"));

			property = variantManager->addProperty(QVariant::Color, tr("Pen Color"));
			property->setValue(sel->getLineColor());
			addProperty(property, QLatin1String("pen"));

    }
    else{
    	 decW->document()->setPlainText("");
    }
}
void MainWindow::itemDoubleClicked(){
	decEdit=true;
	 NKhron *sel=Doc.GetSelHro();
	    if(sel){
	    	decW->document()->setPlainText(sel->getDesc());
	    }

	decW->setReadOnly(false);
}
void MainWindow::kategorijaChanged(const QString &size){

	view->setKat(kategorija->findText(size,Qt::MatchExactly));
	update();
}
void MainWindow::godinaChanged(){
	QString ss=godina->document()->toPlainText();
	NKJD st;
	QRegExp rx("([1-9]|0[1-9]|[1-2][0-9]|3[01])\\.([1-9]|0[1-9]|1[0-2]|3[01])\\.\\-?([1-9])\\d{0,8}");
    if(rx.exactMatch(ss)){
	if(st.ParsDatum(ss,st)){
		skala->SetPocetak(st);
		update();
	}
    }

}
void MainWindow::decChanged(){
	 NKhron *sel=Doc.GetSelHro();

	 if(sel){
		 if(!decEdit){
			 decW->setReadOnly(true);
		 }
		 else{
			 sel->setDesc(decW->document()->toPlainText());
			 decW->setReadOnly(false);
		 }
	 }

}
void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                        tr("Choose a file name"), "",
                        tr("epo (*.epo)"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Dock Widgets"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
    //////////
		    timelineList->clear();
		    peopleList->clear();
		    Tree->clear();
		    decW->clear();
		    decEdit=false;
			Doc.ocisti();
			view->ocisti();
			godina->document()->setPlainText(tr(""));
    //////////
     QDataStream in(&file);
     qint32 verzija;
     in >> verzija; //verzija formata
     double pocetak;
     double rezmera;
	 in >> pocetak;
	 in >> rezmera;
	 NKJD pp(pocetak);
	 skala->SetPocetak(pp);
	 skala->SetRazmera(rezmera);
     in >> decEdit;
     int ins;
	 in >> ins;
	 kategorija->setCurrentIndex(ins);
	  view->open(in);
	  Doc.open(in);
	  Doc.UpdateTree(Tree,peopleList,timelineList);
	  view->update();
    statusBar()->showMessage(tr("Open '%1'").arg(fileName), 2000);
}
void MainWindow::import()
{
	   QString fileName = QFileDialog::getOpenFileName(this,
	                        tr("Choose a file name"), "",
	                        tr("epo (*.epo)"));
	    if (fileName.isEmpty())
	        return;
	    QFile file(fileName);
	    if (!file.open(QIODevice::ReadOnly)) {
	        QMessageBox::warning(this, tr("Dock Widgets"),
	                             tr("Cannot write file %1:\n%2.")
	                             .arg(fileName)
	                             .arg(file.errorString()));
	        return;
	    }
		timelineList->clear();
		peopleList->clear();
		Tree->clear();
		decW->clear();
		decEdit=false;
	     QDataStream in(&file);
	     qint32 verzija;
	     in >> verzija; //verzija formata
	     double pocetak;
	     double rezmera;
		 in >> pocetak;
		 in >> rezmera;
		 NKJD pp(pocetak);
		 skala->SetPocetak(pp);
		 skala->SetRazmera(rezmera);
	     in >> decEdit;
	     int ins;
		 in >> ins;
		 kategorija->setCurrentIndex(ins);
		  view->import(in);
		  Doc.import(in);
		  Doc.UpdateTree(Tree,peopleList,timelineList);
		  view->update();
	    statusBar()->showMessage(tr("import '%1'").arg(fileName), 2000);
}
