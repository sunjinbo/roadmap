/*
* ============================================================================
*  Name        : EditForm.h
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

#ifndef C_CEDITFORM_H
#define C_CEDITFORM_H

// INCLUDES
#include <aknform.h>

// FORWARD DECLARATIONS
class CRoadMapDocument;


/**
 *  
 *  A Edit Window that uses a Form for its implementation.
 *  
 *  @since S60 v3.1
 */
class CEditForm: public CAknForm
    {

public:

    /**
     * defines the data operation type
     */  
    enum TOperationType
   	    {
   	    EOperationAdd = 0,
        EOperationRemove,
        EOperationEdit
   	    };

public:

    /**
     * Create a CEditForm object and Run it
     *
     * @since S60 v3.1
     * @param aOperationType operate mode
     * @param aIndex [in]which index will be edited?
     * @param aMgr [In]operate which CCountryDataManager object
     * @param aIsModified [Out]operate result
     */
    static void RunL( TOperationType aOperationType,
                       TInt aIndex, 
                       CRoadMapDocument* aDoc,
                       TBool& aIsModified );

private:

     /**
     * Constructor - initializing member variable
     *
     * @since S60 v3.1
     * @param aOperationType operate mode
     * @param aIndex [in]which index will be edited?
     * @param aMgr [In]operate which CCountryDataManager object
     * @param aIsModified [Out]operate result
     */
    CEditForm( TOperationType aOperationType,
               TInt aIndex, 
               CRoadMapDocument* aDoc,
               TBool& aIsModified );

    /**
     * Displays an alert window with a brief message
     *
     * @since S60 v3.1
     * @param aResourceId a message resource Id
     */   
    void NoteMessageL( const TInt& aResourceId ) const;

    /**
     * Gets the both of Edwins'text data
     *
     * @since S60 v3.1
     * @param aCode a string get from EdwinCode
     * @param aName a string get from EdwinName
     */  
    void GetInputText( TDes& aCode, TDes& aName ) const;

    /**
     * Sets the both of Edwins' default text
     *
     * @since S60 v3.1
     */  
    void UpdateEditFormL() const;

    /**
     * Sets the both of Edwins' default text
     *
     * @since S60 v3.1
     * @param aType the error type
     * @return a operation whether or not it 
     * would be complete successfully
     */ 
    TBool FeedBackResult( TInt aType ) const;

    /**
     * Form CAknForm
     * Processing Edit Form's menu event according to button id
     *
     * @since S60 v3.1
     * @param aButtonId the menu button Id
     * @return the processing result
     */
    TBool OkToExitL( TInt aButtonId );

    /**
     * Form CAknForm
     * Perform dynamic operations before layout
     *
     * @since S60 v3.1
     */
    void PreLayoutDynInitL();

private:

    /**
     * Operation Mode
     */    
    const TOperationType iOperationType;

    /**
     * Negative, is the mark of add operator. The others, is the mark of 
     * edit operator,in which means the index of TCountryData Data List 
     * of CCountryDataManager.
     */
    TInt iIndex;

    /**
     * The pointer of CCountryDataManager 
     * on which be created in CRoadMapDocument.
     * Not own.
     */
    CRoadMapDocument* iAppDoc ;
    
    /**
     * Use to confirm that the data is modified or not?
     */
    TBool& iIsModified;

    };

#endif //C_CEDITFORM_H

// End of File
