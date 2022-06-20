#include <stdio.h>
#include <termios.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    struct termios old, new;
    char ch = 0;
    tcgetattr(0, &old);
    new = old;
    new.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
			    | INLCR | IGNCR | ICRNL | IXON);
    new.c_oflag &= ~OPOST;
    new.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    new.c_cflag &= ~(CSIZE | PARENB);
    new.c_cflag |= CS8;
    tcsetattr(0,TCSANOW,&new);
    while(ch != 'q') {
	read(0, &ch, 1);
	printf((ch >= '0' && ch <= '9')?("Digit\r\n"):("No digit\n"));
    }
    tcsetattr(0,TCSANOW,&old);
    return 0;
}