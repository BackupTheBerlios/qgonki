/***************************************************************************
 *   Copyright (C) 2004 by Marcin Wrochniak                                *
 *   vrok@intersec.pl                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "qgonki.h"
#include <iostream>

using namespace std;

char *conversions[] 
 = {
 "Mazovia",      
 "ISO-Latin-2", 
 "CSK",         
 "Cyfromat",    
 "DHN",        
 "IINTE-ISIS",  
 "IBM-Latin-2",
 "IEA-Swierk",  
 "Logic",      
 "Microvex",    
 "Windows-EE",  
 "Ventura",    
 "ELWRO-Junior",
 "AmigaPL",
 "TeX.W-wa.1",
 "TeX.W-wa.2",
 "TeX-ohida",
 "UTF-8",
 "tyldy",
 "brak" 
 };

//#include "filesave.xpm"
//#include "fileopen.xpm"
//#include "fileprint.xpm"

Qgonki::Qgonki()
    : QMainWindow( 0, "Qgonki", WDestructiveClose )
{
	folder = new QPixmap(folder_open_xpm);
	folder_locked = new QPixmap(folder_locked_xpm);
	file = new QPixmap(pix_file);
	convert = new QPixmap(convert_xpm);	
	exit = new QPixmap(exit_xpm);
	//folder_open = new QPixmap(fol
	
	setGeometry(100, 100, 560, 400);
	
	status = statusBar();
	status->message(tr("Ready."));
	//<menu>
	actions = new QPopupMenu(this);
	actions->setCheckable(true);
	
	//actions->insertItem("Konwertuj", this, SLOT(do_convert()));
	
	
	actions->insertItem(tr("Convert"), this, SLOT(do_convert()));
	actions->insertItem(tr("Exit"), qApp, SLOT(quit()));
	//from_mazovia_id = actions->insertItem("Konwertuj", this, SLOT(do_convert()));	
	//from_mazovia_id = actions->insertItem("Koniec", this, SLOT(from_mazovia()));
	menuBar()->insertItem(tr("File"), actions);
	
	help = new QPopupMenu(this);
	help->insertItem(tr("About"), this, SLOT(about()));
	help->insertItem(tr("About Qt"), this, SLOT(aboutQt()));
	menuBar()->insertItem(tr("Help"), help);
	//</menu>
	
	toolbar1 = new QToolBar(this);
	tool1 = new QToolButton(*convert, tr("Convert"), tr("Convert selected files"), this, SLOT(do_convert()), toolbar1);
	tool2 = new QToolButton(*exit, tr("Koniec"), tr("Exit Qgonki"), qApp, SLOT(quit()), toolbar1);	
	
	//QVBoxLayout *box; 
	frame = new QFrame(this);
	setCentralWidget(frame);
	
	box = new QVBoxLayout(frame);
		
	QSplitter *splitter = new QSplitter(frame);
	splitter->setOrientation(Vertical);

	
	//<RAMKA PIERWSZA>
	fr1 = new QFrame(frame);  //ramka pierwsza
	sm1 = new QHBoxLayout(fr1);  //rozciągarka splittera
	//fr1->addLayout(sm1);
	QSplitter *split = new QSplitter(fr1);  //splitter
	sm1->addWidget(split);	    //dodtajemy splitter do hboxa
	l1 = new QComboBox(split);  //listbox pierwszy
	l2 = new QComboBox(split);  //listbox drugi	
	//fr1->setMaximumHeight(l1->height());
	
	box->addWidget(fr1);
	box->addWidget(splitter);
	
	for (int i = 0; i < 20; i++)
	{
	  l1->insertItem(conversions[i]);
	  l2->insertItem(conversions[i]);
	}
	//</RAMKA PIERWSZA>
		
	//<RAMKA DRUGA>
	fr2 = new QFrame(splitter);
	sm2 = new QVBoxLayout(fr2);
	QLabel *lab1 = new QLabel(tr("Files to convert:"), fr2);
	list = new QListBox(fr2);
	sm2->addWidget(lab1);
	sm2->addWidget(list);	
	//</RAMKA DRUGA>
	
	//<RAMKA TRZECIA>
	fr3 = new QFrame(splitter);
	sm3 = new QVBoxLayout(fr3);
	QLabel *lab2 = new QLabel(tr("Files:"), fr3);
	files = new QListView(fr3, "Files");
	files->addColumn(tr("File name"));
	files->addColumn(tr("Type"));
	//tralala
	
	//files->hideColumn(1);
	//files->hideColumn(0);
	files->setSorting(1, true);
	files->setAllColumnsShowFocus(true);
	//files->setColumnWidthMode(0, QListView::Maximum);
	files->setResizeMode(QListView::AllColumns);
 	//files->setColumnWidth(0, );
	// files->setSelectionMode(QListView::Extended); <- do tego jeszcze nie doszlismy...
	
	sm3->addWidget(lab2);
	sm3->addWidget(files);	
	
	horiz = new QHBoxLayout();
	sm3->addLayout(horiz);
	line = new QLineEdit(fr3);
	connect(line, SIGNAL(returnPressed()), this, SLOT(change_dir()));
	horiz->addWidget(line);
	set = new QPushButton(tr("Change"), fr3);
	connect(set, SIGNAL(clicked()), this, SLOT(change_dir())); 
	//set->setMinimumSize(50, 50);
	set->setMinimumWidth(40);
	//set->setWidth(40);
	//set->setHeight(30);
	set->setMaximumWidth(80);
	horiz->addWidget(set);
	//</RAMKA TRZECIA>
	

	
	char *tmp_home = getenv("HOME");
	if (tmp_home != NULL)
	{
		directory = tmp_home;
		home_dir = QString(tmp_home)+"/";
	}else
	{
		directory = "/";
		home_dir = "/tmp/";
	} 

	//directory = "/home/vrok/";
	change_dir(directory);
	
	connect(files, SIGNAL(doubleClicked(QListViewItem*)), this, SLOT(dir_click(QListViewItem *)));
	connect(files, SIGNAL(returnPressed(QListViewItem*)), this, SLOT(dir_click(QListViewItem *)));
	
	
	QAction *fileOpenAction = new QAction(QString("Press delete"), "ah",Key_Delete, files); //control "Del" key events
	connect(fileOpenAction, SIGNAL(activated()), this, SLOT(del_pressed()));
	//fileOpenAction->addTo(files);
	
	//QAction *afileOpenAction = new QAction("&Open...", Key_Delete, files);
	//connect(afileOpenAction, SIGNAL(activated()), line, SLOT(clear()));
	//afileOpenAction->addTo(l2);	
}

void Qgonki::del_pressed()
{
 if (list->hasFocus())
 {
   list->removeItem(list->currentItem());
 }
}

void Qgonki::dir_click(QListViewItem * item)
{
 QString tmp, path;
// tmp = &item->text();
 path = item->text(0);
 //path.remove(0, 5);
 QFileInfo info(directory+path);
 
 if (path == ".")
 	return;
 if ((path == "..") && (directory == "/"))
 	return;
 if (path == "..")
 {
 	//QString tmp;
	tmp = directory;
	int tmp1 = tmp.findRev("/", tmp.length()-2);
	tmp.remove(tmp1+1, tmp.length()-tmp1-1);
 }else
 if (info.isFile())
 {
       list->insertItem(*file, directory+path);
       return;
 }else
 	tmp = directory+path + "/";
 
 if (info.isExecutable())	
 	change_dir(tmp);
}

void Qgonki::change_dir()
{
	QDir dir(line->text());
	if (! dir.exists())
		return;
		
	//if (line->text()[line->text().length()-1] != '/')
	//{
	//	line->setText(line->text()+"/");
	//}
	
	change_dir(line->text());	
}

void Qgonki::change_dir(const QString &newdir)
{
	QDir dirr(newdir);
	QString inewdir = newdir;
	
	if (newdir[newdir.length()-1] != '/')
	{
		inewdir = (newdir+ "/");
	}
		
	QFileInfo *finfo = new QFileInfo();
	
	directory = inewdir;
	files->clear();
	for (unsigned i=0; i < dirr.count(); i++)
	{
	        finfo->setFile(directory+dirr[i]);
		if (finfo->isDir())
		{
			QListViewItem *aaa = new QListViewItem(files, dirr[i], "DIR");
			if (finfo->isReadable())
			{
				aaa->setPixmap(0, *folder);
			} else
			{
				aaa->setPixmap(0, *folder_locked);
			}
		// files->insertItem("DIR  "+dirr[i]);
		}else
		{
			QListViewItem *aaa = new QListViewItem(files, dirr[i], "FILE");
			aaa->setPixmap(0, *file);
		} 
		 //files->insertItem("FILE "+dirr[i]);
	}
	line->setText(inewdir);
	files->sort();
}

Qgonki::~Qgonki()
{
    //delete printer;
}

void Qgonki::do_convert()
{
 /* QFile *f;    
		f = new QFile("/home/vrok/yeyeye.txt");
		f->open(IO_WriteOnly);
f->writeBlock("aaaa", sizeof("aaaa"));
		//	f->writeBlock(readbuf, sizeof(readbuf));
			f->close();*/
     	FILE *pipein_fp;
	char readbuf;

	// Potokujemy pwbuildera
	QString cmd ("plconv "+QString(conversions[l1->currentItem()])+":"+QString(conversions[l2->currentItem()]));
	QString pwget;
	for (unsigned i = 0; i < list->count(); i++)
	{
		pwget = list->item(i)->text();
		pwget.replace(" ", "\\ ");
		
		status->message(tr("Conversing ")+QString::number(i+1)+tr(" of ")+QString::number(list->count()));
		
		if (( pipein_fp = popen("cat "+pwget+" | "+cmd+" > "+home_dir+".qgonki_tmp", "r")) == NULL)
		{
		
	    	    perror(tr("Error with popen() !!"));
		    status->message(tr("Error with popen() !!"));
//	 		       exit(1);
		}
		//f = new QFile(list->item(i)->text());
		//f->open(IO_ReadWrite);
			
		
		
		do
		{
			readbuf = fgetc(pipein_fp);
		}while (readbuf != EOF); 
		
		    	
		pclose(pipein_fp);
		
		system("cp "+home_dir+".qgonki_tmp "+pwget);
		
		//f->close();
		//delete f;
	}
	status->message(QString::number(list->count())+tr(" files converted. Ready."));
	//delete f; 

	//m->ml->append("\n<b>Work done!!</b>");
}


void Qgonki::about()
{

    QMessageBox::about( this, tr("Qgonki\n\n"),
			tr("Autor: Marcin Wrochniak\n"
			"Zawiera kod plconv autorstwa Jaroslawa Strzalkowskiego i Wojtka Bogusza\n"
			"Program na licencji GPL"));
}

void Qgonki::aboutQt()
{
    QMessageBox::aboutQt( this, tr("Qgonki") );
}

