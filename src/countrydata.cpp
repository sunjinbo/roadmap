/*
* ============================================================================
*  Name        : CountryDataL.cpp
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

// INCLUDES
#include "countrydata.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Default constructor of TCountryData CLASS
// ---------------------------------------------------------------------------
//
TCountryData::TCountryData() : iCode( KNullDesC ), iName( KNullDesC )
    {    
    }

// ---------------------------------------------------------------------------
// Ohter constructor of TCountryData CLASS
// ---------------------------------------------------------------------------
//
TCountryData::TCountryData( const TDesC& aCode, const TDesC& aName )
    : iCode( aCode ), iName( aName )
    {    
    }

// ---------------------------------------------------------------------------
// Overload TCountryData's operator ==
// ---------------------------------------------------------------------------
//
TBool TCountryData::operator == ( const TCountryData& aData ) const
    {
    TBool result( EFalse );
    if( iCode == aData.iCode )
        {
        result = ETrue;
        }
    return result;
    }

// ---------------------------------------------------------------------------
// Get member data from field Id
// ---------------------------------------------------------------------------
//
const TDes& TCountryData::Field( TFieldType aType ) const
    {
    switch ( aType )
        {
        
        case EBufCode:
            return iCode;
            
        case EBufName:
            return iName;

        default:
            return (TDes&)KNullDesC;

        }
    }

// ---------------------------------------------------------------------------
// Internalizes the data type from a stream
// ---------------------------------------------------------------------------
//
void TCountryData::InternalizeL( RReadStream& aRStream )
    {
    aRStream >> iCode;
    aRStream >> iName;   
    }

// ---------------------------------------------------------------------------
// Externalizes the data type to a stream
// ---------------------------------------------------------------------------
//
void TCountryData::ExternalizeL( RWriteStream& aWStream ) const
    {
    aWStream << iCode;
    aWStream << iName;
    }

// End of File
