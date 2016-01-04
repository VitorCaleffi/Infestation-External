#ifndef __MATH__
#define __MATH

#ifdef WIN32
#pragma once
#endif

#include "stdafx.h"
#include "Visuals.h"

#ifndef M_PI
#define M_PI	3.14159265358979323846f
#endif

#define M_RADPI	57.295779513082f

extern float	DotProduct( const Vector& a, const Vector& b );
extern float	DotProduct( const float *v1, const float *v2 );
extern float	DegToRad( float alpha );
extern bool		InHitbox( Vector vView, Vector vStart, Vector vEnd );
extern bool		WorldToRadar( int Position[ 2 ], int Size, float ViewAnglesYaw, Vector LocalPosition, Vector EntityPosition, int Range, float *Output );
extern bool		WorldToScreen(D3DXVECTOR3 from, D3DXVECTOR3 *to);
extern void		CalculateAngles( Vector vStart, Vector vEnd, Vector& vAngle );
extern void		MakeVector( Vector pfIn, Vector &pfOut );
extern void		VectorTransform( const Vector in1, const matrix3x4_t& in2, Vector& out );
extern void		AngleVectors( const Vector angles, Vector &forward, Vector &right, Vector &up );
extern void		VectorAngles( const Vector forward, Vector &angles );
extern float	AngleDif( Vector angle, Vector src, Vector dst );

#endif // Math.h