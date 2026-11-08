/*
 *
entity_t* wall = malloc(sizeof(*wall));
                        
                        *wall = (entity_t){
                                .type = type,
                                .id = uuid(),
                                .is_alive = 1,
                                .has_transform = 1,
                                .has_sprite = 1,
                                .has_health = 0,
                                .has_input = 0,
                                .has_aabb = 1,
                                .has_damage = 0,
                        };

                        if(entity_index == MAX_ENTITIES) {
                                create_log(ERROR, "Max entities was reached and no more entities can be created!");
                                return;
                        }

                        initialize_transform(wall->id, (vec2_t){ .x = 120, .y = 120}, 0.0f, true);
                        
                        char path[1024];
                        snprintf(path, sizeof(path), "%sassets/wall.png", GetApplicationDirectory());
                        initialize_sprite(wall->id, path, 32, 32);

                        initialize_aabb(wall->id, 32, 24, 0, 4);

                        entities[entity_index] = wall;
                        entity_index++;

 *
 *
 * */
