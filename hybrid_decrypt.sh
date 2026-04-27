#!/bin/bash

# Proverka
if [ "$#" -ne 0 ]; then
    echo "Usage: ./hybrid_decrypt.sh"
    exit 1
fi

# 1. Dekriptirane na AES kliocha s RSA private key
openssl pkeyutl -decrypt \
    -in encrypted_aes_key.enc \
    -inkey private.pem \
    -pkeyopt rsa_padding_mode:oaep \
    -out aes_key.bin

# 2. Dekriptirane na faila s AES
openssl enc -d -aes-256-cbc \
    -in data.enc \
    -out decrypted_output \
    -K $(xxd -p aes_key.bin) \
    -iv $(xxd -p iv.enc)

# 3. Pochistvame
rm aes_key.bin

echo "Dekriptiraneto e uspeshno!"
echo "fail: decrypted_output"
