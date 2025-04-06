#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <string.h>

using namespace std;

// 公钥加密
std::string encrypt_with_public_key(const std::string& data, const std::string& pub_key_path) {
    FILE* pub_key_file = fopen(pub_key_path.c_str(), "r");
    if (!pub_key_file) {
        std::cerr << "Unable to open public key file" << std::endl;
        return "";
    }

    RSA* rsa_pub_key = PEM_read_RSA_PUBKEY(pub_key_file, nullptr, nullptr, nullptr);
    fclose(pub_key_file);
    if (!rsa_pub_key) {
        std::cerr << "Unable to load public key" << std::endl;
        return "";
    }

    int rsa_len = RSA_size(rsa_pub_key);
    char* encrypted = new char[rsa_len];
    int result = RSA_public_encrypt(data.size(), reinterpret_cast<const unsigned char*>(data.c_str()),
                                    reinterpret_cast<unsigned char*>(encrypted), rsa_pub_key, RSA_PKCS1_PADDING);
    if (result == -1) {
        std::cerr << "Error encrypting message: " << ERR_error_string(ERR_get_error(), nullptr) << std::endl;
        RSA_free(rsa_pub_key);
        delete[] encrypted;
        return "";
    }

    std::string encrypted_str(encrypted, result);
    delete[] encrypted;
    RSA_free(rsa_pub_key);
    return encrypted_str;
}

// 私钥解密
std::string decrypt_with_private_key(const std::string& encrypted_data, const std::string& priv_key_path) {
    FILE* priv_key_file = fopen(priv_key_path.c_str(), "r");
    if (!priv_key_file) {
        std::cerr << "Unable to open private key file" << std::endl;
        return "";
    }

    RSA* rsa_priv_key = PEM_read_RSAPrivateKey(priv_key_file, nullptr, nullptr, nullptr);
    fclose(priv_key_file);
    if (!rsa_priv_key) {
        std::cerr << "Unable to load private key" << std::endl;
        return "";
    }

    int rsa_len = RSA_size(rsa_priv_key);
    char* decrypted = new char[rsa_len];
    int result = RSA_private_decrypt(encrypted_data.size(), reinterpret_cast<const unsigned char*>(encrypted_data.c_str()),
                                     reinterpret_cast<unsigned char*>(decrypted), rsa_priv_key, RSA_PKCS1_PADDING);
    if (result == -1) {
        std::cerr << "Error decrypting message: " << ERR_error_string(ERR_get_error(), nullptr) << std::endl;
        RSA_free(rsa_priv_key);
        delete[] decrypted;
        return "";
    }

    std::string decrypted_str(decrypted, result);
    delete[] decrypted;
    RSA_free(rsa_priv_key);
    return decrypted_str;
}

int main() {
    std::string data = "Hello, this is a secret message!";
    std::string public_key = "public.pem";  // 公钥文件路径
    std::string private_key = "private.pem"; // 私钥文件路径

    // 使用公钥加密
    std::string encrypted = encrypt_with_public_key(data, public_key);
    std::cout << "Encrypted: " << encrypted << std::endl;

    // 使用私钥解密
    std::string decrypted = decrypt_with_private_key(encrypted, private_key);
    std::cout << "Decrypted: " << decrypted << std::endl;

    return 0;
}


// 生成私钥（private key）
// openssl genpkey -algorithm RSA -out private.pem -pkeyopt rsa_keygen_bits:2048
// 从私钥中提取出公钥（public key）
// openssl rsa -pubout -in private.pem -out public.pem


