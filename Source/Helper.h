#ifndef HELPER_H
#define HELPER_H

#include "stdafx.h"


struct Helper_t
{
	DWORD		MyAddres;
	DWORD		ResourceAddr;
	DWORD		PlantedAddr;
	int			MyTeam;
	int			BombIndex;
	char		CountDrop;
	bool		C4Planted;
	int			Defus;
};

extern Helper_t Help;

#endif