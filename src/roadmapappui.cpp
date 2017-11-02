/*
* ============================================================================
*  Name        : RoadMapAppui.cpp
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
#include <avkon.hrh>
#include <aknnotewrappers.h> 
#include <roadmap.rsg>
#include <e32def.h>

#include "roadmap.pan"
#include "roadmapappui.h"
#include "roadmapappview.h"
#include "roadmap.hrh"
#include "roadmapeditform.h"
#include "roadmapdocument.h"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Destructor - destroys the view object
// ---------------------------------------------------------------------------
//
CRoadMapAppUi::~CRoadMapAppUi()
    {
    // Removes a control from the app UI's control stack and destroys it
    if ( iAppView )
        {
        RemoveFromStack( iAppView );
        delete iAppView;            
        }
    }

// ---------------------------------------------------------------------------
// Gets a pointer to the app UI's associated document
// ---------------------------------------------------------------------------
//
CRoadMapDocument* CRoadMapAppUi::RoadMapDocument()
    {
    return iAppDoc = static_cast<CRoadMapDocument*>( Document() );
    }

// ---------------------------------------------------------------------------
// Handles user commands
// ---------------------------------------------------------------------------
//
void CRoadMapAppUi::HandleCommandL( TInt aCommand )
    {
    switch( aCommand )
        {
        // Exit
        case EEikCmdExit:
        case EAknSoftkeyExit:
            {
            Exit();
            }
            break;
        // Add
        case EMainMenuAdd:
            {
            HandleAddL();
            }
            break;
        // Remove
        case EMainMenuRemove:
            {
            HandleRemoveL(); 
            }
            break;
        // Edit
        case EMainMenuEdit:
            {
            HandleEditL();
            }
            break;
        // Default
        default:
            {
            ASSERT( EFalse );
            }
            break;
        }
    }

// ---------------------------------------------------------------------------
// Completes construction
// ---------------------------------------------------------------------------
//
void CRoadMapAppUi::ConstructL()
    {
    // initialises this Avkon app UI with standard values
    BaseConstructL( CAknAppUi::EAknEnableSkin );
    // creates a view object
    iAppView = CRoadMapAppView::NewL( ClientRect() );
    // sets the context
    // |->> that is, the enclosing parent control - for this control
    iAppView->SetMopParent( this );
    // inserts a control into the app UI's control stack
    AddToStackL( iAppView );
    // gets a pointer to the app UI's associated document
    iAppDoc = static_cast< CRoadMapDocument* >( Document() );
    }

// ---------------------------------------------------------------------------
// Handles add command
// ---------------------------------------------------------------------------
//
void CRoadMapAppUi::HandleAddL()
    {
    TBool isModified( EFalse );
    // running EditForm, and let it handles add command 
    CEditForm::RunL( 
        CEditForm::EOperationAdd, EInvaildIndex, iAppDoc, isModified );
    // if it was modified any data, updates AppView 
    if ( isModified )
        {
        iAppView->UpdateAppViewL();
        }
    }

// ---------------------------------------------------------------------------
// Handles removed command
// ---------------------------------------------------------------------------
//
void CRoadMapAppUi::HandleRemoveL()
    {
    TInt index( iAppView->CurrentListBoxItemIndex() );
    if ( index != EInvaildIndex )
        {
        // delete this item data and update the AppView
        iAppDoc->DeleteL( index );
        iAppView->UpdateAppViewL();
        }
    }

// ---------------------------------------------------------------------------
// Handles edit command
// ---------------------------------------------------------------------------
//
void CRoadMapAppUi::HandleEditL()
    {
    TBool isModified( EFalse );
    TInt index( iAppView->CurrentListBoxItemIndex() );
    if (  index != EInvaildIndex )
        {
        // running EditForm, and let it handles edit command
        CEditForm::RunL( 
            CEditForm::EOperationEdit, index, iAppDoc, isModified );
        }

    // if it was modified any data, updates AppView
    if ( isModified )
        {
        iAppView->UpdateAppViewL();
        }
    }

// End of File
