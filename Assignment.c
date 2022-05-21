#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

char* deletespaces(char *buffer){
int x = 0, y = 0;
while (buffer[x]) {
  if (buffer[x] != ' ')
  buffer[y++] = buffer[x];
  x++;
}
buffer[y] = '\0';
return buffer;
}

int stringtoint(char *buffer){
int i,result = 0;
for(i=0; i<strlen(buffer); i++) {
  result = result * 10 + (buffer[i] - '0');
}
return result;
}

void write2020(int totalcases, int totaldeaths, int maxcases, int maxdeaths){

int fd1 = open("analysis_summary_2020.txt", O_RDWR | O_CREAT, 0750);
char writethis[200];
sprintf(writethis, "Total cases over the year 2020: %d\nTotal deaths over the year 2020: %d\nThe maximum number of cases reported per date: %d\nThe maximum number of deaths reported per date: %d\n",totalcases,totaldeaths,maxcases,maxdeaths);
write(fd1, writethis, strlen(writethis));
}

void read2020(){

int fd1 = open("2020.txt", O_RDWR | O_CREAT, 0750);
lseek(fd1, 20, SEEK_SET);
int i, readcount;
int totalcases=0, totaldeaths=0, maxcases=0, maxdeaths=0;
char c, casesbuffer[50], deathsbuffer[50];

do {
  readcount = read(fd1,&c,1);
  if(c==',') {
    casesbuffer[0] = '\0';
    for(i=0;i<100;i++){
	readcount = read(fd1,&c,1);
	if(c != ','){
	  strcat(casesbuffer,(char[2]){c});}
	else{
	  casesbuffer[i+5]='\0';
	  deletespaces(casesbuffer);
	  totalcases += stringtoint(casesbuffer);
	  if(stringtoint(casesbuffer) > maxcases)
	    maxcases = stringtoint(casesbuffer);
	    
	  deathsbuffer[0] = '\0';
	  for(i=0;i<100;i++){
	    readcount = read(fd1,&c,1);
	    if(c != '\n'){
		strcat(deathsbuffer,(char[2]){c});}
	    else{
		deathsbuffer[i+5]='\0';
		deletespaces(deathsbuffer);
		totaldeaths += stringtoint(deathsbuffer);
	    	if(stringtoint(deathsbuffer) > maxdeaths)
		maxdeaths = stringtoint(deathsbuffer);
		break;
	    }
	  }
	break;
	}
  }}
}while(readcount > 0);
write2020(totalcases,totaldeaths,maxcases,maxdeaths);
close(fd1);
}

void write2021(int totalcases, int totaldeaths, int maxcases, int maxdeaths){

int fd1 = open("analysis_summary_2021.txt", O_RDWR | O_CREAT, 0750);
char writethis[200];
sprintf(writethis, "Total cases over the year 2021: %d\nTotal deaths over the year 2021: %d\nThe maximum number of cases reported per date: %d\nThe maximum number of deaths reported per date: %d\n",totalcases,totaldeaths,maxcases,maxdeaths);
write(fd1, writethis, strlen(writethis));
}

void read2021(){
int fd1 = open("2021.txt", O_RDWR | O_CREAT, 0750);
lseek(fd1, 20, SEEK_SET);
int i, readcount;
int totalcases=0, totaldeaths=0, maxcases=0, maxdeaths=0;
char c, casesbuffer[50], deathsbuffer[50];

do {
  readcount = read(fd1,&c,1);
  if(c==',') {
    casesbuffer[0] = '\0';
    for(i=0;i<100;i++){
	readcount = read(fd1,&c,1);
	if(c != ','){
	  strcat(casesbuffer,(char[2]){c});}
	else{
	  casesbuffer[i+5]='\0';
	  deletespaces(casesbuffer);
	  totalcases += stringtoint(casesbuffer);
	  if(stringtoint(casesbuffer) > maxcases)
	    maxcases = stringtoint(casesbuffer);
	    
	  deathsbuffer[0] = '\0';
	  for(i=0;i<100;i++){
	    readcount = read(fd1,&c,1);
	    if(c != '\n'){
		strcat(deathsbuffer,(char[2]){c});}
	    else{
		deathsbuffer[i+5]='\0';
		deletespaces(deathsbuffer);
		totaldeaths += stringtoint(deathsbuffer);
	    	if(stringtoint(deathsbuffer) > maxdeaths)
		maxdeaths = stringtoint(deathsbuffer);
		break;
	    }
	  }
	break;
	}
  }}
}while(readcount > 0);
write2021(totalcases,totaldeaths,maxcases,maxdeaths);
close(fd1);
}

void readfinal(int fd1, int *yearinfo){
int i, readcount, linenum=0;
int totalcases=0, totaldeaths=0, maxcases=0, maxdeaths=0;
char c, casesbuffer[50], deathsbuffer[50], maxcasebuffer[50], maxdeathbuffer[50];

do {
  readcount = read(fd1,&c,1);
  if(c==':') {
    switch(linenum){
    	case 0:
        casesbuffer[0] = '\0';
        for(i=0;i<100;i++){
	  readcount = read(fd1,&c,1);
	  if(c != '\n'){
	    strcat(casesbuffer,(char[2]){c});
	    }
	  else{
	    casesbuffer[i+5]='\0';
	    deletespaces(casesbuffer);
	    totalcases = stringtoint(casesbuffer);
	    linenum++;
	    break;
	    }}
	    break;
	
	case 1:
	  deathsbuffer[0] = '\0';
	  for(i=0;i<100;i++){
	    readcount = read(fd1,&c,1);
	    if(c != '\n'){
		strcat(deathsbuffer,(char[2]){c});
		}
	    else{
		deathsbuffer[i+5]='\0';
		deletespaces(deathsbuffer);
		totaldeaths = stringtoint(deathsbuffer);
	    	linenum++;
		break;
	    }}
		break;
	case 2:
          maxcasebuffer[0] = '\0';
          for(i=0;i<100;i++){
	    readcount = read(fd1,&c,1);
	    if(c != '\n'){
	      strcat(maxcasebuffer,(char[2]){c});
	     }
	  else{
	      maxcasebuffer[i+5]='\0';
	      deletespaces(maxcasebuffer);
	      maxcases = stringtoint(maxcasebuffer);
	      linenum++;
	      break;
	    }}
	      break;
	case 3:
          maxdeathbuffer[0] = '\0';
          for(i=0;i<100;i++){
	    readcount = read(fd1,&c,1);
	    if(c != '\n'){
	      strcat(maxdeathbuffer,(char[2]){c});
	      }
	  else{
	      maxdeathbuffer[i+5]='\0';
	      deletespaces(maxdeathbuffer);
	      maxdeaths = stringtoint(maxdeathbuffer);
	      linenum++;
	      break;
	    }}
	      break;
	      }
	}
  }
while(readcount > 0 && linenum <= 3);
yearinfo[0] = totalcases;
yearinfo[1] = totaldeaths;
yearinfo[2] = maxcases;
yearinfo[3] = maxdeaths;
close(fd1);
}

void writefinal(int *yearinfo2020, int *yearinfo2021){
int fd1 = open("final_summary.txt", O_RDWR | O_CREAT, 0750);
char writethis[200];
int totalcases = yearinfo2020[0] + yearinfo2021[0];
int totaldeaths = yearinfo2020[1] + yearinfo2021[1];
int maxcases = 0, maxdeaths = 0;
if(yearinfo2020[2] > yearinfo2021[2])
	maxcases = yearinfo2020[2];
else
	maxcases = yearinfo2021[2];
	
if(yearinfo2020[3] > yearinfo2021[3])
	maxdeaths = yearinfo2020[3];
else
	maxdeaths = yearinfo2021[3];


sprintf(writethis, "Across the two years, the total of cases: %d\nThe total of deaths: %d\nThe maximum number of cases reported per date: %d\nThe maximum number of deaths reported per date: %d",totalcases,totaldeaths,maxcases,maxdeaths);
write(fd1, writethis, strlen(writethis));
close(fd1);
}

int main() {
int status;
pid_t pid2020 = fork();
if (pid2020 == 0)
  read2020();

else {
  pid_t pid2021 = fork();
  if(pid2021 == 0)
    read2021();

else {
waitpid(pid2020, &status, 0);
waitpid(pid2021, &status, 0);
int yearinfo2020[4];
int yearinfo2021[4];
int fd1 = open("analysis_summary_2020.txt", O_RDWR | O_CREAT, 0750);
int fd2 = open("analysis_summary_2021.txt", O_RDWR | O_CREAT, 0750);
readfinal(fd1, yearinfo2020);
readfinal(fd2, yearinfo2021);
writefinal(yearinfo2020,yearinfo2021);
}}
return 0;
}

