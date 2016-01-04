#include "CEngine.h"

CEngine* g_pEngine = new CEngine();

int CEngine::getBombIndex( void )
{
	return 0;
}

int CEngine::getBombOwner(void)
{
	return Memory::Read<int>(Memory::Read<DWORD>(Memory::GetModule("engine") + cEngine) + 0x1B934384);
}

Vector CEngine::ViewAngles( void )
{
	return Memory::Read<Vector>( Memory::Read<DWORD>( Memory::GetModule( "engine" ) + cEngine ) + cViewAngles );
}