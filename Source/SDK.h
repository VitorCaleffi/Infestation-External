#pragma once
#include "stdafx.h"

#define Player 0x21
#define Zombie 0x20001
#define Cars   0x250005
#define Item   0x240005

namespace SDK
{
	extern DWORD ItemCount;
	extern DWORD PlayerCount;
	extern DWORD ZombieCount;
	extern DWORD CarCount;

	extern DWORD ItemArray[350];
	extern DWORD PlayerArray[200];
	extern DWORD CarArray[20];

	enum ITEM_CATEGORIES
	{
		I_GEAR,
		I_CONSUMABLE,
		I_FOOD,
		I_THROWABLE,
		I_WEAPON,
		I_MELEE,
		I_ATTACHEMENT,
		I_BACKPACK,
		I_BARRICADES,
		I_VEHICLES,
		I_RECIPES,
		I_CRAFTCOMPONENTS,
		I_UNKNOWN
	};

	typedef struct
	{
		char * name;
		Color color;
		int type;
	}cItems;

	extern cItems GetItemInfo(DWORD address, bool read);

	extern D3DXVECTOR3 GetBoneOrigin(DWORD pPlayer, int iBoneID);
	extern float GetDistance(D3DXVECTOR3 Origin);
	extern void ListObjects();
}

