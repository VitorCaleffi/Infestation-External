#include "Math.h"

float DotProduct( const Vector& a, const Vector& b )
{
	return( a.x * b.x + a.y * b.y + a.z * b.z );
}
float DotProduct( const float *v1, const float *v2 )
{
	return v1[ 0 ] * v2[ 0 ] + v1[ 1 ] * v2[ 1 ] + v1[ 2 ] * v2[ 2 ];
}
float DegToRad( float alpha )
{
	return alpha / 180.0f * 3.1415926535f;
}
bool InHitbox( Vector vView, Vector vStart, Vector vEnd )
{
	if( ( vView[ 0 ] > vStart[ 0 ] && vView[ 0 ] < vEnd[ 0 ] ) && ( vView[ 1 ] > vStart[ 1 ] && vView[ 1 ] < vEnd[ 1 ] ) ) return true;
	else return false;
}
bool WorldToRadar( int Position[ 2 ], int Size, float ViewAnglesYaw, Vector LocalPosition, Vector EntityPosition, int Range, float *Output )
{
	float flMiddle[ 2 ]			= { ( float )Position[ 0 ] + ( ( float )Size / 2.f ),
									( float )Position[ 1 ] + ( ( float )Size / 2.f ) };

	float flViewAnglesYaw[ 2 ]	= { cos( DegToRad( ViewAnglesYaw ) ),
									sin( DegToRad( ViewAnglesYaw ) ) };

	float flMapPoint[ 2 ]		= { EntityPosition.x - LocalPosition.x,
									EntityPosition.y - LocalPosition.y };

	float flTemp[ 2 ]			= { ( flMapPoint[ 1 ] * flViewAnglesYaw[ 0 ] - flMapPoint[ 0 ] * flViewAnglesYaw[ 1 ] ) / Range,
									( flMapPoint[ 0 ] * flViewAnglesYaw[ 0 ] + flMapPoint[ 1 ] * flViewAnglesYaw[ 1 ] ) / Range };

	Output[ 0 ] =  flTemp[ 0 ] + flMiddle[ 0 ];
	Output[ 1 ] = -flTemp[ 1 ] + flMiddle[ 1 ];

	if( Output[ 0 ] < flMiddle[ 0 ] )
	{
		float flTmp = flMiddle[ 0 ] - Output[ 0 ];
		Output[ 0 ] = flMiddle[ 0 ] + flTmp;
	}
	else if( Output[ 0 ] > flMiddle[ 0 ] )
	{
		float flTmp = Output[ 0 ] - flMiddle[ 0 ];
		Output[ 0 ] = flMiddle[ 0 ] - flTmp;
	}

	if( Output[ 0 ] > Position[ 0 ] && Output[ 0 ]< Position[ 0 ] + Size && Output[ 1 ] > Position[ 1 ] && Output[ 1 ] < Position[ 1 ] + Size ) return true;
	else return false;
}

bool WorldToScreen(D3DXVECTOR3 from, D3DXVECTOR3 *to)
{
	D3DVIEWPORT9 ViewPort;
	D3DXMATRIX mWorld;
	
	Direct3D9::pDevice->GetViewport(&ViewPort);
	
	D3DXMatrixIdentity(&mWorld);
	
	D3DXVec3Project(to, &from, &ViewPort, &(pVisuals->Matrix[2]), &(pVisuals->Matrix[0]), &mWorld);

	if (to->z >= 1 || to->z < 0 || to->x < 0 || to->y < 0 || pVisuals->Matrix[2].m[3][3] == 1.f)//from nov's code
		return false;

	return true;
	/*
	int xx, yy;
	D3DMATRIX matrix = pVisuals->Matrix[2];
	D3DXVECTOR4 position;
	D3DVIEWPORT9 viewport;

	Direct3D9::pDevice->GetVertexShaderConstantF(0, (float *)&matrix, 4);
	Direct3D9::pDevice->GetViewport(&viewport);

	D3DXMatrixTranspose((D3DXMATRIX *)&matrix, (D3DXMATRIX *)&matrix);

	position.x = from.x * matrix._11 + from.y * matrix._21 + from.z * matrix._31 + matrix._41;
	position.y = from.x * matrix._12 + from.y * matrix._22 + from.z * matrix._32 + matrix._42;
	position.z = from.x * matrix._13 + from.y * matrix._23 + from.z * matrix._33 + matrix._43;
	position.w = from.x * matrix._14 + from.y * matrix._24 + from.z * matrix._34 + matrix._44;

	xx = ((position.x / position.w) * (viewport.Width / 2)) + viewport.X + (viewport.Width / 2);
	yy = viewport.Y + (viewport.Height / 2) - ((position.y / position.w) * (viewport.Height / 2));

	to->x = xx;
	to->y = yy;

	if (xx < 0 || yy < 0 || xx > 2000 || yy > 2000)
		return false;

	return true;*/
}

void CalculateAngles( Vector vStart, Vector vEnd, Vector& vAngle )
{
	double delta[ 3 ] = { vStart[ 0 ] - vEnd[ 0 ], vStart[ 1 ] - vEnd [ 1 ] , vStart[ 2 ] - vEnd[ 2 ] };
	double hyp = sqrt( delta[ 0 ] * delta[ 0 ] + delta[ 1 ] * delta[ 1 ] );

	vAngle[ 0 ] = ( float ) ( atan( delta[ 2 ] / hyp ) * M_RADPI );
	vAngle[ 1 ] = ( float ) ( atan( delta[ 1 ] / delta[ 0 ] ) * M_RADPI );
	vAngle[ 2 ] = 0.0f;

	if( delta[ 0 ] >= 0.0 ) vAngle[ 1 ] += 180.0f;
}
void MakeVector( Vector pfIn, Vector &pfOut )
{
	float pitch;
	float yaw;
	float tmp;		
	
	pitch = ( float ) ( pfIn[ 0 ] * M_PI / 180);
	yaw = ( float ) ( pfIn[ 1 ] * M_PI / 180);
	tmp = ( float ) cos( pitch );
	
	pfOut[ 0 ] = ( float ) ( -tmp * -cos( yaw ) );
	pfOut[ 1 ] = ( float ) ( sin( yaw )*tmp );
	pfOut[ 2 ] = ( float ) -sin( pitch );
}
void VectorTransform( const Vector in1, const matrix3x4_t& in2, Vector& out )
{
	out[ 0 ] = DotProduct( in1, in2[ 0 ] ) + in2[ 0 ][ 3 ];
	out[ 1 ] = DotProduct( in1, in2[ 1 ] ) + in2[ 1 ][ 3 ];
	out[ 2 ] = DotProduct( in1, in2[ 2 ] ) + in2[ 2 ][ 3 ];
}
void AngleVectors( const Vector angles, Vector &forward, Vector &right, Vector &up )
{
	float angle;
	static float sp, sy, cp, cy;

	angle = angles[ 0 ] * ( M_PI / 180.f );
	sp = sin( angle );
	cp = cos( angle );

	angle = angles[ 1 ] * ( M_PI / 180.f );
	sy = sin( angle );
	cy = cos( angle );

	if( forward ) 
	{
		forward[ 0 ] = cp * cy;
		forward[ 1 ] = cp * sy;
		forward[ 2 ] = -sp;
	}
	if( right || up ) 
	{
		static float sr, cr;

		angle = angles[ 2 ] * ( M_PI / 180.f );
		sr = sin( angle );
		cr = cos( angle );

		if( right )
		{
			right[ 0 ] = -1 * sr * sp * cy + -1 * cr * -sy;
			right[ 1 ] = -1 * sr * sp * sy + -1 * cr *cy;
			right[ 2 ] = -1 * sr * cp;
		}
		if( up ) 
		{
			up[ 0 ] = cr * sp *cy + -sr * -sy;
			up[ 1 ] = cr * sp *sy + -sr * cy;
			up[ 2 ] = cr * cp;
		}
	}
}
void VectorAngles( const Vector forward, Vector &angles )
{
	float	tmp, yaw, pitch;
	
	if ( forward[ 1 ] == 0 && forward[ 0 ] == 0 )
	{
		yaw = 0;
		if ( forward[ 2 ] > 0 )
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = ( atan2( forward[ 1 ], forward[ 0 ] ) * 180.f / M_PI);
		if ( yaw < 0.f )
			yaw += 360.f;

		tmp = sqrt ( forward[ 0 ] * forward[ 0 ] + forward[ 1 ]*forward[ 1 ] );
		pitch = ( atan2( - forward[ 2 ], tmp ) * 180.f / M_PI );
		if ( pitch < 0.f )
			pitch += 360.f;
	}
	
	angles[ 0 ] = pitch;
	angles[ 1 ] = yaw;
	angles[ 2 ] = 0;
}
float AngleDif( Vector angle, Vector src, Vector dst )
{ 
	Vector ang, aim;
	float angDifference; 

	CalculateAngles( src, dst, ang ); 
	MakeVector( angle, aim ); 
	MakeVector( ang, ang );      

	float mag_s = sqrt( ( aim[ 0 ] * aim[ 0 ] ) + ( aim[ 1 ] * aim[ 1 ] ) + ( aim[ 2 ] * aim[ 2 ] ) ); 
	float mag_d = sqrt( ( aim[ 0 ] * aim[ 0 ] ) + ( aim[ 1 ] * aim[ 1 ] ) + ( aim[ 2 ] * aim[ 2 ] ) ); 

	float u_dot_v = aim[ 0 ] * ang[ 0 ] + aim[ 1 ] * ang[ 1]  + aim[ 2 ] * ang[ 2 ]; 

	angDifference = acos( u_dot_v / ( mag_s*mag_d ) ) * ( 180.0 / M_PI ); 

	return angDifference; 
}