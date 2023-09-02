#include "engine.h"
#include "service_provider.h"
#include <stddef.h>

typedef enum{
    Update,
}private_funcs_e;

static Engine engine ={0};
void engine_init(const char* window_name,int w, int h){
    //load service and open window
    service_provider_init(window_name,w,h);

    create_input_provider(&engine);
}
void engine_update(void){
    engine.input->private_funcs[Update](NULL);
}