#include <iostream>
#include "person.pb.h"

int main() {
    // 创建一个 Person 对象
    Person person;
    person.set_name("Alice");
    person.set_id(123);
    person.set_email("alice@example.com");

    // 序列化为字符串
    std::string serialized_person;
    person.SerializeToString(&serialized_person);
    std::cout << "Serialized data: " << serialized_person << std::endl;

    // 反序列化
    Person new_person;
    new_person.ParseFromString(serialized_person);
    std::cout << "Deserialized data:" << std::endl;
    std::cout << "Name: " << new_person.name() << std::endl;
    std::cout << "ID: " << new_person.id() << std::endl;
    std::cout << "Email: " << new_person.email() << std::endl;

    return 0;
}
