#include <stdio.h>
#include <string.h>
#include "token.h"
#include "base64.h"
#include "hmac.h"
#include "md5.h"


typedef struct {
    char  et[32];
    char * version;
    char * method;
    char res[128];
    char sign[128];
} sign_msg;


typedef  struct {
    char * old_str;
    char * str;
}URL_PARAMETES;


static int url_encoding_for_token(sign_msg * msg, char * token, int maxlen) {
    int i, j, k, slen;
    sign_msg * temp_msg = msg;
    URL_PARAMETES url_patametes[] = {
       {"+","%2B"},
       {" ","%20"},
       {"/","%2F"},
       {"?","%3F"},
       {"%","%25"},
       {"#","%23"},
       {"&","%26"},
       {"=","%3D"},
    };
    char temp[128] = {0};
    /**
     * @brief res 进行url编码
     *
     */
    slen = strlen(temp_msg->res);
    for (i = 0, j = 0; i < slen; i++) {
        for (k = 0; k < 8; k++) {
            if (temp_msg->res[i] == url_patametes[k].old_str[0]) {
                memcpy(&temp[j], url_patametes[k].str, strlen(url_patametes[k].str));
                j += 3;
                break;
            }
        }
        if (k == 8) {
            temp[j++] = temp_msg->res[i];
        }

    }
    memcpy(temp_msg->res, temp, strlen(temp));
    temp_msg->res[strlen(temp)] = 0;

    /**
     * @brief sign 进行url 编码
     *
     */
    memset(temp, 0x00, sizeof(temp));
    slen = strlen(temp_msg->sign);
    for (i = 0, j = 0; i < slen; i++) {
        for (k = 0; k < 8; k++) {
            if (temp_msg->sign[i] == url_patametes[k].old_str[0]) {
                memcpy(&temp[j], url_patametes[k].str, strlen(url_patametes[k].str));
                j += 3;
                break;
            }
        }
        if (k == 8) {
            temp[j++] = temp_msg->sign[i];
        }
    }
    memcpy(temp_msg->sign, temp, strlen(temp));
    temp_msg->sign[strlen(temp)] = 0;

    sprintf(token, "version=%s&res=%s&et=%s&method=%s&sign=%s", temp_msg->version, temp_msg->res, temp_msg->et, temp_msg->method, temp_msg->sign);
    return strlen(token);
}


int onenet_creat_token_init(onenet_msg_t * msg, long long time, char * token, int maxlen) {
    int declen = 0;
    int enclen = 0;
    char plaintext[64] = {0};
    char hmac[64] = {0};
    sign_msg sign;
    memset(&sign, 0x00, sizeof(sign));
    sign.version = "2018-10-31";
    sprintf(sign.et, "%lld", time);
    sprintf(sign.res, "products/%s/devices/%s", msg->produt_id, msg->device_name);
    mbedtls_base64_decode((unsigned char *)plaintext, sizeof(plaintext), &declen, (unsigned char *)msg->key, strlen((char *)msg->key));

    char StringForSignature[256] = {0};

    sign.method = "md5";
    sprintf(StringForSignature, "%s\n%s\n%s\n%s", sign.et, sign.method, sign.res, sign.version);
    esp_hmac_md5((unsigned char *)plaintext, declen, (unsigned char *)StringForSignature, strlen(StringForSignature), (unsigned char *)hmac);

    mbedtls_base64_encode((unsigned char *)sign.sign, sizeof(sign.sign), &enclen, (unsigned char *)hmac, strlen(hmac));
    return url_encoding_for_token(&sign, token, maxlen);
}
