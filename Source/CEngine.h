#ifndef __CENGINE__
#define __CENGINE__

#ifdef _WIN32
#pragma once
#endif

#include "stdafx.h"

class CEngine
{
public:
	int		getBombIndex(void);
	int		getBombOwner(void);
	Vector	ViewAngles( void );
};

extern CEngine* g_pEngine;

#endif