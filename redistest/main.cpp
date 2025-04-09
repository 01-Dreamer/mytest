#include <sw/redis++/redis++.h>
#include <iostream>
#include <chrono>

using namespace std;

int main() {
    try {
        sw::redis::ConnectionOptions opts;
        opts.host = "127.0.0.1";
        opts.port = 6379;
        opts.db = 15;
        opts.keep_alive = true;
        sw::redis::Redis client(opts);

        const string list_key = "test";

        // 2. 插入数据到List头部/尾部
        client.lpush(list_key, {"task1", "task2"}); // 头部插入
        client.rpush(list_key, "task3");            // 尾部插入

        client.set("your_key", "your_value", std::chrono::seconds(60));  // 精确秒数

        auto val = client.get("your_key");
        if(val) cout << *val << endl;
        else cout << "null" << endl;

        // 3. 获取列表长度
        auto len = client.llen(list_key);
        cout << "当前列表长度: " << len << endl;  // 输出: 3

        cout << *client.rpop("test") << std::endl;



    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}