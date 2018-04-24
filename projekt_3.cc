#include <cstdlib>
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/neutrino.h>
#include <sys/syspage.h>
#include <inttypes.h>
#include <pthread.h>

using namespace std;

#define MILIARD 1000000000L;
#define milisekundy = 1000000L

pthread_mutex_t muteks;


string odebrane;
char c=0, poprzednia=0;
bool started=0, zakonczenie=0;
uint64_t start, stop, ile_cykli, cps;

void dekodowanie(){
	
	if(odebrane.compare("01")==0)
		cout << "A";
	else if(odebrane.compare("1000")==0)
		cout << "B";
	else if(odebrane.compare("1010")==0)
		cout << "C";
	else if(odebrane.compare("100")==0)
		cout << "D";
	else if(odebrane.compare("0")==0)
		cout << "E";
	else if(odebrane.compare("0010")==0)
		cout << "F";
	else if(odebrane.compare("110")==0)
		cout << "G";
	else if(odebrane.compare("0000")==0)
		cout << "H";
	else if(odebrane.compare("00"==0))
		cout << "I";
	else if(odebrane.compare("0111")==0)
		cout << "J";
	else if(odebrane.compare("101")==0)
		cout << "K";
	else if(odebrane.compare("0100")==0)
		cout << "L";
	else if(odebrane.compare("11")==0)
		cout << "M";
	else if(odebrane.compare("10")==0)
		cout << "N";
	else if(odebrane.compare("111")==0)
		cout << "O";
	else if(odebrane.compare("0110")==0)
		cout << "P";
	else if(odebrane.compare("1101")==0)
		cout << "Q";
	else if(odebrane.compare("010")==0)
		cout << "R";
	else if(odebrane.compare("000")==0)
		cout << "S";
	else if(odebrane.compare("1")==0)
		cout << "T";
	else if(odebrane.compare("001")==0)
		cout << "U";
	else if(odebrane.compare("0001")==0)
		cout << "V";
	else if(odebrane.compare("011")==0)
		cout << "W";
	else if(odebrane.compare("1001")==0)
		cout << "X";
	else if(odebrane.compare("1011")==0)
		cout << "Y";
	else if(odebrane.compare("1100")==0)
		cout << "Z";
	else if(odebrane.compare("01111")==0)
		cout << "1";
	else if(odebrane.compare("00111")==0)
		cout << "2";
	else if(odebrane.compare("00011")==0)
		cout << "3";
	else if(odebrane.compare("00001")==0)
		cout << "4";
	else if(odebrane.compare("00000")==0)
		cout << "5";
	else if(odebrane.compare("10000")==0)
		cout << "6";
	else if(odebrane.compare("11000")==0)
		cout << "7";
	else if(odebrane.compare("11100")==0)
		cout << "8";
	else if(odebrane.compare("11110")==0)
		cout << "9";
	else if(odebrane.compare("11111")==0)
		cout << "0";
	
	odebrane.clr();
	
}

void OdliczCzas(void){

	double sekund;

	if(started==0){
			start=ClockCycles();
			started=1;
			cout << "poczatek pomiaru" <<endl;
			return;
		}
	if(started ==1){
			stop=ClockCycles();
			started=0;
			zakonczenie=1;
			cout << "zakonczenie pomiaru" << endl;
		}

		if(zakonczenie){
			ile_cykli = stop - start;
			cps = SYSPAGE_ENTRY (qtime) -> cycles_per_sec;
			sekund = (double)ile_cykli / cps;
			cout << "Minelo" << sekund << "sekund."<<endl;
			if (sekund < 1.)
				odebrane += "0";
			else if (sekund > 1. && sekund <3. )
				odebrane += "1";
			else if (sekund > 7.)
				dekodowanie();
			zakonczenie = 0;
		}


}


void czytaj(void){

	int fd, rd;
	timespec nanoczas = {0};

	nanoczas.tv_nsec = 500 * milisekundy;
	
	fd=open("/dev/ser1", O_RDONLY);
	read(fd, &c, 1);
	if(c!=poprzednia)
		OdliczCzas();
	nanosleep(&nanoczas,NULL);
	poprzednia=c;
	flushall();
	close(fd);
	}

void ustaw(void);

void 
int main(int argc, char *argv[]) {
	ustaw();
	do{
	czytaj();
	}while(1);
	
	return EXIT_SUCCESS;
}

void ustaw(void){
	int fd;
		struct termios termio;
		int res;
		int baud;

		baud = 9600;
		fd = open("/dev/ser1", O_RDWR);

		res = tcgetattr(fd, &termio);		// Read /dev/ser1 settings into termio variable

		termio.c_cflag &= ~(PARENB|PARODD|PARSTK|CSIZE|CSTOPB); // no parity bit, one stop bit
		termio.c_cflag |= CS8;				// characters with a length of 8 bits
		termio.c_cflag &= ~(IHFLOW|OHFLOW);		// no flow control
		cfsetispeed(&termio, baud);			// change input speed
		cfsetospeed(&termio, baud);			// change output speed

		res = tcsetattr(fd, TCSANOW, &termio);		// Set the new /dev/ser1 settings
		if(res == -1) {
			perror("Blad");
		}
		printf("parametry portu ustawione \n");
}
