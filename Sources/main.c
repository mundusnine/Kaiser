#include <stdio.h>
#include "engine.h"

int main(int argc, char** argv) {
	engine_init("Dear ImGui", 1024, 768);

	
	engine_start();
	return 0;
}
