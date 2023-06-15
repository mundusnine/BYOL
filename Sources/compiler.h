#pragma once

#include "repl.h"

#ifdef __cplusplus
extern "C" {
#endif

ReplStatus compiler_init(void);
void compiler_close(void);

//char* compiler_get_prompt(void);

ReplStatus compiler_handle_repl_text(char* text,char* chunkname,int from_user_input);
//void compiler_set_project(void);
//int compiler_get_project(void);
//int compiler_do_start_commands(void);
//int compiler_get_state(void);
char* compiler_get_repl_input(void);
//void compiler_set_options(int debug_level);
//int compiler_connect_to_target(char* ip,int port);
//void compiler_ping_server(void);
//char* compiler_send_server( const char* cmd, const char* chunkname, const char* content,size_t len);
//void compiler_close_server(void);

#ifdef __cplusplus
}
#endif