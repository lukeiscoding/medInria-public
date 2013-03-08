#include "itkFiltersShrinkProcess.h"

#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractDataFactory.h>
#include <dtkCore/dtkSmartPointer.h>

#include <medMetaDataKeys.h>

#include "itkFiltersShrinkProcess_p.h"

//-------------------------------------------------------------------------------------------

itkFiltersShrinkProcess::itkFiltersShrinkProcess(itkFiltersShrinkProcess *parent) 
    : itkFiltersProcessBase(*new itkFiltersShrinkProcessPrivate(this), parent)
{
    DTK_D(itkFiltersShrinkProcess);
    
    d->filter = this;
    d->input = NULL;
    d->output = NULL;
    
    d->shrinkFactors[0] = 1;
    d->shrinkFactors[1] = 1;
    d->shrinkFactors[2] = 1;
}


itkFiltersShrinkProcess::itkFiltersShrinkProcess(const itkFiltersShrinkProcess& other) 
    : itkFiltersProcessBase(*new itkFiltersShrinkProcessPrivate(*other.d_func()), other)
{
}

itkFiltersShrinkProcess& itkFiltersShrinkProcess::operator = (const itkFiltersShrinkProcess& other)
{
    itkFiltersProcessBase::operator=(other);

    DTK_D(itkFiltersShrinkProcess);
    d->callback = other.d_func()->callback;
    d->filter = other.d_func()->filter;
    d->input = other.d_func()->input;
    d->output = other.d_func()->output;
    
    d->shrinkFactors[0] = other.d_func()->shrinkFactors[0];
    d->shrinkFactors[1] = other.d_func()->shrinkFactors[1];
    d->shrinkFactors[2] = other.d_func()->shrinkFactors[2];

    return *this;
}

//-------------------------------------------------------------------------------------------

itkFiltersShrinkProcess::~itkFiltersShrinkProcess( void )
{
}

//-------------------------------------------------------------------------------------------

bool itkFiltersShrinkProcess::registered( void )
{
    return dtkAbstractProcessFactory::instance()->registerProcessType("itkShrinkProcess", createitkFiltersShrinkProcess);
}

//-------------------------------------------------------------------------------------------

QString itkFiltersShrinkProcess::description() const
{
    return tr("ITK shrink filter");
}

//-------------------------------------------------------------------------------------------

void itkFiltersShrinkProcess::setInput(dtkAbstractData *data)
{
    if (!data)
        return;
    
    QString identifier = data->identifier();
    
    DTK_D(itkFiltersShrinkProcess);
    
    d->output = dtkAbstractDataFactory::instance()->createSmartPointer(identifier);
    d->input = data;
}

//-------------------------------------------------------------------------------------------

void itkFiltersShrinkProcess::setParameter(double data, int channel)
{   
    DTK_D(itkFiltersShrinkProcess);
    
    if (channel > 2)
        return;
    
    switch ( channel )
    {
    case 0:
        d->shrinkFactors[0] = ( unsigned int ) data;
        break;
    case 1:
        d->shrinkFactors[1] = ( unsigned int ) data;
        break;
    case 2:
        d->shrinkFactors[2] = ( unsigned int ) data;
        break;
    }
}

//-------------------------------------------------------------------------------------------

int itkFiltersShrinkProcess::update ( void )
{
    DTK_D(itkFiltersShrinkProcess);
    
    if ( !d->input )
        return -1;

    QString id = d->input->identifier();

    if ( id == "itkDataImageChar3" )
    {
        d->update<char>();
    }
    else if ( id == "itkDataImageUChar3" )
    {
        d->update<unsigned char>();
    }
    else if ( id == "itkDataImageShort3" )
    {
        d->update<short>();
    }
    else if ( id == "itkDataImageUShort3" )
    {
        d->update<unsigned short>();
    }
    else if ( id == "itkDataImageInt3" )
    {
        d->update<int>();
    }
    else if ( id == "itkDataImageUInt3" )
    {
        d->update<unsigned int>();
    }
    else if ( id == "itkDataImageLong3" )
    {
        d->update<long>();
    }
    else if ( id== "itkDataImageULong3" )
    {
        d->update<unsigned long>();
    }
    else if ( id == "itkDataImageFloat3" )
    {
        d->update<float>();
    }
    else if ( id == "itkDataImageDouble3" )
    {
        d->update<double>();
    }
    else
    {
        qDebug() << "Error : pixel type not yet implemented ("
        << id
        << ")";
        return -1;
    }

    return EXIT_SUCCESS;
}

//-------------------------------------------------------------------------------------------


dtkAbstractData * itkFiltersShrinkProcess::output ( void )
{
    DTK_D(itkFiltersShrinkProcess);
    
    return ( d->output );
}

// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractProcess * createitkFiltersShrinkProcess ( void )
{
    return new itkFiltersShrinkProcess;
}
