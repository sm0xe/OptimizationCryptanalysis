#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <iostream>
#include <string>

using namespace CryptoPP;
using std::cout;
using std::cerr;
using std::endl;

std::string aes_encrypt(std::array<std::byte,AES::DEFAULT_KEYLENGTH> keyarray, std::string plaintext){
  SecByteBlock key((const byte*)keyarray.data(),AES::DEFAULT_KEYLENGTH);

  std::string encoded, ciphertext;

  try{
    ECB_Mode<AES>::Encryption e(key,key.size());
    
    StringSource encrypt_aes(plaintext, true,
        new StreamTransformationFilter(e,
          new StringSink(ciphertext)
          )
        );
  }
  catch(const CryptoPP::Exception& e){
    cerr << e.what() << endl;
    exit(1);
  }

  StringSource hex_encode(ciphertext, true,
      new HexEncoder(
        new StringSink(encoded)
        )
      );
  return encoded;
}

std::string aes_decrypt(std::array<std::byte,AES::DEFAULT_KEYLENGTH> keyarray, std::string encoded){
  SecByteBlock key((const byte*)keyarray.data(),AES::DEFAULT_KEYLENGTH);

  std::string ciphertext, recovered;

  try{
    ECB_Mode<AES>::Decryption d(key, key.size());
    StringSource decode_hex(encoded, true,
        new HexDecoder(
          new StringSink(ciphertext)
          )
        );
    StringSource decrypt_aes(ciphertext, true,
        new StreamTransformationFilter(d,
          new StringSink(recovered)
          )
        );
    return recovered;
  }
  catch(const CryptoPP::Exception& d){
    cerr << d.what() << endl;
    exit(1);
  }
}

void test_aes(std::array<std::byte,AES::DEFAULT_KEYLENGTH> keyarray){
  std::string plain = "ECB Mode Test";

  std::string encoded = aes_encrypt(keyarray,plain);
  cout << "ciphertext: " << encoded << endl;

  std::string recovered = aes_decrypt(keyarray, encoded);
  cout << "recovered text: " << recovered << endl;
}
