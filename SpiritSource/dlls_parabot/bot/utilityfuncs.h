#ifndef UTILITY_FUNCS_H
#define UTILITY_FUNCS_H


#include "extdll.h"



Vector getRight( const Vector &vec );
bool canShootAt( edict_t *bot, Vector target );

bool playerExists( edict_t *pEdict );
bool isAlive(edict_t *pEdict);
bool isUnderwater( edict_t *ent );
bool needsAir( edict_t *ent );

// for Valve:
edict_t* tripmineOwner( CBaseEntity *tripmine );
edict_t* laserdotOwner( edict_t *laser );
CBaseEntity* getActiveItem( edict_t *player );

#endif