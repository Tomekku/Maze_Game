#include "../include/gameManager.h"
#ifdef __WIN32__
#undef main
#include "../include/functions.h"
#endif

int main(int argc, char const *argv[]) {
	#ifdef __WIN32__
	HWND stealth;
	stealth=FindWindowA("ConsoleWindowClass",NULL);
	ShowWindow(stealth,0);
	#endif
    runGame();
    return 0;
}