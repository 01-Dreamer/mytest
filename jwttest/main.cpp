#include <jwt-cpp/jwt.h>
#include <iostream>
#include <string>
#include <uuid/uuid.h>  // 引入UUID库
#include <cstdlib>

const std::string JWT_SECRET_KEY = std::getenv("JWT_SECRET_KEY");


std::string generate_uuid() {
    uuid_t bin_uuid;
    uuid_generate_random(bin_uuid);  // 生成一个随机UUID
    char uuid_str[37];  // UUID的字符串长度（36个字符 + 1个终止符）
    uuid_unparse_lower(bin_uuid, uuid_str);  // 将UUID转换为字符串
    return std::string(uuid_str);
}

int main() {
    // 原始数据
    std::string data = "Hello, this is a JWT test!";

    // 生成唯一的UUID
    std::string unique_id = generate_uuid();

    // 创建JWT
    auto token = jwt::create()
        .set_issuer("auth0")  // 设置issuer
        .set_payload_claim("data", jwt::claim(data))  // 将原始数据存储在JWT的有效负载中
        .set_payload_claim("unique_id", jwt::claim(unique_id))  // 添加唯一的UUID
        .sign(jwt::algorithm::hs256{JWT_SECRET_KEY});  // 使用HMAC SHA256算法和"secret"密钥签名

    std::cout << "Encrypted JWT: " << token << std::endl;

    // 解密JWT并获取数据
    try {
        auto decoded = jwt::decode(token);

        // 验证签名并解码有效负载
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{JWT_SECRET_KEY})  // 允许HS256算法验证
            .with_issuer("auth0");

        verifier.verify(decoded);

        // 获取JWT的有效负载
        std::string decoded_data = decoded.get_payload_claim("data").as_string();
        std::string decoded_uuid = decoded.get_payload_claim("unique_id").as_string();

        std::cout << "Decrypted Data: " << decoded_data << std::endl;
        std::cout << "Unique ID (UUID): " << decoded_uuid << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
