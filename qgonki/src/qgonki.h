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

#ifndef QGONKI_H
#define QGONKI_H

#include <iostream>

using namespace std;

#include <qmainwindow.h>
#include <qlistbox.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qmultilineedit.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qlabel.h>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qapplication.h>
#include <qaccel.h>
#include <qwhatsthis.h>
#include <qlayout.h>
#include <qframe.h>
#include <qsplitter.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qaction.h>
#include <qstringlist.h>
#include <qfile.h>
#include <qcombobox.h>
#include <qlistview.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>


class QTextEdit;

class Qgonki: public QMainWindow
{
    Q_OBJECT

public:
    Qgonki();
    ~Qgonki();
    QListBox *from_l, *to_l;
    void change_dir(const QString &newdir);
    QString directory, home_dir;

private slots:

    void about();
    void aboutQt();
    void dir_click(QListViewItem* item);
    void del_pressed();
    void do_convert();
    void change_dir();

private:

    QPopupMenu *actions, *from, *to, *help; 
    QVBoxLayout *box, *sm2, *sm3; 
    QHBoxLayout *box2, *sm1;
    QComboBox *l1, *l2;
    QListBox *list; 
    QListView *files;
    QFrame *frame, *fr1, *fr2, *fr3;
    QLineEdit *line;
    QPushButton *set;
    QHBoxLayout *horiz;
    QStatusBar *status;
    QPixmap *folder, *file, *convert, *exit, *folder_locked;
    QToolBar *toolbar1;
    QToolButton *tool1, *tool2;
    
};

//ikonki :)
#include "artwork/convert.xpm" 
#include "artwork/exit.xpm" 


static const char* folder_open_xpm[]={
    "16 16 11 1",
    "# c #000000",
    "g c #c0c0c0",
    "e c #303030",
    "a c #ffa858",
    "b c #808080",
    "d c #a0a0a4",
    "f c #585858",
    "c c #ffdca8",
    "h c #dcdcdc",
    "i c #ffffff",
    ". c None",
    "....###.........",
    "....#ab##.......",
    "....#acab####...",
    "###.#acccccca#..",
    "#ddefaaaccccca#.",
    "#bdddbaaaacccab#",
    ".eddddbbaaaacab#",
    ".#bddggdbbaaaab#",
    "..edgdggggbbaab#",
    "..#bgggghghdaab#",
    "...ebhggghicfab#",
    "....#edhhiiidab#",
    "......#egiiicfb#",
    "........#egiibb#",
    "..........#egib#",
    "............#ee#"};

static const char * folder_locked_xpm[]={
    "16 16 10 1",
    "h c #808080",
    "b c #ffa858",
    "f c #c0c0c0",
    "e c #c05800",
    "# c #000000",
    "c c #ffdca8",
    ". c None",
    "a c #585858",
    "g c #a0a0a4",
    "d c #ffffff",
    "..#a#...........",
    ".#abc####.......",
    ".#daa#eee#......",
    ".#ddf#e##b#.....",
    ".#dfd#e#bcb##...",
    ".#fdccc#daaab#..",
    ".#dfbbbccgfg#ba.",
    ".#ffb#ebbfgg#ba.",
    ".#ffbbe#bggg#ba.",
    ".#fffbbebggg#ba.",
    ".##hf#ebbggg#ba.",
    "...###e#gggg#ba.",
    ".....#e#gggg#ba.",
    "......###ggg#b##",
    ".........##g#b##",
    "...........####."};

static const char * pix_file []={
    "16 16 7 1",
    "# c #000000",
    "b c #ffffff",
    "e c #000000",
    "d c #404000",
    "c c #c0c000",
    "a c #ffffc0",
    ". c None",
    "................",
    ".........#......",
    "......#.#a##....",
    ".....#b#bbba##..",
    "....#b#bbbabbb#.",
    "...#b#bba##bb#..",
    "..#b#abb#bb##...",
    ".#a#aab#bbbab##.",
    "#a#aaa#bcbbbbbb#",
    "#ccdc#bcbbcbbb#.",
    ".##c#bcbbcabb#..",
    "...#acbacbbbe...",
    "..#aaaacaba#....",
    "...##aaaaa#.....",
    ".....##aa#......",
    ".......##......."};



#endif

//string dzokej = "nanana";
