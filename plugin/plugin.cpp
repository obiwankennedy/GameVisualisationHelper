/***************************************************************************
 *   Copyright (C) 2015 by Renaud Guezennec                                *
 *   http://renaudguezennec.homelinux.org/accueil,3.html                   *
 *                                                                         *
 *   rolisteam is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "teamspeak/public_definitions.h"
#include "teamspeak/public_errors.h"
#include "teamspeak/public_errors_rare.h"
#include "teamspeak/public_rare_definitions.h"
#include "ts3_functions.h"

#include "plugin.h"

#define PLUGIN_API_VERSION 23
#define PATH_BUFSIZE 512
#define COMMAND_BUFSIZE 128
#define INFODATA_BUFSIZE 128
#define SERVERINFO_BUFSIZE 256
#define CHANNELINFO_BUFSIZE 512
#define RETURNCODE_BUFSIZE 128

static struct TS3Functions ts3Functions;
static char* pluginID  = NULL;
static bool s_recording= false;

#define _strcpy(dest, destSize, src)      \
    {                                     \
        strncpy(dest, src, destSize - 1); \
        (dest)[destSize - 1]= '\0';       \
    }

const char* ts3plugin_name()
{
    return "Dbus Plugin";
}

const char* ts3plugin_version()
{
    return "1.2";
}

int ts3plugin_apiVersion()
{
    return PLUGIN_API_VERSION;
}

const char* ts3plugin_author()
{
    return "Rolisteam";
}

const char* ts3plugin_description()
{
    return "show avatar of the speaking user";
}

/* Set TeamSpeak 3 callback functions */
void ts3plugin_setFunctionPointers(const struct TS3Functions funcs)
{
    ts3Functions= funcs;
}

/*
 * Custom code called right after loading the plugin. Returns 0 on success, 1 on failure.
 * If the function returns 1 on failure, the plugin will be unloaded again.
 */
int ts3plugin_init()
{
    char appPath[PATH_BUFSIZE];
    char resourcesPath[PATH_BUFSIZE];
    char configPath[PATH_BUFSIZE];
    char pluginPath[PATH_BUFSIZE];

    ts3Functions.getAppPath(appPath, PATH_BUFSIZE);
    ts3Functions.getResourcesPath(resourcesPath, PATH_BUFSIZE);
    ts3Functions.getConfigPath(configPath, PATH_BUFSIZE);
    ts3Functions.getPluginPath(pluginPath, PATH_BUFSIZE, pluginID);

    printf("PLUGIN: App path: %s\nResources path: %s\nConfig path: %s\nPlugin path: %s\n", appPath, resourcesPath,
           configPath, pluginPath);

    return 0;
}

/* Custom code called right before the plugin is unloaded */
void ts3plugin_shutdown()
{
    /* Your plugin cleanup code here */
    printf("PLUGIN: shutdown\n");

    /* Free pluginID if we registered it */
    if(pluginID)
    {
        free(pluginID);
        pluginID= NULL;
    }
}

void ts3plugin_onUpdateClientEvent(uint64 serverConnectionHandlerID, anyID clientID, anyID invokerID,
                                   const char* invokerName, const char* invokerUniqueIdentifier)
{
    using namespace std;

    anyID ownID= 0;
    ts3Functions.getClientID(serverConnectionHandlerID, &ownID);
    if(ownID == 0 || ownID != clientID)
        return;

    int val= -1;
    ts3Functions.getClientVariableAsInt(serverConnectionHandlerID, clientID, CLIENT_IS_RECORDING, &val);
    if(val == 1)
    {
        if(s_recording) // record but in pause
        {
            printf("PLUGIN: inside if OnRecordStartPase\n");
            std::string str;
            str+= "dbus-send --type=method_call --session --dest=be.maartenbaert.ssr /  "
                  "local.PageRecord.OnRecordStartPause";
            system(str.c_str());
        }
        else
        {
            printf("PLUGIN: inside else recordedStart\n");
            std::string str2;
            str2+= "dbus-send --type=method_call --session --dest=be.maartenbaert.ssr /  "
                   "local.PageRecord.OnRecordStartPause";
            system(str2.c_str());
            s_recording= true;
        }
        /* std::string startAudioRecorder;
         startAudioRecorder +="audio-recorder -c start &";
         system(startAudioRecorder.c_str());*/
    }
    else
    {

        if(s_recording)
        {
            printf("PLUGIN: inside else val == 1 OnRecordStartPause\n");
            std::string str;
            str+= "dbus-send --type=method_call --session --dest=be.maartenbaert.ssr /  "
                  "local.PageRecord.OnRecordStartPause";
            system(str.c_str());
        }

        /* std::string startAudioRecorder;
         startAudioRecorder +="audio-recorder -c stop &";
         system(startAudioRecorder.c_str());*/

        /*std::string str2;
        str2 += "dbus-send --type=method_call --session --dest=org.rolisteam.display /  local.MainWindow.recordedStart";
        system(str2.c_str());*/
    }
}

void ts3plugin_onTalkStatusChangeEvent(uint64 serverConnectionHandlerID, int status, int isReceivedWhisper,
                                       anyID clientID)
{
    // printf("ts3plugin_onTalkStatusChangeEvent\n");
    /* Demonstrate usage of getClientDisplayName */
    char name[512];
    if(ts3Functions.getClientDisplayName(serverConnectionHandlerID, clientID, name, 512) == ERROR_ok)
    {
        if(status == STATUS_TALKING)
        {
            std::string str;
            str+= "dbus-send --type=method_call --session --dest=org.rolisteam.display /  "
                  "local.MainWindow.displayCorrectImage string:'";
            str+= name;
            str+= "'";

            system(str.c_str());
        }
        else
        {
            std::string str;
            str+= "dbus-send --type=method_call --session --dest=org.rolisteam.display /  local.MainWindow.hideImage "
                  "string:'";
            str+= name;
            str+= "'";

            system(str.c_str());
        }
    }
}
