#include <stdio.h>
#include "engine.h"

#ifdef KORE_G1 
// this means we are using Kinc, sadly we don't have a G6.
int kickstart(int argc, char** argv) {
#elif _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
#else
int main(int argc, char** argv) {
#endif
	init_gameplay();
	return 0;
}
