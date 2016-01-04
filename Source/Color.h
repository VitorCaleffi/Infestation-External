#ifndef __COLOR__
#define __COLOR__

#ifdef _WIN32
#pragma once
#endif

#include "stdafx.h"

class Color
{
private:
	int	A, R, G, B;

public:
	inline Color( void )
	{

	}
	inline Color( int a, int r, int g, int b )
	{
		A = a;
		R = r;
		G = g;
		B = b;
	}
	inline Color( int r, int g, int b ) 
	{
		A = 255;
		R = r;
		G = g;
		B = b;
	}
	inline Color( DWORD dwColor )
	{
		A = ( int )( ( dwColor >> 24 ) & 0xFF );
		R = ( int )( ( dwColor >> 16 ) & 0xFF );
		G = ( int )( ( dwColor >>  8 ) & 0xFF );
		B = ( int )( ( dwColor ) & 0xFF );
	}
	inline int a( void ) const
	{
		return A;
	}
	inline int r( void ) const
	{
		return R;
	}
	inline int g( void ) const
	{
		return G;
	}
	inline int b( void ) const
	{
		return B;
	}
	inline DWORD HEX( void ) const
	{
		return( ( ( DWORD )A << 24 ) | ( ( DWORD )R << 16 ) | ( ( DWORD )G << 8 ) | ( DWORD )B );
	}
	inline void getColor( int& a, int& r, int& g, int& b )
	{
		a = A;
		r = R;
		g = G;
		b = B;
	}
	inline void getColor( int& r, int& g, int& b )
	{
		r = R;
		g = G;
		b = B;
	}
	inline void getColor( DWORD& color )
	{
		color = ( ( ( DWORD )A << 24 ) | ( ( DWORD )R << 16 ) | ( ( DWORD )G << 8 ) | ( DWORD )B );
	}
};

#ifndef WHITE
#define WHITE			Color( 255, 255, 255, 255 )
#endif

#ifndef BLACK
#define BLACK			Color( 255,   0,   0,   0 )
#endif

#ifndef RED
#define RED				Color( 255, 255,   0,   0 )
#endif

#ifndef GREEN
#define GREEN			Color( 255,   0, 255,   0 )
#endif

#ifndef BLUE
#define BLUE			Color( 255,   0,   0, 255 )
#endif

#define BABYBLUE		Color( 255,   0, 176, 255 )

#endif