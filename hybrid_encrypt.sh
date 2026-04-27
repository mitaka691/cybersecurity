#!/bin/bash

# Proverka na argument
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 input_file"
    exit 1
fi

INPUT_FILE=$1

# 1. Generirane na AES klioch (32 baita)
openssl rand -out aes_key.bin 32

# 2. Generirane na IV (16 baita za AES-CBC)
openssl rand -out iv.bin 16

# 3. Kriptirane na faila s AES-256-CBC
openssl enc -aes-256-cbc -in "$INPUT_FILE" -out data.enc \
    -K $(xxd -p aes_key.bin) \
    -iv $(xxd -p iv.bin)

# 4. Kriptirane na AES kliocha s RSA
openssl pkeyutl -encrypt \
    -in aes_key.bin \
    -pubin -inkey public.pem \
    -pkeyopt rsa_padding_mode:oaep \
    -out encrypted_aes_key.enc

# 5. Zapazvame IV (za dekriptirane)
mv iv.bin iv.enc

# 6. Pochistvame
rm aes_key.bin

echo "Gotovo!"
echo "Izpratih failovete:"
echo "- data.enc"
echo "- encrypted_aes_key.enc"
echo "- iv.enc"
