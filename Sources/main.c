#include <kinc/pch.h>

#include <kinc/graphics4/graphics.h>
#include <kinc/system.h>

#include <stdio.h>

static void update(){
	printf("Hello Kaiser !");	
}

int kickstart(int argc, char** argv) {
	kinc_init("Dear ImGui", 1024, 768, NULL, NULL);

	kinc_set_update_callback(update);
	kinc_start();
	return 0;
}
