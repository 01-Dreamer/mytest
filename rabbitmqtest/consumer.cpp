#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <iostream>

int main()
{
    try
    {
        // 1. 连接到 RabbitMQ 服务器
        AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Create("localhost");

        // 2. 声明一个队列
        channel->DeclareQueue("my_queue", false, true, false, false);

        // 绑定队列到交换机
        std::string exchange_name = "amq.direct";   // 默认交换机
        std::string binding_key = "mytest"; // 绑定键
        channel->BindQueue("my_queue", exchange_name, binding_key);

        // 3. 设置消费者并开始消费消息
        std::string consumer_tag = channel->BasicConsume("my_queue", "", false, false, false, 1);
        std::cout << " [*] Waiting for messages. To exit press Ctrl+C" << std::endl;

        // 4. 循环接收消息
        while (true)
        {
            // 从队列中获取消息
            AmqpClient::Envelope::ptr_t envelope = channel->BasicConsumeMessage(consumer_tag);

            // 提取消息内容
            std::string message = envelope->Message()->Body();
            std::cout << " [x] Received: " << message << std::endl;

            // 手动确认消息（确保消息被正确处理）
            channel->BasicAck(envelope);
        }
    }
    catch (const std::exception &e)
    {
        // 捕获并打印异常
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}