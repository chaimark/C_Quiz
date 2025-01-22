#ifndef _CIPHER_HMAC_ALL_H
#define _CIPHER_HMAC_ALL_H

#define    MD5_DIGEST_SIZE  16
void esp_hmac_md5(unsigned char * key, int key_len, unsigned char * text, int text_len, unsigned char * hmac);

#endif /* _CIPHER_HMAC_ALL_H */
