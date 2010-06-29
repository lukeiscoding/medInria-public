/* medDatabaseNonPersitentItem.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Sun Jun 27 18:41:16 2010 (+0200)
 * Version: $Id$
 * Last-Updated: Tue Jun 29 16:09:12 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 8
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef MEDDATABASENONPERSITENTITEM_H
#define MEDDATABASENONPERSITENTITEM_H

#include "medSqlExport.h"

#include <medCore/medDataIndex.h>

#include <QtCore/QObject>
#include <QtCore/QList>

class dtkAbstractData;

class medDatabaseNonPersitentItemPrivate;

class medDatabaseNonPersitentItem : public QObject
{
    Q_OBJECT

public:
     medDatabaseNonPersitentItem(void);
    ~medDatabaseNonPersitentItem(void);

    const QString& name(void) const;
    const QString& studyName(void) const;
    const QString& file(void) const;
    const QImage& thumb(void) const;

    const medDataIndex& index(void) const;
    
    dtkAbstractData *data(void);

private:
    friend class medDatabaseNonPersitentController;
    friend class medDatabaseNonPersitentReader;

private:
    medDatabaseNonPersitentItemPrivate *d;
};

#endif
