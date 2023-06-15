#include "compiler.h"

#include "types.h"

#include <assert.h>

#include "fmt/color.h"
#include "fmt/core.h"

#define HEAP_SIZE 1024 * 1024 * 1024
static uint8_t* heap = NULL;
static size_t heap_top = 0;

static void* allocate(size_t size) {
    size_t old_top = heap_top;
    heap_top += size;
    assert(heap_top <= HEAP_SIZE);
    return &heap[old_top];
}

ReplStatus compiler_handle_repl_text(char* text, char* chunkname, int from_user_input)
{
    if (text[0] == '\0') {
        return Repl_OK;
    }
    
    char sym[512] = { 0 };
    size_t sym_len = 0;
    char* pos = &text[0];
    pos--;
    GOAL_ATOM* root = NULL;
    GOAL_ATOM** cur = &root;
    GOAL_ATOM** last_atom = &root;
START:
    pos++;
    if(pos[0] != '\0') {
        char c = pos[0];
        if (c == ' ') {
            goto START;
        }
        if (c == '(') {
            GOAL_ATOM* atom = (GOAL_ATOM*)allocate(sizeof(GOAL_ATOM));
            atom->type = GOAL_LIST;
            atom->child = (GOAL_ATOM*)allocate(sizeof(GOAL_ATOM));
        }
        sym[sym_len] = pos[0];
    }

END:
    return Repl_ERROR_SEND;
}


ReplStatus compiler_init(void)
{
    heap = (uint8_t*)malloc(HEAP_SIZE);
    assert(heap != NULL);

    repl_greet();

    return ReplStatus::Repl_OK;
}

void compiler_close(void)
{
}

static char prompt_out[64];
char* compiler_get_prompt(void)
{
    std::string prompt = fmt::format(fmt::emphasis::bold | fg(fmt::color::rebecca_purple), "gc > ");
    snprintf(prompt_out, 256, "\033[0m%s", prompt.c_str());
    return prompt_out;
}

const char* temp = "\0";
char* compiler_get_repl_input(void) {
    char* str = (char*)repl_readline(compiler_get_prompt());
    if (str) {
        repl_add_history(str);
        return str;
    }
    else {

        return (char*)temp;
    }
}
