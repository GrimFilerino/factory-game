#ifndef DAMAGE_H
#define DAMAGE_H

typedef struct damage {
        unsigned short damage; // <-- current expected damage of an entity (can change based on weapons and upgrades)
        unsigned short crit_chance; // <-- current expected crit chance of an entity (can change based on weapons and upgrades, range from 0 to 1000 aka 0 to 100%)
} damage_t;


void set_damage_data(char* entityId, damage_t damage);
void do_damage(char* entityId, char* otherEntityId);

#endif



