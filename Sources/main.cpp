#include "repl.h"
#include "compiler.h"
#include <string.h>

int kickstart(int argc, char** argv) {
	
	char filename[260] = {0};
	int len = snprintf(filename,260,"%s/proj.gc","./test");
	FILE* f = fopen(filename, "rb+");
	if(f == NULL){
		filename[len] = '\0';
		f = fopen(filename,"rb+");
	}
	
	ReplStatus status = compiler_init() ? Repl_OK : Repl_EXIT;

	// if(f != NULL && status == Repl_OK){
	// 	//found project file, load it !
	// 	size_t len = get_file_size(filename);
	// 	read_file(filename,big_file,big_size);
	// 	compiler_handle_repl_text(big_file,NULL,1);
		
	// 	//Did project load ?
	// 	if(compiler_get_state() == LUA_OK){
	// 		compiler_set_project();
	// 	}

	// 	compiler_do_start_commands();
	// }

	while(status != Repl_EXIT){
		if(status == Repl_RELOAD){
			repl_save_history();
			status = compiler_init() ? Repl_OK : Repl_EXIT;
		}

		repl_set_prompt("\0");//Reset the prompt history
		char* from_stdin = compiler_get_repl_input();
		size_t len = strlen(from_stdin);
		if(from_stdin[0] != '\0'){
			// kinc_mutex_lock(&compiler_mutex);
			status = compiler_handle_repl_text(from_stdin,NULL,1);
			// kinc_mutex_unlock(&compiler_mutex);
		}
		else if(from_stdin[0] == '\n' && len > 1){
			char* start = &from_stdin[1];
			repl_print(start);
		}
	}

	compiler_close();
	return 0;
}