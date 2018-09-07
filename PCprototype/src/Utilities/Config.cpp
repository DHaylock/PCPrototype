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
        if(c.isMember("kenkenpa"))
        {
            PCMessage("Config Manager", "[Success]: Ken Ken Pa Config Found");
            kkpdata.player1StartKey = c["kenkenpa"]["player1startkey"].asInt();
            kkpdata.player1EndKey = c["kenkenpa"]["player1endkey"].asInt();
            kkpdata.player2StartKey = c["kenkenpa"]["player2startkey"].asInt();
            kkpdata.player2EndKey = c["kenkenpa"]["player2endkey"].asInt();
            kkpdata.dualPlayersStartKey = c["kenkenpa"]["dualplayerstartkey"].asInt();
            kkpdata.dualPlayersEndKey = c["kenkenpa"]["dualplayersendkey"].asInt();
            
            vector<KenKenPa> kkd;
            // Get the Versions
            for (int i = 0; i < c["kenkenpa"]["versions"].size(); i++)
            {
                kkd.push_back(KenKenPa(c["kenkenpa"]["versions"][i]["id"].asInt(),
                                c["kenkenpa"]["versions"][i]["name"].asString(),
                                c["kenkenpa"]["versions"][i]["waitouttimer"].asInt(),
                                c["kenkenpa"]["versions"][i]["attractortimer"].asInt(),
                                c["kenkenpa"]["versions"][i]["attractor"].asString(),
                                c["kenkenpa"]["versions"][i]["kiosk"].asString(),
                                c["kenkenpa"]["versions"][i]["reward"].asString()));
            }
            
            kkpdata.versions = kkd;
        }
        else {
            PCMessage("Config Manager", "[Error]: No kenkenpa config found");
        }
    }
}

//--------------------------------------------------------------
KenKenPaData Config::getKenKenPa()
{
    return kkpdata;
}
