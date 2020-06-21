#include "pb_weapon.h"
#include "pb_global.h"
#include "bot.h"
#include "bot_weapons.h"

extern bot_t bots[32];
extern bot_weapon_t weapon_defs[MAX_WEAPONS];

///////////////////////////////////////////////////////////////////////////////////
//
//  WEAPON LISTS	( all orders must match pb_weapon.h! )
//
//        highAimProb:  norm=0.5  fast=0.4  expl=0.3  closeCombat=0.2  autoAim=0.1
//
///////////////////////////////////////////////////////////////////////////////////

// weapon volumes (from SDK)
#define WV_NONE		  0.0
#define	WV_SWING	128.0
#define WV_QUIET	200.0
#define WV_NORMAL	600.0
#define WV_LOUD	   1000.0
#define WV_FLASH	450.0
#define WV_LOAD		256.0

// weapon flashes (from SDK)
#define WF_NONE		  0.0
#define WF_DIM		128.0
#define WF_NORMAL	256.0
#define WF_BRIGHT	512.0


// Valve Weaponlist 
static tWeaponRec valveWeapon[MAX_VALVE_WEAPONS] = { 
	// name				bestDist	cone	highAimProb	secAmmo	volAttack1	volAttack2	visAttack1	visAttack2	fireDelay	shortName
	{ "",					 0,		0.1,	0.0,		false,	WV_NONE,	WV_NONE,	WF_NONE,	WF_NONE,	0.0,	""				},	//   doesn't exist!
	{ "weapon_crowbar",		10,		0.866,	0.0,		false,	WV_SWING,	WV_SWING,	WF_NONE,	WF_NONE,	0.0,	"crowbar"		},
	{ "weapon_9mmhandgun", 200,		0.052,	0.5,		false,	WV_NORMAL,	WV_NORMAL,	WF_NORMAL,	WF_NORMAL,	0.0,	"glock"			},	// = glock
	{ "weapon_357",		   600,		0.017,	0.5,		false,	WV_LOUD,	WV_NONE,	WF_NORMAL,	WF_NONE,	0.0,	"python"		},	// = python
	{ "weapon_9mmAR",	   200,		0.104,	0.4,		true,	WV_NORMAL,	WV_NORMAL,	WF_NORMAL,	WF_BRIGHT,	0.0,	"mp5"			},	// = mp5
	{ "weapon_crossbow",   600,		0.017,	0.5,		false,	WV_QUIET,	WV_NONE,	WF_NONE,	WF_NONE,	0.0,	"crossbow"		},
	{ "weapon_shotgun",		50,		0.173,	0.5,		false,	WV_LOUD,	WV_LOUD,	WF_NORMAL,	WF_NORMAL,	0.0,	"shotgun"		},
	{ "weapon_rpg",		   400,		0.173,	0.1,		false,	WV_LOUD,	WV_NONE,	WF_BRIGHT,	WF_NONE,	0.0,	"rocketlauncher"},
	{ "weapon_gauss",	   300,		0.017,	0.5,		false,	WV_FLASH,	WV_LOAD,	WF_NORMAL,	WF_NONE,	0.0,	"gauss"			},
	{ "weapon_egon",	   300,		0.017,	0.5,		false,	WV_FLASH,	WV_FLASH,	WF_BRIGHT,	WF_BRIGHT,	0.0,	"egon"			},
	{ "weapon_hornetgun",  200,		0.173,	0.1,		false,	WV_QUIET,	WV_NORMAL,	WF_NORMAL,	WF_NORMAL,	0.0,	"hornetgun"		},
	{ "weapon_handgrenade",400,		0.342,	0.3,		false,	WV_NONE,	WV_NONE,	WF_NONE,	WF_NONE,	0.0,	"handgrenade"	},
	{ "weapon_tripmine",	 0,		0.1,	0.0,		false,	WV_QUIET,	WV_NONE,	WF_NONE,	WF_NONE,	0.0,	"tripmine"		},
	{ "weapon_satchel",    400,		0.342,	0.3,		false,	WV_QUIET,	WV_QUIET,	WF_NONE,	WF_NONE,	0.0,	"satchel"		},
	{ "weapon_snark",	   400,		0.173,	0.1,		false,	WV_QUIET,	WV_QUIET,	WF_NONE,	WF_NONE,	0.0,	"snark"			} 
};

const char* getWeaponName( int wId )
{

	if (wId>=MIN_VALVE_WEAPONS && wId<MAX_VALVE_WEAPONS) return valveWeapon[wId].shortName;
	else return "shitty unknown MOD weapon";
}



///////////////////////////////////////////////////////////////////////////////////
//
//  INIT ROUTINES
//
///////////////////////////////////////////////////////////////////////////////////


void PB_Weapon::initMOD()
{
	modWeapon = 0;

	modWeapon = &valveWeapon[0];
	minModWeapon = MIN_VALVE_WEAPONS;
	maxModWeapon = MAX_VALVE_WEAPONS;

	assert( modWeapon != 0 );
}



PB_Weapon::PB_Weapon()
{
	initMOD();
	currentWeapon = minModWeapon;
}


PB_Weapon::PB_Weapon( int wId )
{
	initMOD();
	if ( wId>=minModWeapon && wId<maxModWeapon ) currentWeapon = wId;
	else currentWeapon = minModWeapon;
}


void PB_Weapon::init( int slot, edict_t *ent, PB_Action *action )
{
	botSlot = slot;
	botEnt = ent;
	botAction = action;
	for (int i=0; i<MAX_WEAPONS; i++) {
		bestMode[i] = 1;	// primary attack
	}
	nextAttackTime = 0;
	lastAttackTime = 0;
	reloading = false;
	grenadePrepared = false;
	loadingGauss = false;
	armedWeapon = minModWeapon;
	currentWeapon = minModWeapon;
}


void PB_Weapon::setCurrentWeapon( int wId )
{ 
	if ( wId>=minModWeapon && wId<maxModWeapon ) currentWeapon = wId;
}


void PB_Weapon::registerArmedWeapon( int wId )
{ 
	if ( wId>=minModWeapon && wId<maxModWeapon ) armedWeapon = wId; 
}




///////////////////////////////////////////////////////////////////////////////////
//
//  WEAPON SCORES
//
///////////////////////////////////////////////////////////////////////////////////

float PB_Weapon::getScore( float distance, float hitProb, int flags, bool checkAmmo )
// returns max. 10 pts
{
	float score = 0;
	float score2 = 0;
	bool notSuitable = false;

	switch (currentWeapon) {

	case VALVE_WEAPON_CROWBAR:
		if ( flags & WF_NEED_GRENADE ) break;
		
		if (distance < 55) score = 9;
		else if (distance < 100) score = (100-distance) / 5;

		if ( flags & WF_SINGLE_SHOT_KILL ) notSuitable = true;
		break;

	case VALVE_WEAPON_GLOCK:
		if ( flags & WF_NEED_GRENADE ) break;
					
		score = 1.5 - (2*distance/6400);
		if (score<0.1) score = 0.1;

		if (checkAmmo) {
			if (ammo1() == 0) score = 0;
			else if (ammo1() <= 5) score /= 2;
		}
		if (hitProb > 0.3) bestMode[currentWeapon] = 2;
		else			   bestMode[currentWeapon] = 1;	// don't waste bullets

		if ( flags & WF_SINGLE_SHOT_KILL ) notSuitable = true;
		break;

	case VALVE_WEAPON_PYTHON:
		if ( flags & (WF_UNDERWATER | WF_NEED_GRENADE) ) break;
		
		score = 4 - (4*distance/6400);
		if (score<0.3) score = 0.3;

		if (checkAmmo) {
			if (ammo1() == 0) score = 0;
			else if (ammo1() <= 3) score /= 2;
		}
		if ( hitProb < 0.5) score *= (hitProb + 0.5);	// punish slow reload
		if ( flags & WF_SINGLE_SHOT_KILL ) notSuitable = true;
		break;

	case VALVE_WEAPON_MP5:
		if ( flags & WF_UNDERWATER ) break;

		if (checkAmmo && (ammo2()>0) && (distance>250)) {	// if not sure assume that
			  if (distance<400) score2 = (distance-250) / 15;	// player doesn't have grens
			  else if (distance<550) score2 = (550-distance) / 15;
			  bestMode[currentWeapon] = 2;
		}
		if ( flags & WF_NEED_GRENADE ) break;
				
		score = 7 - (7*distance/1600);
		if (score<0.2) score = 0.2;
		
		if (checkAmmo) {
			if (ammo1() == 0) score = 0;
			else if (ammo1() <= 10) score /= 2;
		}
		if ( flags & WF_SINGLE_SHOT_KILL ) {
			notSuitable = true;
			if  ((score/10) > score2) bestMode[currentWeapon] = 1;
		}
		else if (score > score2) bestMode[currentWeapon] = 1;
		break;

	case VALVE_WEAPON_CROSSBOW:
		if (checkAmmo && ammo1() == 0) break;

		if (distance<600) {
			score = (distance-200) / 100;
			if (score<2) score = 2;		// in any case better than glock!
		}
		else score = 4;

		if (hitProb>0.5) bestMode[currentWeapon] = 2;	// use sniper mode when possible
		else {
			bestMode[currentWeapon] = 1;
			if ( flags & WF_SINGLE_SHOT_KILL ) notSuitable = true;
		}
		break;

	case VALVE_WEAPON_SHOTGUN:
		if ( flags & (WF_UNDERWATER | WF_NEED_GRENADE) ) break;
				
		score = 8 - (8*distance/1600);
		if (score<0.2) score = 0.2;

		if (checkAmmo) {
			if (ammo1() == 0) score = 0;
			else if (ammo1() <= 4) score /= 2;
		}
		if ( hitProb < 0.5) score *= (hitProb + 0.5);	// punish slow reload
		
		if (hitProb>0.5 && distance<200 && ammo1()>1) {
			bestMode[currentWeapon] = 2;	// use double mode when possible
			score = 10;			// to win against crowbar
		}
		else {
			bestMode[currentWeapon] = 1;
			if ( flags & WF_SINGLE_SHOT_KILL ) notSuitable = true;
		}
		break;

	case VALVE_WEAPON_RPG:
		if (checkAmmo && ammo1() == 0) break;

		if (distance < 400) {
			bestMode[currentWeapon] = 1;
			score = (distance-250) / 18.75;
			if (score<1.5) score = 1.5;	// don't use glock!
		}
		else {
			bestMode[currentWeapon] = 2;
			score = 8 - 8*(distance-400)/1600; 
			if ( flags & WF_ENEMY_ABOVE ) score -= 1;
			if (score<1) score = 1;
		}
		break;

	case VALVE_WEAPON_GAUSS:
		if ( flags & (WF_UNDERWATER | WF_NEED_GRENADE) ) break;
				
		score = 6;
		
		if (checkAmmo) {
			if (ammo1() <= 1) score = 0;
			else if (ammo1() <= 10) score /= 2;
		}
		bestMode[currentWeapon] = 2;
		break;

	case VALVE_WEAPON_EGON:
		if ( flags & (WF_UNDERWATER | WF_NEED_GRENADE) ) break;
				
		if (distance < 250) {
			score = (distance-150) / 12.5;
			if (score<0.5) score = 0.5;
		}
		else {
			score = 8 - 8*(distance-250)/1600;
			if (score<4) score = 4;		// not that bad...
		}

		if (checkAmmo) {
			if (ammo1() <= 1) break;
			else if (ammo1() <= 10) score /= 2;
		}
		if ( flags & WF_SINGLE_SHOT_KILL ) notSuitable = true;
		break;

	case VALVE_WEAPON_HORNETGUN:
		
		score = 2;
		if ( flags & WF_SINGLE_SHOT_KILL ) notSuitable = true;
		break;

	case VALVE_WEAPON_HANDGRENADE:
		if ( flags & WF_UNDERWATER ) break;
		// explosion at 450
		if (300<=distance && distance<=600) score = 1;
		break;

	case VALVE_WEAPON_TRIPMINE:
		return 0;		// never arm for combat

	case VALVE_WEAPON_SATCHEL:
		if ( flags & (WF_UNDERWATER | WF_ENEMY_ABOVE)) break;
		if (250<=distance && distance<=400) 
			score = 3;
		break;

	case VALVE_WEAPON_SNARK:
		if ( flags & (WF_UNDERWATER | WF_ENEMY_ABOVE)) break;
		if (200<=distance && distance<=1000) {
			score = 0.75;	// must be less than glock (to use glock against snarks)
			if ( flags & WF_ENEMY_BELOW ) score += 2;
		}
		break;

	default:
		debugMsg( "ValveWeaponScore: Unknown ID %i !\n", currentWeapon );
	
	}

	// switch-time handicaps
	if ( armedWeapon != currentWeapon ) {
		if (flags & WF_IMMEDIATE_ATTACK) {
			if ( score > 4.1 ) score -= 4.0;
			else if (score > 0) score = 0.1;	// it has to remain better than 0
		}
		else if (flags & WF_FAST_ATTACK) {
			if ( score > 2.1 ) score -= 2.0;
			else if (score > 0) score = 0.1;	// it has to remain better than 0
		}
		else {
			if ( score > 0.6 ) score -= 0.5;
			else if (score > 0) score = 0.1;	// it has to remain better than 0
		}
	}
	
	if (notSuitable) score /= 10;

	//debugMsg( "wscore=%.2f\n", score );
	return score;
}

///////////////////////////////////////////////////////////////////////////////////
//
//  ATTACK ROUTINES
//
///////////////////////////////////////////////////////////////////////////////////


bool PB_Weapon::attackValveHandgrenade( Vector &target )
{
	if (worldTime() < nextAttackTime) return false;

	bool grenadeThrown = false;
	if (!grenadePrepared) {
		//debugMsg( "Arming HG!\n" );
		grenadePrepared=true;
		grenadeLaunchTime = worldTime() + 2.0;
		grenadeTarget = target;
		grenadeWId = VALVE_WEAPON_HANDGRENADE;
	}
	if ( worldTime() < grenadeLaunchTime ) {
		//debugMsg( "Holding HG, counter=%.1f\n", (grenadeLaunchTime-worldTime()) );
		botAction->add( BOT_FIRE_PRIM );
	}
	else {
		//debugMsg( "Throwing HG!\n" );
		grenadeThrown = true;
		grenadePrepared = false;
		nextAttackTime = worldTime() + 0.5;	// give time to switch weapons
	}

	return grenadeThrown;
}


bool PB_Weapon::attackValveSatchel( Vector &target )
{
	if (worldTime() < nextAttackTime) return false;

	bool grenadeThrown = false;
	if (!grenadePrepared) {
		//debugMsg( "Throwing satchel!\n" );
		botAction->add( BOT_FIRE_PRIM );
		if ( strcmp( STRING(botEnt->v.viewmodel), "models/v_satchel_radio.mdl" ) == 0 ) {
			grenadePrepared=true;
			grenadeLaunchTime = worldTime() + 1.5;
			grenadeWId = VALVE_WEAPON_SATCHEL;
		}
	}
	else if ( worldTime() > grenadeLaunchTime ) {
		//debugMsg( "Blowing up satchel!\n" );
		botAction->add( BOT_FIRE_PRIM );
		if ( worldTime() > (grenadeLaunchTime+0.1) ) {
			grenadeThrown = true;
			grenadePrepared = false;
			nextAttackTime = worldTime() + 0.5;	// give time to switch weapons
		}
	}
	//else debugMsg( "Waiting for satchel, counter=%.1f\n", (grenadeLaunchTime-worldTime()) );

	return grenadeThrown;
}


bool PB_Weapon::attack( Vector target, float accuracy, Vector relVel )
// aims at target, if accuracy is reached fires and returns true, else returns false
// reloads when necessary
{
	bool fired = false;

	botAction->setAimDir( target, relVel );

	// check for reload:
	if ( needReload() ) reload();
		
	else 
	{				
		if ( currentWeapon==VALVE_WEAPON_GAUSS && bestMode[currentWeapon]==2 ) 
		{
			if (!loadingGauss) 
			{
				loadingGauss = true;
				loadStartTime = worldTime();
				nextAttackTime = worldTime() + 1.0;	// at least load 1 sec.
			}
			// check if we have to stop loading to not explode...
			if ((worldTime()-loadStartTime) < 5) botAction->add( BOT_FIRE_SEC );
			else 
			{
				loadingGauss = false;
				fired = true;
			}
		}
		else if (currentWeapon==VALVE_WEAPON_HANDGRENADE) 
		{
			fired = attackValveHandgrenade( target );// pull trigger before aiming perfectly
		}
		else if (currentWeapon==VALVE_WEAPON_SATCHEL && grenadePrepared) 
		{
			fired = attackValveSatchel( target );	// no need for aiming when satchel thrown
		}

		if (fired) return true;	// no need to go on

		// fire if delay and accuracy are ok:
		if (( worldTime() > nextAttackTime ) && 
			( botAction->targetAccuracy() > accuracy || lastAttackTime > (worldTime()-0.5) )) 
		{
			lastAttackTime = worldTime();
			if ( bestMode[currentWeapon] == 1 ) 
			{	
				if (currentWeapon==VALVE_WEAPON_HANDGRENADE) fired = attackValveHandgrenade( target );
				else if (currentWeapon==VALVE_WEAPON_SATCHEL) fired = attackValveSatchel( target );
				else {  botAction->add( BOT_FIRE_PRIM );  fired = true;  }
			}
			else 
			{	
				if (currentWeapon==VALVE_WEAPON_GAUSS) 
				{
					botAction->add( BOT_RELEASE_SEC );
					loadingGauss = false;
				}
				else if ( currentWeapon==VALVE_WEAPON_CROSSBOW || 
					      currentWeapon==VALVE_WEAPON_PYTHON   || 
						  currentWeapon==VALVE_WEAPON_RPG) 
				{	// these weapons had their correct mode set in armBestWeapon
					botAction->add( BOT_FIRE_PRIM );
				}
				else 
				{
					botAction->add( BOT_FIRE_SEC );
				}
				fired = true;
			}
			nextAttackTime = worldTime() + modWeapon[currentWeapon].fireDelay;
			if ( modWeapon[currentWeapon].fireDelay > 0 ) 
			{		// has to release button
				float rDelay = RANDOM_FLOAT( 0, 0.3 );	// add random delay
				nextAttackTime += rDelay;
			}
		}
	}
	return fired;
}


void PB_Weapon::finishAttack()
{
	//debugMsg( "Forced to finish attack!\n" );
	if (currentWeapon==VALVE_WEAPON_HANDGRENADE) {
		botAction->setViewDir( grenadeTarget, 5 );
		attackValveHandgrenade( grenadeTarget );
	}
	else if (currentWeapon==VALVE_WEAPON_SATCHEL) {
		attackValveSatchel( grenadeTarget );
	}
	else {
		debugMsg( "ERROR: Illegal wID!\n" );
	}
}




///////////////////////////////////////////////////////////////////////////////////
//
//  STANDARD QUERIES
//
///////////////////////////////////////////////////////////////////////////////////


int PB_Weapon::ammo1()
{
	return (bots[botSlot].m_rgAmmo[weapon_defs[currentWeapon].iAmmo1]);
}


int PB_Weapon::ammo2()
{
	return (bots[botSlot].m_rgAmmo[weapon_defs[currentWeapon].iAmmo2]);
}


float PB_Weapon::highAimProb()
{
	assert( modWeapon != 0 );
	return modWeapon[currentWeapon].highAimProb;
}


float PB_Weapon::getAudibleDistance( int attackFlags )
{
	assert( modWeapon != 0 );

	if (attackFlags & IN_ATTACK2)   return ( 2 * modWeapon[currentWeapon].volAttack2 );
	else							return ( 2 * modWeapon[currentWeapon].volAttack1 );
}


bool PB_Weapon::needReload()
// returns true if the current weapon needs to be reloaded
{
	// ammoclip values only available for armed weapons!
	if ( currentWeapon!=armedWeapon ) return false;

	bool shouldReload = false;
		
	if (modWeapon[currentWeapon].secAmmo && bestMode[currentWeapon]==2) {	
		// attack with secondary ammo
		if ( bots[botSlot].current_weapon.iAmmo2 == 0 ) {
			bestMode[currentWeapon] = 1;
			if ( bots[botSlot].current_weapon.iClip == 0 ) shouldReload = true;
		}
	}
	else {
		// attack with primary ammo
		if ( bots[botSlot].current_weapon.iClip == 0 ) shouldReload = true;
	}

	// check if reloading has to be set to false
	if (!shouldReload) reloading = false;

	return shouldReload;
}


void PB_Weapon::reload()
{
	// only execute if not reloading yet and weapon armed
	if (!reloading && currentWeapon==armedWeapon) {
		reloading = true;
		botAction->add( BOT_RELOAD );
		//debugMsg( "Reload!\n" );
	}
}


float PB_Weapon::bestDistance()
// returns best distance for currentWeapon
{
	assert( modWeapon != 0 );
	return modWeapon[currentWeapon].bestDist;
}

