/* Simple AES GCM test program, uses the same NIST data used for the FIPS
 * self test but uses the application level EVP APIs.
 */
#include <stdio.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

/* AES-GCM test data from NIST public test vectors */

static const unsigned char gcm_key[] = {
    0xee,0xbc,0x1f,0x57,0x48,0x7f,0x51,0x92,0x1c,0x04,0x65,0x66,
    0x5f,0x8a,0xe6,0xd1,0x65,0x8b,0xb2,0x6d,0xe6,0xf8,0xa0,0x69,
    0xa3,0x52,0x02,0x93,0xa5,0x72,0x07,0x8f
};

static const unsigned char gcm_iv[] = {
    0x99,0xaa,0x3e,0x68,0xed,0x81,0x73,0xa0,0xee,0xd0,0x66,0x84
};

static const unsigned char gcm_pt[] = {
    0xf5,0x6e,0x87,0x05,0x5b,0xc3,0x2d,0x0e,0xeb,0x31,0xb2,0xea,
    0xcc,0x2b,0xf2,0xa5
};

static const unsigned char gcm_aad[] = {
    0x4d,0x23,0xc3,0xce,0xc3,0x34,0xb4,0x9b,0xdb,0x37,0x0c,0x43,
    0x7f,0xec,0x78,0xde
};

static const unsigned char gcm_ct[] = {
    0xf7,0x26,0x44,0x13,0xa8,0x4c,0x0e,0x7c,0xd5,0x36,0x86,0x7e,
    0xb9,0xf2,0x17,0x36
};

static const unsigned char gcm_tag[] = {
    0x67,0xba,0x05,0x10,0x26,0x2a,0xe4,0x87,0xd7,0x37,0xee,0x62,
    0x98,0xf7,0x7e,0x0c
};

void aes_gcm_encrypt(const unsigned char* key, int key_len,
                    const unsigned char* iv, int iv_len,
                    unsigned char* plain_text, int plen,
                    unsigned char* CIPHERTEXT, int *outlen)
{
    const EVP_CIPHER *cipher;
    switch(key_len)
    {
        case 128: cipher = EVP_aes_128_gcm();break;
        case 192: cipher = EVP_aes_192_gcm();break;
        case 256: cipher = EVP_aes_256_gcm();break;
        default:break;
    }
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, cipher, NULL, NULL, NULL);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv_len, NULL);
    EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv);
    EVP_EncryptUpdate(ctx, CIPHERTEXT, outlen, plain_text, plen);
    EVP_EncryptFinal_ex(ctx,CIPHERTEXT, outlen);
    EVP_CIPHER_CTX_free(ctx);
}

void aes_gcm_decrypt(const unsigned char* key, int key_len,
                     const unsigned char* iv, int iv_len,
                     unsigned char* CIPHERTEXT, int ct_len,
                     unsigned char* outbuf, int *outlen)
{
    const EVP_CIPHER *cipher;
    switch(key_len)
    {
        case 128: cipher = EVP_aes_128_gcm();break;
        case 192: cipher = EVP_aes_192_gcm();break;
        case 256: cipher = EVP_aes_256_gcm();break;
        default:break;
    }
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, cipher, NULL, NULL, NULL);
    EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv_len, NULL);
    EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv);
    EVP_DecryptUpdate(ctx, outbuf, outlen, CIPHERTEXT, ct_len);
    int rv = EVP_DecryptFinal_ex(ctx, outbuf, outlen);
    EVP_CIPHER_CTX_free(ctx);
}

int main()
{
    printf("AES GCM Encrypt:\n");
    BIO_dump_fp(stdout, gcm_pt, sizeof(gcm_pt));
    int howmany = 0;
    int pLen = sizeof(gcm_pt);
    int outLen = (pLen/16+1)*16;
    unsigned char* CIPHERTEXT = (unsigned char*)malloc(outLen);
    memset(CIPHERTEXT, 0, outLen);
    aes_gcm_encrypt(gcm_key, 256, gcm_iv, sizeof(gcm_iv),
                    gcm_pt, sizeof(gcm_pt),
                    CIPHERTEXT, &howmany);
    printf("Encrypt outLen %d, howmany %d\n", outLen, howmany);
    BIO_dump_fp(stdout, CIPHERTEXT, outLen);

    unsigned char* outbuf = (unsigned char*)malloc(pLen);
    memset(outbuf, 0, pLen);
    int outhowmany = 0;
    aes_gcm_decrypt(gcm_key, 256, gcm_iv, sizeof(gcm_iv),
                    CIPHERTEXT, outLen,
                    outbuf, &outhowmany);
    printf("Decrypt pLen %d, outhowmany %d\n", pLen, outhowmany);
    BIO_dump_fp(stdout, outbuf, pLen);
    free(CIPHERTEXT);
    free(outbuf);


    return 0;
}


