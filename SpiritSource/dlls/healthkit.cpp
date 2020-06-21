/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "player.h"
#include "items.h"
#include "gamerules.h"

#define SF_WALLHEALTH_SPEC    1
#define SF_WALLHEALTH_SKILL    2

extern int gmsgItemPickup;

class CHealthKit : public CItem
{
	void Spawn( void );
	void Precache( void );
	BOOL MyTouch( CBasePlayer *pPlayer );

/*
	virtual int		Save( CSave &save ); 
	virtual int		Restore( CRestore &restore );
	
	static	TYPEDESCRIPTION m_SaveData[];
*/

};


LINK_ENTITY_TO_CLASS( item_healthkit, CHealthKit );

/*
TYPEDESCRIPTION	CHealthKit::m_SaveData[] = 
{

};


IMPLEMENT_SAVERESTORE( CHealthKit, CItem);
*/

void CHealthKit :: Spawn( void )
{
	Precache( );
	SET_MODEL(ENT(pev), "models/w_medkit.mdl");

	CItem::Spawn();
}

void CHealthKit::Precache( void )
{
	PRECACHE_MODEL("models/w_medkit.mdl");
	PRECACHE_SOUND("items/smallmedkit1.wav");
}

BOOL CHealthKit::MyTouch( CBasePlayer *pPlayer )
{
	if ( pPlayer->pev->deadflag != DEAD_NO )
	{
		return FALSE;
	}

	if ( pPlayer->TakeHealth( gSkillData.healthkitCapacity, DMG_GENERIC ) )
	{
		MESSAGE_BEGIN( MSG_ONE, gmsgItemPickup, NULL, ENT(pPlayer->pev) );
			WRITE_STRING( STRING(pev->classname) );
		MESSAGE_END();

		EMIT_SOUND(ENT(pPlayer->pev), CHAN_ITEM, "items/smallmedkit1.wav", 1, ATTN_NORM);

		if ( g_pGameRules->ItemShouldRespawn( this ) )
		{
			Respawn();
		}
		else
		{
			UTIL_Remove(this);	
		}

		return TRUE;
	}

	return FALSE;
}



//-------------------------------------------------------------
// Wall mounted health kit
//-------------------------------------------------------------
class CWallHealth : public CBaseToggle
{
public:
	void Spawn( );
	void Precache( void );
	void EXPORT Off(void);
	void EXPORT Recharge(void);
	void KeyValue( KeyValueData *pkvd );
	void Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value );
	virtual int	ObjectCaps( void ) { return (CBaseToggle :: ObjectCaps() | FCAP_CONTINUOUS_USE) & ~FCAP_ACROSS_TRANSITION; }
	virtual int		Save( CSave &save );
	virtual int		Restore( CRestore &restore );
	virtual STATE GetState( void );

	static	TYPEDESCRIPTION m_SaveData[];

	float m_flNextCharge; 
	int		m_iReactivate ; // DeathMatch Delay until reactivated
	int		m_iJuice;
	int		m_iOn;			// 0 = off, 1 = startup, 2 = going
	float   m_flSoundTime;
};

TYPEDESCRIPTION CWallHealth::m_SaveData[] =
{
	DEFINE_FIELD( CWallHealth, m_flNextCharge, FIELD_TIME),
	DEFINE_FIELD( CWallHealth, m_iReactivate, FIELD_INTEGER),
	DEFINE_FIELD( CWallHealth, m_iJuice, FIELD_INTEGER),
	DEFINE_FIELD( CWallHealth, m_iOn, FIELD_INTEGER),
	DEFINE_FIELD( CWallHealth, m_flSoundTime, FIELD_TIME),
};

IMPLEMENT_SAVERESTORE( CWallHealth, CBaseEntity );

LINK_ENTITY_TO_CLASS(func_healthcharger, CWallHealth);


void CWallHealth::KeyValue( KeyValueData *pkvd )
{
	if (	FStrEq(pkvd->szKeyName, "style") ||
				FStrEq(pkvd->szKeyName, "height") ||
				FStrEq(pkvd->szKeyName, "value1") ||
				FStrEq(pkvd->szKeyName, "value2") ||
				FStrEq(pkvd->szKeyName, "value3"))
	{
		pkvd->fHandled = TRUE;
	}
	else if (FStrEq(pkvd->szKeyName, "dmdelay"))
	{
		m_iReactivate = atoi(pkvd->szValue);
		pkvd->fHandled = TRUE;
	}
	else
		CBaseToggle::KeyValue( pkvd );
}

void CWallHealth::Spawn()
{
	Precache( );

	pev->solid		= SOLID_BSP;
	pev->movetype	= MOVETYPE_PUSH;

	UTIL_SetOrigin(this, pev->origin);		// set size and link into world
	UTIL_SetSize(pev, pev->mins, pev->maxs);
	SET_MODEL(ENT(pev), STRING(pev->model) );

	if (pev->spawnflags & SF_WALLHEALTH_SKILL)
		pev->health = (int)GetSkillCvar( (char *)STRING(pev->message) );

	if (pev->spawnflags & SF_WALLHEALTH_SPEC)
		m_iJuice = max( pev->health, 0);
	else
		m_iJuice = gSkillData.healthchargerCapacity;

	if ( m_iJuice > 0 )
		pev->frame = 0;
	else
		pev->frame = 1;
			
	//LRC
	if (m_iStyle >= 32) LIGHT_STYLE(m_iStyle, "a");
	else if (m_iStyle <= -32) LIGHT_STYLE(-m_iStyle, "z");
}

void CWallHealth::Precache()
{
	PRECACHE_SOUND("items/medshot4.wav");
	PRECACHE_SOUND("items/medshotno1.wav");
	PRECACHE_SOUND("items/medcharge4.wav");
}


void CWallHealth::Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value )
{ 
	// Make sure that we have a caller
	if (!pActivator)
		return;
	// if it's not a player, ignore
	if ( !pActivator->IsPlayer() )
		return;

	// if there is no juice left, turn it off
	if (m_iJuice <= 0)
	{
		pev->frame = 1;			
		//LRC
		if (m_iStyle >= 32) LIGHT_STYLE(m_iStyle, "z");
		else if (m_iStyle <= -32) LIGHT_STYLE(-m_iStyle, "a");
		Off();
	}
          
          CBasePlayer *pPlayer = (CBasePlayer *)pActivator;
	
	// if the player doesn't have the suit, or there is no juice left, make the deny noise
	if ((m_iJuice <= 0) || (!(pPlayer->m_iHideHUD & ITEM_SUIT)) || (pActivator->pev->health == 100))
	{
		if (m_flSoundTime <= gpGlobals->time)
		{
			m_flSoundTime = gpGlobals->time + 0.62;
			EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/medshotno1.wav", 1.0, ATTN_NORM );
		}
		return;
	}

	// scrama: altrules
	if ( (pActivator->pev->health == 100) && (CVAR_GET_FLOAT ( "sv_altweapons" )) )
	{
		if (m_flSoundTime <= gpGlobals->time)
		{
			m_flSoundTime = gpGlobals->time + 0.62;
			EMIT_SOUND_DYN(ENT(pev), CHAN_ITEM, "items/medshotno1.wav", 0.85, ATTN_NORM, 0, PITCH_NORM+1 );
		}
		return;
	}

	SetNextThink( 0.25 );
	SetThink(&CWallHealth::Off);

	// Time to recharge yet?

	if (m_flNextCharge >= gpGlobals->time)
		return;

	// Play the on sound or the looping charging sound
	if (!m_iOn)
	{
		m_iOn++;
		EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/medshot4.wav", 1.0, ATTN_NORM );
		m_flSoundTime = 0.56 + gpGlobals->time;
	}
	if ((m_iOn == 1) && (m_flSoundTime <= gpGlobals->time))
	{
		m_iOn++;
		EMIT_SOUND(ENT(pev), CHAN_STATIC, "items/medcharge4.wav", 1.0, ATTN_NORM );
	}


	// charge the player
	if ( pActivator->TakeHealth( 1, DMG_GENERIC ) )
	{
		m_iJuice--;
	}

	// govern the rate of charge
	m_flNextCharge = gpGlobals->time + 0.1;
}

void CWallHealth::Recharge(void)
{
		EMIT_SOUND(ENT(pev), CHAN_ITEM, "items/medshot4.wav", 1.0, ATTN_NORM );
	m_iJuice = gSkillData.healthchargerCapacity;
	pev->frame = 0;			
	//LRC
	if (m_iStyle >= 32) LIGHT_STYLE(m_iStyle, "a");
	else if (m_iStyle <= -32) LIGHT_STYLE(-m_iStyle, "z");
	SetThink(&CWallHealth:: SUB_DoNothing );
}

void CWallHealth::Off(void)
{
	// Stop looping sound.
	if (m_iOn > 1)
		STOP_SOUND( ENT(pev), CHAN_STATIC, "items/medcharge4.wav" );

	m_iOn = 0;

	if ((!m_iJuice) &&  ( ( m_iReactivate = g_pGameRules->FlHealthChargerRechargeTime() ) > 0) )
	{
		SetNextThink( m_iReactivate );
		SetThink(&CWallHealth::Recharge);
	}
	else
		SetThink(&CWallHealth:: SUB_DoNothing );
}

STATE CWallHealth::GetState( void )
{
	if (m_iOn == 2)
		return STATE_IN_USE;
	else if (m_iJuice)
		return STATE_ON;
	else
		return STATE_OFF;
}

//=============================================
//
// Health charger Control Entity by Maxwel
//
//=============================================

#define SF_WALLHEALTH_CONTROL_ONCE    1
#define SF_WALLHEALTH_CONTROL_AWARD    2
#define SF_WALLHEALTH_CONTROL_SKILL    4
#define SF_WALLHEALTH_CONTROL_NSND    8
 
class CWallHealthControl : public CPointEntity
{
public:
    void Spawn( void );
    void Precache( void );
    void Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value );
private:
    int m_iPrevJuice;
};
LINK_ENTITY_TO_CLASS( trigger_healthcharger_control, CWallHealthControl );

void CWallHealthControl::Precache( void )
{
    PRECACHE_SOUND("items/medshotno1.wav");
    PRECACHE_SOUND("items/medcharge4.wav");
}

void CWallHealthControl::Spawn(void)
{
    Precache();
    pev->solid = SOLID_NOT;
    pev->movetype = MOVETYPE_NONE;
    
    if (pev->spawnflags & SF_WALLHEALTH_CONTROL_SKILL)
    {
        pev->health = (int)GetSkillCvar( (char *)STRING(pev->message) );
    }
}

void CWallHealthControl::Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value )
{
    CWallHealth *pRecharge = NULL;
    pRecharge = (CWallHealth *)UTIL_FindEntityByTargetname( NULL, STRING(pev->target) );
    
    if (pRecharge)
    {
        m_iPrevJuice = pRecharge->m_iJuice;
        
        if (pev->spawnflags & SF_WALLHEALTH_CONTROL_AWARD)
        {
            pRecharge->m_iJuice += (int)pev->health;
        }
        else
            pRecharge->m_iJuice = (int)pev->health;
        
        if (pRecharge->m_iJuice > 0)
        {
            pRecharge->pev->frame = 0;
        }
        else
            pRecharge->pev->frame = 1;
        
        if (!(pev->spawnflags & SF_WALLHEALTH_CONTROL_NSND))
        {
            if ( (m_iPrevJuice <= 0) && (pRecharge->m_iJuice > 0) )
            {
                EMIT_SOUND_DYN( ENT(pRecharge->pev), CHAN_STATIC, "items/medcharge4.wav", 1, ATTN_NORM, 0, 150 );
            }
            if ( (m_iPrevJuice > 0) && (pRecharge->m_iJuice <= 0) )
            {
                EMIT_SOUND_DYN( ENT(pRecharge->pev), CHAN_STATIC, "items/medshotno1.wav", 1, ATTN_NORM, 0, 150 );
            }
        }
    }
    
    if (pev->spawnflags & SF_WALLHEALTH_CONTROL_ONCE)
    {
        UTIL_Remove( this );
    }
}


