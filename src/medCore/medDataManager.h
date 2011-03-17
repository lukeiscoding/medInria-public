/* medDataManager.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Mon Dec 21 08:34:45 2009 (+0100)
 * Version: $Id$
 * Last-Updated: Wed Mar 17 18:25:19 2010 (+0100)
 *           By: Julien Wintz
 *     Update #: 5
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef MEDDATAMANAGER_H
#define MEDDATAMANAGER_H

#include <QtCore/QObject>

#include "medCoreExport.h"
#include "medDataIndex.h"

class dtkAbstractData;
class dtkAbstractDataFactory;

class medDataManagerPrivate;

/**
 * This class is the global access point to data stored in the database. 
 * It tries to use several database-controllers to provide/store data
 * Another role is to cache data to provide faster access (work in progress)
 */
class MEDCORE_EXPORT medDataManager : public QObject
{
    Q_OBJECT

public:
    static medDataManager *instance(void);

    /*
        void insert(const medDataIndex& index, dtkAbstractData *data);
        void remove(const medDataIndex& index);
    */

    /**
    * Ask the data-manager to provide the data belonging to this index using it's registered controllers
    * @params const medDataIndex & index medDataIndex for data
    * @return dtkAbstractData * the data
    */
    dtkAbstractData* data(const medDataIndex& index);

    /**
    * Use this function to insert data into the database,
    * Do *not* use the concrete database controller implementation for it
    * The data-manager will take over this task
    * @params const dtkAbstractData & data
    * @return medDataIndex
    */
    medDataIndex import(dtkAbstractData *data);

    /**
    * Use this function to insert data into the non-persistent database,
    * Do *not* use the concrete database controller implementation for it
    * The data-manager will take over this task
    * @params const dtkAbstractData & data
    * @return medDataIndex
    */
    medDataIndex importNonPersistent(dtkAbstractData *data);

    /**
    * Use this functions to save all non-persistent data to the sql database.
    * The list of non-persistent data will then be cleared, and any subsequent
    * access to those data will trigger a reading from the database.
    */
    void storeNonPersistentDataToDatabase (void);

    /**
    * Returns the number of non-persistent data contained in the data manager
    */
    int nonPersistentDataCount (void) const;

    /**
    * Clear the list of non-persistent data
    */
    void clearNonPersistentData (void);

    /*
        QList<dtkAbstractData *> dataForPatient(int id);
        QList<dtkAbstractData *> dataForStudy  (int id);
        QList<dtkAbstractData *> dataForSeries (int id);
        QList<dtkAbstractData *> dataForImage  (int id);
    */

signals:
    /**
    * This signal is emitted whenever a data was added in either the persistent
    * or non persistent database by calling import() or importNonPersistentData().
    */
    void dataAdded (const medDataIndex&);
      
protected:
     medDataManager(void);
    ~medDataManager(void);

protected:
    static medDataManager *s_instance;

private:
    medDataManagerPrivate *d;
};

#endif // MEDDATAMANAGER_H
