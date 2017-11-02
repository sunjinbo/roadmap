/*
* ============================================================================
*  Name        : CountryDataManager.h
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

#ifndef C_CCOUNTRYDATAMGR_H
#define C_CCOUNTRYDATAMGR_H

// INCLUDES
#include <barsc.h>
#include <barsread.h>
#include <s32file.h>

#include "basedatamanager.h"
#include "countrydata.h"


/**
 *  
 *  Manage and Storage a set of country data
 *  
 *  @since S60 v3.1
 */
class CCountryDataManager : public CBase, public MBaseDataManager
    {

    /**
     * defines the data format type
     */  
    enum TFormatType
        {
        EFormatDigit = -1,
        EFormatAlpha
        };

public: // Constructors and destructor
    
    /**
     * Construct a CContDocument for the AVKON application aApp
     * using two phase construction, and return a pointer to 
     * the created object
     *
     * @since S60 v3.1
     * @return a pointer to the created instance of CCountryDataManager
     */
    static CCountryDataManager* NewL();

    /**
     * Construct a CContDocument for the AVKON application aApp
     * using two phase construction, and return a pointer to 
     * the created object
     *
     * @since S60 v3.1
     * @return a pointer to the created instance of CCountryDataManager
     */
    static CCountryDataManager* NewLC();

    /**
     * Destroy the object and release all memory objects
     * Destructor is always virtual
     *
     * @since S60 v3.1
     */
    virtual ~CCountryDataManager();

public: // New functions
    
    /**
     * Get Country Data form its Index
     *
     * @since S60 v3.1
     * @param aIndex 
     * @return 
     */
    const TCountryData& CountryDataL( TInt aIndex ) const;
    
public: // From base class MBaseDataManager

    /**
     * Form MBaseDataManager
     * Add a TCountryData objct to the manager
     *
     * @since S60 v3.1
     * @param aMBaseData the pointer of a new TCountryData oject
     * @return the Add result(ETrue/EFalse)
     */
    virtual TInt AddL( const MBaseData& aData );

    /**
     * Form MBaseDataManager
     * DeleteL a TCountryData object from array
     *
     * @since S60 v3.1
     * @param aIndex the index indicate which item will be deleted
     * @return the Del result(ETrue/EFalse)
     */   
    virtual TInt DeleteL( TInt aIndex );

    /**
     * Form MBaseDataManager
     * Edit a TCountryData objct from the manager
     *
     * @since S60 v3.1
     * @param aIndex the index indicate which item will be modified
     * @param aMBaseData the pointer of a new TCountryData oject
     * @return the Edit result(ETrue/EFalse)
     */
    virtual TInt EditL( TInt aIndex, const MBaseData& aData );

    /**
     * Form MBaseDataManager
     * Find the position of an element within the array
     *
     * @since S60 v3.1
     * @param aMBaseData the pointer of a TCountryData oject
     * @return the position
     */    
    virtual TInt Find( const MBaseData& aData ) const;

    /**
     * Form MBaseDataManager
     * Is this data already exist?
     *
     * @since S60 v3.1
     * @param aMBaseData a TCountryData oject
     * @param aIndex just used in Edit mode for fixed bug
     * @return the position
     */    
    virtual TInt IsExist
        ( const MBaseData& aData, TInt aIndex ) const;

    /**
     * Form MBaseDataManager
     * Gets the number of TCountryData elements held in this manager
     *
     * @since S60 v3.1
     * @return The number of array elements 
     */
    virtual TInt Count() const;

private: // Constructors and destructor

    /**
     * Constructor
     *
     * @since S60 v3.1
     */
    CCountryDataManager();
 
     /**
     * initialize phases 2
     *
     * @since S60 v3.1
     * @param aButtonId the menu button Id
     * @return the processing result
     */    
    void ConstructL();

private: // New functions

    /**
     * Get data from outside storage medium
     *
     * @since S60 v3.1
     */
    void RestoreL();

    /**
     * Save data to outside storage medium
     *
     * @since S60 v3.1
     */
    void StoreL();

    /**
     * Create default file assume that original file is lost or destroyed
     *
     * @since S60 v3.1
     */    
    void CreateDefaultFileL();

    /**
     * Check data format is reasonable or not
     *
     * @since S60 v3.1
     */
    TInt CheckDataFormat( const TFormatType& aFormat, const TDes& aData );

private: // Members

    /**
     * Make use of it to storage some TCountryData objects
     * Own.
     */    
    RArray<TCountryData> iCountryDataList;

   /**
     * A ref to the file server session of framework
     * Not own.
     */    
    RFs& iFs;

    };

#endif // C_CCOUNTRYDATAMGR_H

// End of File
