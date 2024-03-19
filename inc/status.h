#ifndef STATUS_H
#define STATUS_H

typedef enum {
    JUPITER_OK = 0,
    JUPITER_UNKNOWN,
    JUPITER_INVALID_ARGS,
    JUPITER_RESOURCE_EXHAUSTED,
    JUPITER_UNREACHABLE,
    JUPITER_TIMEOUT,
    JUPITER_EMPTY,
    JUPITER_OUT_OF_RANGE,
    JUPITER_UNIMPLEMENTED,
    JUPITER_UNINITIALIZED,
    JUPITER_INTERNAL_ERROR,
    JUPITER_INCOMPLETE,
    JUPITER_NUM_STATUS_CODES,
} JupiterStatus;

// Use to forward failures or continue on success.
#define status_ok_or_return(code)              \
    ({                                         \
        __typeof__(code) status_expr = (code); \
        if (status_expr) return status_expr;   \
    })

#endif