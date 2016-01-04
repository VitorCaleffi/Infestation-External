#include "Direct3D9.h"
#include "Visuals.h"


namespace Direct3D9
{
	bool Render( void )
	{
		static bool bInit = false;

		DWORD renderBase = Memory::Read<DWORD>(Memory::baseAddress + Renderer);
		ReadProcessMemory(Memory::hProcess, LPCVOID(renderBase + 0x1A0), &pVisuals->Matrix, sizeof(pVisuals->Matrix), NULL);

		if( !bInit )
		{
			bInit = true;
		}
		if( PeekMessage( &uMSG, NULL, 0, 0, PM_REMOVE ) )
		{
			if( uMSG.message == WM_QUIT )
				return false;
			TranslateMessage( &uMSG );
			DispatchMessage( &uMSG );
		}

		if (!IsWindow(hWndTarget))
			return false;

		if (pVisuals->Matrix[2].m[3][3] != 1.f)
		{
			pDevice->Clear(NULL, NULL, D3DCLEAR_TARGET, 0x00000000, 1.f, NULL);

			if (SUCCEEDED(pDevice->BeginScene()))
			{
				if (hWndTarget == GetForegroundWindow())
				{
					pVisuals->Main();
					Explorer::Tick();
				}
				pDevice->EndScene();
			}
		}
		
		pDevice->PresentEx( NULL, NULL, NULL, NULL, NULL );

		return true;
	}
	
	HRESULT CreateOverlay( HWND WNHandle, std::string szOverlayTitle )
	{
		hWndTarget = WNHandle;

		if( !hWndTarget )
			return E_FAIL;

		RECT rect_client, rect_app;

		GetClientRect(WNHandle, &rect_client);

		iResolution[ 0 ] = rect_client.right;
		iResolution[ 1 ] = rect_client.bottom;
		iCenter[ 0 ] = iResolution[ 0 ] / 2;
		iCenter[ 1 ] = iResolution[ 1 ] / 2;

		WNDCLASSEX wc	= {	sizeof( WNDCLASSEX ), 0, WndProc, 0, 0, NULL, LoadIcon( NULL, IDI_APPLICATION ),
							LoadCursor( 0, IDC_ARROW ), 0, 0, ( LPCSTR )szOverlayTitle.c_str(), LoadIcon( 0, IDI_APPLICATION ) };

		RegisterClassEx( &wc );

		hWndOverlay		= CreateWindowEx( WS_EX_TOPMOST | WS_EX_COMPOSITED | WS_EX_TRANSPARENT | WS_EX_LAYERED, ( LPCSTR )szOverlayTitle.c_str(), ( LPCSTR )szOverlayTitle.c_str(),
			WS_POPUP, /*CW_USEDEFAULT*/rect_client.left, /*CW_USEDEFAULT*/rect_client.top, iResolution[0], iResolution[1], 0, 0, NULL, 0);

		if( !hWndOverlay )
			return E_FAIL;

		DwmExtendFrameIntoClientArea( hWndOverlay, &mgDWMMargins );
		ShowWindow( hWndOverlay, SW_SHOWDEFAULT );
		UpdateWindow( hWndOverlay );
		GetWindowRect( hWndTarget, &rect_app );

		int border_x = GetSystemMetrics( SM_CXBORDER );
		int border_y = GetSystemMetrics( SM_CYCAPTION );

		MoveWindow( hWndOverlay, rect_app.left, rect_app.top, iResolution[ 0 ], iResolution[ 1 ], false );

		if( SUCCEEDED( Startup( hWndOverlay ) ) )
		{
			Shutdown();
			return( SUCCEEDED( Startup( hWndOverlay ) ) );
		}
		else
			return E_FAIL;
	}
}