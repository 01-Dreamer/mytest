#include <iostream>
#include <string>
#include <curl/curl.h>
#include <random>
#include <sstream>

// 生成随机验证码
std::string generate_verification_code(int length = 6) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    
    std::stringstream ss;
    for(int i = 0; i < length; ++i) {
        ss << dis(gen);
    }
    return ss.str();
}

// libcurl回调函数
static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    std::string *data = (std::string *)userp;
    if(size * nmemb < 1 || data->empty()) return 0;

    size_t len = data->copy((char *)ptr, size * nmemb);
    *data = data->substr(len);
    return len;
}

bool send_email(const std::string& to, const std::string& verification_code) {
    CURL *curl;
    CURLcode res = CURLE_OK;
    
    // 配置部分（与Python版本保持一致）
    const std::string from = "2711339704@qq.com";
    const std::string smtp_server = "smtp.qq.com";
    const int smtp_port = 465;  // 使用SSL端口465
    const std::string auth_code = "xlvahvcmradrdhfg";  // 你的授权码
    
    // 邮件内容（与Python版本相同格式）
    const std::string subject = "软件工程实训饿了么验证码";
    const std::string body = "您的验证码是: " + verification_code + "\n验证码有效时间为120秒";
    
    // 构造MIME格式邮件（关键修改！）
    std::string email_data =
        "From: " + from + "\r\n"
        "To: " + to + "\r\n"
        "Subject: " + subject + "\r\n"
        "MIME-Version: 1.0\r\n"
        "Content-Type: text/plain; charset=utf-8\r\n"
        "\r\n"
        + body + "\r\n";
    
    curl = curl_easy_init();
    if(curl) {
        // 1. 设置服务器（使用smtps://协议）
        std::string url = "smtps://" + smtp_server + ":" + std::to_string(smtp_port);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        // 2. 设置认证方式（关键！）
        curl_easy_setopt(curl, CURLOPT_USERNAME, from.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, auth_code.c_str());
        curl_easy_setopt(curl, CURLOPT_LOGIN_OPTIONS, "AUTH=LOGIN");  // 明确指定认证方式
        
        // 3. 设置邮件内容
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from.c_str());
        struct curl_slist *recipients = NULL;
        recipients = curl_slist_append(recipients, to.c_str());
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        
        // 4. 设置数据源
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &email_data);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        
        // 5. SSL设置（关键！）
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // 调试时可禁用验证
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        
        // 6. 调试信息
        //curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
        // 7. 执行发送
        res = curl_easy_perform(curl);
        
        // 清理
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
        
        if(res != CURLE_OK) {
            std::cerr << "邮件发送失败: " << curl_easy_strerror(res) << std::endl;
            return false;
        }
        return true;
    }
    return false;
}

int main() {
    std::string to_email = "2711339704@qq.com";
    std::string verification_code = generate_verification_code();
    
    std::cout << "生成的验证码: " << verification_code << std::endl;
    
    if(send_email(to_email, verification_code)) {
        std::cout << "邮件发送成功！" << std::endl;
    } else {
        std::cerr << "发送邮件失败！" << std::endl;
    }
    
    return 0;
}