#include "stdafx.h"
#include "Threads.h"

CThreads thread;

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	if( Memory::Initialize( "Infestation.exe" ) )
	{
		//Pega os endereços padrões
		Memory::GetGame();
		Memory::GetGameWorld();
		Memory::GetLocalPlayer();
		//thread para listar objetos
		thread.SetInterval(5000, SDK::ListObjects);
		//inicializa menu
		Explorer::Init();
	}
	else
	{
		MessageBoxA( NULL, "Processo nao encontrado", "Error [01]", MB_ICONERROR );
		return NULL;
	}

	if (SUCCEEDED(Direct3D9::CreateOverlay(Memory::hWindow, "ViHAO")))
	{
		while( Direct3D9::Render() )
		{
			Sleep( 5 );
		}
	}
	return NULL;
}