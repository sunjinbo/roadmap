/*
* ============================================================================
*  Name        : roadmapdocument.h
*  Part of     : RoadMap
*  Description : 
*  Version     : 
*
*  Copyright © 2007 Nokia.  All rights reserved.
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

#ifndef C_CRMDOC_H
#define C_CRMDOC_H

// INCLUDES
#include <akndoc.h>

// FORWARD DECLARATIONS
class CRoadMapAppUi;
class CEikApplication;
class MBaseData;
class TCountryData;
class CCountryDataManager;


/**
 *  An instance of the Application View object for the RoadMap 
 *  example application
 *
 *  This View provided a user interface which including some controls;
 *  and also provided a OfferKeyEventL function in order to handles 
 *  key events of these controls
 *
 *  @since S60 v3.1
 */
class CRoadMapDocument : public CAknDocument
    {

public: // Constructors and destructor

    /**
     * Construct a CRoadMapDocument for the AVKON application aApp 
     * using two phase construction, 
     * and return a pointer to the created object
     * 
     * @since S60 v3.1
     * @param aApp application creating this document
     * @return a pointer to the created instance of CRoadMapDocument
     */
    static CRoadMapDocument* NewL( CEikApplication& aApp );

    /**
     * Construct a CRoadMapDocument for the AVKON application aApp 
     * using two phase construction, 
     * and return a pointer to the created object
     * 
     * @since S60 v3.1
     * @param aApp application creating this document
     * @return a pointer to the created instance of CRoadMapDocument
     */
    static CRoadMapDocument* NewLC( CEikApplication& aApp );

    /**
     * The Destructor Function of CRoadMapDocument class
     * Destroy the object and release all memory objects
     * 
     * @since S60 v3.1
     */
    ~CRoadMapDocument();
 
 public: // New functions
 
    /**
     * 
     * Add a TCountryData objct to the CCountryDataManager
     *
     * @since S60 v3.1
     * @param aCode a description specifies the code value
     * @param aName a description specifies the name value
     * @return the Add result(ETrue/EFalse)
     */
     TInt AddL( const TDesC& aCode, const TDesC& aName );

    /**
     * 
     * DeleteL a TCountryData object from CCountryDataManager
     *
     * @since S60 v3.1
     * @param aIndex the index indicate which item will be deleted
     * @return the Del result(ETrue/EFalse)
     */   
     TInt DeleteL( TInt aIndex );

    /**
     * 
     * Edit a TCountryData objct from the CCountryDataManager
     *
     * @since S60 v3.1
     * @param aIndex the index indicate which item will be modified
     * @param aCode a description specifies the code value
     * @param aName a description specifies the name value
     * @return the Edit result(ETrue/EFalse)
     */
    TInt EditL( 
        TInt aIndex, const TDesC& aCode, const TDesC& aName );
    
    /**
     * 
     * Find the position of an element within the array
     *
     * @since S60 v3.1
     * @param aCode a description specifies the code value
     * @return the position
     */    
    TInt Find( const TDesC& aCode ) const;
    
    /**
     * 
     * Is this data already exist?
     *
     * @since S60 v3.1
     * @param aMBaseData a TCountryData oject
     * @param aIndex just used in Edit mode for fixed bug
     * @return the position
     */      
    TInt IsExist( const TDesC& aData, TInt aIndex ) const;

    /**
     * 
     * Gets the numbers elements held in CCountryDataManager
     *
     * @since S60 v3.1
     * @return The number of array elements 
     */
    TInt Count() const;
    
    /**
     * 
     * Gets the Code by its index
     *
     * @since S60 v3.1
     * @param  aIndex the index indicate which item's code will be got
     * @return the code val
     */
    const TDesC& Code( TInt aIndex );
    
    /**
     * 
     * Gets the Name by its index
     *
     * @since S60 v3.1
     * @param aIndex the index indicate which item's name will be got
     * @return the name
     */
    const TDesC& Name( TInt aIndex );
    
    /**
     * From CAknDocument
     * Create a CRoadMapAppUi object and return a pointer to it
     * 
     * @since S60 v3.1
     * @param void
     * @return a pointer to the created instance of the AppUi created
     */
    CEikAppUi* CreateAppUiL();

private: // Constructors and destructor

    /**
     * The Constructor Function of CRoadMapDocument class
     * Perform the first phase of two phase construction 
     * 
     * @since S60 v3.1
     * @param aApp application creating this document
     */
    CRoadMapDocument( CEikApplication& aApp );

    /**
     * Perform the second phase construction of a doc object
     * 
     * @since S60 v3.1
     */
    void ConstructL();

private: // New functions
 
    /**
     * Get Country Data accroding to its Index
     *
     * @since S60 v3.1
     * @param aIndex 
     * @return a pointer of TCountryData object owned by doc
     */
    const TCountryData& CountryDataL( TInt aIndex ) const;
    
private: // Members
    
    /**
     * Use it to manage some country data
     * Own.
     */
    CCountryDataManager* iCountryDataManager;

    };

#endif // C_CRMDOC_H

// End of File
