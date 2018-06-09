#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

//using namespace std;

int Xconnect(int *s);

void Xread(int client);

#endif