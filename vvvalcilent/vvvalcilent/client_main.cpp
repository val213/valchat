#include"client_config.h"
void socklib_init()
{
	WSADATA wsa_data;
	int ret;
	if ((ret = WSAStartup(MAKEWORD(2, 2), &wsa_data)) != 0)
	{
		errmusic();
		printf("client:windows socket ;oad failed with error code:%d\n", ret);
		exit(-1);
	}
}

void sock_cleanup(int fd)
{
	closesocket(fd);
	WSACleanup();
}


int  client_sock_init(char* addr)
{
	int sfd;
	struct sockaddr_in serv;
	socklib_init();

	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		errmusic();
		printf("client: socket error \n");
		return -1;
	}

	memset(&serv, 0, sizeof(serv));
	serv.sin_family = AF_INET;
	serv.sin_port = htons(SERVER_PORT);
	if (inet_pton(AF_INET, addr, &serv.sin_addr) <= 0)
	{
		errmusic();
		printf("client: inet_pton error for %s\n", addr);
		return -2;
	}
	//���ӷ�����
	//sockaddr<-sockaddr_in
	if (connect(sfd, (struct sockaddr*)&serv, sizeof(serv)) < 0)
	{
		errmusic();
		printf("client:connect error!");
		return -3;
	}

	return sfd;
}


int init_args(int argc, char** argv)
{
	if (argc != 2)
	{
		errmusic();
		fprintf(stderr, "usage:%s <IPv4 server ip>\n", *argv);
		return -1;
	}

	myself.w_sockfd = client_sock_init(argv[1]);
	if (myself.w_sockfd < 0) return -1;
	return 0;
}
//���߳�
void* client_cli_thread(void* arg)
{
	char line[MAX_LINE_LEN];
	char user_prompt[MAX_PROMPT_LEN];
	while (1)
	{
		if (myself.w_id != -1)
		{
			_snprintf(user_prompt, MAX_PROMPT_LEN, "%s(%s)#", USER_PROM, myself.w_name);
		}
		else
		{
			_snprintf(user_prompt, MAX_PROMPT_LEN, "%s(unknown)#", USER_PROM);
		}
		printf("%s", user_prompt);
		memset(line, 0, sizeof(line));
		if (fgets(line, MAX_LINE_LEN, stdin) == NULL)
		{
			printf("fgets == null");
			break;
		}
		if (line[strlen(line) - 1] == '\n')
		{
			line[strlen(line) - 1] = '\0';
		}
		//ִ��ָ����������ж��Ƿ�Ϊ�˳�ָ��
		if (usr_cmd_process(line) == -2)
		{

			printf("client: user logout����\n");
			break;
		}
	}
	closesocket(myself.w_sockfd);
	printf("client: exit pthread...\n");
	return NULL;
}

void client_main_loop()
{
	int n;
	pthread_t client_stdin_pid;
	pthread_create(&client_stdin_pid, NULL, client_cli_thread, NULL);
	while ((n = recv(myself.w_sockfd, myself.w_buf, MAX_MSG_SIZE, NULL)) > 0)
	{
		printf("client: recv msg_len=%d\n", n);
		//ѭ����ӡ�յ���myself.w_buf��ʮ������
		for (int i = 0; i < n; i++)
		{
			printf("%02x ", myself.w_buf[i]);
		}
		printf("\n");
		
		


		dec_server_resp(myself.w_buf, n);
	}
	printf("client: recv len<0, exiting����\n");
}


#define TIMEOUT_SECONDS 60

//Ҫ��ֻ��һ��������IPv4
int fore = 0, back = 0;
int main(int argc, char** argv)
{

	system("title ValClient");
	//���ÿ���̨��ɫ
	SetColor(fore, back);
	//�û����ݽṹ��ʼ��
	init_user_struct(&myself);
	//������ʼ��
	if (init_args(argc, argv) < 0)
	{
		return -1;
	}
	//�ͻ�����ѭ��������
	//���߳�
	client_main_loop();
	//������
	sock_cleanup(myself.w_sockfd);


	return 0;
}