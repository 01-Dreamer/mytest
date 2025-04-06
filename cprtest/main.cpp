#include <cpr/cpr.h>
#include <iostream>

int main() {
    // 发起GET请求到百度
    cpr::Response r = cpr::Get(
        cpr::Url{"https://www.baidu.com"},
        cpr::Header{
            {"User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"},
            {"Accept", "text/html"}
        }
    );

    // 输出结果
    std::cout << "Status Code: " << r.status_code << std::endl;  // 200表示成功
    std::cout << "Response Length: " << r.text.length() << " bytes\n";
    
    // 如果需要查看完整响应（谨慎使用，内容可能很长）
    // std::cout << "Content:\n" << r.text << std::endl;

    return 0;
}
