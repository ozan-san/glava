#ifndef _GLAVA_H
#define _GLAVA_H

#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>

#define GLAVA_REQ_NONE   0
#define GLAVA_REQ_RESIZE 1

struct gl_data;

typedef struct renderer {
    volatile bool alive;
    bool    mirror_input;
    size_t  bufsize_request, rate_request, samplesize_request;
    char*   audio_source_request;
    int     off_tex;      /* final GL texture for offscreen rendering */
    pthread_mutex_t lock; /* lock for reading from offscreen texture  */
    pthread_cond_t  cond; /* cond for reading from offscreen texture  */
    volatile struct {
        int x, y, w, h;
    } sizereq;
    volatile int sizereq_flag;
    struct gl_data* gl;
} renderer;

/* External API */

typedef struct renderer* volatile renderer_handle;
__attribute__((noreturn, visibility("default"))) void (*glava_abort)            (void);
__attribute__((noreturn, visibility("default"))) void (*glava_return)           (void);
__attribute__((visibility("default")))           void glava_assign_external_ctx (void* ctx);
__attribute__((visibility("default")))           void glava_entry               (int argc, char** argv, renderer_handle* ret);
__attribute__((visibility("default")))           void glava_terminate           (renderer_handle* ref);
__attribute__((visibility("default")))           void glava_reload              (renderer_handle* ref);
__attribute__((visibility("default")))           void glava_sizereq             (renderer_handle r, int x, int y, int w, int h);
__attribute__((visibility("default")))           void glava_wait                (renderer_handle* ref);

#endif /* _GLAVA_H */
