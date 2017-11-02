/*
* ============================================================================
*  Name        : roadmap.pan
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

#ifndef P_ROADMAPPAN_H
#define P_ROADMAPPAN_H

/** RoadMap application panic codes */
enum TRoadMapPanics 
    {
    ERoadMapBasicUi = 7777
    // add further panics here
    };

inline void Panic(TRoadMapPanics aReason)
    {
    _LIT(applicationName,"RoadMap");
    User::Panic(applicationName, aReason);
    }

#endif // P_ROADMAPPAN_H
