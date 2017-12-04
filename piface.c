#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <bcm2835.h>
#include <pthread.h>
#include "hd44780.h"
#include "commonLcd.h"
#include "spiLcd.h"

#define PIN RPI_GPIO_P1_22 

hd44780 header;
time_t rawtime;
struct tm *timeinfo;
char time_of_day[16];
int offset = 0;
int len;
char fortySP[40];

void *threadFunc(void *arg)
{
    while (1)
    {
	if (!bcm2835_gpio_lev(PIN)) {
		readBytes(&header, INTCAPA);
		printf("INTCAPA: %d %x\n", header.spiD, header.spiD);
	}
	delay(500);
    }

}
int
main ()
{
	if (!bcm2835_init())
		exit(-1);

	bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
	bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_UP);

	pthread_t gpioThread;
	pthread_create(&gpioThread,NULL,threadFunc,"gpioRead");
	
	strcpy(fortySP, "                                        ");

	setDefaultHd44780 (&header);
	initialiseDisplay (&header);
	clearDisplay (&header);
	moveCursor (&header, CURSOR_HOME);
	cursorControl (&header, 0);
	cursorBlink (&header, 0);

	while (1)
	{
		time (&rawtime);
		timeinfo = localtime (&rawtime);
	
		strftime (time_of_day, 16, "%T %b,%d\n", timeinfo);
	
		clearDisplay (&header);
		moveCursor (&header, CURSOR_HOME);
		printString (&header, time_of_day);
		printString (&header, "\n");
		sleep (2);
	}

	pthread_join(gpioThread,NULL);
	bcm2835_close();

	return 0;
}
