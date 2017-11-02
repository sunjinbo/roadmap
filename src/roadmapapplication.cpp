/*
* ============================================================================
*  Name        : RoadMapApplication.cpp
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
#include "roadmapdocument.h"
#include "roadmapapplication.h"

// CONSTANTS
// UID of the application
const TUid KUidRoadMapApp = {0x0CD41FC8};


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Creates a CRoadMapDocument object
// ---------------------------------------------------------------------------
//
CApaDocument* CRoadMapApplication::CreateDocumentL()
    {  
    CApaDocument* doc = CRoadMapDocument::NewL( *this );
    return doc;
    }

// ---------------------------------------------------------------------------
// Gets the application specific UID
// ---------------------------------------------------------------------------
//
TUid CRoadMapApplication::AppDllUid() const
    {
    return KUidRoadMapApp;
    }

// End of File
