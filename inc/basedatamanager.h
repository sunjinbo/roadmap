/*
* ============================================================================
*  Name        : basedatamanager.h
*  Part of     : RoadMap
*  Interface   : 
*  Description : 
*  Version     : 
*
*  Copyright 2007 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* 
*/

#ifndef M_MBASEDATAMGR_H
#define M_MBASEDATAMGR_H

// INCLUDES
#include <e32cmn.h>
#include <e32base.h>
#include <badesca.h>
#include <s32std.h>

#include "basedata.h"


/**
 *  
 *  A interface only, all the data manager class which can be dirived from it
 *  
 *  @since S60 v3.1
 */
class MBaseDataManager
    {

public: // New functions

    /**
     * 
     * Add a MBaseData objct to the manager
     *
     * @since S60 v3.1
     * @param aData the MBaseData objct which will be added
     * @return the processing result
     */
    virtual TInt AddL( const MBaseData& aData ) = 0;

    /**
     * 
     * DeleteL a MBaseData objct from the manager
     *
     * @since S60 v3.1
     * @param aIndex the INDEX in which will be deleted
     * @return the processing result
     */
    virtual TInt DeleteL( TInt aIndex ) = 0;
      
    /**
     * 
     * Edit a MBaseData objct from the manager
     *
     * @since S60 v3.1
     * @param aData the MBaseData objct which will be edited
     * @return the processing result
     */    
    virtual TInt EditL
        ( TInt aIndex, const MBaseData& aData ) = 0;

    /**
     * 
     * Find a MBaseData object from the manager
     *
     * @since S60 v3.1
     * @param aData the MBaseData objct which will be found
     * @return the processing result
     */
    virtual TInt Find( const MBaseData& aMBaseData ) const = 0;

    /**
     * 
     * Is this data already exist?
     *
     * @since S60 v3.1
     * @param aMBaseData the pointer of a TCountryData oject
     * @return the position
     */    
    virtual TInt IsExist
        ( const MBaseData& aData, TInt aIndex ) const = 0;

    /**
     * 
     * How many MBaseData object in this manager?
     *
     * @since S60 v3.1
     * @return the result
     */
    virtual TInt Count() const = 0;

    };

#endif // M_MBASEDATAMGR_H

// End of File
