/****************************************************************************
** Qgonki meta object code from reading C++ file 'qgonki.h'
**
** Created: Wed Jul 14 19:26:48 2004
**      by: The Qt MOC ($Id: moc_qgonki.cpp,v 1.1 2004/07/31 09:02:54 vrok Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "qgonki.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Qgonki::className() const
{
    return "Qgonki";
}

QMetaObject *Qgonki::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Qgonki( "Qgonki", &Qgonki::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Qgonki::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Qgonki", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Qgonki::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Qgonki", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Qgonki::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"about", 0, 0 };
    static const QUMethod slot_1 = {"aboutQt", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ "item", &static_QUType_ptr, "QListViewItem", QUParameter::In }
    };
    static const QUMethod slot_2 = {"dir_click", 1, param_slot_2 };
    static const QUMethod slot_3 = {"del_pressed", 0, 0 };
    static const QUMethod slot_4 = {"do_convert", 0, 0 };
    static const QUMethod slot_5 = {"change_dir", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "about()", &slot_0, QMetaData::Private },
	{ "aboutQt()", &slot_1, QMetaData::Private },
	{ "dir_click(QListViewItem*)", &slot_2, QMetaData::Private },
	{ "del_pressed()", &slot_3, QMetaData::Private },
	{ "do_convert()", &slot_4, QMetaData::Private },
	{ "change_dir()", &slot_5, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"Qgonki", parentObject,
	slot_tbl, 6,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Qgonki.setMetaObject( metaObj );
    return metaObj;
}

void* Qgonki::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Qgonki" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool Qgonki::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: about(); break;
    case 1: aboutQt(); break;
    case 2: dir_click((QListViewItem*)static_QUType_ptr.get(_o+1)); break;
    case 3: del_pressed(); break;
    case 4: do_convert(); break;
    case 5: change_dir(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool Qgonki::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Qgonki::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool Qgonki::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
