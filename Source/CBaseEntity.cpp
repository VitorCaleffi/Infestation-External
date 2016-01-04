#include "CBaseEntity.h"

DWORD CWeaponBase;
int WeaponID;

CBaseEntity::CBaseEntity(int nIndex)
{
	this->dwEntity = Memory::Read<DWORD>((Memory::GetModule("client") + cEntityList + nIndex * 0x10) - 0x10);
	this->iIndex = nIndex;


	DWORD RadarStruct = Memory::Read<DWORD>(Memory::GetModule("client") + cRadarStruct);
	RadarStruct = Memory::Read<DWORD>(RadarStruct + 0x50);

	uintptr_t pNext = Memory::Readçççççççç<uintptr_t>(this->dwEntity + 8);
	pNext = Memory::Read<uintptr_t>(pNext + 8);
	pNext = Memory::Read<uintptr_t>(pNext + 1);
	pNext = Memory::Read<uintptr_t>(pNext + 8);

	ReadProcessMemory(Memory::hProcess, LPCVOID(pNext), &this->ClassName, sizeof(this->ClassName), NULL);

	ReadProcessMemory(Memory::hProcess, LPCVOID(RadarStruct + (0x1E0 * this->iIndex + 0x24)), &this->Name, sizeof(this->Name), NULL);
}

bool CBaseEntity::isDefusing()
{
	return Memory::Read<bool>(dwEntity + 0x1BD8);
}

bool CBaseEntity::BombOwner(void)
{
	return Memory::Read<bool>(dwEntity + 0x1BFC);
}
bool CBaseEntity::IsValid( void )
{
	return( this->dwEntity && this->m_iHealth() > 0 && this->m_lifeState() == 0 );
}
bool CBaseEntity::IsVisible( void )
{
	return Memory::Read<bool>( dwEntity + 0x935 );
}
BYTE CBaseEntity::m_fFlags( void )
{
	return Memory::Read<BYTE>( dwEntity + c_fFlags );
}
BYTE CBaseEntity::m_lifeState( void )
{
	return Memory::Read<BYTE>( dwEntity + c_lifeState );
}
DWORD CBaseEntity::getEntity( void )
{
	return this->dwEntity;
}
DWORD CBaseEntity::TeamColor( void )
{
	if( this->m_iTeamNum() == 3 )
		return Color( 0, 176, 255 ).HEX();
	return Color( 255, 0, 0 ).HEX();
}
int CBaseEntity::m_Money(void)
{
	return Memory::Read<int>(dwEntity + 0x234C);
}
int CBaseEntity::getIndex( void )
{
	return this->iIndex;
}
int CBaseEntity::m_iHealth( void )
{
	return Memory::Read<int>( dwEntity + c_iHealth );
}
int CBaseEntity::m_iTeamNum( void )
{
	return Memory::Read<int>( dwEntity + c_iTeamNum );
}
matrix3x4_t CBaseEntity::BoneData( int iBone )
{
	return Memory::Read<matrix3x4_t>( Memory::Read<DWORD>( dwEntity + cBoneMatrix ) + 0x30 * iBone );
}
Vector CBaseEntity::EyePosition( void )
{
	return ( this->m_vecOrigin() + this->m_vecViewOffset() );
}
Vector CBaseEntity::m_vecOrigin( void )
{
	return Memory::Read<Vector>( dwEntity + c_vecOrigin );
}
Vector CBaseEntity::m_vecViewOffset( void )
{
	return Memory::Read<Vector>( dwEntity + c_vecViewOffset );
}
void CBaseEntity::getTeamColor( Color& cOut )
{
	cOut = Color( this->TeamColor() );
}
void CBaseEntity::getEyePosition( Vector& vOut )
{
	vOut = this->EyePosition();
}
void CBaseEntity::getBoneData( int iBone, matrix3x4_t& m3x4Out )
{
	m3x4Out = this->BoneData( iBone );
}

Vector CBaseEntity::WeaponClassOr()
{
	DWORD ActualWeaponID = Memory::Read<DWORD>(this->dwEntity + 0x12B8) & 0xFFF;
	DWORD WeaponClass = Memory::Read<DWORD>(Memory::GetModule("client") + cEntityList + (-0x10 + (ActualWeaponID * 0x10)));
	return Memory::Read<Vector>(WeaponClass + c_vecViewOffset);
}

int CBaseEntity::WeaponName(void)
{
	char WeaponClassName[10];
	int WeaponHandle;
	int WeaponIDFirst;
	int i = 0;


	WeaponHandle = Memory::Read<int>(this->dwEntity + 0x12C0);
	WeaponIDFirst = WeaponHandle & 0xFFF;
	CWeaponBase = Memory::Read<DWORD>(Memory::GetModule("client") + cEntityList + (-0x10 + (WeaponIDFirst * 0x10)));
	WeaponID = Memory::Read<int>(CWeaponBase + 0x1684);

	return (WeaponID < 50) ? WeaponID : 0;
}