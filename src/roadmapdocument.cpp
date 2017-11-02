/*
* ============================================================================
*  Name        : RoadMapDocument.cpp
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

// INCLUDES
#include "roadmapappui.h"
#include "roadmapdocument.h"
#include "countrydatamanager.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Creates a doc object
// ---------------------------------------------------------------------------
//
CRoadMapDocument* CRoadMapDocument::NewL( CEikApplication& aApp )
    {
    CRoadMapDocument* self = NewLC( aApp );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Creates a doc object, and puts a pointer to it onto the cleanup stack
// ---------------------------------------------------------------------------
//
CRoadMapDocument* CRoadMapDocument::NewLC( CEikApplication& aApp )
    {
    CRoadMapDocument* self = new ( ELeave ) CRoadMapDocument( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor - destroys the CountryDataManager object
// ---------------------------------------------------------------------------
//
CRoadMapDocument::~CRoadMapDocument()
    {
    delete iCountryDataManager;
    }

// ---------------------------------------------------------------------------
// Constructs the application UI
// ---------------------------------------------------------------------------
//
CEikAppUi* CRoadMapDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it,
    // the framework takes ownership of this object
    CEikAppUi* appUi = new (ELeave) CRoadMapAppUi;
    return appUi;
    }

// ---------------------------------------------------------------------------
// Constructor for CRoadMapDocument
// ---------------------------------------------------------------------------
//
CRoadMapDocument::CRoadMapDocument( CEikApplication& aApp )
    : CAknDocument( aApp ) 
    {
    }
   
// ---------------------------------------------------------------------------
// Completes construction - Create a CountryDataManager object
// ---------------------------------------------------------------------------
//
void CRoadMapDocument::ConstructL()
    {
    iCountryDataManager = CCountryDataManager::NewL();
    }

// ---------------------------------------------------------------------------
// Add a TCountryData objct to the CCountryDataManager
// ---------------------------------------------------------------------------
//
TInt CRoadMapDocument::AddL( const TDesC& aCode, const TDesC& aName )
    {
    TCountryData data( aCode, aName );
    return iCountryDataManager->AddL( data );
    }

// ---------------------------------------------------------------------------
// DeleteL a TCountryData object from CCountryDataManager
// ---------------------------------------------------------------------------
//
TInt CRoadMapDocument::DeleteL( TInt aIndex )
    {
    return iCountryDataManager->DeleteL( aIndex );
    }

// ---------------------------------------------------------------------------
// Edit a TCountryData objct from the CCountryDataManager
// ---------------------------------------------------------------------------
//
TInt CRoadMapDocument::EditL
    ( TInt aIndex, const TDesC& aCode, const TDesC& aName )
    {
    TCountryData data( aCode, aName );
    return iCountryDataManager->EditL( aIndex, data );
    }

// ---------------------------------------------------------------------------
// Find the position of an element within the array
// ---------------------------------------------------------------------------
//
TInt CRoadMapDocument::Find( const TDesC& aCode ) const
    {
    TBuf<ECodeMaxChars> code( aCode );
    TBuf<ENameMaxChars> name;
    TCountryData data( code, name );
    return iCountryDataManager->Find( data );
    }

// ---------------------------------------------------------------------------
// Is this data already exist?
// ---------------------------------------------------------------------------
//
TInt CRoadMapDocument::IsExist( const TDesC& aData, TInt aIndex ) const
    {
    TBuf<ECodeMaxChars> code( aData );
    TBuf<ENameMaxChars> name;
    TCountryData data( code, name );
    return iCountryDataManager->IsExist( data, aIndex );
    }

// ---------------------------------------------------------------------------
// Count the number of TCountryData objects contained in CCountryDataManager
// ---------------------------------------------------------------------------
//
TInt CRoadMapDocument::Count() const
    {
    return iCountryDataManager->Count();
    }

// ---------------------------------------------------------------------------
// Get TCountryData's Code by its index
// ---------------------------------------------------------------------------
//   
const TDesC& CRoadMapDocument::Code( TInt aIndex )
    {
    return CountryDataL( aIndex ).Field( MBaseData::EBufCode );
    }

// ---------------------------------------------------------------------------
// Get TCountryData's Name by its index
// ---------------------------------------------------------------------------
//    
const TDesC& CRoadMapDocument::Name( TInt aIndex )
    {
    return CountryDataL( aIndex ).Field( MBaseData::EBufName );
    }

// ---------------------------------------------------------------------------
// Get Country Data form its Index
// ---------------------------------------------------------------------------
//
const TCountryData& CRoadMapDocument::CountryDataL( TInt aIndex ) const
    {
    return iCountryDataManager->CountryDataL( aIndex );
    }

// End of File
