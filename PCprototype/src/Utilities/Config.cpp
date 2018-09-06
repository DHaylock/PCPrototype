//--------------------------------------------------------------
//  Config.h
//  wa_study_1
//  Created by David Haylock on 22/08/2018.
//! wa_study_1
/** Config Class */
//-------------------------------------------------------------

#include "Config.h"

//--------------------------------------------------------------
void Config::load()
{
    ofxJSONElement c;
    if (!c.open("config.json"))
    {
        PCMessage("Config Manager", "[Error]: Failed to Load Config");
        return;
    }
    else
    {
        PCMessage("Config Manager", "[Success]: Config File Loaded");
        
        // Load the Controllers
        if(c.isMember("area"))
        {
//            WAMessage("Config", "Area Parameters Found");
//            width = c["area"]["width"].asInt();
//            height = c["area"]["height"].asInt();
        }
    }
}
