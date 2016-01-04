#include "stdafx.h"

class CBone{

public:
	char*       m_BoneName;       //0x00  
	char        pad_04[136];      //0x04
	D3DXMATRIX  BoneMatrix;       //0x8C  
	D3DXMATRIX  SomeMatrix;       //0xCC  
};


class CBoneInfo{

public:
	char       pad_00[20];
	DWORD      oneNum;            //0x14 
	CBone*     pBones;            //0x18 
};


class CSkeleton{

public:
	char       pad_00[40];
	CBoneInfo* BonePtr;           //0x28 
};

class CGameWorld
{
public:
	char _0x0000[8];
	__int32 m_Counter;             //0x0008 
	char _0x000C[32];
	DWORD m_MaxObjects;            //0x002C  XORed
	char _0x0030[20];
	DWORD m_ObjectList;            //0x0044  XORed

	DWORD GetMaxObjects()
	{
		return m_MaxObjects ^ XOR_OBJLIST_MAX;
	}

	DWORD GetObjectAddr(int id)
	{
		return 	(m_ObjectList ^ XOR_OBJLIST_PTR) + (id * 4);
	}
};

class CObject
{
public:

	char _0x0000[36]; //0x0000 
	D3DXVECTOR3 m_Position; //0x0024 
	char _0x0030[480]; //0x0030 
	int m_flags; //0x0210 
	char _0x0214[452]; //0x0214 
	DWORD m_NameXor; //0x03D8 
	char _0x03DC[60]; //0x03DC 
	int m_NameLength; //0x0418 
	char _0x041C[132]; //0x041C 
	int m_BackPackID; //0x04A0 
	int m_IsAlive; //0x04A4 
	char _0x04A8[12]; //0x04A8 
	float m_Health; //0x04B4 
	float m_Hunger; //0x04B8 
	float m_Thirst; //0x04BC 
	char _0x04C0[40]; //0x04C0 
	int m_LocalPlayerSafeZone; //0x04E8 
	char _0x04EC[2920]; //0x04EC 
	bool m_enableRendering; //0x1054 
	char _0x1055[3]; //0x1055 
	float standStillVisiblity; //0x1058 
	float walkVisibility; //0x105C 
	float runVisibility; //0x1060 
	float sprintVisibility; //0x1064 
	char _0x1068[16]; //0x1068 
	float walkNoise; //0x1078 
	float runNoise; //0x107C 
	float sprintNoise; //0x1080 
	float fireNoise; //0x1084 
	char _0x1088[8]; //0x1088 
	float smell; //0x1090 
	float smell2; //0x1094 
	char _0x1098[352]; //0x1098 
	CSkeleton* m_Skeleton; //0x11F8 
	int PlayerState; //0x11FC 
	int PlayerMoveDir; //0x1200 
	char _0x1204[12]; //0x1204 
	//CWeaponInfo* m_pWeaponPrimary; //0x1210 
	//CWeaponInfo* m_pWeaponSecondary; //0x1214 
	char _0x1218[20]; //0x1218 
	int m_SelectedWeapon; //0x122C 
	int m_PrevSelectedWeapon; //0x1230 
	bool m_isPressedFireTrigger; //0x1234 
	bool m_isAiming; //0x1235 
	bool m_isChnagedAiming1; //0x1236 
	bool m_isInScope; //0x1237 
	bool m_isFinishedAiming; //0x1238 
	char _0x1239[3]; //0x1239 
	float m_BloodTimer; //0x123C 
	char _0x1240[8]; //0x1240 
	float m_PickupTime; //0x1248 
	char _0x124C[32]; //0x124C 
	float lastRewardShowTime_; //0x126C 
	float bodyAdjust_x; //0x1270 
	float bodyAdjust_y[2]; //0x1274 
	int boneId_Bip01_Spine1; //0x127C 
	int boneId_Bip01_Spine2; //0x1280 
	int boneId_Bip01_Neck; //0x1284 
	int boneId_Bip01_LUpperArm; //0x1288 
	int boneId_Bip01_RUpperArm; //0x128C 
	int boneId_Bip01_Head; //0x1290 
	int boneId_Bip01_R_Hand; //0x1294 
	int boneId_Bip01_L_Hand; //0x1298 
	float m_SpeedBoost; //0x129C 
	float m_SpeedBoostTime; //0x12A0 
	float m_MorphineShotTime; //0x12A4 
	float m_BandagesEffectTime; //0x12A8 
	D3DXVECTOR3 plr_local_Velocity; //0x12AC 
	float plr_local_moving_speed; //0x12B8 
	float Height; //0x12BC 
	float m_Stamina; //0x12C0 
	float m_StaminaPenaltyTime; //0x12C4 
	char _0x12C8[16]; //0x12C8 
	float m_Breath; //0x12D8 
	float lastDamageRcvd; //0x12DC 
	float lastTimeHit; //0x12E0 
	int lastTimeHitBone; //0x12E4 
	D3DXVECTOR3 lastTimeHitForce; //0x12E8 
	float BloodEffect; //0x12F4 
	int bDead; //0x12F8 
	float TimeOfDeath; //0x12FC 
	//Items::STORE_CATEGORIES DeathDamageSource; //0x1300 
	D3DXVECTOR3 PosOfDeath; //0x1304 
	int TimeOfLastRespawn; //0x1310 
	int Dead_KillerID; //0x1314 
	bool DisableKillerView; //0x1318 
	bool bCrouch; //0x1319 
	bool bProne; //0x131A 
	bool bOnGround; //0x131B 
	float fHeightAboveGround; //0x131C 
	float JumpVelocity; //0x1320 
	float JumpStartTime; //0x1324 
	char _0x1328[8]; //0x1328 
	D3DXVECTOR3 m_vRecoilCameraAngles; //0x1330 
	char _0x133C[120]; //0x133C 
	float m_yaw; //0x13B4 
	float m_pitch; //0x13B8 
	char _0x13BC[12]; //0x13BC 
	float m_Speed; //0x13C8 
	float m_SpeedStrafe; //0x13CC 
	char _0x13D0[88]; //0x13D0 
	D3DXMATRIX m_BoneCoeff; //0x1428 
	D3DXMATRIX DrawFullMatrix; //0x1468 
	D3DXMATRIX DrawFullMatrix_Localized; //0x14A8 
	D3DXMATRIX MoveMatrix; //0x14E8 
	char _0x1528[16]; //0x1528 
	float afterRespawnTimer; //0x1538 
	float lastWeapDataRep; //0x153C 
	float lastTimeWeaponSwitch; //0x1540 
	D3DXVECTOR3 viewTargetPos; //0x1544 
	D3DXVECTOR3 viewTargetNorm; //0x1550 
	float m_ReticleTargetScale; //0x155C 
	float m_ReticleCurrentScale; //0x1560 
	bool m_isFemaleHero; //0x1564 
	char _0x1565[11]; //0x1565 
	bool bAllowToUseWeapons; //0x1570 
};