// ai generated shit
// A hack for processing keys in the console since glfw can't handle them in termux lol

#include "ConsoleInput.h"
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

char readCharNonBlocking()
{
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    char c = 0;
    read(STDIN_FILENO, &c, 1);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, flags);

    return c;
}
