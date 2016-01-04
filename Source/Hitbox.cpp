#include "Hitbox.h"
Hitbox_t Hitbox[ HITBOX_MAX ];
void SetupHitbox( void )
{
	Hitbox[ PELVIS ].vMin		= Vector( -6.420f, -4.280f, -6.955f );
	Hitbox[ PELVIS ].vMax		= Vector( 4.280f, 4.280f, 6.955f );
	Hitbox[ PELVIS ].iBone		= 0;

	Hitbox[ L_THIGH ].vMin		= Vector( 5.029f, -3.959f, -2.140f );
	Hitbox[ L_THIGH ].vMax		= Vector( 22.149f, 3.424f, 4.280f );
	Hitbox[ L_THIGH ].iBone		= 26;

	Hitbox[ L_CALF ].vMin		= Vector( 2.675f, -3.210f, -2.247f );
	Hitbox[ L_CALF ].vMax		= Vector( 19.260f, 2.675f, 2.247f );
	Hitbox[ L_CALF ].iBone		= 27;

	Hitbox[ L_FOOT ].vMin		= Vector( 2.943f, -2.675f, -2.408f );
	Hitbox[ L_FOOT ].vMax		= Vector( 6.688f, 9.095f, 2.408f );
	Hitbox[ L_FOOT ].iBone		= 28;

	Hitbox[ R_THIGH ].vMin		= Vector( 5.029f, -3.959f, -4.280f );
	Hitbox[ R_THIGH ].vMax		= Vector( 22.149f, 3.424f, 2.140f );
	Hitbox[ R_THIGH ].iBone		= 23;

	Hitbox[ R_CALF ].vMin		= Vector( 5.029f, -3.959f, -4.280f );
	Hitbox[ R_CALF ].vMax		= Vector( 22.149f, 3.424f, 2.140f );
	Hitbox[ R_CALF ].iBone		= 24;

	Hitbox[ R_FOOT ].vMin		= Vector( 2.943f, -2.675f, -2.408f );
	Hitbox[ R_FOOT ].vMax		= Vector( 6.688f, 9.095f, 2.408f );
	Hitbox[ R_FOOT ].iBone		= 25;

	Hitbox[ SPINE2 ].vMin		= Vector( -4.280f, -4.280f, -5.885f );
	Hitbox[ SPINE2 ].vMax		= Vector( 3.210f, 5.350f, 5.885f );
	Hitbox[ SPINE2 ].iBone		= 2;

	Hitbox[ SPINE3 ].vMin		= Vector( -4.280f, -4.280f, -5.885f );
	Hitbox[ SPINE3 ].vMax		= Vector( 3.210f, 5.350f, 5.885f );
	Hitbox[ SPINE3 ].iBone		= 3;

	Hitbox[ SPINE4 ].vMin		= Vector( -4.280f, -4.280f, -5.885f );
	Hitbox[ SPINE4 ].vMax		= Vector( 6.420f, 5.350f, 5.885f );
	Hitbox[ SPINE4 ].iBone		= 4;

	Hitbox[ NECK ].vMin			= Vector( -1.070f, -2.622f, -2.151f );
	Hitbox[ NECK ].vMax			= Vector( 3.103f, 2.622f, 2.151f );
	Hitbox[ NECK ].iBone		= 5;

	Hitbox[ HEAD ].vMin			= Vector( -2.140f, -3.745f, -3.670f );
	Hitbox[ HEAD ].vMax			= Vector( 6.955f, 3.745f, 3.670f );
	Hitbox[ HEAD ].iBone		= 10;

	Hitbox[ L_UPPERARM ].vMin	= Vector( -2.675f, -3.210f, -2.140f );
	Hitbox[ L_UPPERARM ].vMax	= Vector( 12.840f, 3.210f, 2.140f );
	Hitbox[ L_UPPERARM ].iBone	= 7;

	Hitbox[ L_FOREARM ].vMin	= Vector( -0.000f, -2.140f, -2.140f );
	Hitbox[ L_FOREARM ].vMax	= Vector( 9.630f, 2.140f, 2.140f );
	Hitbox[ L_FOREARM ].iBone	= 8;

	Hitbox[ L_HAND ].vMin		= Vector( -1.723f, -1.220f, -1.380f );
	Hitbox[ L_HAND ].vMax		= Vector( 4.473f, 1.220f, 1.380f );
	Hitbox[ L_HAND ].iBone		= 9;

	Hitbox[ R_UPPERARM ].vMin	= Vector( -2.675f, -3.210f, -2.140f );
	Hitbox[ R_UPPERARM ].vMax	= Vector( 12.840f, 3.210f, 2.140f );
	Hitbox[ R_UPPERARM ].iBone	= 13;

	Hitbox[ R_FOREARM ].vMin	= Vector( -0.000f, -2.140f, -2.140f );
	Hitbox[ R_FOREARM ].vMax	= Vector( 9.630f, 2.140f, 2.140f );
	Hitbox[ R_FOREARM ].iBone	= 14;

	Hitbox[ R_HAND ].vMin		= Vector( -1.723f, -1.220f, -1.380f );
	Hitbox[ R_HAND ].vMax		= Vector( 4.473f, 1.220f, 1.380f );
	Hitbox[ R_HAND ].iBone		= 15;
}