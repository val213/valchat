#pragma once

#pragma once
#ifndef SERV_CONFIG_H
#define SERV_CONFIG_H

#define	SERV_PORT		50050
#define	MAX_USER_NUM	200
#define	MAX_FRIEND_NUM	50
#define	CONF_LOW_ID		1000
/*用户查询所有在线用户每次返回的用户数目*/
#define MAX_USER_SIZE	20

#define MAX_MSG_SIZE	512

#define	SERV_USER_FILE		"serv_user_file"
#define	SERV_FRIEND_FILE	"serv_friend_file"



#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <stdio.h>
#include <windows.h>
#include <Ws2tcpip.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define HAVE_STRUCT_TIMESPEC
#include "pthread.h"
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "pthreadVC2.lib")
#include<thread>
#include<mutex>
#include"list.h"
#include"msg_type.h"
#include"serv_config.h"
#include"serv_handle.h"
#include"serv_dec.h"
#include"serv_enc.h"
#include"serv_user.h"
#include"ui.h"
#include<Mmsystem.h>
#include<winddi.h>
#pragma comment(lib,"winmm.lib")
typedef struct thread_args
{
	pthread_t t_tid;
	int t_sckfd;
	/*每个用户的id关联一个子线程*/
	int t_id;
}THREAD_ARGS;
#endif // !SERV_CONFIG_H



