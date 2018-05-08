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

pthread_mutex_t muteks;

string odebrane, wyswietlane;
char c=0, poprzednia=0;
bool started=0, zakonczenie=0;
uint64_t start, stop, ile_cykli, cps;
float czascalkowity=0;

void czas(void){

	double sekund;

	if(started==0){
			start=ClockCycles();
			started=1;
			poprzednia=c;
			return;
		}
	if(started ==1){
			stop=ClockCycles();
			started=0;
			zakonczenie=1;
		}

		if(zakonczenie){
			ile_cykli = stop - start;
			cps = SYSPAGE_ENTRY (qtime) -> cycles_per_sec;
			sekund = (double)ile_cykli / cps;
			czascalkowity+=sekund;
			if (sekund < 1.){
					odebrane += "0";
					cout << "*";
			}

			else if (sekund > 1. && sekund <3. ){
					odebrane += "1";
					cout << "-";
			}

			else if (sekund > 3. && sekund < 7.){
				if(odebrane=="01")
						wyswietlane+="A";
					else if(odebrane=="1000")
						wyswietlane+="B";
					else if(odebrane=="1010")
						wyswietlane+="C";
					else if(odebrane=="100")
						wyswietlane+="D";
					else if(odebrane=="0")
						wyswietlane+="E";
					else if(odebrane=="0010")
						wyswietlane+="F";
					else if(odebrane=="110")
						wyswietlane+="G";
					else if(odebrane=="0000")
						wyswietlane+="H";
					else if(odebrane=="00")
						wyswietlane+="I";
					else if(odebrane=="0111")
						wyswietlane+="J";
					else if(odebrane=="101")
						wyswietlane+="K";
					else if(odebrane=="0100")
						wyswietlane+="L";
					else if(odebrane=="11")
						wyswietlane+="M";
					else if(odebrane=="10")
						wyswietlane+="N";
					else if(odebrane=="111")
						wyswietlane+="O";
					else if(odebrane=="0110")
						wyswietlane+="P";
					else if(odebrane=="1101")
						wyswietlane+="Q";
					else if(odebrane=="010")
						wyswietlane+="R";
					else if(odebrane=="000")
						wyswietlane+="S";
					else if(odebrane=="1")
						wyswietlane+="T";
					else if(odebrane=="001")
						wyswietlane+="U";
					else if(odebrane=="0001")
						wyswietlane+="V";
					else if(odebrane=="011")
						wyswietlane+="W";
					else if(odebrane=="1001")
						wyswietlane+="X";
					else if(odebrane=="1011")
						wyswietlane+="Y";
					else if(odebrane=="1100")
						wyswietlane+="Z";
					else if(odebrane=="01111")
						wyswietlane+="1";
					else if(odebrane=="00111")
						wyswietlane+="2";
					else if(odebrane=="00011")
						wyswietlane+="3";
					else if(odebrane=="00001")
						wyswietlane+="4";
					else if(odebrane=="00000")
						wyswietlane+="5";
					else if(odebrane=="10000")
						wyswietlane+="6";
					else if(odebrane=="11000")
						wyswietlane+="7";
					else if(odebrane=="11100")
						wyswietlane+="8";
					else if(odebrane=="11110")
						wyswietlane+="9";
					else if(odebrane=="11111")
						wyswietlane+="0";
			odebrane.clear();
			cout <<endl<< wyswietlane<<endl;
			zakonczenie = 0;
			}
			else if (sekund > 7.){
				wyswietlane+=" ";
				cout <<endl<<wyswietlane<<endl;
			}
		}
}


void czytaj(void){

	int fd, rd;
	fd=open("/dev/ser1", O_RDONLY);

	read(fd, &c, 1);
	if(c!=poprzednia)
		czas();
	poprzednia=c;
	flushall();
	close(fd);
	}
void ustaw(void);
int main(int argc, char *argv[]) {
	ustaw();
	cout << "Kropka 0-1 sek." << endl;
	cout << "Kreska 1-3 sek." << endl;
	cout << "Koniec znaku 3-7 sek." << endl;
	cout << "Spacja 7+ sek." << endl;
	do{
	czytaj();
	}while(1);

	return EXIT_SUCCESS;
}

void ustaw(void){

		struct termios termio;
		int res;
		int baud;
		int fd;
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
		printf("Parametry portu ustawione \n");
}
