/*
* ============================================================================
*  Name        : RoadMapAppview.h
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

#ifndef C_RMAPPVIEW_H
#define C_RMAPPVIEW_H

// INCLUDES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CEikLabel;
class CAknIntegerEdwin;
class CEikTextListBox;
class CEikEdwin;
class CRoadMapAppUi;
class CRoadMapDocument;


/**
 *  An instance of the Application View object for the RoadMap 
 *  example application
 *
 *  This View provided a user interface which including some controls;
 *  and also provided a OfferKeyEventL function in order to handles 
 *  key events of these controls
 *
 *  @since S60 v3.1
 */
class CRoadMapAppView : public CCoeControl
    {

public: // Constructors and destructor

    /**
     * Constructs view object by retrieving the rect status using aRect
     * 
     * @since S60 v3.1
     * @param aRect the rectangle this view will be drawn to
     * @return a pointer to the created instance of CRoadMapAppView
     */
    static CRoadMapAppView* NewL( const TRect& aRect );

    /**
     * Constructs view object by retrieving the rect status using aRect
     * 
     * @since S60 v3.1
     * @param aRect the rectangle this view will be drawn to
     * @return a pointer to the created instance of CRoadMapAppView
     */
    static CRoadMapAppView* NewLC( const TRect& aRect );

    /**
     * Destructor - ( It destroys the 4 controls owned by the View )
     * 
     * @since S60 v3.1
     */
     ~CRoadMapAppView();

public: // New functions
  
    /**
     * Initialises or reinitialises the controls' status of CRoadMapView
     * 
     * @since S60 v3.1
     */
    void UpdateAppViewL() const;
    
    /**
     * Gets the ListBox index number of the selected item.
     * 
     * @since S60 v3.1
     */
    TInt CurrentListBoxItemIndex() const;

private: // Constructors and destructor

    /**
     * Constructor
     * 
     * @since S60 v3.1
     */
    CRoadMapAppView();

    /**
     * Completes construction of the CRoadMapAppView object.
     * 
     * @since S60 v3.1
     * @param aRect the rectangle this view will be drawn to
     */
    void ConstructL( const TRect& aRect );

private: // New functions

    /**
     * Create a CEikLabel object for CRoadMapAppView
     * 
     * @since S60 v3.1
     */
    void CreateLabelInputL();

    /**
     * Create a CAknIntegerEdwin object for CRoadMapAppView
     * 
     * @since S60 v3.1
     */
    void CreateEdwinInputL();

    /**
     * Create a CEikTextListBox object for CRoadMapAppView
     * 
     * @since S60 v3.1
     */
    void CreateListBoxL();

    /**
     * Create a CEikEdwin object for CRoadMapAppView
     * 
     * @since S60 v3.1
     */
    void CreateEdwinDescriptionL();

    /**
     * Layout these controls on this view
     * 
     * @since S60 v3.1
     */
    void LayoutControls();

        /**
     * Initialises or reinitialises the listbox control' status
     * 
     * @since S60 v3.1
     */
    void UpdateListBoxL() const;

    /**
     * Sets the height of the ListBox item to the selected value
     * 
     * @since S60 v3.1
     */
    void SetListBoxItemHighlight( TInt aIndex ) const;

    /**
     * Get the text of EdwinInput control
     * 
     * @since S60 v3.1
     * @return a text get from EdwinInput
     */
    HBufC* GetEdwinInputTextL() const;

    /**
     * Display text on EdwinDescription, according to ListBox's 
     * current index
     * 
     * @since S60 v3.1
     */
    void SetEdwinDescriptionTextL() const ;

    /**
     * Handles Up & Down Key Events
     * 
     * @since S60 v3.1
     * @param aKeyEvent the Key event details
     * @param aType the Types of standard events
     * @return a TKeyResponse which indicates whether or not the 
     *  key event was used by this control.
     */
    TKeyResponse HandleKeyUpDownEventL
        ( const TKeyEvent& aKeyEvent, TEventCode aType ) const;
 
    /**
     * Handles Left & Right Key Events
     * 
     * @since S60 v3.1
     * @param aKeyEvent the Key event details
     * @param aType the Types of standard events
     * @return a TKeyResponse which indicates whether or not the 
     *  key event was used by this control.
     */
    TKeyResponse HandleKeyLeftRightEventL
        ( const TKeyEvent& aKeyEvent, TEventCode aType ) const;

    /**
     * Handles Backspace Key Events
     * 
     * @since S60 v3.1
     */
    TKeyResponse HandleKeyBackspaceEventL() const ;
    
    /**
     * Handles DeleteL Key Events
     * 
     * @since S60 v3.1
     */
    TKeyResponse HandleKeyDeleteEventL() const ;
    
    /**
     * Handles OK & Enter Key Events
     * 
     * @since S60 v3.1
     */
    TKeyResponse CRoadMapAppView::HandleKeyOKEnterEventL() const;
    
    /**
     * Search country code from ListBox and highlight it
     * 
     * @since S60 v3.1
     */
    void HandleSearchL() const ;

private: // From base class CCoeControl

    /**
     * From CCoeControl
     * Gets an indexed component of a compound control
     * 
     * @since S60 v3.1
     * @param aIndex the index of the control
     * @return void
     */
    CCoeControl* ComponentControl( TInt aIndex ) const;
     
    /**
     * From CCoeControl
     * Gets the number of controls contained in a compound control
     * 
     * @since S60 v3.1
     * @param void
     * @return the number of component controls contained by this control
     */
    TInt CountComponentControls() const;
 
    /**
     * From CCoeControl
     * Handles Other Key Events
     * 
     * @since S60 v3.1
     * @param aKeyEvent the Key event details
     * @param aType the Types of standard events
     * @return a TKeyResponse which indicates whether or not the 
     *  key event was used by this control.
     */                                         
    TKeyResponse HandleKeyOtherEventL
        ( const TKeyEvent& aKeyEvent, TEventCode aType ) const;

    /**
     * From CCoeControl
     * Responds to changes to the size and position of the contents 
     * of this control
     * 
     * @since S60 v3.1
     */
     void SizeChanged();

    /**
     * From CCoeControl
     * Draw this CRoadMapAppView to the screen
     * 
     * @since S60 v3.1
     * @param aRect the rectangle of this view that needs updating
     */
    void Draw( const TRect& aRect ) const;
  
    /**
     * From CCoeControl
     * Handls Key Events of these controls
     * 
     * @since S60 v3.1
     * @param aKeyEvent the Key event details
     * @param aType the Types of standard events
     * @return a TKeyResponse which indicates whether or not the 
     *  key event was used by this control.
     */
    TKeyResponse OfferKeyEventL
        ( const TKeyEvent& aKeyEvent, TEventCode aType );

private: // Members
     
    /**
     * Use it to show the text 'Input'
     * Own.
     */
    CEikLabel* iLabelInput;
    
    /**
     * Use it to search the country code
     * Own.
     */
    CAknIntegerEdwin* iEdwinInput;
  
    /**
     * Use it to show the country code
     * Own.
     */
    CEikTextListBox* iListBox;
  
    /**
     * Use it to show the country name
     * Own..
     */
    CEikEdwin* iEdwinDescription;

    /**
     * Use it to process inner data
     * Not own..
     */
    CRoadMapDocument* iAppDoc;
     
    };

#endif // C_RMAPPVIEW_H

// End of File
