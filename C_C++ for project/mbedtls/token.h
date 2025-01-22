#ifndef _CIPHER_TOKEN_H
#define _CIPHER_TOKEN_H
#ifdef  __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdint.h>
    typedef struct onenet_msg {
        char produt_id[32];
        char device_name[32];
        char key[128];
    }onenet_msg_t;

    extern int onenet_creat_token_init(onenet_msg_t * msg, long long time, char * token, int maxlen);
#ifdef  __cplusplus
}
#endif /* __cplusplus */
#endif /* _CIPHER_SHA256_H */
