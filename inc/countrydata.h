/*
* ============================================================================
*  Name        : CountryDataL.h
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

#ifndef T_TCOUNTRYDATA_H
#define T_TCOUNTRYDATA_H

// INCLUDES
#include <s32std.h>

#include "basedata.h"
#include "roadmap.hrh"


/**
 *  
 *  Storage Country Data, Inherit from Class MBaseData
 *  
 *  @since S60 v3.1
 */
class TCountryData : public MBaseData
    {

public: // Constructors and destructor

    /**
     * Default constructor of TCountryData CLASS
     *
     * @since S60 v3.1
     */
    TCountryData();

    /**
     * Other constructor of TCountryData CLASS
     *
     * @since S60 v3.1
     * @param aCode a description specifies the code value
     * @param aName a description specifies the code value
     */
    TCountryData( const TDesC& aCode, const TDesC& aName );

public: // New functions

    /**
     * 
     * Overload TCountryData's operator ==
     *
     * @since S60 v3.1
     * @param aData the ref of a TCountryData object
     * @return the compare result
     */
    TBool operator == ( const TCountryData& aData ) const;

public: // From base class MBaseData
    
    /**
     * From base class MBaseData
     * Get member data from field Id
     *
     * @since S60 v3.1
     * @param the field Id
     * @return the member data
     */
    virtual const TDes& Field( TFieldType aType ) const;

    /**
     * From base class MBaseData
     * Internalizes the data type from a stream
     *
     * @since S60 v3.1
     * @param the read stream ref
     */
    virtual void InternalizeL( RReadStream& aRStream );
    
    /**
     * From base class MBaseData
     * Externalizes the data type to a stream
     *
     * @since S60 v3.1
     * @param the write stream ref
     */
    virtual void ExternalizeL( RWriteStream& aWStream ) const;

private: // Members

    /**
     * Save a code value and its chars'number no more than 5
     */
    TBuf<ECodeMaxChars> iCode;

    /**
     * Save a name value and its chars'number no more than 20
     */
    TBuf<ENameMaxChars> iName;

    };

#endif // T_TCOUNTRYDATA_H

// End of File
