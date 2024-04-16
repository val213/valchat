#pragma once
#ifndef SERV_ENC_H
#define SERV_ENC_H
#include "serv_config.h"

int init_reg_struct(REG_RESP* r, int id, char* reason);
void init_msg_hdr(MSG_HDR* h, int n, unsigned char type, unsigned char stype);
int enc_reg_resp(char* buf, int* n, int id, char* reason);
int init_login_struct(LIG_RESP* l, int stat, char* name, char* reason);
int enc_login_resp(char* buf, int* n, int stat, char* name, char* resaon);
int init_fmgt_struct(FRND_RESP* f, unsigned char stype, short stat, FRND_ST* fs, short cnt);
int enc_fmgt_resp(char* buf, int* n, unsigned char stype, short stat, FRND_ST* fs, short cnt);
int init_chat_struct(CHAT_RESP* c, int stat, const char* reason);
int enc_chat_resp(char* buf, int* n, int stat, const char* reason);


#endif // !SERV_ENC_H