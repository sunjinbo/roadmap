/*
* ============================================================================
*  Name        : RoadMapAppview.cpp
*  Part of     : RoadMap
*  Description : 
*  Version     : 
*
*  Copyright © 2007 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, ay or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* 
*/

// INCLUDES
#include <coemain.h>
#include <roadmap.rsg>
#include <eiklabel.h>
#include <aknlists.h>
#include <eikedwin.h>
#include <stringloader.h>
#include <barsread.h>
#include <aknnotewrappers.h>
#include <eiktxlbx.h>
#include <eiktxlbm.h>
#include <eikgted.h>
#include <coemain.h>

#include "roadmapappview.h"
#include "roadmapappui.h"
#include "roadmapdocument.h"
#include "roadmap.hrh"

// CONSTANTS
// Specifies the minimum value for a code data
const TInt KCodeMin( 0 );
// Specifies the maximum value for a code data
const TInt KCodeMax( 99999 );
// How many component controls on the AppView?
const TInt KCountComponentControls( 4 );
// Specifies the gap between these controls on the AppView
const TInt KGap( 5 );
// Specifies the upper-top corner of this label-input ctrl
const TInt KLabelInputTop( 5 );
// Specifies the upper-left corner of this label-input ctrl
const TInt KLabelInputLeft( 5 );


// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// Constructs view object by retrieving the rect status using aRect
// ---------------------------------------------------------------------------
//
CRoadMapAppView* CRoadMapAppView::NewL( const TRect& aRect )
    {
    CRoadMapAppView* self = CRoadMapAppView::NewLC( aRect );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// Constructs view object by retrieving the rect status using aRect
// ---------------------------------------------------------------------------
//
CRoadMapAppView* CRoadMapAppView::NewLC( const TRect& aRect )
    {
    CRoadMapAppView* self = new ( ELeave ) CRoadMapAppView;
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    return self;
    }

// ---------------------------------------------------------------------------
// Destructor - ( It destroys the 4 controls owned by the View )
// ---------------------------------------------------------------------------
//
CRoadMapAppView::~CRoadMapAppView()
    {
    delete iLabelInput;
    delete iEdwinInput;
    delete iListBox;
    delete iEdwinDescription;
    }

// ---------------------------------------------------------------------------
// Initialises or reinitialises the controls' status of CRoadMapView
// ---------------------------------------------------------------------------
//
void CRoadMapAppView::UpdateAppViewL() const
    {
    iEdwinInput->SetTextL( &KNullDesC );
    iEdwinDescription->SetTextL( &KNullDesC );
    UpdateListBoxL();
    }

// ---------------------------------------------------------------------------
// Gets the ListBox index number of the selected item.
// ---------------------------------------------------------------------------
//
TInt CRoadMapAppView::CurrentListBoxItemIndex() const
    {
    TInt index( EInvaildIndex );
    if ( iListBox->IsFocused() && iAppDoc->Count() > 0 )
        {
        index = iListBox->CurrentItemIndex();
        }
    return index;
    }

// ---------------------------------------------------------------------------
// Construct - Get AppDoc's pointer
// ---------------------------------------------------------------------------
//
CRoadMapAppView::CRoadMapAppView()
    {
    CRoadMapAppUi* appui = static_cast<CRoadMapAppUi*>( iCoeEnv->AppUi() );
    iAppDoc = appui->RoadMapDocument();
    }

// ---------------------------------------------------------------------------
// Completes construction of the CRoadMapAppView object.
// ---------------------------------------------------------------------------
//
void CRoadMapAppView::ConstructL( const TRect& aRect )
    {
    // create a window for this application view
    CreateWindowL();

    // create four controls for CRoadMapView
    CreateLabelInputL();
    CreateEdwinInputL();
    CreateListBoxL();
    CreateEdwinDescriptionL();

    // initialize for controls' status for CRoadMapView
    UpdateAppViewL();
    //iListBox->SetFocus( EFalse );
    iEdwinInput->SetFocus( ETrue );
    
    // set the windows size
    SetRect( aRect );

    // activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ---------------------------------------------------------------------------
// Create a CEikLabel object for CRoadMapAppView
// ---------------------------------------------------------------------------
//
void CRoadMapAppView::CreateLabelInputL()
    {
    iLabelInput = new ( ELeave ) CEikLabel;
    iLabelInput->SetContainerWindowL( *this );
    HBufC* inputString = StringLoader::LoadLC( R_ROADMAP_LABEL_INPUT );
    iLabelInput->SetTextL( *inputString );
    CleanupStack::PopAndDestroy( inputString );
    }

// ---------------------------------------------------------------------------
// Create a CAknIntegerEdwin object for CRoadMapAppView
// ---------------------------------------------------------------------------
//
void CRoadMapAppView::CreateEdwinInputL()
    {
    iEdwinInput = new ( ELeave ) CAknIntegerEdwin();
    iEdwinInput->ConstructL( KCodeMin, KCodeMax, ECodeMaxChars );
    iEdwinInput->SetContainerWindowL( *this );
    }

// ---------------------------------------------------------------------------
// Create a CEikTextListBox object for CRoadMapAppView
// ---------------------------------------------------------------------------
//
void CRoadMapAppView::CreateListBoxL()
    {
    iListBox = new ( ELeave ) CEikTextListBox;
    iListBox->ConstructL( this );
    iListBox->SetContainerWindowL( *this );
    iListBox->CreateScrollBarFrameL( ETrue );
    iListBox->ScrollBarFrame()->SetScrollBarVisibilityL
       ( CEikScrollBarFrame::EOn, CEikScrollBarFrame::EAuto );
    }

// ---------------------------------------------------------------------------
// Create a CEikEdwin object for CRoadMapAppView
// ---------------------------------------------------------------------------
//
void CRoadMapAppView::CreateEdwinDescriptionL()
    {
    iEdwinDescription = new ( ELeave ) CEikEdwin;
    iEdwinDescription->ConstructL( CEikEdwin::EWidthInPixels | 
        CEikEdwin::EReadOnly, KCodeMin, KCodeMax, ECodeMaxChars );
    iEdwinDescription->SetContainerWindowL( *this );
    }

// ---------------------------------------------------------------------------
// Layout these controls on this view
// ---------------------------------------------------------------------------
//
void CRoadMapAppView::LayoutControls()
    {
    TRect screen( Rect() );
    TInt screenWidth( screen.Width() );
    TInt screenHeight( screen.Height() );
    
    TRect rect;
    // The co-ordinates of the rectangle's top left hand corner
    TPoint point;
    // The rectangle's width and height
    TSize size;
    // Gets min height between iLableInput and iEdwinInput
    TInt minHeight = Max( iLabelInput->MinimumSize().iHeight, 
                          iEdwinInput->MinimumSize().iHeight );
    
    // Setting iLableInput's Position
    point = screen.iTl + TPoint( KLabelInputTop, KLabelInputLeft );
    size = TSize( iLabelInput->MinimumSize().iWidth, minHeight );
    rect.SetRect( point, size );
    iLabelInput->SetRect( rect );
    
    
    // Setting iEdwinInput's Position
    point = iLabelInput->Rect().iBr + TPoint(KGap, - minHeight );
    size = TSize( screenWidth - iLabelInput->Rect().Width() - KGap * 3, 
                  minHeight );
    rect.SetRect( point, size );
    iEdwinInput->SetRect( rect );
    
    // Setting iListBox's Position
    point = iLabelInput->Rect().iTl + TPoint( 0, minHeight + KGap );
    size = TSize( ( screenWidth - KGap * 3 ) / 2, 
        screenHeight - minHeight - KGap * 3 ) ;
    rect.SetRect( point, size );
    iListBox->SetRect( rect );
    
    // Setting iEdwinDescription's Position
    
    
    rect.Move( iListBox->Rect().Width() + KGap, 0 );
    iEdwinDescription->SetRect( rect );
    }

// ---------------------------------------------------------------------------
// Initialises or reinitialises the listbox control' status.
// ---------------------------------------------------------------------------
//
void CRoadMapAppView::UpdateListBoxL() const
    {
    
    // Get ListBox CTRL's text array
    CDesCArray* items =
        static_cast<CDesCArray*>( iListBox->Model()->ItemTextArray() );
    items->AppendL ( KNullDesC );
  
    // if the pointers is not available, backing out directly
    if( items )
        {
        items->Reset();
        // take turns insert item to listbox
        items->AppendL ( KNullDesC );
        TInt count = iAppDoc->Count();
        for ( TInt i = EFirstIndex; i < count; ++i )
            {
            if( i == EFirstIndex )
                {
                items->Reset();
                }
            items->AppendL ( iAppDoc->Code( i ) );
            }
        iListBox->HandleItemAdditionL();
        // sets the first item to be the top item and draw it
        SetListBoxItemHighlight( EFirstIndex );
        }
    DrawNow();

    }

// ---------------------------------------------------------------------------
// Sets the height of the ListBox item to the selected value
// ---------------------------------------------------------------------------
//
void CRoadMapAppView::SetListBoxItemHighlight( TInt aIndex ) const
    {
    iEdwinInput->SetFocus( EFalse );
    iListBox->SetFocus( ETrue );
    iListBox->SetTopItemIndex( aIndex );
    iListBox->SetCurrentItemIndex( aIndex );
    iListBox->DrawNow();
    }

// ---------------------------------------------------------------------------
// Get the text of EdwinInput control
// ---------------------------------------------------------------------------
//
HBufC* CRoadMapAppView::GetEdwinInputTextL() const
    {
    return iEdwinInput->GetTextInHBufL();
    }

// ---------------------------------------------------------------------------
// Display text on EdwinDescription, according to ListBox's current index
// ---------------------------------------------------------------------------
//
void CRoadMapAppView::SetEdwinDescriptionTextL() const
    {
    TInt index = iListBox->CurrentItemIndex();
    if ( iAppDoc->Count() > 0 )
        {
        iEdwinDescription->SetTextL( &(iAppDoc->Name( index )) );   
        }
    else
        {
        iEdwinDescription->SetTextL( &KNullDesC );
        }
    }

// ---------------------------------------------------------------------------
// Handles Up & Down Key Events
// ---------------------------------------------------------------------------
//  
TKeyResponse CRoadMapAppView::HandleKeyUpDownEventL( 
    const TKeyEvent& aKeyEvent, TEventCode aType ) const
    {
    // if EdwinInput doesn't have focus, ListBox handles key events
    if ( !iEdwinInput->IsFocused() )
        {
        iListBox->OfferKeyEventL( aKeyEvent, aType );
        }
    // otherwise, switch focus between EdwinInput and ListBox
    else
        {
        iEdwinInput->SetFocus( EFalse );
        iListBox->SetFocus( ETrue );
        iListBox->SetCurrentItemIndex( iListBox->CurrentItemIndex() );
        iListBox->DrawNow();
        }
    return EKeyWasConsumed;
    }

// ---------------------------------------------------------------------------
// Handles Left & Right Key Events
// ---------------------------------------------------------------------------
//  
TKeyResponse CRoadMapAppView::HandleKeyLeftRightEventL( 
    const TKeyEvent& aKeyEvent, TEventCode aType ) const
    {
    // if ListBox doesn't have focus, EdwinInput handles key events
    if ( !iListBox->IsFocused() )
        {
        iEdwinInput->OfferKeyEventL( aKeyEvent, aType );
        }
    // otherwise, switch focus between ListBox and EdwinInput
    else
        {
        iListBox->SetFocus( EFalse );
        iEdwinInput->SetFocus( ETrue );
        }
    return EKeyWasConsumed;
    }

// ---------------------------------------------------------------------------
// Handles Backspace Key Event
// ---------------------------------------------------------------------------
//  
TKeyResponse CRoadMapAppView::HandleKeyBackspaceEventL() const
    {
    // if EdwinInput doesn't have focus, return directly
    if( !iEdwinInput->IsFocused() )
        {
        return EKeyWasNotConsumed;
        }

    // gets EdwinInput's text
    TBuf<ECodeMaxChars> oldString;
    TInt pos = iEdwinInput->CursorPos();
    iEdwinInput->GetText( oldString );
    // delete a char behind the cursor pos
    TPtrC16 leftString = oldString.Left( pos - ( pos > 0) );
    TPtrC16 rightString = oldString.Mid( pos ); 
    TBuf<ECodeMaxChars> newString( leftString );
    newString.Append( rightString );
    // sets EdwinInput's text
    iEdwinInput->SetTextL( &newString );
    iEdwinInput->SetCursorPosL( pos - ( pos > 0), EFalse );
    iEdwinInput->DrawNow();
    HandleSearchL();
    return EKeyWasConsumed;
    }

// ---------------------------------------------------------------------------
// Handles DeleteL Key Event
// ---------------------------------------------------------------------------
//
TKeyResponse CRoadMapAppView::HandleKeyDeleteEventL() const
    {
    // if EdwinInput doesn't have focus, return directly
    if( !iEdwinInput->IsFocused() )
        {
        return EKeyWasNotConsumed;
        }
    // gets EdwinInput's text
    TBuf<ECodeMaxChars> oldString;
    TInt pos = iEdwinInput->CursorPos();
    iEdwinInput->GetText( oldString );
    // delete a char before the cursor pos
    TPtrC16 leftString = oldString.Left( pos );
    TPtrC16 rightString = 
        oldString.Mid( pos + ( pos < oldString.Length() ) );
    TBuf<ECodeMaxChars> newString( leftString );
    newString.Append( rightString );
    // sets EdwinInput's text
    iEdwinInput->SetTextL( &newString );
    iEdwinInput->SetCursorPosL( pos, EFalse );
    iEdwinInput->DrawNow();
    HandleSearchL();
    
    return EKeyWasConsumed;
    }

// ---------------------------------------------------------------------------
// Handles OK & Enter Key Event
// ---------------------------------------------------------------------------
//
TKeyResponse CRoadMapAppView::HandleKeyOKEnterEventL() const
    {
    if ( iEdwinInput->IsFocused() )
        {
        HandleSearchL();
        }
    else
        {
        SetEdwinDescriptionTextL();
        }                               
    return EKeyWasConsumed;
    }

// ---------------------------------------------------------------------------
// Handles Other Key Event
// ---------------------------------------------------------------------------
//
TKeyResponse CRoadMapAppView::HandleKeyOtherEventL( 
    const TKeyEvent& aKeyEvent, TEventCode aType ) const
    {
    if ( iEdwinInput->IsFocused() )
        {
        iEdwinInput->OfferKeyEventL( aKeyEvent, aType );
        HandleSearchL();
        }
    return EKeyWasConsumed;                              
    }
   
// ---------------------------------------------------------------------------
// Search country code from ListBox and highlight it
// ---------------------------------------------------------------------------
//
void CRoadMapAppView::HandleSearchL() const
    {
    TBuf<ECodeMaxChars> codestr;
    iEdwinInput->GetText( codestr );

    TInt index = iAppDoc->Find( codestr );
    // if finds it, this item should be highlighted
    if( index > EInvaildIndex )
        {
        SetListBoxItemHighlight( index );
        iListBox->SetFocus( EFalse );
        iEdwinInput->SetFocus( ETrue );
        }
    // otherwise, the first item will be highlighted
    else
        {
        SetListBoxItemHighlight( EFirstIndex );
        iListBox->SetFocus( EFalse );
        iEdwinInput->SetFocus( ETrue );
        }
    }

// ---------------------------------------------------------------------------
// Gets an indexed component of a compound control
// ---------------------------------------------------------------------------
//
CCoeControl* CRoadMapAppView::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case EMainViewLabelInputID:
            return iLabelInput;

        case EMainViewEdwinInputID:
            return iEdwinInput;

        case EMainViewListBoxID:
            return iListBox;

        case EMainViewEdwinDescriptionID:
            return iEdwinDescription;
  
        default:
            return NULL;
        }
     }

// ---------------------------------------------------------------------------
// Gets the number of controls contained in a compound control
// ---------------------------------------------------------------------------
//
TInt CRoadMapAppView::CountComponentControls() const
    {
    return EMainViewTotalNumber;
    }

// ---------------------------------------------------------------------------
// Respond to changes to the size and position of the contents of this control
// ---------------------------------------------------------------------------
//
void CRoadMapAppView::SizeChanged()
    {
    DrawNow();
    LayoutControls();
    
    }

// ---------------------------------------------------------------------------
// Draw this application's view to the screen
// ---------------------------------------------------------------------------
//
void CRoadMapAppView::Draw( const TRect& /*aRect*/ ) const
    {
    // get the standard graphics context 
    CWindowGc& gc( SystemGc() );
    // gets the control's extent
    TRect rect( Rect() );
    // sets the background color
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetPenColor( KRgbBlack );
    gc.SetBrushColor( TRgb(0x555555) );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    // clears the screen and Reset graphics context's property
    gc.Clear(rect);
    }

// ---------------------------------------------------------------------------
// Handles key events
// ---------------------------------------------------------------------------
//
TKeyResponse CRoadMapAppView::OfferKeyEventL( 
    const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    switch(aKeyEvent.iCode)
        {
        // Up&Down
        case EKeyUpArrow:
        case EKeyDownArrow:
            {
            return HandleKeyUpDownEventL( aKeyEvent, aType );
            }
            break;
        // Left&Right
        case EKeyLeftArrow:
        case EKeyRightArrow:
            {
            HandleKeyLeftRightEventL( aKeyEvent, aType );    
            }
            break;
        // DeleteL
        case EKeyDelete:
            {
            HandleKeyDeleteEventL();
            }
            break;
        // Backspace
        case EKeyBackspace:
            {
            HandleKeyBackspaceEventL();
            }
            break;
        // OK&Enter
        case EKeyOK:
        case EKeyEnter:
            {
            HandleKeyOKEnterEventL();
            }
            break;
        // Null
        case EKeyNull:
            break;
        // Default
        default:
            {
            HandleKeyOtherEventL( aKeyEvent, aType );
            }
            break;
        }
 
    return EKeyWasNotConsumed;
    }

// End of File
