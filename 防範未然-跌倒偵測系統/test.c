#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

/* the followings are timer function */
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <locale.h>

timer_t timerid;


/* the followings are I2C function */
#define sensor_addr	0x0A

#if 0
BCM2835_I2C_CLOCK_DIVIDER_2500  10us = 100 kHz
BCM2835_I2C_CLOCK_DIVIDER_626  2.504us = 399.3610 kHz
BCM2835_I2C_CLOCK_DIVIDER_150  60ns = 1.666 MHz (default at reset)
BCM2835_I2C_CLOCK_DIVIDER_148  59ns = 1.689 MHz
#endif

uint16_t clk_div = BCM2835_I2C_CLOCK_DIVIDER_2500;

void i2c_set_baudrate(uint32_t baudrate)
{
        uint32_t divider;
        /* use 0xFFFE mask to limit a max value and round down any odd number */
        divider = (BCM2835_CORE_CLK_HZ / baudrate) & 0xFFFE;
        bcm2835_i2c_setClockDivider( (uint16_t)divider );
}

void sensor_write(unsigned char *data, int len)
{
	bcm2835_i2c_write(data, len);
}

int sensor_read(unsigned char cmd, unsigned char *data, int len)
{
	unsigned char cmdbuf[2];

	cmdbuf[0] = cmd;
	bcm2835_i2c_write(cmdbuf, 1);
	bcm2835_i2c_read(data, len);
	return 0;
}

void stop_sensor_op(void)
{
	unsigned char wbuf[2];
	
	wbuf[0] = 0x00;
	sensor_write(wbuf, 1);
	sleep(1);
}

void start_sensor_op(void)
{
	unsigned char wbuf[2];
	
	wbuf[0] = 0x01;
	sensor_write(wbuf, 1);
	sleep(1);
}

int pi_i2c_init(void)
{
    if (!bcm2835_init()) {
        printf("bcm2835_init failed. Are you running as root??\n");
        return -1;
    }
    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress((uint8_t)sensor_addr);
    bcm2835_i2c_setClockDivider(clk_div);
    i2c_set_baudrate(40*1024); /* set to 50K */

    return 0;
}

void print_data(unsigned char *buf)
{
    unsigned short data[8][8];
    int i, j, k;

    /* transform data */
    for (i = 0; i < 128;) {
        for (j = 0; j < 8; j++) {
            for (k = 0; k < 8; k++) {
                data[j][k] = (buf[i+1] << 8) | buf[i];
                i += 2;
            }
        }
    }

    for (j = 0; j < 8; j++) {
        for (k = 0; k < 8; k++) {
	    //printf("%3.2f ", (float)data[j][k]/10);
	    printf("%d, ", data[j][k]);
        }
        printf("\n");
    }
#if 0
    printf("\n\n");
    for (j = 0; j < 8; j++) {
        for (k = 0; k < 8; k++) {
	    printf("%4x ", data[j][k]);
        }
        printf("\n");
    }
#endif
}

void timer_handler(int sig, siginfo_t *si, void *uc)
{
	time_t mytime;
	struct tm *mytm;
	char my_date[12];
	char my_week[12];
	char my_time[12];

	unsigned char buf[256];
	unsigned char ambientbuf[3];
	unsigned short amb_data;

	mytime=time(NULL);
	mytm=localtime(&mytime);
	strftime(my_date,12,"%F",mytm);
	strftime(my_week,12,"%A",mytm);
	strftime(my_time,12,"%H:%M:%S",mytm);
	printf("\n%s %s %s\n\n", my_date, my_week, my_time);

	sensor_read(0x03, ambientbuf, 2);
	amb_data = (ambientbuf[1] << 8) | ambientbuf[0];
	printf("amb_data=%3.2f\n", (float)amb_data/10);
	sensor_read(0x02, buf, 128);
	print_data(buf);
}

int stop_timer(void)
{
   return(timer_delete(timerid));
}

int start_timer(void)
{

   char *my_locale;

   struct sigaction sa;
   struct itimerspec value;
   struct sigevent sev;

   my_locale=setlocale(LC_TIME,"");
   setlocale(LC_TIME,my_locale);

   /* Establish handler for timer signal */
   sa.sa_flags = SA_SIGINFO;
   sa.sa_sigaction = timer_handler;
   sigemptyset(&sa.sa_mask);
   if (sigaction(SIGRTMIN, &sa, NULL) == -1) {
      printf("sigaction error\n");
      return -1;
   }

   /* Create the timer */
   sev.sigev_notify = SIGEV_SIGNAL;
   sev.sigev_signo = SIGRTMIN;
   sev.sigev_value.sival_ptr = &timerid;
   if (timer_create(CLOCK_REALTIME, &sev, &timerid) == -1) {
      printf("timer_create error\n");
      return -2;
   }
   //printf("timer ID is 0x%lx\n", (long) timerid);

   /* Start the timer */
   value.it_value.tv_sec = 3; /* 3 seconds */
   value.it_value.tv_nsec = 0;
   value.it_interval.tv_sec = 3; /* 3 seconds */
   value.it_interval.tv_nsec = 0;

   if (timer_settime(timerid, 0, &value, NULL) == -1) {
      printf("timer_settime error");
      return -3;
   }
   return 0;
}

int main(int argc, char **argv)
{
	unsigned char buf[256];
	unsigned char wbuf[1];
	unsigned char ambientbuf[3];
	int i,j,k;
	int cnt;
	unsigned short amb_data;

	if (pi_i2c_init() != 0)
	   return -1;

	/* start thermal operation */
	start_sensor_op();
#if 1
	/* get current state */
	sensor_read(0xf7, buf, 1);
	printf("content 0xf7: %x\n", buf[0]);
	/* amplifier gain */
	sensor_read(0xf1, buf, 1);
	printf("0xf1 amplifier gain: %x\n", buf[0]);
#endif

#if 0
	/* set fps = 1, cont, gain auto adjust */
	wbuf[0] = 0xf7;
	wbuf[1] = 0x99;
	sensor_write(wbuf, 2);
	sleep(1);
	sensor_read(0xf7, buf, 1);
	printf("content f7: %x\n", buf[0]);
	sleep(1);

	sensor_read(0xf7, buf, 1);
	printf("af start content f7: %x\n", buf[0]);
	sleep(1);
#endif
	
#if 0
	/* get emission adjust data */
	sensor_read(0xf2, ambientbuf, 2);
	printf("emission adjust data: %x %x\n", ambientbuf[0], ambientbuf[1]);
#endif

	start_timer();

#if 0 /* use timer function to read the data */
	for (cnt=0; cnt<3;cnt++) {
		printf("Number[%d] \n", cnt);
	sensor_read(0x03, ambientbuf, 2);
	amb_data = (ambientbuf[1] << 8) | ambientbuf[0];
	printf("amb_data=%3.2f\n", (float)amb_data/10);
		/* get infrared output data */
		//wbuf[0] = 0x02;
		//bcm2835_i2c_read_register_rs(wbuf, buf, 128);
		sensor_read(0x02, buf, 128);
		print_data(buf);
	    sleep(3);
	}
#else
	while (1) {
	   ;
	}
#endif
	stop_sensor_op(); /* stop thermal sensor */
	stop_timer(); /* stop timer */
	bcm2835_i2c_end(); /* stop I2C */
}


