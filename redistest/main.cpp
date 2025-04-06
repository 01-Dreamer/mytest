#include <sw/redis++/redis++.h>
#include <iostream>
#include <chrono>

int main() {
    try {
        sw::redis::ConnectionOptions opts;
        opts.host = "127.0.0.1";
        opts.port = 6379;
        opts.db = 0;
        opts.keep_alive = true;
        sw::redis::Redis client(opts);


        //bool exists = client.exists("test");

        client.set("test","Hello redis++",std::chrono::seconds(60));

        auto ttl = client.ttl("test");
        std::cout << ttl << std::endl;




    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}