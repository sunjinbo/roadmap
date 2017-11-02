/*
* ============================================================================
*  Name        : EditForm.cpp
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
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <avkon.hrh>
#include <eikedwin.h>
#include <roadmap.rsg>

#include "roadmapeditform.h"
#include "roadmapdocument.h"
#include "roadmap.hrh"


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Create a CEditForm object and Run it
// ---------------------------------------------------------------------------
//
void CEditForm::RunL( TOperationType aOperationType,
                       TInt aIndex, 
                       CRoadMapDocument* aDoc,
                       TBool& aIsModified )
    {
    // Creates a dialog object
    CEditForm* form = new (ELeave) CEditForm
        ( aOperationType, aIndex, aDoc, aIsModified );
    form->ExecuteLD( R_ROADMAP_DLG_EDITDIALOG );
    }


// ---------------------------------------------------------------------------
// Constructor - initializing member variable
// ---------------------------------------------------------------------------
//
CEditForm::CEditForm( TOperationType aOperationType,
                      TInt aIndex, 
                      CRoadMapDocument* aDoc,
                      TBool& aIsModified )
                    : iOperationType( aOperationType ),
                      iIndex ( aIndex ),
                      iAppDoc ( aDoc ),
                      iIsModified ( aIsModified )
                      
    {
    }

// ---------------------------------------------------------------------------
// Displays an alert window with a brief message
// ---------------------------------------------------------------------------
// 
void CEditForm::NoteMessageL( const TInt& aResourceId ) const
    {
    // reads a resource string with memory allocation 
    // and pushes the string onto the cleanup stack
    HBufC* message = StringLoader::LoadLC( aResourceId );
    iEikonEnv->AlertWin( *message );
    CleanupStack::PopAndDestroy( message );
    }

// ---------------------------------------------------------------------------
// Gets the both of Edwins'text data
// ---------------------------------------------------------------------------
//
void CEditForm::GetInputText( TDes& aCode, TDes& aName ) const
    {
    CEikEdwin* editor( NULL );
    // gets a pointer to the Code Edwin Control
    editor = static_cast<CEikEdwin*>( Control( EEditFormCodeEdwinID ) );
    // gets the text of the Code Edwin Control
    editor->GetText( aCode );
    // gets a pointer to the Name Edwin Control 
    editor = static_cast<CEikEdwin*>( Control( EEditFormNameEdwinID ) );
    // gets the text of the Code Edwin Control
    editor->GetText( aName );
    }

// ---------------------------------------------------------------------------
// Sets the both of Edwins' default text
// ---------------------------------------------------------------------------
//
void CEditForm::UpdateEditFormL() const
    {
    // Edit Opertor
    if ( iOperationType == EOperationEdit )
        {
        CEikEdwin* editor( NULL );
        // gets the pointer of the Code Edwin Control 
        editor = 
           static_cast<CEikEdwin*>( Control( EEditFormCodeEdwinID ) );
        // sets the text to the Code Edwin Control
        editor->SetTextL( &(iAppDoc->Code( iIndex )) );
        // gets the pointer of the Name Edwin Control
        editor = 
           static_cast<CEikEdwin*>( Control( EEditFormNameEdwinID ) );
        // sets the text to the Name Edwin Control
        editor->SetTextL( &(iAppDoc->Name( iIndex )) );
        }
    }

// ---------------------------------------------------------------------------
// Feed back result to user accroding to the Error type
// ---------------------------------------------------------------------------
//
TBool CEditForm::FeedBackResult( TInt aType ) const
    {
    TBool result( EFalse );
    switch( aType )
        {

        case KErrNone:
            {
            iIsModified = ETrue;
            result = ETrue;
            }
            break;
        
        case KErrAlreadyExists:
            {
            NoteMessageL( R_ROADMAP_WARNING_EXIST );
            }
            break;
        
        case KErrGeneral:
            {
            NoteMessageL( R_ROADMAP_WARNING_FORMAT );
            }
            break;
          
        case KErrCompletion:
            {
            NoteMessageL( R_ROADMAP_WARNING_LOSE );
            }
            break;

        default:
            break;

        }
    return result;
    }

// ---------------------------------------------------------------------------
// Processing Edit Form's menu event according to button id
// ---------------------------------------------------------------------------
//
TBool CEditForm::OkToExitL( TInt aButtonId )
    {
    TInt result( KErrNone );
    
    if ( aButtonId == EAknSoftkeyOk )
        {
        TBuf<ECodeMaxChars> code;
        TBuf<ENameMaxChars> name;
        // Get Text String from the Input Fields
        GetInputText( code, name );
        result = iAppDoc->IsExist( code, iIndex );
        if ( result == KErrNone )
            {
            switch( iOperationType )
                {
                // Add
                case EOperationAdd:
                    {
                    result = iAppDoc->AddL( code, name );
                    }
                    break;
                // Edit
                case EOperationEdit:
                    {
                    result = iAppDoc->EditL( iIndex, code, name );
                    }
                    break;
                // Other
                default:
                    break;
                }
            }
        }
    return FeedBackResult( result );
    }

// ---------------------------------------------------------------------------
// Perform dynamic operations before layout
// ---------------------------------------------------------------------------
//
void CEditForm::PreLayoutDynInitL()
    {
    CAknForm::PreLayoutDynInitL();
    // sets the both of Edwins' default text
    UpdateEditFormL();
    }

// End of File
