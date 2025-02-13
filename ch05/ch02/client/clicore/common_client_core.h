#ifndef COMMON_CLIENT_CORE_H
#define COMMON_CLIENT_CORE_H

#include <calc_proto_ser.h>
#include <calc_proto_req.h>

struct context_t {
  int sd;
  struct calc_proto_ser_t* ser;
};

/* Функция для преобразования строки в число с плавающей точкой*/
int _to_double(const char* str, double* num);

/* Функции для преобразования кодов ошибок и статусов в строки */
const char* _error_to_str(int error_code);
const char* _status_to_str(status_t status);

/* Обработчики ошибок и ответов */
void on_error(void* obj, int req_id, int error_code);
void on_response(void* obj, struct calc_proto_resp_t resp);

/* Функция для разбора пользовательского ввода */
void parse_client_input(char* buf, struct calc_proto_req_t* req, int *brk, int*cnt);

#endif
