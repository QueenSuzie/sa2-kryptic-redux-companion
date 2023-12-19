/**************************************************************************************
 *   main.cpp  --  This file is part of Kryptic Redux Companion.                      *
 *                                                                                    *
 *   Copyright (C) 2023 Queen Suzie                                                   *
 *                                                                                    *
 *   Kryptic Redux Companion is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published                *
 *   by the Free Software Foundation, either version 3 of the License,                *
 *   or (at your option) any later version.                                           *
 *                                                                                    *
 *   Kryptic Redux Companion is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty                      *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                          *
 *   See the GNU General Public License for more details.                             *
 *                                                                                    *
 *   You should have received a copy of the GNU General Public License                *
 *   along with this program.  If not, see http://www.gnu.org/licenses/.              *
 *                                                                                    *
 *************************************************************************************/

#include "pch.h"
#include "SA2ModLoader/FunctionHook.h"

FunctionHook<void, EmeManObj2*> hInitEmeralds((intptr_t)EmeraldLocations_1POr2PGroup3);

void InitEmeralds(EmeManObj2* a1) {
	hInitEmeralds.Original(a1);
	if (CurrentLevel == LevelIDs_WildCanyon) {
		for (auto& obj : SETObjects) {
			if (obj.SETEntry && obj.SETEntry->ID == 39 && obj.SETEntry->XRot == 0) {
				obj.field_1 = '\x1';
			} else if (obj.SETEntry && obj.SETEntry->ID == 39) {
				obj.SETEntry->Position.x = -1000;
				obj.SETEntry->Position.y = -1000;
				obj.SETEntry->Position.z = -1000;
			}
		}
	}
}

extern "C" {
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions) {
		hInitEmeralds.Hook(InitEmeralds);
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer }; // This is needed for the Mod Loader to recognize the DLL.
}