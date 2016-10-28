#ifndef __OFFSETS__
#define __OFFSTES__

#ifdef _WIN32
#pragma once
#endif

#define GameOffset 0x8BBA10 //A1 10 BA CB 00 ref: g_pClientLo"
#define GameWorldOffset 0x8BBA78 //A1 78 BA CB 00  ref: g_pGameWorl"

#define GameXOR 0x1735146A
#define GameWorldXOR 0xFC5AD98D

#define Renderer 0xE15C88 //8B 0D 88 6C 21 01 .\\Source\\r3dRender.CPP

#define LocalPlayerOffset 0xCE92C //8B 97 2C E9 0C 00 localPlayer (local player dropped by server)
#define LocalPlayerXOR 0x8347816F

#define XOR_OBJLIST_PTR     0x304CFD16 
#define XOR_OBJLIST_MAX     0x13E1855C 

#endif
