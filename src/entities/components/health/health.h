#ifndef HEALTH_H
#define HEALTH_H

/**
 *  @brief Health Struct 
 *  
 *  @param current_health The health of an entity (2 bytes)
 *  @param max_health The max health of an entity (2 bytes)
 */

typedef struct health {
        float current_health;
        float max_health;
} health_t;

/**
 *  @brief Initialize the health data of an entity 
 *  
 *  @param[in] entityId The string id of the entity
 *  @param[in] health The starting health
 *  @param[in] max_health The current max health of the entity
 */
void initialize_health(char* entityId, float health, float max_health);

/**
 *  @brief A way to adjust the max_health
 *  
 *  @param[in] entityId The string id of the entity
 *  @param[in] new_max_health The amount the new max_health should be
 */
void set_max_health(char* entityId, float new_max_health);


/**
 *  @brief A way to adjust health by healing or taking damage
 *  
 *  @param[in] entityId The string id of the entity
 *  @param[in] amount The amount which the health should be adjusted
 */
void adjust_health(char* entityId, float amount);


/**
 *  @brief A way to get the health of an entity
 *
 *  @param[in] entityId The string id of the entity
 *
 *  @return The health of the entity
 */
float get_health(char* entityId);


#endif
