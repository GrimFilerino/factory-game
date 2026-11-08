#include "components.h"
#include "aabb/aabb.h"
#include "transform/transform.h"
#include "camera/camera.h"
#include "input/input.h"

bool has_component(char* id, components_t component) {
        switch(component) {
                case COMPONENT_TRANSFORM:
                        return get_transform_component(id) ? true : false; 

                case COMPONENT_INPUT:
                        return entity_has_input(id); 

                case COMPONENT_CAMERA:
                        return camera_follows_entity(id);
                
                case COMPONENT_AABB:
                        return get_aabb_component(id) ? true : false;
        }
}
