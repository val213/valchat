#pragma once
#ifndef CLIENT_CONFIG_H
#define CLIENT_CONFIG_H
#define SERVER_PORT 50050
#define MAX_MSG_SIZE 512
#define _CRT_SECURE_NO_WARNINGS
#include<WinSock2.h>
#include<Windows.h>
#include<Ws2tcpip.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#define HAVE_STRUCT_TIMESPEC
#include "pthread.h"
#include<thread>
#pragma comment (lib, "ws2_32.lib")
#pragma comment(lib,"pthreadVC2.lib")


#include<Mmsystem.h>
#include<winddi.h>
#pragma comment(lib,"winmm.lib")

#include"client_user.h"
#include"cmsg_dec.h"
#include"cmsg_enc.h"

#include"cusr_cmd.h"
#include"list.h"
#include"msg_cipher.h"
#include"msg_type.h"
#include "client_handle.h"
#include"client_log.h"
#include"ui.h"

#endif // !CLIENT_CONFIG_H

