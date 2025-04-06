#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <iostream>

const std::string key = std::getenv("amapKey");

int main() {
    // 创建 HTTP 客户端
    web::http::client::http_client client(U("https://restapi.amap.com"));

    // 创建请求对象
    web::http::http_request request(web::http::methods::GET);
    
    // 设置请求头
    request.headers().add(U("Accept"), U("application/json"));

    // 设置查询参数
    web::uri_builder builder(U("/v3/geocode/geo"));
    builder.append_query(U("address"), U("北京"));
    builder.append_query(U("output"), U("JSON"));
    builder.append_query(U("key"), key); // 替换为你的高德 API 密钥
    request.set_request_uri(builder.to_uri());

    // 发送请求并处理响应
    client.request(request).then([](web::http::http_response response) {
        if (response.status_code() == web::http::status_codes::OK) {
            // 将 jsonResponse.serialize() 转换为合适的格式
            std::wcout << L"JSON Response: " << response.extract_json().get().serialize().c_str() << std::endl;
        } else {
            std::cerr << "Request failed with status code: " << response.status_code() << std::endl;
        }
    }).wait();

    return 0;
}
