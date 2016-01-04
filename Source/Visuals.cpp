#include "Visuals.h"

Visuals* pVisuals = new Visuals();

float GetBox(const float PosB, const float PosA)
{
	float h = PosB - PosA;
	float ang = (40 * 3.14159265358979323846) / 180;
	return (h*tan(ang)) * 2;
}

void Visuals::DrawPlayer()
{
	D3DXVECTOR3 to;
	D3DXVECTOR3 toHead;

	if (SDK::PlayerCount)
	{
		for (int i = 0; i <= SDK::PlayerCount - 1; i++)
		{
			CObject ActualPlayer = Memory::Read<CObject>(SDK::PlayerArray[i]);
			D3DXVECTOR3 head = SDK::GetBoneOrigin(SDK::PlayerArray[i], 6);

			int WpID = Memory::Read<int>(SDK::PlayerArray[i] + (DWORD)0x610);

			if (WorldToScreen(ActualPlayer.m_Position, &to))
			{
				if (WorldToScreen(head, &toHead))
				{
					float Width = GetBox(head.y, to.y - 25) / 4;
					float Height = to.y - head.y;
					

					Direct3D9::pRender->BorderBox(toHead.x, toHead.y, 5, 5, 1, Color(255, 0, 0));
					Direct3D9::pRender->BorderBox(to.x, to.y, 5, 5, 1, Color(255, 0, 0));

					Direct3D9::pRender->StringOutlined(to.x + 20, to.y, Color(255, 0, 0), Direct3D9::GetFont("Arial"), "D: %i", (int)SDK::GetDistance(ActualPlayer.m_Position));
					Direct3D9::pRender->StringOutlined(to.x + 20, to.y + 15, Color(255, 0, 0), Direct3D9::GetFont("Arial"), "H: %i", (int)ActualPlayer.m_Health);
					Direct3D9::pRender->StringOutlined(to.x + 20, to.y + 30, Color(255, 255, 0), Direct3D9::GetFont("Arial"), "W: %s" ,SDK::GetItemInfo(WpID,false).name );
				}
				else
				{
					Direct3D9::pRender->BorderBox(to.x, to.y, 10, 10, 1, Color(255, 0, 0));
					Direct3D9::pRender->StringOutlined(to.x + 20, to.y, Color(255, 0, 0), Direct3D9::GetFont("Arial"), "D: %i", (int)SDK::GetDistance(ActualPlayer.m_Position));
					Direct3D9::pRender->StringOutlined(to.x + 20, to.y + 15, Color(255, 0, 0), Direct3D9::GetFont("Arial"), "H: %i", (int)ActualPlayer.m_Health);
					Direct3D9::pRender->StringOutlined(to.x + 20, to.y + 30, Color(255, 255, 0), Direct3D9::GetFont("Arial"), "W: %s" ,SDK::GetItemInfo(WpID,false).name);
				}

			}
		}
	}
}

void ShowItems(void)
{
	D3DXVECTOR3 to;
	D3DXVECTOR3 WorldPos;

	if (SDK::ItemCount)
	{
		for (int i = 0; i <= SDK::ItemCount - 1; i++)
		{
			WorldPos = Memory::Read<D3DXVECTOR3>(SDK::ItemArray[i] + 0x24);

			if (WorldToScreen(WorldPos, &to))
			{
				SDK::cItems itemIn = SDK::GetItemInfo(SDK::ItemArray[i], true);

				if (itemIn.type < 10 && itemIn.type >= 0)
				{
					if (Explorer::MenuOpt[itemIn.type])
						Direct3D9::pRender->StringOutlined(to.x, to.y, itemIn.color, Direct3D9::GetFont("Arial"), itemIn.name);
				}
			}
		}
	}
}

void ShowCarros()
{
	D3DXVECTOR3 to;
	D3DXVECTOR3 WorldPos;

	if (SDK::CarCount)
	{
		for (int i = 0; i <= SDK::CarCount - 1; i++)
		{
			WorldPos = Memory::Read<D3DXVECTOR3>(SDK::CarArray[i] + 0x24);

			if (WorldToScreen(WorldPos, &to))
			{
				Direct3D9::pRender->BorderBox(to.x, to.y, 5, 5, 1, Color(0, 0, 255));
				Direct3D9::pRender->StringOutlined(to.x, to.y, Color(0, 0, 255), Direct3D9::GetFont("Arial"), "Carro");
			}
		}
	}
}

void Visuals::Main(void)
{
	if (Explorer::ShowPlayers)
		DrawPlayer();

	if (Explorer::ShowItems)
		ShowItems();

	if (Explorer::ShowCarros)
		ShowCarros();
}

Visuals::Visuals(void)
{

}