#ifndef VECTOR_H
#define VECTOR_H

#ifdef WIN32
#pragma once
#endif

#include <cmath>
#include <float.h>

class Vector
{
public:
	float x, y, z;

	inline Vector( void )
	{

	}
	inline Vector( float X, float Y, float Z ) 
	{
		this->x = X;
		this->y = Y;
		this->z = Z;
	}
	inline Vector( float args[ 3 ] )
	{
		this->x = args[ 0 ];
		this->y = args[ 1 ];
		this->z = args[ 2 ];
	}
	inline Vector( const Vector &v )
	{
		this->x = v.x;
		this->y = v.y;
		this->z = v.z;
	}
	inline Vector operator-( void ) const				
	{ 
		return Vector( -x, -y, -z );				
	}
	inline int operator==( const Vector& v ) const	
	{
		return ( x == v.x && y == v.y && z == v.z );	
	}
	inline int operator!=( const Vector& v ) const	
	{
		return !( *this == v );					
	}
	inline Vector operator+( const Vector& v ) const	
	{ 
		return Vector( x + v.x, y + v.y, z + v.z );	
	}
	inline Vector operator-( const Vector& v ) const	
	{
		return Vector( x - v.x, y - v.y, z - v.z );	
	}
	inline Vector operator*( Vector& v ) const
	{
		return Vector( x * v.x, y *v.y, z * v.z );
	}
	inline Vector operator*( float fl ) const			
	{ 
		return Vector( x * fl, y * fl, z * fl );		
	}
	inline Vector operator/( float fl ) const			
	{ 
		return Vector( x / fl, y / fl, z / fl);		
	}
	inline void operator +=( const Vector &v )
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}
	inline void operator -=( const Vector &v )
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}
	inline void operator *=( const Vector &v )
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
	}
	inline void operator /=( const Vector &v )
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
	}
	float DotProduct( Vector in ) 
	{
		return ( this->x * in.x + this->y * in.y + this->z * in.z );
	}
	inline void CopyToArray( float* rgfl ) const	
	{ 
		rgfl[ 0 ] = x, rgfl[ 1 ] = y, rgfl[ 2 ] = z; 
	}
	inline float Length( void ) const					
	{ 
		return ( float )sqrt( x * x + y * y + z * z ); 
	}
	operator float *(  )								
	{ 
		return &x; 
	}
	operator const float *( ) const					
	{
		return &x; 
	}
	inline Vector Normalize( void ) const
	{
		float flLen = Length( );
		if( flLen == 0 ) return Vector( 0, 0, 1 );
		flLen = 1 / flLen;
		return Vector( x * flLen, y * flLen, z * flLen );
	}
	inline float Length2D( void ) const					
	{ 
		return ( float )sqrt( x * x + y * y ); 
	}
	inline float GetDistance( const Vector &s ) const
	{
		Vector fDelta( x - s.x, y - s.y, z - s.z );
		return ( float )( sqrt( ( fDelta.x * fDelta.x ) + ( fDelta.y * fDelta.y ) + ( fDelta.z * fDelta.z ) ) );
	}
	inline void NormalizeAngles( void )
	{
		if( x > 180 )			x -= 360;
		else if( x < -180 )		x += 360;

		if( y > 180 )			y -= 360;
		else if( y < -180 )		y += 360;

		if( z > 180 )			z -= 360;
		else if( z < -180 )		z += 360;
	}
	float Angle( Vector &in )
	{
		#define M_PI 3.14159265358979323846
		#define RADTODEG(x) (x * (180 / M_PI))
		float f = ( float )RADTODEG( acos( this->DotProduct( in ) / ( this->Length( ) * in.Length( ) ) ) );
		if( _finite( f ) ) return f;

		return 0.0f;
	}
};
inline Vector operator*(float fl, const Vector& v)	{ return v * fl; }
typedef Vector Vec;
typedef Vector Vec3;

inline float BitsToFloat( unsigned long i )
{
	return *reinterpret_cast<float*>(&i);
}

#define FLOAT32_NAN_BITS     (unsigned long)0x7FC00000	// not a number!
#define  assert( _exp )										((void)0)

/// Computes the dot product of a float3 and another vector given by three floats.
/// @param v1 A vector of type float3, or a C array of three elements.
/// @param x The x component of a second vector.
/// @param y The y component of a second vector.
/// @param z The z component of a second vector.
/// @see DOT3(), ABSDOT3(), DOT3STRIDED().
#define DOT3_xyz(v1, x, y, z) ((v1)[0] * (x) + (v1)[1] * (y) + (v1)[2] * (z))

struct matrix3x4_t
{
	matrix3x4_t() {}
	matrix3x4_t( 
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23 )
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void Init( const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin )
	{
		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t( const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector &vecOrigin )
	{
		Init( xAxis, yAxis, zAxis, vecOrigin );
	}

	inline void Invalidate( void )
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_flMatVal[i][j] = BitsToFloat( FLOAT32_NAN_BITS );
			}
		}
	}

	inline const Vector Col(int column)
	{
		return Vector(m_flMatVal[0][column], m_flMatVal[1][column], m_flMatVal[2][column]);

	}

	inline void SetCol(int column, float m_0c, float m_1c, float m_2c)
	{
			m_flMatVal[0][column] = m_0c;
			m_flMatVal[1][column] = m_1c;
			m_flMatVal[2][column] = m_2c;
	}

	inline void SetCol(int column, const Vector &columnVector)
	{
			SetCol(column, columnVector.x, columnVector.y, columnVector.z);
	}

	void SetTranslatePart(const Vector &offset) { SetCol(3, offset); }

	template<typename T>
	void Swap(T &a, T &b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	Vector TransformDir(float x, float y, float z) const
	{
		return Vector(DOT3_xyz(m_flMatVal[0], x,y,z),
					  DOT3_xyz(m_flMatVal[1], x,y,z),
					  DOT3_xyz(m_flMatVal[2], x,y,z));
	}

	void InverseOrthonormal()
	{
		Swap(m_flMatVal[0][1], m_flMatVal[1][0]);
		Swap(m_flMatVal[0][2], m_flMatVal[2][0]);
		Swap(m_flMatVal[1][2], m_flMatVal[2][1]);
		SetTranslatePart(TransformDir(-m_flMatVal[0][3], -m_flMatVal[1][3], -m_flMatVal[2][3]));
	}

	Vector TransformDir(const Vector &directionVector) const
	{
		return TransformDir(directionVector.x, directionVector.y, directionVector.z);
	}

	Vector TransformPos(float x, float y, float z) const
	{
		return Vector(DOT3_xyz(m_flMatVal[0], x,y,z) + m_flMatVal[0][3],
					  DOT3_xyz(m_flMatVal[1], x,y,z) + m_flMatVal[1][3],
					  DOT3_xyz(m_flMatVal[2], x,y,z) + m_flMatVal[2][3]);
	}

	Vector TransformPos(const Vector &pointVector) const
	{
		return TransformPos(pointVector.x, pointVector.y, pointVector.z);
	}

	Vector MulPos(const Vector &pointVector) const { return this->TransformPos(pointVector); }
	Vector MulDir(const Vector &directionVector) const { return this->TransformDir(directionVector); }

	float *operator[]( int i )				{ return m_flMatVal[i]; }
	const float *operator[]( int i ) const	{ return m_flMatVal[i]; }
	float *Base()							{ return &m_flMatVal[0][0]; }
	const float *Base() const				{ return &m_flMatVal[0][0]; }

	float m_flMatVal[3][4];
};

#endif // Vector.h