/*
* ============================================================================
*  Name        : roadmapappui.h
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

#ifndef C_RMAPPUI_H
#define C_RMAPPUI_H

// INCLUDES
#include <aknappui.h>

// FORWARD DECLARATIONS
class CRoadMapAppView;
class CRoadMapDocument;


/**
 *  The UserInterface part of the AVKON application framework 
 *  for the RoadMap example application
 *
 *  Handles application-wide aspects of the application's user interface 
 *  such as the menu bar, toolbar pop-up menus, opening and closing files 
 *  and exiting the application cleanly.
 *  An app UI's main role is to handle commands, in its HandleCommandL() 
 *  function. These may be invoked using the menu bar, toolbar, or hotkeys; 
 *  the commands that an app UI handles are specified in the application's 
 *  resource file.
 *
 *  @since S60 v3.1
 */
class CRoadMapAppUi : public CAknAppUi
    {

public: // Constructors and destructor

    /**
     * Destructor - destroys the view object
     *
     * @since S60 v3.1
     */
    ~CRoadMapAppUi();

public: // New functions

    /**
     * Gets a pointer to the app UI's associated document
     *
     * @since S60 v3.1
     * @return a pointer of the CRoadMapDocument object
     */
    CRoadMapDocument* RoadMapDocument();

    /**
     * From CAknAppUi
     * Handle user commands
     *
     * @since S60 v3.1
     * @param aCommand the enumerated code for the option selected
     * @return void
     */
    void HandleCommandL( TInt aCommand );

private: // Constructors and destructor
    
    /**
     * Completes construction
     * 
     * @since S60 v3.1
     */
    void ConstructL();

private: // New functions

    /**
     * Handle Add command
     *
     * @since S60 v3.1
     */
    void HandleAddL();
    
    /**
     * Handle Remove command
     *
     * @since S60 v3.1
     */
    void HandleRemoveL();

    /**
     * Handle Edit command
     *
     * @since S60 v3.1
     */
    void HandleEditL();

private: // Members

    /**
     * @var iAppView The application view
     * Own.
     */
    CRoadMapAppView* iAppView;

    /**
     * @var iAppDoc The application document
     * Not own.
     */    
    CRoadMapDocument* iAppDoc;

    };

#endif // C_RMAPPUI_H

// End of File
