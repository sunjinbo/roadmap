/*
* ============================================================================
*  Name        : CountryDataManager.cpp
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
#include <s32std.h>
#include <e32err.h>
#include <stringloader.h>
#include <roadmap.rsg>

#include "basedatamanager.h"
#include "countrydata.h"
#include "countrydatamanager.h"
#include "roadmap.hrh"

// CONSTANTS
const TInt KDataMatchFailture( -1 );
const TInt KDataMatchSuccess( 0 );
// Specifies a empty file size
const TInt KEmptyFileSize( 0 );
// Specifies how many items in the default data file
const TUint32 KDefaultItemNum( 20 );
// Literal constant for generating default country code
_LIT( KCountryCode, "%d" );
// Literal constant for generating default country name
_LIT( KCountryName, "CountryName - %d" );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Creates a CCountryDataManager object
// ---------------------------------------------------------------------------
//
CCountryDataManager* CCountryDataManager::NewL()
    {
    CCountryDataManager* self = CCountryDataManager::NewLC();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Creates a CCountryDataManager object 
// And puts a pointer to it onto the cleanup stack
// ---------------------------------------------------------------------------
//
CCountryDataManager* CCountryDataManager::NewLC()
    {
    CCountryDataManager* self = new ( ELeave ) CCountryDataManager;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor - closes the array and frees all memory allocated to the array
// ---------------------------------------------------------------------------
//
CCountryDataManager::~CCountryDataManager()
    {
    iCountryDataList.Close();
    }

// ---------------------------------------------------------------------------
// Get Country Data form its Index
// ---------------------------------------------------------------------------
//
const TCountryData& CCountryDataManager::CountryDataL( TInt aIndex ) const
    {
    if ( aIndex < EInvaildIndex || aIndex >= iCountryDataList.Count() )
        {
        User::Leave( KErrArgument );
        }
    return iCountryDataList[aIndex];
    }

// ---------------------------------------------------------------------------
// Add a TCountryData objct to the RArray
// ---------------------------------------------------------------------------
//
TInt CCountryDataManager::AddL( const MBaseData& aData )
    {
    TInt result( KErrNone );
    // adds this TCountryData object to TCountryData List
    TCountryData data( aData.Field( MBaseData::EBufCode ), 
                       aData.Field( MBaseData::EBufName ) );
 
    result = CheckDataFormat
        ( EFormatDigit, data.Field( MBaseData::EBufCode ) );
    if ( result == KErrNone )
        {
        result = CheckDataFormat
            ( EFormatAlpha, data.Field( MBaseData::EBufName ) );
        if ( result == KErrNone )
            {
            // adds data to list
            iCountryDataList.AppendL( data );
            // save data to file
            StoreL();
            }
        }
    return result;
    }

// ---------------------------------------------------------------------------
// DeleteL a TCountryData object from array
// ---------------------------------------------------------------------------
//
TInt CCountryDataManager::DeleteL( TInt aIndex )
    {
    TInt result( KErrNone );
    // check the index is available or not
    if ( aIndex < Count() && aIndex > EInvaildIndex )
        {
        // deletes this TCountryData object from TCountryData List
        iCountryDataList.Remove( aIndex );
        // save data to file
        StoreL();
        }
    else
        {
        result = KErrArgument;
        }
    return result;
    }

// ---------------------------------------------------------------------------
// Edit a TCountryData objct from the RArray
// ---------------------------------------------------------------------------
//
TInt CCountryDataManager::EditL( TInt aIndex, const MBaseData& aData )
    {
    TInt result( KErrNone );
    // edits this TCountryData object from TCountryData List
    TCountryData data( aData.Field( MBaseData::EBufCode ), 
                       aData.Field( MBaseData::EBufName ) );
    
    result = CheckDataFormat( 
        EFormatDigit, data.Field( MBaseData::EBufCode ) );
    if ( result == KErrNone )
        {
        result = CheckDataFormat( 
            EFormatAlpha, data.Field( MBaseData::EBufName ) );
        if ( result == KErrNone )
            {
            // modify data
            iCountryDataList[aIndex] = data;
            // save data to file
            StoreL();            
            }
        }
    return result;
    }

// ---------------------------------------------------------------------------
// Find the position of an element within the array
// ---------------------------------------------------------------------------
//
TInt CCountryDataManager::Find( const MBaseData& aData ) const
    {  
    TBuf<ECodeMaxChars> code( aData.Field( MBaseData::EBufCode ) );
    TBuf<ECodeMaxChars> list;
    TBuf<ECodeMaxChars> match;
    const TInt count( iCountryDataList.Count() );
    for ( TInt i = code.Length(); i > EFirstIndex ; --i )
        {
        match = code.Left( i );
        for ( TInt j = EFirstIndex; j < count; ++j )
            {
            list = iCountryDataList[j].Field( MBaseData::EBufCode );
            if ( list.Compare( match ) == KDataMatchSuccess )
                {
                return j;
                }
            }
        }
    return KDataMatchFailture;
    }

// ---------------------------------------------------------------------------
// Is the data exist in CCountryDataManager?
// ---------------------------------------------------------------------------
//
TInt CCountryDataManager::IsExist
    ( const MBaseData& aData, TInt aIndex ) const
    {
    TInt result( KErrNone );
    TBuf<ECodeMaxChars> code( aData.Field( MBaseData::EBufCode ) );
    TBuf<ECodeMaxChars> list;
    for ( TInt i = EFirstIndex; i < iCountryDataList.Count(); ++i )
        {
        list = iCountryDataList[i].Field( MBaseData::EBufCode );
        if ( code == list && i != aIndex )
            {
            result =  KErrAlreadyExists;
            break;
            }
        }
    return result;
    }

// ---------------------------------------------------------------------------
// Count the number of TCountryData objects contained in this array
// ---------------------------------------------------------------------------
//
TInt CCountryDataManager::Count() const
    {
    return iCountryDataList.Count();
    }   

// ---------------------------------------------------------------------------
// Constructor - no implementation required
// ---------------------------------------------------------------------------
//
CCountryDataManager::CCountryDataManager()
    : iFs( CCoeEnv::Static()->FsSession() )
    {
    }

// ---------------------------------------------------------------------------
// Second-phase constructor geting the RFs object ref from framework
// And restoring data from outside storage medium
// ---------------------------------------------------------------------------
//
void CCountryDataManager::ConstructL()
    {
    iFs.CreatePrivatePath( EDriveC );
    // gets data from the outside storage medium
    RestoreL();
    }

// ---------------------------------------------------------------------------
// Get data from outside storage medium
// ---------------------------------------------------------------------------
//
void CCountryDataManager::RestoreL()
    {
    // open file
    RFile file;
    HBufC* fileName = StringLoader::LoadLC( R_ROADMAP_DATA_FILENAME );
    while ( file.Open( iFs, *fileName, EFileRead ) != KErrNone )
        {
        CreateDefaultFileL();
        }
    CleanupStack::PopAndDestroy( fileName );

    // deletes all elements from the array
    iCountryDataList.Reset();
    // makes use of the read stream object to get data from the file
    RFileReadStream frs( file );
    CleanupClosePushL( frs );
    TUint count = frs.ReadUint32L();
    for ( TUint32 i = EFirstIndex; i < count; ++i )
        {
        TCountryData data;
        data.InternalizeL( frs );
        iCountryDataList.AppendL( data );
        }
    // close the file and the read stream object
    //frs.Close();
    CleanupStack::PopAndDestroy( &frs );
    file.Close();
    }

// ---------------------------------------------------------------------------
// Save data to outside storage medium
// ---------------------------------------------------------------------------
//
void CCountryDataManager::StoreL()
    {
    // open file
    RFile file;
    HBufC* fileName = StringLoader::LoadLC( R_ROADMAP_DATA_FILENAME );
    while ( file.Open( iFs, *fileName, EFileWrite ) != KErrNone )
        {
        CreateDefaultFileL();
        }
    CleanupStack::PopAndDestroy( fileName );
    file.SetSize( KEmptyFileSize );
    // makes use of the write stream object to get data from the file
    RFileWriteStream fws( file );
    CleanupClosePushL( fws );
    TUint count = iCountryDataList.Count();
    fws.WriteUint32L( count );
    for ( TUint32 i = EFirstIndex; i < count; ++i )
        {
        iCountryDataList[i].ExternalizeL( fws );
        }
    
    // close the file and the write stream object
    fws.CommitL();
    //fws.Close();
    CleanupStack::PopAndDestroy( &fws );
    file.Close();
    }

// ---------------------------------------------------------------------------
// Create default file assume that the data file is lost or destroyed
// ---------------------------------------------------------------------------
//
void CCountryDataManager::CreateDefaultFileL()
    {
    // create a file
    RFile file;
    HBufC* fileName = StringLoader::LoadLC( R_ROADMAP_DATA_FILENAME );
    User::LeaveIfError( file.Create( iFs, *fileName, EFileWrite ) );
    CleanupStack::PopAndDestroy( fileName );
    RFileWriteStream fws( file );
    CleanupClosePushL( fws );
    TBuf<ECodeMaxChars> code;
    TBuf<ENameMaxChars> name;
    // create and save default data to file stream
    fws.WriteUint32L( KDefaultItemNum );
    for ( TUint i = EFirstIndex; i < KDefaultItemNum; ++i )
        {
        code.Format( KCountryCode(), i );
        fws<<code;
        name.Format( KCountryName(), i );
        fws<<name;
        }

    // commit data
    fws.CommitL();
    // close the file and the write stream object
    //fws.Close();
    CleanupStack::PopAndDestroy( &fws );
    file.Close();
    }

// ---------------------------------------------------------------------------
// Check data format is reasonable or not
// ---------------------------------------------------------------------------
//
TInt CCountryDataManager::CheckDataFormat
    ( const TFormatType& aFormat, const TDes& aData )
    {
    TInt result( KErrNone ); 
    TInt count( aData.Length() );
    if ( count > EFirstIndex )
        {
        TChar temp;
        // Check string according to check-up type
        switch( aFormat )
            {
            // Digit
            case EFormatDigit:
                {
                for ( TInt i = EFirstIndex; i < count; i++ )
                    {
                    temp = static_cast<TChar>( aData[i] );
                    if ( !temp.IsDigit() )
                        {
                        result = KErrGeneral;
                        break;
                        }
                    }
                }
                break;
            // Alpha    
            case EFormatAlpha:
                {
                for ( TInt i = EFirstIndex; i < count; i++ )
                    {
                    temp = static_cast<TChar>( aData[i] );
                    if ( !temp.IsAlpha() )
                        {
                        result = KErrGeneral;
                        break;
                        }
                    }
                }
                break;
            // Other
            default:
                break;
            }        
        }
    else // The string is empty, and then return error directly!
        {
        result = KErrCompletion;
        }

    return result;
    }

// End of File
