#include <SimpleAmqpClient/SimpleAmqpClient.h> // 包含 SimpleAmqpClient 头文件
#include <iostream>

int main() {
    try {
        // 1. 连接到 RabbitMQ 服务器
        // 参数是 RabbitMQ 服务器的主机名或 IP 地址
        AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Create("localhost");

        // 2. 声明一个队列
        // 参数依次为：队列名称、是否持久化、是否独占、是否自动删除、是否等待服务器响应
        channel->DeclareQueue("my_queue", false, true, false, false);

        // 3. 发送消息到队列
        std::string message = "Hello, RabbitMQ from Producer!";
        channel->BasicPublish("", "my_queue", AmqpClient::BasicMessage::Create(message));
        std::cout << " [x] Sent: " << message << std::endl;

        // 4. 不需要显式调用 Close，Channel 对象析构时会自动关闭连接
    } catch (const std::exception& e) {
        // 捕获并打印异常
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}