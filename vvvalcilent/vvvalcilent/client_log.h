#pragma once
#ifndef CLIENT_LOG_H
#define CLIENT_LOG_H
#define FILED_SEPS "/"
/*ÿһ�е��ֶθ���*/
#define MSG_FIELDS 4

#define CLIENT_LOG_FILE "msg_bakup.txt"


void client_log_save(char* msg, int from, int to);
void client_log_export(FILE* sfp, FILE* dfp, int from, int to);


#endif // !CLIENT_LOG_H	