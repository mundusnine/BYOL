#pragma once

#ifdef __cplusplus
#include "replxx.hxx"
replxx::Replxx::key_press_handler_t repl_commit_text_action(std::string& text_to_commit);
extern "C" {
#endif

#pragma warning( suppress : 26812)
typedef enum { Repl_OK, Repl_RELOAD, Repl_EXIT, Repl_ERROR_SEND } ReplStatus;

void repl_clear(void);
void repl_print(const char* msg);
void repl_set_prompt(const char* msg);
const char* repl_readline(char* prompt);
void repl_add_history(char* line);
void repl_save_history(void);
void repl_load_history(void);
void repl_greet(void);
void repl_print_halp(void);
void repl_print_keybind_help(void);

#ifdef __cplusplus
};
#endif