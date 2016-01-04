#ifndef __CBASEENTITY__
#define __CBASEENTITY__

#ifdef _WIN32
#pragma once
#endif

#include "stdafx.h"

class CBaseEntity
{
public:
	DWORD		dwEntity;
	int			iIndex;

public:
	CBaseEntity( int nIndex );

	wchar_t		Name[32];
	char		ClassName[32];

	bool		IsValid( void );
	bool		IsVisible( void );
	bool		BombOwner(void);
	bool		isDefusing();

	BYTE		m_fFlags( void );
	BYTE		m_lifeState( void );

	DWORD		getEntity( void );
	DWORD		TeamColor( void );

	int			getIndex( void );
	int			m_iHealth( void );
	int			m_iTeamNum( void );
	int			m_Money(void);

	matrix3x4_t	BoneData( int iBone );

	Vector		EyePosition( void );
	Vector		m_vecOrigin( void );
	Vector		m_vecViewOffset( void );
	Vector		WeaponClassOr();

	void		getTeamColor( Color& cOut );
	void		getEyePosition( Vector& vOut );
	void		getBoneData( int iBone, matrix3x4_t& m3x4Out );
	int		WeaponName(void);
};

#endif