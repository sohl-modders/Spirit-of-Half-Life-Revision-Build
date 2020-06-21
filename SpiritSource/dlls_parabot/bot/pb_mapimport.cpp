#include "pb_global.h"
#include "pb_mapgraph.h"
#include "pb_mapcells.h"
#include "entity_state.h"
#include "bot.h"

extern PB_MapGraph mapGraph;
extern PB_MapCells map;

char actualMapname[100] = "";

void saveLevelData()
{
	char fileName[100];
		
	strcpy( fileName, actualMapname );
	strcat( fileName, ".pnf" );
	infoMsg( "\nSaving level data to ", fileName, "\n" );
	mapGraph.save( fileName );

	strcpy( fileName, actualMapname );
	strcat( fileName, ".pcf" );
	infoMsg( "\nSaving cell data to ", fileName, "\n" );
	map.save( fileName );
	return;
}

void importNav( int code )
{
	CBaseEntity *pOther = NULL;
	PB_Navpoint n;
	Vector pos;
	
	char *classname = PB_Navpoint::classname( code ); 

	while ( (pOther = UTIL_FindEntityByClassname (pOther, classname)) != NULL) {
		pos = (pOther->pev->absmax + pOther->pev->absmin) * 0.5;
		n.init( pos, code, 0 );
		mapGraph.addNavpoint( n );
	}
}

void importNav( int code, const char *modelName )
{
	CBaseEntity *pOther = NULL;
	PB_Navpoint n;
	Vector pos;
	
	char *classname = PB_Navpoint::classname( code ); 

	while ( (pOther = UTIL_FindEntityByClassname (pOther, classname)) != NULL) {
		if (!FStrEq( STRING(pOther->pev->model), modelName )) continue;
		pos = (pOther->pev->absmax + pOther->pev->absmin) * 0.5;
		n.init( pos, code, 0 );
		mapGraph.addNavpoint( n );
	}
}


void importHL_Specifics()
{
	// import weapons
	importNav( NAV_W_CROSSBOW );
	importNav( NAV_W_CROWBAR );
	importNav( NAV_W_EGON );
	importNav( NAV_W_GAUSS );
	importNav( NAV_W_HANDGRENADE );
	importNav( NAV_W_HORNETGUN );
	importNav( NAV_W_MP5 );
	importNav( NAV_W_9MMAR );
	importNav( NAV_W_PYTHON );
	importNav( NAV_W_357 );
	importNav( NAV_W_RPG );
	importNav( NAV_W_SATCHEL );
	importNav( NAV_W_SHOTGUN );
	importNav( NAV_W_SNARK );
	importNav( NAV_W_TRIPMINE );
	importNav( NAV_W_GLOCK );
	importNav( NAV_W_9MMHANDGUN );
	// import ammo
	importNav( NAV_A_CROSSBOW );
	importNav( NAV_A_CROSSBOW_BOLT );
	importNav( NAV_A_EGONCLIP );
	importNav( NAV_A_GAUSSCLIP	);
	importNav( NAV_A_MP5CLIP );
	importNav( NAV_A_MP5GRENADES );
	importNav( NAV_A_9MMAR	);
	importNav( NAV_A_9MMBOX );
	importNav( NAV_A_9MMCLIP );
	importNav( NAV_A_ARGRENADES );
	importNav( NAV_A_357 );
	importNav( NAV_A_RPGCLIP );
	importNav( NAV_A_RPG_ROCKET );
	importNav( NAV_A_BUCKSHOT );
	importNav( NAV_A_GLOCKCLIP	);
	// import funcs	
	importNav( NAV_F_TANK );
	importNav( NAV_F_TANKCONTROLS );
	importNav( NAV_F_RECHARGE );
	importNav( NAV_F_HEALTHCHARGER );
	// import items
	importNav(  NAV_I_HEALTHKIT );
	importNav(  NAV_I_LONGJUMP );
	importNav(  NAV_I_AIRTANK );
	importNav(  NAV_I_BATTERY );
}

bool loadLevelData()
{
	char fileName[100];
	
	if (strcmp( STRING(gpGlobals->mapname), actualMapname )==0) return true;

	if ( strcmp( actualMapname, "" ) != 0 && 
		 mapGraph.numberOfNavpoints() > 0    ) saveLevelData();
	
	mapGraph.clear();
	map.clear();
	strcpy( actualMapname, STRING(gpGlobals->mapname) );
	strcpy( fileName, STRING(gpGlobals->mapname) );
	strcat( fileName, ".pnf" );
	if (!mapGraph.load( fileName ))	{
		infoMsg( "Importing level data...\n" );
			
	// import funcs
		importNav( NAV_F_BUTTON	);
		importNav( NAV_F_ROT_BUTTON	);
		importNav( NAV_F_DOOR );
		importNav( NAV_F_DOOR_ROTATING );
		importNav( NAV_F_PLAT );
		importNav( NAV_F_PLATROT );
		importNav( NAV_F_TRAIN );
		importNav( NAV_F_BREAKABLE );

	// import player-start
		importNav(  NAV_INFO_PLAYER_DM );

	// teleport
		importNav(  NAV_INFO_TELEPORT_DEST );	
		importNav(  NAV_TRIG_TELEPORT );	
		
	// import ladders
		CBaseEntity *pOther = NULL;
		PB_Navpoint n;
		Vector posUp, posDown;
	
		while ( (pOther = UTIL_FindEntityByClassname (pOther, "func_ladder")) != NULL) {
			posUp = (pOther->pev->absmax + pOther->pev->absmin) * 0.5;
			posUp.z = pOther->pev->absmax.z;
			posDown = posUp;
			posDown.z = pOther->pev->absmin.z;
		/*	Vector dir = pOther->v.absmax - pOther->v.absmin;
			dir.z = 0;
			dir = CrossProduct( dir, Vector(0,0,1));
			dir = 30 * dir.Normalize();	
			TraceResult tr;
			UTIL_TraceLine( posUp, posDown+dir, ignore_monsters, NULL, &tr );
			if (tr.flFraction<1.0) posDown = posDown - dir;
			else				   posDown = posDown + dir; */
			posUp.z += 36;
			posDown.z += 36;
			n.init( posUp, NAV_F_LADDER_TOP, 0 );
			mapGraph.addNavpoint( n );
			n.init( posDown, NAV_F_LADDER_BOTTOM, 0 );
			mapGraph.addNavpoint( n );
		}


		importHL_Specifics();		
		
		// import specials
		if (strcmp( STRING(gpGlobals->mapname), "crossfire" )==0) {
			PB_Navpoint n;
			n.init( Vector( 0,-2236,-1852 ), NAV_S_AIRSTRIKE_BUTTON, 0 );
			mapGraph.addNavpoint( n );
		}
	}
	else {
		strcpy( fileName, STRING(gpGlobals->mapname) );
		strcat( fileName, ".pcf" );
		map.load( fileName );
		infoMsg( "Loaded level data.\n" );
	}
	if (mapGraph.numberOfNavpoints() > 0 ) return true;
	else return false;
}


