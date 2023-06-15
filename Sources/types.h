#include <stdint.h>
#pragma warning( suppress : 26812)
typedef enum {
    GOAL_NIL = 1,
    GOAL_TRUE = 2,
    GOAL_FALSE = 4,
    GOAL_INTEGER = 8,
    GOAL_FLOAT = 16,
    GOAL_SYMBOL = 32,
    GOAL_STRING = 64,
    GOAL_LIST = 128,
    //GOAL_VECTOR = 256,
    //GOAL_HASH_MAP = 512,
    //GOAL_ATOM = 1024,
    //GOAL_FUNCTION_C = 2048,
    GOAL_FUNCTION = 4096,
} GoalType;

typedef struct G_ATOM GOAL_ATOM;

struct G_ATOM{
    GoalType type;
    void* value;
    GOAL_ATOM* child;
    size_t c_len;
};

typedef struct {
    GOAL_ATOM* atom;
    size_t len;
}GOAL_ENV;