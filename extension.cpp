/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod Sample Extension
 * Copyright (C) 2004-2008 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#include "extension.h"

#define TAGLIB_STATIC
#include "soundfile.h"

IBaseFileSystem *basefilesystem;

/**
 * @file extension.cpp
 * @brief Implement extension code here.
 */

SoundLib g_SoundLib;		/**< Global singleton for extension's main interface */

SMEXT_LINK(&g_SoundLib);

class FileTypeHandler : public IHandleTypeDispatch
{
public:
	void OnHandleDestroy(HandleType_t type, void *object)
	{
		delete (SoundFile*)object;
	}
};

HandleType_t g_SoundFileType;
FileTypeHandler g_FileTypeHandler;

extern sp_nativeinfo_t g_Natives[];

bool SoundLib::SDK_OnLoad(char * error, size_t maxlength, bool late)
{
	g_SoundFileType = handlesys->CreateType("SoundFile", &g_FileTypeHandler, 0, NULL, NULL, myself->GetIdentity(), NULL);
	sharesys->AddNatives(myself, g_Natives);
	return true;
}

void SoundLib::SDK_OnUnload()
{
	handlesys->RemoveType(g_SoundFileType, myself->GetIdentity());
}

bool SoundLib::SDK_OnMetamodLoad(ISmmAPI * ismm, char * error, size_t maxlen, bool late)
{
	GET_V_IFACE_CURRENT(GetFileSystemFactory, basefilesystem, IBaseFileSystem, BASEFILESYSTEM_INTERFACE_VERSION);
	return true;
}
