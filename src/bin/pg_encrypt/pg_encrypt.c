/*
 * Portions Copyright (c) 1996-2022, PostgreSQL Global Development Group
 * Portions Copyright(c) 1994, Regents of the University of California
 * Portions Copyright (c) 1996-2022, PostgreSQL Global Development Group
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <resolv.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <resolv.h>
#include <string.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/x509.h>

    int main()
{
    EVP_CIPHER_CTX *ctx;
    char *base64Encode(const char *buffer, int length);

    unsigned char key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    unsigned char iv[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    unsigned char encdata[1024] = {0};
    unsigned char decdata[1024] = {0};

    int enclen = 0, tmplen;
    int declen = 0;
    unsigned char msg[1024];
    scanf("%s", msg);
    int ret;
    OpenSSL_add_all_algorithms();
    ctx = EVP_CIPHER_CTX_new();


    /* Encrypt */
    ret = EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
    if (ret != 1)
    {
        printf("EVP_EncryptInit_ex failed.\n");
        goto end;
    }

    ret = EVP_EncryptUpdate(ctx, encdata, &enclen, msg, strlen(msg));
    if (ret != 1)
    {
        printf("EVP_EncryptUpdate failed.\n");
        goto end;
    }

    ret = EVP_EncryptFinal_ex(ctx, encdata + enclen, &tmplen);
    if (ret != 1)
    {
        printf("EVP_EncryptFinal_ex failed.\n");
        goto end;
    }

    enclen = enclen + tmplen;

    char *encode = base64Encode(encdata, enclen);
    printf("加密密码为%s\n", encode);
    /* Decrypt */
//     ret = EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
//     if (ret != 1)
//     {
//         printf("EVP_EncryptFinal_ex failed.\n");
//         goto end;
//     }

//     ret = EVP_DecryptUpdate(ctx, decdata, &declen, encdata, enclen);
//     if (ret != 1)
//     {
//         printf("EVP_EncryptFinal_ex failed.\n");
//         goto end;
//     }

//     ret = EVP_DecryptFinal_ex(ctx, decdata + declen, &tmplen);
//     if (ret != 1)
//     {
//         printf("EVP_EncryptFinal_ex failed.\n");
//         goto end;
//     }

//     /* check the result */
//     printf("original message: %s.\n", msg);
//     printf("decrypt message: %s.\n", decdata);
end:

    EVP_CIPHER_CTX_free(ctx);

    return 0;
}

// base64 编码
char * base64Encode(const char *buffer, int length)
{
    BIO *bmem = NULL;
    BIO *b64 = NULL;
    BUF_MEM *bptr;

    b64 = BIO_new(BIO_f_base64());
    
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, buffer, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);
    BIO_set_close(b64, BIO_NOCLOSE);

    char *buff = (char *)malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;
    BIO_free_all(b64);

    return buff;
}

// base64 解码
char * base64Decode(char *input, int length)
{
    BIO *b64 = NULL;
    BIO *bmem = NULL;
    char *buffer = (char *)malloc(length);
    memset(buffer, 0, length);
    b64 = BIO_new(BIO_f_base64());
   
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);
    BIO_read(bmem, buffer, length);
    BIO_free_all(bmem);

    return buffer;
}

