#pragma once

#ifdef GL_core_profile
#define VERSION(number) #version number
#else
#define VERSION(number) "#version "#number
#endif