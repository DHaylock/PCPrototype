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
            
            kkpdata.pK.player1StartKey = c["kenkenpa"]["playertriggerkeys"]["player1startkey"].asInt();
            kkpdata.pK.player1EndKey = c["kenkenpa"]["playertriggerkeys"]["player1endkey"].asInt();
            kkpdata.pK.player2StartKey = c["kenkenpa"]["playertriggerkeys"]["player2startkey"].asInt();
            kkpdata.pK.player2EndKey = c["kenkenpa"]["playertriggerkeys"]["player2endkey"].asInt();
            kkpdata.pK.dualPlayersStartKey = c["kenkenpa"]["playertriggerkeys"]["dualplayerstartkey"].asInt();
            kkpdata.pK.dualPlayersEndKey = c["kenkenpa"]["playertriggerkeys"]["dualplayersendkey"].asInt();
            
            kkpdata.mK.allStopKey = c["kenkenpa"]["triggerkeys"]["allstop"].asInt();
            kkpdata.mK.attractorModeKey = c["kenkenpa"]["triggerkeys"]["attractormode"].asInt();
            kkpdata.mK.explainerModeKey = c["kenkenpa"]["triggerkeys"]["explainermode"].asInt();
            kkpdata.mK.countdownModeKey = c["kenkenpa"]["triggerkeys"]["countdownmode"].asInt();
            kkpdata.mK.gameModeKey = c["kenkenpa"]["triggerkeys"]["gamemode"].asInt();
            kkpdata.mK.winModeKey = c["kenkenpa"]["triggerkeys"]["gamemode"].asInt();
        
            kkpdata.boostFile1 = c["kenkenpa"]["boost"]["boost1"].asString();
            kkpdata.boostFile2 = c["kenkenpa"]["boost"]["boost2"].asString();
            kkpdata.boostFile3 = c["kenkenpa"]["boost"]["boost3"].asString();
            kkpdata.boostFile4 = c["kenkenpa"]["boost"]["boost4"].asString();
            kkpdata.boost1StartKey = c["kenkenpa"]["boost"]["boost1startkey"].asInt();
            kkpdata.boost2StartKey = c["kenkenpa"]["boost"]["boost2startkey"].asInt();
            kkpdata.boost3StartKey = c["kenkenpa"]["boost"]["boost3startkey"].asInt();
            kkpdata.boost4StartKey = c["kenkenpa"]["boost"]["boost4startkey"].asInt();
            
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
