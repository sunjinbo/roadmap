/*
* ============================================================================
*  Name        : basedata.h
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

#ifndef M_MBASEDATA_H
#define M_MBASEDATA_H

// FORWARD DECLARATIONS
class RReadStream;
class RWriteStream;


/**
 *  
 *  A interface only, all the data class which can be dirived from it
 *  
 *  @since S60 v3.1
 */
class MBaseData
    {

public: // Data types declaration

    /** Define a set of member data Id
     */
    enum TFieldType
        {
        EBufCode = 0,
        EBufName
        };

public: // New functions

    /**
     * 
     * Get a ref of the member data in terms of its Id 
     * 
     * @since S60 v3.1
     * @param aRStream a read stream buffer
     */
     virtual const TDes& Field( TFieldType aType ) const = 0;

    /**
     * 
     * Internalizes the MBaseData object data from the read stream
     * 
     * @since S60 v3.1
     * @param aRStream a read stream buffer
     */
     virtual void InternalizeL( RReadStream& aRStream ) = 0;

    /**
     * 
     * Externalises the MBaseData object data to the specified stream
     * 
     * @since S60 v3.1
     * @param aWStream a  write stream buffer
     */
     virtual void ExternalizeL( RWriteStream& aWStream ) const = 0;

    };

#endif // M_MBASEDATA_H

// End of File
