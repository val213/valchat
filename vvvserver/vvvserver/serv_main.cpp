#include "serv_config.h"
#include <mutex> // 添加互斥锁所需的头文件

// 声明一个全局互斥锁
std::mutex mtx;
using namespace std;
int serv_sock_init()
{
	WSADATA wsa_data;
	int ret, lfd;

	struct sockaddr_in	saddr;

	ret = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (ret != 0)
	{
		printf("serv: windows socket load failed with error code %d\n", ret);
		return -1;
	}

	lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (lfd < 0)
	{
		perror("socker return error!\n");
		return -1;
	}

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(SERV_PORT);

	ret = bind(lfd, (struct sockaddr*)&saddr, sizeof(saddr));
	if (ret < 0)
	{
		perror("scoker bind error!\n");
		return -1;
	}

	listen(lfd, 10);

	return lfd;
}

void serv_sock_clean(int fd)
{
	closesocket(fd);
	WSACleanup();
}

void* client_thread(void* targs)
{
	THREAD_ARGS* a = (THREAD_ARGS*)targs;
	int fd = a->t_sckfd;
	int uid = a->t_id;
	int n;
	char buf[MAX_MSG_SIZE];

	for (;;)
	{
		n = recv(fd, buf, MAX_MSG_SIZE, 0);
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
		printf("recv buf: ");
		for (int i = 0; i < n; i++)
		{
			printf("%02x ", (unsigned char)buf[i]);
		}
		printf("\n");
		SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		//printf("client_thread:n= %d\n", n);
		if (n <= 0)
		{
			printf("serv: rcv error, exit thread! n=%d,fd=%d\n", n, fd);
			break;
		}
		//mtx.lock();
		if (handle_client_msgs(&uid, fd, buf, n) == -2)
		{
			printf("serv: handle msg return -2, thread exiting...\n");
			break;
		}
		//mtx.unlock();
	}

	usr_logout_exit(uid);
	free(targs);

	return NULL;
}

void serv_main_loop(int fd)
{

	int cfd;
	int len;
	char line[80];
	struct sockaddr_in caddr;
	THREAD_ARGS* targs;
	
	for (;;)
	{
		
		len = sizeof(caddr);
		printf("serv: waitting for client's connection......\n");

		cfd = accept(fd, (struct sockaddr*)&caddr, &len);
		printf("serv: connection from %s, port %d\n",
			inet_ntop(AF_INET, &caddr.sin_addr, line, sizeof(line)), ntohs(caddr.sin_port));

		targs = (THREAD_ARGS*)malloc(sizeof(*targs));
		if (targs == NULL)
		{
			printf("serv: memory malloc for thread args failed!\n");
			closesocket(cfd);
			continue;
		}

		memset(targs, 0, sizeof(*targs));
		targs->t_sckfd = cfd;
		mtx.lock();
		pthread_create(&targs->t_tid, NULL, &client_thread, (void*)targs);
		mtx.unlock();
	}

}

int init_args(int argc, char** argv)
{
	if (argc > 3)
	{
		fprintf(stderr, "%s <user file> <friend file>\n", argv[0]);
		return -1;
	}

	init_all_usr_struct(argc, argv);

	return 0;
}

int serv_init(int argc, char** argv)
{
	if (init_args(argc, argv) < 0)
	{
		return -1;
	}

	return serv_sock_init();
}



int main(int argc, char** argv)
{

	system("title ValServer");
	hide();
	setcolor("color 0A");
	for (int i = 0; i < MAX_USER_NUM; i++)
	{
		memset(&all_users[i], 0, sizeof(IM_USER));
	}
	thread r(codeRain);
	thread v(valchat);
	thread m(bgm);

	//setcolor("color 1F");

	Sleep(2000);
	
	int lfd; //listrn fd;
	
	lfd = serv_init(argc, argv);
	if (lfd < 0)
	{
		fprintf(stderr, "serv: socket init error!\n");
		return -1;
	}

	serv_main_loop(lfd);

	serv_sock_clean(lfd);
	r.join();
	v.join();
	m.join();
	return 0;
}