/*
* ============================================================================
*  Name        : roadmap.h
*  Part of     : RoadMap
*  Description : The Entry point of the whole Application
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
#include <eikstart.h>

#include "roadmapapplication.h"


// ======== GLOBAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// Create an application, and return a pointer to it
// ---------------------------------------------------------------------------
EXPORT_C CApaApplication* NewApplication()
    {
    return new CRoadMapApplication;
    }

// ---------------------------------------------------------------------------
// Main function of the application executable.
// ---------------------------------------------------------------------------
GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File
