//
// HPB_bot - botman's High Ping Bastard bot
//
// (http://planethalflife.com/botman/)
//
// bot_client.h
//

void Client_Valve_DeathMsg(void *p, int noMatter);
void BotClient_Valve_WeaponList(void *p, int bot_index);
void BotClient_Valve_CurrentWeapon(void *p, int bot_index);
void HumanClient_CurrentWeapon( void *p, int clientIndex );
void BotClient_Valve_AmmoX(void *p, int bot_index);
void BotClient_Valve_AmmoPickup(void *p, int bot_index);
void BotClient_Valve_WeaponPickup(void *p, int bot_index);
void BotClient_Valve_ItemPickup(void *p, int bot_index);
void BotClient_Valve_Health(void *p, int bot_index);
void BotClient_Valve_Battery(void *p, int bot_index);
void BotClient_Valve_Damage(void *p, int bot_index);


