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

#include "public_errors.h"
#include "public_errors_rare.h"
#include "public_definitions.h"
#include "public_rare_definitions.h"
#include "ts3_functions.h"

#include "plugin.h"

#define PLUGIN_API_VERSION 20
#define PATH_BUFSIZE 512
#define COMMAND_BUFSIZE 128
#define INFODATA_BUFSIZE 128
#define SERVERINFO_BUFSIZE 256
#define CHANNELINFO_BUFSIZE 512
#define RETURNCODE_BUFSIZE 128

static struct TS3Functions ts3Functions;
static char* pluginID = NULL;

const char* ts3plugin_name()
{
    return "Speaker Plugin";
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
    ts3Functions = funcs;
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


    printf("PLUGIN: App path: %s\nResources path: %s\nConfig path: %s\nPlugin path: %s\n", appPath, resourcesPath, configPath, pluginPath);

    return 0;
}

/* Custom code called right before the plugin is unloaded */
void ts3plugin_shutdown() {
    /* Your plugin cleanup code here */
    printf("PLUGIN: shutdown\n");



    /* Free pluginID if we registered it */
    if(pluginID)
    {
        free(pluginID);
        pluginID = NULL;
    }
}
void ts3plugin_onTalkStatusChangeEvent(uint64 serverConnectionHandlerID, int status, int isReceivedWhisper, anyID clientID)
{
    /* Demonstrate usage of getClientDisplayName */
    char name[512];
    if(ts3Functions.getClientDisplayName(serverConnectionHandlerID, clientID, name, 512) == ERROR_ok)
    {
        if(status == STATUS_TALKING)
        {
            std::string str;
            str += "dbus-send --type=method_call --session --dest=org.rolisteam.display /  local.MainWindow.displayCorrectImage string:'";
            str += name;
            str += "'";

            system(str.c_str());
        }
	else if(status == STATUS_NOT_TALKING)
	{
            std::string str;
            str += "dbus-send --type=method_call --session --dest=org.rolisteam.display /  local.MainWindow.hideImage string:'";
            str += name;
            str += "'";

            system(str.c_str());

	}
    }
}
/*
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}*/
