#include "damage.h"
#include "../../../hashmap/hashmap.h"

Hashmap* damages;


void initialize_damage(char* entity_id, float damage, float crit_chance) {}

void update_crit_chance(char* entity_id, float new_crit_chance) {}

void update_damage(char* entity_id, float new_damage) {}

void do_damage(char* entity_id, char* other_entity_id) {}

damage_t* get_damage_component(char* entity_id) {
        return NULL;
}
