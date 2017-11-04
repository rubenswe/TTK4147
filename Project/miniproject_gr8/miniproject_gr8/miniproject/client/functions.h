#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>

#include "miniproject.h"

#define PORT 9999
#define BUFLEN 64
#define SERVER "192.168.0.1"
#define PERIOD 1500

#define Kp 10
#define Ki 800
#define REF 1

struct udp_conn conn;
pthread_mutex_t udp;

void init_simulation();
void *pi();
double extract_output();
void stop_simulation();
void request_output();
void set_input(double u);