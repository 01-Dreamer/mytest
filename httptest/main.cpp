#include <httplib.h>
#include <iostream>

int main() {
    // 创建一个 HTTP 服务器对象
    httplib::Server svr;

    // 设置路由，处理根路径请求
    svr.Get("/", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("Hello, World!", "text/plain");
    });

    // 设置路由，处理其他请求
    svr.Get("/hello", [](const httplib::Request& req, httplib::Response& res) {
        res.set_content("Hello from /hello endpoint!", "text/plain");
    });

    // 启动 HTTP 服务器，监听端口 8080
    std::cout << "Server is running" << std::endl;
    svr.listen("127.0.0.1", 8080);

    return 0;
}
