#include "repl.h"

#include "fmt/color.h"
#include "fmt/core.h"

#define GOALC_VERSION_MAJOR 0
#define GOALC_VERSION_MINOR 1

replxx::Replxx repl;

void repl_clear(void){
    repl.clear_screen();
}

void repl_print(const char* msg){
    repl.print(msg);
}

void repl_set_prompt(const char* msg){
    static std::string old_proompt = std::string("");
    if(msg[0] == '\0'){
        old_proompt.reserve(8192);
        old_proompt.shrink_to_fit();
        return;
    }
    old_proompt.append(msg);
    std::string proompt = std::string(old_proompt);
    // proompt.append(compiler_get_prompt());
    repl.set_prompt(proompt);
}

const char* repl_readline(char* prompt){
    return repl.input(std::string(prompt));
}

void repl_set_history_max_size(size_t len){
    repl.set_max_history_size(len);
}
void repl_add_history(char* line){
    repl.history_add(std::string(line));
}

static char filepath[260] = "./goal.repl.history";

void repl_save_history(void){    
    repl.history_save(std::string(filepath));
}

void repl_load_history(void){
    FILE* f = fopen(filepath,"rb+");
    if (f != NULL) {
        fclose(f);
        repl.history_load(std::string(filepath));
    } else {
        fmt::print("Couldn't locate REPL history file at '{}'\n", filepath);
    }
}

void repl_greet(void){
    const char* message= 
    " __       __    __  ______  __    __  ______  \n"
    "|  \\     |  \\  |  \\/      \\|  \\  |  \\/      \\ \n"
    "| ▓▓     | ▓▓  | ▓▓  ▓▓▓▓▓▓\\ ▓▓  | ▓▓  ▓▓▓▓▓▓\\\n"
    "| ▓▓     | ▓▓  | ▓▓ ▓▓__| ▓▓ ▓▓  | ▓▓ ▓▓   \\▓▓\n"
    "| ▓▓     | ▓▓  | ▓▓ ▓▓    ▓▓ ▓▓  | ▓▓ ▓▓      \n"
    "| ▓▓     | ▓▓  | ▓▓ ▓▓▓▓▓▓▓▓ ▓▓  | ▓▓ ▓▓   __ \n"
    "| ▓▓_____| ▓▓__/ ▓▓ ▓▓  | ▓▓ ▓▓__/ ▓▓ ▓▓__/  \\\n"
    "| ▓▓     \\\\▓▓    ▓▓ ▓▓  | ▓▓\\▓▓    ▓▓\\▓▓    ▓▓\n"
    " \\▓▓▓▓▓▓▓▓ \\▓▓▓▓▓▓ \\▓▓   \\▓▓ \\▓▓▓▓▓▓  \\▓▓▓▓▓▓ \n";
    fmt::print(fmt::emphasis::bold | fg(fmt::color::deep_sky_blue), message);

    fmt::print("Welcome to GOAL {}.{}!\n", GOALC_VERSION_MAJOR,GOALC_VERSION_MINOR);

    fmt::print("Run {} or {} for help with common commands and REPL usage.\n",
            fmt::styled("help()", fmt::emphasis::bold | fg(fmt::color::rebecca_purple)),
            fmt::styled("keybinds()", fmt::emphasis::bold | fg(fmt::color::rebecca_purple)));
    fmt::print("Run ");
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::rebecca_purple), "lt()");
    // fmt::print(" to connect to the local target.\n");

    // fmt::print("Run ");
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::rebecca_purple), "(mi)");
    // fmt::print(" to rebuild the entire game.\n\n");

}

void repl_print_halp(void){
    fmt::print(fmt::emphasis::bold, "\nREPL Controls:\n");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::rebecca_purple), "clear()\n");
    fmt::print(" - Clear the current screen\n");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::rebecca_purple), "exit()\n");
    fmt::print(" - Exit the compiler\n");
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::rebecca_purple), "lt( [ip-address], [port-number] )\n");
    // fmt::print(
    //     " - Connect the listener to a running target. The IP address defaults to `127.0.0.1` and the "
    //     "port to `8112`\n");
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::rebecca_purple), "r( [ip-address], [port-number] )\n");
    // fmt::print(
    //     " - Attempt to reset the target and reconnect. After this, the target will have nothing "
    //     "loaded.\n");
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::rebecca_purple), "status()\n");
    // fmt::print(" - Send a ping-like message to the target. Requires the target to be connected\n");
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::rebecca_purple), "shutdown-target()\n");
    // fmt::print(" - If the target is connected, make it exit\n");

    // fmt::print(fmt::emphasis::bold, "\nCompiling & Building:\n");
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::lime_green), "ma()\n");
    // fmt::print(" - Build entire game\n");
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::lime_green), "mgp()\n");
    // fmt::print(" - Build gameplay code\n");
    // fmt::print(fmt::emphasis::bold | fg(fmt::color::lime_green), "mge()\n");
    // fmt::print(" - Build game engine\n");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::lime_green), "m(\"filename\")\n");
    fmt::print(" - Compile a goal source file\n");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::lime_green), "ml(\"filename\")\n");
    fmt::print(" - Compile and Load (or reload) a goal source file\n");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::lime_green), "make (\"project-file\")\n");
    fmt::print(
        " - Build a project. This file must be a target in the make. If project file was passed at start or in config project file can be nil. \n");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::lime_green), "watch (\"project-file\")\n");
    fmt::print(
        " - Watch and build any files in the project and any out-of-date dependencies.\n");

    fmt::print(fmt::emphasis::bold, "\nOther:\n");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::magenta), "gr()\n");
    fmt::print(" - Enter a Goal REPL\n");
}

void repl_print_keybind_help(void) {
  fmt::print(fmt::emphasis::bold, "\nREPL KeyBinds:\n");
//   for (const auto& bind : repl_config.keybinds) {
//     fmt::print("{}\n", fmt::styled(bind.string(), fmt::fg(fmt::color::cyan)));
//     fmt::print("{}\n", fmt::styled(bind.description, fmt::fg(fmt::color::gray)));
//   }
}

static char commited_text[4096];
static size_t text_len;
static replxx::Replxx::ACTION_RESULT commit(char32_t code){
    repl.set_state(
        replxx::Replxx::State(commited_text, static_cast<int>(text_len)));
    return repl.invoke(replxx::Replxx::ACTION::COMMIT_LINE, code);
}
replxx::Replxx::key_press_handler_t repl_commit_text_action(std::string& text_to_commit) {
    text_len = text_to_commit.size();
    memcpy(commited_text,text_to_commit.c_str(),sizeof(char) * text_len);
    return commit;

}

// #include <kinc/network/socket.h>
// #include <kinc/threads/thread.h>
// #include <kinc/threads/mutex.h>
// #include "compiler.h"

// typedef struct shared_data{
//     int test;
// } shared_data_t;

// shared_data_t data;
// kinc_socket_t server_sock;
// kinc_socket_t client_sock;
// kinc_thread_t server_thread;
// kinc_mutex_t compiler_mutex;
// static int (*should_shutdown)(void);

// static void server_run(void* param){
//     kinc_thread_set_name("Luauc_Server_thread");
//     u_int remoteAddr = 0xDEADBEEF;
//     u_int remoteport = 0xDEADBEEF;
//     while(!kinc_socket_accept(&server_sock,&client_sock,&remoteAddr,&remoteport)){

//     }
//     while(!should_shutdown()){
        
//     }
// }
// int repl_start_server(int (shutdown_callback)(void),int port){
//     should_shutdown = shutdown_callback;
//     kinc_thread_wait_and_destroy(&server_thread);
//     kinc_mutex_init(&compiler_mutex);
//     kinc_socket_init(&server_sock);
//     kinc_socket_options_t opts;
//     kinc_socket_options_set_defaults(&opts);
//     if(!kinc_socket_open(&server_sock,&opts) || !kinc_socket_listen(&server_sock,1)){
//         kinc_socket_destroy(&server_sock);
//         return 0;
//     }
//     kinc_thread_init(&server_thread,server_run,&data);
    
//     return 1;
// }