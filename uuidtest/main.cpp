#include <iostream>
#include <uuid/uuid.h>
#include <string>
#include <sstream>

std::string generate_uuid() {
    uuid_t uuid;
    uuid_generate(uuid);
    
    char uuid_str[37];
    uuid_unparse(uuid, uuid_str);
    
    return std::string(uuid_str);
}

int main() {
    std::string uuid = generate_uuid();
    std::cout << "生成的 UUID: " << uuid << std::endl;
    
    return 0;
}