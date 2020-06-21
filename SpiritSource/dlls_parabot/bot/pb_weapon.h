#if !defined( PB_WEAPON_H )
#define PB_WEAPON_H


#include "pb_action.h"


// weapon structure
typedef struct {
	char	name[64];
	float	bestDist;
	float	cone;
	float	highAimProb;
	bool	secAmmo;
	float	volAttack1;
	float	volAttack2;
	float	visAttack1;
	float	visAttack2;
	float	fireDelay;
	char	shortName[32];
} tWeaponRec;


#define MAX_WEAPONS 32	// have to fit in 32-bit-flag

// weapon ID values for Valve's Half-Life Deathmatch
#define MIN_VALVE_WEAPONS		   1

#define VALVE_WEAPON_CROWBAR       1
#define VALVE_WEAPON_GLOCK         2
#define VALVE_WEAPON_PYTHON        3
#define VALVE_WEAPON_MP5           4
#define VALVE_WEAPON_CROSSBOW      5
#define VALVE_WEAPON_SHOTGUN       6
#define VALVE_WEAPON_RPG           7
#define VALVE_WEAPON_GAUSS         8
#define VALVE_WEAPON_EGON          9
#define VALVE_WEAPON_HORNETGUN    10
#define VALVE_WEAPON_HANDGRENADE  11
#define VALVE_WEAPON_TRIPMINE     12
#define VALVE_WEAPON_SATCHEL      13
#define VALVE_WEAPON_SNARK        14

#define MAX_VALVE_WEAPONS		  15

// weapon flags
#define WF_UNDERWATER			(1<<0)
#define WF_FAST_ATTACK			(1<<1)
#define WF_IMMEDIATE_ATTACK		(1<<2)
#define WF_HIDE_ORIGIN			(1<<3)
#define WF_NEED_GRENADE			(1<<4)
#define WF_SINGLE_SHOT_KILL	    (1<<5)
#define WF_ENEMY_ABOVE			(1<<6)
#define WF_ENEMY_BELOW			(1<<7)

// define weapon advice flags
#define WA_EXACT_AIM			(1<<0)
#define WA_FIRE					(1<<1)
#define WA_CLOSE_UP				(1<<2)
#define WA_GAIN_DISTANCE		(1<<3)


#define CHANGE_WEAPON_DELAY		1.0	// time needed to switch between weapons



const char* getWeaponName( int wId );
// returns the short weapon name of weapon wId


class PB_Weapon
{
	
public:
	
	PB_Weapon();

	PB_Weapon( int wId );
	// directly initializing currentWeapon
	
	void init( int slot, edict_t *ent, PB_Action *action );
	// has to be called with the botSlot before all other methods

	float getScore( float distance, float hitProb, int flags, bool checkAmmo );
	// returns the weapon-score for given situation

	float getAudibleDistance( int attackFlags );
	// returns the audible distance

	bool attack( Vector target, float accuracy, Vector relVel = Vector(0,0,0) );
	// attacks in best mode at best time the given position when accuracy is reached

	bool hasToFinishAttack() { return grenadePrepared; }
	// true if bot has to finish e.g. a grenade attack

	int armedGrenade() { return grenadeWId; }
	// returns the weapon id that has to finish attack

	void finishAttack();
	// throws grenade to avoid blasting up 

	bool needReload();
	// returns true if the current weapon needs to be reloaded

	void reload();
	// reloads weapon

	float bestDistance();
	// returns best distance for currentWeapon

	int ammo1();

	int ammo2();

	float highAimProb();
	// returns necessary aimProb for a high precision attack for current weapon

	void setCurrentWeapon( int wId );
	
	void registerArmedWeapon( int wId );

	char* name() {  return ( (char*)&modWeapon[currentWeapon].name );  }
	// returns the weapon-name

	float cone()	{ return modWeapon[currentWeapon].cone; }
	void setNextAttackTime( float time ) {	nextAttackTime = time; }

	int bestAttackMode() {  return bestMode[currentWeapon];  }

	void setAttackMode( int mode )  {  bestMode[currentWeapon] = mode;  }



private:

	int currentWeapon;			// holds the Weapon ID that all functions are working with
	int armedWeapon;			// weapon the player has armed

	int			botSlot;		// slot the bot is using
	edict_t		*botEnt;
	PB_Action	*botAction;		// pointer to action-instace the bot is using

	float	nextAttackTime;		// worldTime next attack can occur
	float	lastAttackTime;		// worldTime last attack was executed
	bool	reloading;			// true if current weapon is being reloaded

	int bestMode[MAX_WEAPONS];	// if weapons have several modes, the best get
								// stored here in getWeaponScore()
	
	tWeaponRec *modWeapon;		// pointer to the correct mod-weapons
	int minModWeapon, maxModWeapon;
	

	bool grenadePrepared;		// for handgrenades and satchels
	float grenadeLaunchTime;	// when to throw/bomb
	Vector grenadeTarget;		// for handgrenades to remember where to throw if forced to
	int grenadeWId;				// holds wid if grenadePrepared

	bool loadingGauss;
	float loadStartTime;

	// private methods:

	void initMOD();
	
	bool attackValveHandgrenade( Vector &target );
	bool attackValveSatchel( Vector &target );
};

#endif