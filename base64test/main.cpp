#include <iostream>
#include <string>
#include <sstream>
#include <b64/encode.h>
#include <b64/decode.h>

// Base64 编码函数
std::string base64_encode(const std::string &input) {
    // 使用流式接口
    std::istringstream input_stream(input);
    std::ostringstream output_stream;
    
    base64::encoder encoder;
    encoder.encode(input_stream, output_stream);
    
    return output_stream.str();
}

// Base64 解码函数
std::string base64_decode(const std::string &input) {
    // 使用流式接口
    std::istringstream input_stream(input);
    std::ostringstream output_stream;
    
    base64::decoder decoder;
    decoder.decode(input_stream, output_stream);
    
    return output_stream.str();
}

int main() {
    std::string original = "Hello, Base64!";
    std::cout << "原始字符串: " << original << std::endl;

    std::string encoded = base64_encode(original);
    std::cout << "Base64 编码: " << encoded << std::endl;

    std::string decoded = base64_decode(encoded);
    std::cout << "Base64 解码: " << decoded << std::endl;

    // 验证是否还原
    std::cout << "验证结果: " << (original == decoded ? "成功" : "失败") << std::endl;
    
    return 0;
}