#include "SDK.h"

#define MELEE_COLOR				   Color(255, 255, 255)
#define WEAPON_COLOR			   Color(0, 255, 255)
#define THROWABLES_COLOR		   Color(255, 0, 255)
#define BACKPACKS_COLOR			   Color(200, 200, 255)
#define CONSUMABLES_COLOR		   Color(255, 255, 200)
#define ATTACHMENTS_COLOR		   Color(255, 150, 255)
#define BARRICADES_COLOR		   Color(100, 255, 150)
#define GEAR_COLOR				   Color(100, 50, 255)
#define FOOD_COLOR			       Color(100, 255, 150)
#define DRINKS_COLOR			   Color(100, 100, 125)
#define VEHICLES_COLOR			   Color(50, 50, 255)
#define RECIPES_COLOR			   Color(150, 200, 200)
#define CRAFTCOMPS_COLOR		   Color(200, 50, 50)

namespace SDK
{

	DWORD ItemCount = 0;
	DWORD PlayerCount = 0;
	DWORD ZombieCount = 0;
	DWORD CarCount = 0;

	DWORD ItemArray[350] = { 0 };
	DWORD PlayerArray[200] = { 0 };
	DWORD CarArray[20] = { 0 };

	DWORD SkeletonAddress = 0x11F8;
	DWORD BoneCoeffAddress = 0x1428;

	D3DXVECTOR3 GetBoneOrigin(DWORD pPlayer, int iBoneID)
	{
		D3DXMATRIX v6;
		D3DXMATRIX v7;
		D3DXMATRIX BoneMatrix;
		D3DXVECTOR3 Pos;

		D3DXMatrixRotationYawPitchRoll(&v6, 0.0, 1.5707963, 0.0);

		DWORD CSkeletonAddress = Memory::Read<DWORD>(pPlayer + SkeletonAddress);

		CSkeleton _pSkeleton = Memory::Read<CSkeleton>(CSkeletonAddress);
		CBoneInfo _pBoneInfo = Memory::Read<CBoneInfo>((DWORD)_pSkeleton.BonePtr);

		DWORD CBoneArrayAddress = (DWORD)_pBoneInfo.pBones;

		CBone Bone = Memory::Read<CBone>((DWORD)CBoneArrayAddress + (iBoneID * sizeof(CBone)));

		BoneMatrix = Bone.BoneMatrix;

		D3DXMATRIX BoneCoeff = Memory::Read<D3DXMATRIX>(pPlayer + BoneCoeffAddress);

		D3DXMatrixMultiply(&BoneMatrix, &BoneMatrix, &BoneCoeff);
		D3DXMatrixMultiply(&v7, &v6, &BoneMatrix);

		Pos.x = v7._41;
		Pos.y = v7._42;
		Pos.z = v7._43;

		return Pos;
	}

	float GetDistance(D3DXVECTOR3 Origin)
	{
		D3DXVECTOR3 me = Memory::Read<D3DXVECTOR3>(Memory::LocalPlayerAddress + 0x24);
		float tempx, tempy, tempz, tempA;

		tempx = (me.x - Origin.x)*(me.x - Origin.x);
		tempy = (me.y - Origin.y)*(me.y - Origin.y);
		tempz = (me.z - Origin.z)*(me.z - Origin.z);

		tempA = tempx + tempy + tempz;

		if (tempA < 0)
			tempA = (tempA * (-1));

		return sqrt(tempA);
	}

	void ListObjects()
	{
		CGameWorld CGameWo = Memory::Read<CGameWorld>(Memory::GameWorldAddress);
		int objMax = CGameWo.GetMaxObjects();
		DWORD Actual = 0;
		int type = 0;

		ItemCount = 0;
		PlayerCount = 0;
		ZombieCount = 0;
		CarCount = 0;

		for (int a = 0; a <= objMax; a++)
		{
			Actual = Memory::Read<DWORD>(CGameWo.GetObjectAddr(a));
			type   = Memory::Read<int>(Actual + 0x210);

			switch (type)
			{
			case Player:
				if (Actual != Memory::LocalPlayerAddress)
					PlayerArray[PlayerCount++] = Actual;
				break;
			case Zombie:
				ZombieCount++;
				break;
			case Cars:
				CarArray[CarCount++] = Actual;
				break;
			case Item:
				ItemArray[ItemCount++] = Actual;
				break;
			}
		}
	}

	cItems GetItemInfo(DWORD address, bool read)
	{
		char * id;
		DWORD ID = address;

		if (read)
			ID = Memory::Read<DWORD>(address + (DWORD)0x3B0);

		switch (ID)
		{
		case 101002: return {"M16", WEAPON_COLOR, I_WEAPON}; break;
		case 101005: return {"G36", WEAPON_COLOR, I_WEAPON}; break;
		case 101022: return {"AK-47M", WEAPON_COLOR, I_WEAPON}; break;
		case 101032: return {"AKM", WEAPON_COLOR, I_WEAPON}; break;
		case 101040: return {"M4 SEMI", WEAPON_COLOR, I_WEAPON}; break;
		case 101055: return {"M4", WEAPON_COLOR, I_WEAPON}; break;
		case 101169: return {"MASSADA", WEAPON_COLOR, I_WEAPON}; break;
		case 101172: return {"SIG SAUER 556", WEAPON_COLOR, I_WEAPON}; break;
		case 101173: return {"IMI TAR-21", WEAPON_COLOR, I_WEAPON}; break;
		case 101193: return {"FN SCAR CQC", WEAPON_COLOR, I_WEAPON}; break;
		case 101210: return {"FN SCAR NIGHT STALKER", WEAPON_COLOR, I_WEAPON}; break;
		case 101322: return {"Compound Crossbow", WEAPON_COLOR, I_WEAPON}; break;
		case 101332: return {"Kruger .22 Rifle", WEAPON_COLOR, I_WEAPON}; break;
		case 101334: return {"Kruger Mini-14", WEAPON_COLOR, I_WEAPON}; break;
		case 101341: return {"Mosin Nagant", WEAPON_COLOR, I_WEAPON}; break;

		//Melee Weapons
		case 101267: return {"Tactical Knife", MELEE_COLOR, I_MELEE}; break;
		case 101278: return {"Bat", MELEE_COLOR, I_MELEE}; break;
		case 101306: return {"Flashlight", MELEE_COLOR, I_MELEE}; break;
		case 101307: return {"Hammer", MELEE_COLOR, I_MELEE}; break;
		case 101308: return {"Hatchet", MELEE_COLOR, I_MELEE}; break;
		case 101309: return {"Pickaxe", MELEE_COLOR, I_MELEE}; break;
		case 101313: return {"Spiked Bat", MELEE_COLOR, I_MELEE}; break;
		case 101314: return {"Metal Bat", MELEE_COLOR, I_MELEE}; break;
		case 101335: return {"Kandy Kane", MELEE_COLOR, I_MELEE}; break;
		case 101336: return {"Katana", MELEE_COLOR, I_MELEE}; break;
		case 101337: return {"Jokoto Katana", MELEE_COLOR, I_MELEE}; break;
		case 101338: return {"Wakizashi", MELEE_COLOR, I_MELEE}; break;
		case 101339: return {"Machete", MELEE_COLOR, I_MELEE}; break;
		case 101343: return {"Brass Knuckles", MELEE_COLOR, I_MELEE}; break;
		case 101344: return {"Canoe Paddle", MELEE_COLOR, I_MELEE}; break;
		case 101345: return {"Cricket Bat", MELEE_COLOR, I_MELEE}; break;
		case 101346: return {"Shovel", MELEE_COLOR, I_MELEE}; break;
		case 101347: return {"Chainsaw", MELEE_COLOR, I_MELEE}; break;
		case 101381: return {"Butterfly Knife", MELEE_COLOR, I_MELEE}; break;
		case 101382: return {"Crowbar", MELEE_COLOR, I_MELEE}; break;
		case 101383: return {"Fire Axe", MELEE_COLOR, I_MELEE}; break;
		case 101384: return {"Frying Pan", MELEE_COLOR, I_MELEE}; break;
		case 101385: return {"Garden Shears", MELEE_COLOR, I_MELEE}; break;
		case 101386: return {"Golf Club", MELEE_COLOR, I_MELEE}; break;
		case 101388: return {"Pitchfork", MELEE_COLOR, I_MELEE}; break;
		case 101389: return {"Police Baton", MELEE_COLOR, I_MELEE}; break;
		case 101390: return {"Power Drill", MELEE_COLOR, I_MELEE}; break;
		case 101391: return {"Wrench", MELEE_COLOR, I_MELEE}; break;
		case 101398: return {"Bare Hands", MELEE_COLOR, I_MELEE}; break;
		case 101401: return {"The Brothethood", MELEE_COLOR, I_MELEE}; break;
		case 101402: return {"Shank", MELEE_COLOR, I_MELEE}; break;
		case 101406: return {"Excessive Force", MELEE_COLOR, I_MELEE}; break;
		case 101407: return {"Clean Sweep", MELEE_COLOR, I_MELEE}; break;
		case 101408: return {"Harvesting Tool", MELEE_COLOR, I_MELEE}; break;
		case 101409: return {"Premium Harvesting Tool", MELEE_COLOR, I_MELEE}; break;

		//Machine Guns
		case 101060: return {"PKM", WEAPON_COLOR, I_WEAPON}; break;
		case 101093: return {"RPK-74", WEAPON_COLOR, I_WEAPON}; break;
		case 101095: return {"FN M249", WEAPON_COLOR, I_WEAPON}; break;
		case 101197: return {"RA H23", WEAPON_COLOR, I_WEAPON}; break;

		//Snipers
		case 101068: return {"SVD", WEAPON_COLOR, I_WEAPON}; break;
		case 101084: return {"VSS VINTOREZ", WEAPON_COLOR, I_WEAPON}; break;
		case 101085: return {"MAUSER SP66", WEAPON_COLOR, I_WEAPON}; break;
		case 101087: return {"AW Magnum", WEAPON_COLOR, I_WEAPON}; break;
		case 101088: return {"M107", WEAPON_COLOR, I_WEAPON}; break;
		case 101217: return {"MAUSER SRG DESERT", WEAPON_COLOR, I_WEAPON}; break;
		case 101247: return {"BLASER R93", WEAPON_COLOR, I_WEAPON}; break;

		//Shotguns
		case 101098: return {"SAIGA", WEAPON_COLOR, I_WEAPON}; break;
		case 101158: return {"MOSSBERG 590", WEAPON_COLOR, I_WEAPON}; break;
		case 101183: return {"KT DECIDER", WEAPON_COLOR, I_WEAPON}; break;
		case 101200: return {"AA-12", WEAPON_COLOR, I_WEAPON}; break;
		case 101321: return {"Double Barrel", WEAPON_COLOR, I_WEAPON}; break;

		//Submachine Guns
		case 101035: return {"AKS-74U", WEAPON_COLOR, I_WEAPON}; break;
		case 101063: return {"MP7", WEAPON_COLOR, I_WEAPON}; break;
		case 101064: return {"UZI", WEAPON_COLOR, I_WEAPON}; break;
		case 101103: return {"MP5/10", WEAPON_COLOR, I_WEAPON}; break;
		case 101106: return {"Honey Badger", WEAPON_COLOR, I_WEAPON}; break;
		case 101107: return {"FN P90", WEAPON_COLOR, I_WEAPON}; break;
		case 101108: return {"EVO-3", WEAPON_COLOR, I_WEAPON}; break;
		case 101109: return {"BIZON", WEAPON_COLOR, I_WEAPON}; break;
		case 101201: return {"VERESK SR-2", WEAPON_COLOR, I_WEAPON}; break;
		case 101246: return {"FN P90S", WEAPON_COLOR, I_WEAPON}; break;

		//Hand Guns
		case 101004: return {"FN Five Seven", WEAPON_COLOR, I_WEAPON}; break;
		case 101111: return {"B92", WEAPON_COLOR, I_WEAPON}; break;
		case 101112: return {"B93R", WEAPON_COLOR, I_WEAPON}; break;
		case 101115: return {"Jericho 9mm", WEAPON_COLOR, I_WEAPON}; break;
		case 101120: return {"Sig Sauer P226", WEAPON_COLOR, I_WEAPON}; break;
		case 101180: return {"Desert Eagle", WEAPON_COLOR, I_WEAPON}; break;
		case 101224: return {"STI Eagle Elite .45 ACP", WEAPON_COLOR, I_WEAPON}; break;
		case 101320: return {"Flare Gun", WEAPON_COLOR, I_WEAPON}; break;
		case 101330: return {"Kruger .22", WEAPON_COLOR, I_WEAPON}; break;
		case 101331: return {"Anaconda", WEAPON_COLOR, I_WEAPON}; break;
		case 101342: return {"1911", WEAPON_COLOR, I_WEAPON}; break;
		case 101392: return {"Nail Gun", WEAPON_COLOR, I_WEAPON}; break;

		//Throwables
		case 101310: return {"Grenade", THROWABLES_COLOR, I_THROWABLE}; break;
		case 101311: return {"Chemlight White", THROWABLES_COLOR, I_THROWABLE}; break;
		case 101312: return {"Flare", THROWABLES_COLOR, I_THROWABLE}; break;
		case 101325: return {"Chemlight Blue", THROWABLES_COLOR, I_THROWABLE}; break;
		case 101326: return {"Chemlight Green", THROWABLES_COLOR, I_THROWABLE}; break;
		case 101327: return {"Chemlight Orange", THROWABLES_COLOR, I_THROWABLE}; break;
		case 101328: return {"Chemlight Red", THROWABLES_COLOR, I_THROWABLE}; break;
		case 101329: return {"Chemlight Yellow", THROWABLES_COLOR, I_THROWABLE}; break;
		case 101403: return {"Bada Boom!", THROWABLES_COLOR, I_THROWABLE}; break;
		case 101404: return {"Trip Bada Boom!", THROWABLES_COLOR, I_THROWABLE}; break;

		//Backpacks
		case 20175: return {"Medium Backpack", BACKPACKS_COLOR, I_BACKPACK}; break;
		case 20176: return {"Small Backpack", BACKPACKS_COLOR, I_BACKPACK}; break;
		case 20179: return {"Large Backpack", BACKPACKS_COLOR, I_BACKPACK}; break;
		case 20180: return {"Military Ruck", BACKPACKS_COLOR, I_BACKPACK}; break;
		case 20181: return {"Teddy Bear backpack", BACKPACKS_COLOR, I_BACKPACK}; break;
		case 20185: return {"ALICE Rucksack", BACKPACKS_COLOR, I_BACKPACK}; break;
		case 20196: return {"GS Special BackPack", BACKPACKS_COLOR, I_BACKPACK}; break;
		case 20200: return {"Santa's Sack", BACKPACKS_COLOR, I_BACKPACK}; break;

		//Consumables & Usable Items
		case 301321: return{ "Gasoline", CONSUMABLES_COLOR, I_CONSUMABLE }; break;
		case 101256: return {"Antibiotics", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101261: return {"Bandages", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101262: return {"Bandages DX", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101300: return {"Pain killers", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101301: return {"Zombie Repellent", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101302: return {"C01-Vaccine", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101303: return {"C04-Vaccine", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101304: return {"Medkit", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101305: return {"Time Capsule", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101315: return {"Binoculars", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101316: return {"Barb wire barricade", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101317: return {"Wood shield barricade", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101318: return {"Riot shield", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101319: return {"Range Finder", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101323: return {"Air Horn", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101324: return {"Sandbag barricade", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101348: return {"Personal locker", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101352: return {"Wooden door", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101353: return {"Metal wall", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101354: return {"Tall brick wall", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101355: return {"Wooden wall", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101356: return {"Short brick wall", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101357: return {"Farm", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101358: return {"Industrial power generator", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101359: return {"Small power generator", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101360: return {"Solar water purifier", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101361: return {"Placeable light", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101362: return {"Bag of Chips farm block", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101399: return {"Repair Kit", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101400: return {"Premium Repair Kit", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101405: return {"Poultice", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101416: return {"ZB Riot", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 101417: return {"ZB Basic", CONSUMABLES_COLOR, I_CONSUMABLE}; break;
		case 1196379204: return {"Money", CONSUMABLES_COLOR, I_CONSUMABLE}; break;

		//Attachments
		case 400000: return {"Forward Grip", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400001: return {"5.45 AK 30", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400003: return {"ACOG", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400004: return {"Rifle Laser", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400005: return {"Holographic", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400007: return {"Kobra", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400008: return {"Tactical Sniper Scope", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400009: return {"SMG Grip", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400010: return {"STANAG 60", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400012: return {"Flash Hider", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400013: return {"Silencer", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400015: return {"STANAG 45", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400016: return {"STANAG 30", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400017: return {"STANAG C-Mag", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400018: return {"Rifle Flashlight", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400019: return {"Compact Scope", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400020: return {"Red Dot SP", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400021: return {"Pistol laser", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400022: return {"Pistol Flashlight", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400023: return {"Reflex Sight", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400027: return {"PSO-1", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400029: return {"G36 Ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400030: return {"VSS-20", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400031: return {"VSS-10", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400032: return {"MP7-40", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400033: return {"MP7-30", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400034: return {"9x19 Para Mag", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400038: return {"Blackwater Long Range", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400039: return {"Swiss Arms Scope x8", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400043: return {"AWM .338 Magnum ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400046: return {"P90 50 Rounds", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400047: return {"Bizon 64 ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400048: return {"SVD ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400049: return {"CZ Scorpion EVO-3 ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400050: return {"AA-12 Drum", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400069: return {"5.45 AK 45", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400070: return {".308 Winchester Sniper rifle ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400071: return {"9mm Mag", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400073: return {"Saiga 10 ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400079: return {"MP5 10mm Mag", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400084: return {"SMG-20 ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400085: return {"SMG-40 ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400086: return {"Desert Eagle ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400087: return {"FN57 ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400088: return {"Modular Aluminum Combat Grip", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400099: return {"G36 C-Mag", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400100: return {"5.45 AK Drum", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400101: return {"7.62 AKM magazine", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400133: return {".50 BMG", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400135: return {".45 ACP STI Eagle Elite ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400136: return {"12 Gauge Ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400139: return {"Arrow Explosive", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400140: return {"Arrow", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400141: return {"Shotgun shell 2x", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400143: return {"M249 Ammo Box", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400144: return {".22 Caliber Clip", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400145: return {"Anaconda rounds", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400146: return {"Large Kruger Rifle Clip", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400147: return {"Medium Kruger Rifle Clip", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400148: return {"Standard Kruger .22 Rifle Clip", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400150: return {"Kruger Mini-14 clip", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400152: return {"Flare gun ammo", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400153: return {"Standard Mosin Magazine", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400154: return {".40 caliber 1911 mag", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400156: return {"Pistol Silencer", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400157: return {"Nail Strip", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400158: return {"PKM Ammo Box", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;
		case 400159: return {"The Cleaner", ATTACHMENTS_COLOR, I_ATTACHEMENT}; break;

		//Gear
		case 20006: return {"K. Style Helmet", GEAR_COLOR, I_GEAR}; break;
		case 20015: return {"Custom Guerilla", BARRICADES_COLOR, I_GEAR}; break;
		case 20022: return {"Beret Cover", GEAR_COLOR, I_GEAR}; break;
		case 20023: return {"Boonie Cover", GEAR_COLOR, I_GEAR}; break;
		case 20025: return {"Shadow", GEAR_COLOR, I_GEAR}; break;
		case 20032: return {"Black Mask", GEAR_COLOR, I_GEAR}; break;
		case 20033: return {"Clown Mask", GEAR_COLOR, I_GEAR}; break;
		case 20034: return {"Jason Mask", GEAR_COLOR, I_GEAR}; break;
		case 20035: return {"Skull Mask", GEAR_COLOR, I_GEAR}; break;
		case 20036: return {"Slash Mask", GEAR_COLOR, I_GEAR}; break;
		case 20041: return {"Boonie Desert", GEAR_COLOR, I_GEAR}; break;
		case 20042: return {"Boonie Green", GEAR_COLOR, I_GEAR}; break;
		case 20043: return {"M9 helmet black", GEAR_COLOR, I_GEAR}; break;
		case 20046: return {"M9 Helmet with Goggles", GEAR_COLOR, I_GEAR}; break;
		case 20047: return {"M9 Helmet Green", GEAR_COLOR, I_GEAR}; break;
		case 20048: return {"M9 Helmet Urban", GEAR_COLOR, I_GEAR}; break;
		case 20049: return {"M9 Helmet Forest 1", GEAR_COLOR, I_GEAR}; break;
		case 20050: return {"M9 Helmet Goggles 1", GEAR_COLOR, I_GEAR}; break;
		case 20054: return {"IBA Sand", BARRICADES_COLOR, I_GEAR}; break;
		case 20056: return {"MTV Forest", BARRICADES_COLOR, I_GEAR}; break;
		case 20059: return {"Light Gear Forest", BARRICADES_COLOR, I_GEAR}; break;
		case 20067: return {"K Style NVG", GEAR_COLOR, I_GEAR}; break;
		case 20096: return {"Boonie Hat Leather", GEAR_COLOR, I_GEAR}; break;
		case 20097: return {"Fireman Helmet", GEAR_COLOR, I_GEAR}; break;
		case 20098: return {"Hard Hat", GEAR_COLOR, I_GEAR}; break;
		case 20177: return {"Gas Mask", GEAR_COLOR, I_GEAR}; break;
		case 20178: return {"Gas Mask 2", GEAR_COLOR, I_GEAR}; break;
		case 20187: return {"NVG Goggles", GEAR_COLOR, I_GEAR}; break;
		case 20188: return {"Night vision civilian", GEAR_COLOR, I_GEAR}; break;
		case 20192: return {"Helloween Special!", GEAR_COLOR, I_GEAR}; break;
		case 20197: return {"Christmas Special", GEAR_COLOR, I_GEAR}; break;
		case 20198: return {"Santa's Lil Helper", GEAR_COLOR, I_GEAR}; break;
		case 20199: return {"Captain Jack Frost", GEAR_COLOR, I_GEAR}; break;
		case 20204: return {"Uncle Sam Blue", GEAR_COLOR, I_GEAR}; break;
		case 20205: return {"Uncle Sam Red", GEAR_COLOR, I_GEAR}; break;
		case 20206: return {"Improvised Gas Mask", GEAR_COLOR, I_GEAR}; break;
		case 20210: return {"Artgaymiss Knives Hat", GEAR_COLOR, I_GEAR}; break;
		case 20211: return {"Dakotaz Wolf Hat", GEAR_COLOR, I_GEAR}; break;

		//Food and Drinks
		case 101283: return {"Bag of Chips", FOOD_COLOR, I_FOOD}; break;
		case 101284: return {"Bag MRE", FOOD_COLOR, I_FOOD}; break;
		case 101285: return {"Instant Oatmeal", FOOD_COLOR, I_FOOD}; break;
		case 101286: return {"Coconut Water", DRINKS_COLOR, I_FOOD}; break;
		case 101288: return {"Chocolate Bar", FOOD_COLOR, I_FOOD}; break;
		case 101289: return {"Granola Bar", FOOD_COLOR, I_FOOD}; break;
		case 101290: return {"Can of Pasta", FOOD_COLOR, I_FOOD}; break;
		case 101291: return {"Can of Soup", FOOD_COLOR, I_FOOD}; break;
		case 101292: return {"Can of Ham", FOOD_COLOR, I_FOOD}; break;
		case 101293: return {"Can of Tuna", FOOD_COLOR, I_FOOD}; break;
		case 101294: return {"Energy drink", DRINKS_COLOR, I_FOOD}; break;
		case 101295: return {"Electro-AID", DRINKS_COLOR, I_FOOD}; break;
		case 101296: return {"Can of soda", DRINKS_COLOR, I_FOOD}; break;
		case 101297: return {"Juice", DRINKS_COLOR, I_FOOD}; break;
		case 101298: return {"Water 1L", DRINKS_COLOR, I_FOOD}; break;
		case 101299: return {"Water 375ml", DRINKS_COLOR, I_FOOD}; break;
		case 101340: return {"MiniSaints", FOOD_COLOR, I_FOOD}; break;

		//Vehicles
		case 101412: return {"Buggy", VEHICLES_COLOR, I_VEHICLES}; break;
		case 101413: return {"Stryker", VEHICLES_COLOR, I_VEHICLES}; break;
		case 101414: return {"Zombie Killer Car", VEHICLES_COLOR, I_VEHICLES}; break;
		case 101415: return {"T80 Tank", VEHICLES_COLOR, I_VEHICLES}; break;

		//Recipes
		case 301340: return {"Poultice Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301341: return {"The Cleaner Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301342: return {"Brotherhood Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301343: return {"Excessive Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301344: return {"Gas Mask Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301345: return {"Shank Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301346: return {"Clean Sweep Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301347: return {"Bada Boom! Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301348: return {"Trip Bada Boom! Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301389: return {"Wooden Door Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301390: return {"Metal Wall Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301391: return {"Brick Wall Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301392: return {"Wood Wall Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301393: return {"Short Brick Wall Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301394: return {"Farm Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301395: return {"Solar Water Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301396: return {"Light Recipe", RECIPES_COLOR, I_RECIPES}; break;
		case 301397: return {"Small Power Generator", RECIPES_COLOR, I_RECIPES}; break;
		case 301398: return {"Large Power Generator", RECIPES_COLOR, I_RECIPES}; break;

		//Crafting Components
		case 301317: return {"Battery", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301318: return {"Empty Can", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301319: return {"Duct Tape", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301320: return {"Empty Bottle", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301322: return {"Glass Bottle", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301323: return {"Glue", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301324: return {"Gun Powder", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301325: return {"Empty Jerry Can", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301326: return {"Liquor", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301327: return {"Metal Scrap", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301328: return {"Nails", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301329: return {"Oil", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301330: return {"Potatoes", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301331: return {"Rag", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301332: return {"Barbed Wire", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301333: return {"Red Wine", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301334: return {"Salt", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301335: return {"Scissors", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301336: return {"Wrist Watch", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301337: return {"Wire", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301339: return {"Thread", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301349: return {"Acid", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301350: return {"Aerosol Spray", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301351: return {"Aluminum Foil", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301352: return {"Ammunition", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301353: return {"Ammonia", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301354: return {"Belt", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301355: return {"Broom", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301356: return {"Car Battery", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301357: return {"Charcoal", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301358: return {"Cig Lighter", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301359: return {"Drain Cleaner", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301360: return {"Fat", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301361: return {"Fireworks", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301362: return {"Jumper Cables", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301363: return {"Ketchup", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301364: return {"Lime", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301365: return {"Metal Pipe", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301366: return {"Ointment", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301367: return {"PVC Pipe", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301368: return {"Paint Stirrer", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301369: return {"Propane Canister", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301370: return {"Rope", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301371: return {"Rubber Tubes", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301372: return {"Saw Blade", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301373: return {"Sewing Kit", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301374: return {"Soap", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301375: return {"Sticks", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301376: return {"Sugar", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301377: return {"Syringe", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301378: return {"Tar", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301379: return {"Thermite", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301380: return {"Vinegar", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301386: return {"Metal", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301387: return {"Stone", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		case 301388: return {"Wood", CRAFTCOMPS_COLOR, I_CRAFTCOMPONENTS}; break;
		}

		return{ "", Color(0, 0, 0), 255 };
	}
}