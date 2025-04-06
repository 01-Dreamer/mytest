#include <iostream>
#include <sodium.h>
#include <vector>
#include <cstring>

int main() {
    if (sodium_init() < 0) {
        std::cerr << "初始化 libsodium 失败" << std::endl;
        return 1;
    }

    std::string password = "114514";
    
    // 1. 哈希密码 (使用 Argon2id)
    char hashed_password[crypto_pwhash_STRBYTES];

    // 使用较低的操作限制和内存限制来加快速度
    if (crypto_pwhash_str(hashed_password, password.c_str(), password.length(),
                          crypto_pwhash_OPSLIMIT_INTERACTIVE,  // 降低计算复杂度
                          crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {  // 降低内存消耗
        std::cerr << "密码哈希失败" << std::endl;
        return 1;
    }

    std::cout << hashed_password << std::endl;
    
    // 2. 验证密码
    if (crypto_pwhash_str_verify(hashed_password, 
                                password.c_str(), 
                                password.length()) == 0) {
        std::cout << "密码验证成功" << std::endl;
    } else {
        std::cout << "密码验证失败" << std::endl;
    }
    
    // 3. 测试错误密码
    if (crypto_pwhash_str_verify(hashed_password,
                                "114514",
                                strlen("114514")) == 0) {
        std::cout << "错误密码验证成功 (不应该发生)" << std::endl;
    } else {
        std::cout << "错误密码验证失败 (正确行为)" << std::endl;
    }
    
    return 0;
}
