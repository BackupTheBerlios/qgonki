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

#include <qapplication.h>
#include "qgonki.h"
#include <qtranslator.h>
#include <iostream>

#include "config.cpp"

//extern char DESTSHARE;

using namespace std;

int main( int argc, char ** argv ) {
    
	
    QApplication a( argc, argv );
    QTranslator translator(0);
    if (argc > 1)
    {
        if (strcmp(argv[1], "en") != 0)
	{
		translator.load(QString(DESTSHARE)+"/qgonki/translations/pl.qm", ".");	
   		a.installTranslator(&translator);
	}
	 
    }else
    {
    	translator.load(QString(DESTSHARE)+"/qgonki/translations/pl.qm", ".");	
   	a.installTranslator(&translator);
    }

    Qgonki * mw = new Qgonki();
    mw->setCaption( "Qgonki" );   

    
    mw->show();
    a.connect( &a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()) );
    return a.exec();
}
