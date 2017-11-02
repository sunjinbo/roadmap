/*
* ============================================================================
*  Name        : roadmapapplication.h
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

#ifndef C_CRMAPP_H
#define C_CRMAPP_H

// INCLUDES
#include <aknapp.h>


/**
 *  Defines the basic behaviour for roadmap apps.
 *
 *  The class defines the basic twin roles of an application class 
 *  as a factory that creates concrete document objects, and as 
 *  a supplier of utility functions not specific to any particular 
 *  instance of a document.
 *
 *  @since S60 v3.1
 */
class CRoadMapApplication : public CAknApplication
    {

public:  // From base class CAknApplication
    
    /**
     * Get the RoadMap Application UID value
     *
     * @since S60 v3.1
     * @param void
     * @return the UID value of this Application
     */
    TUid AppDllUid() const;

private: // From base class CAknApplication

    /**
     * Create a CApaDocument object and return a pointer to it
     *
     * @since S60 v3.1
     * @param void
     * @return a pointer to the created document
     */
    CApaDocument* CreateDocumentL();

    };

#endif // C_CRMAPP_H

// End of File
