#include <iostream>
#include <jsoncpp/json/json.h>


int main() {
    // 示例 JSON 字符串
    std::string json_str = R"({
        "name": "John Doe",
        "age": 30,
        "is_student": false,
        "courses": ["Math", "Science", "English"]
    })";

    // 创建一个 JSON 对象
    Json::CharReaderBuilder readerBuilder;
    Json::Value root;
    std::string errs;

    // 解析 JSON 字符串
    std::stringstream s(json_str);
    if (!Json::parseFromStream(readerBuilder, s, &root, &errs)) {
        std::cout << "Failed to parse JSON: " << errs << std::endl;
        return 1;
    }

    // 访问 JSON 对象的元素
    std::cout << "Name: " << root["name"].asString() << std::endl;
    std::cout << "Age: " << root["age"].asInt() << std::endl;
    std::cout << "Is student: " << (root["is_student"].asBool() ? "Yes" : "No") << std::endl;

    std::cout << "Courses: ";
    for (const auto& course : root["courses"]) {
        std::cout << course.asString() << " ";
    }
    std::cout << std::endl;

    // 创建 JSON 对象并输出
    Json::Value newRoot;
    newRoot["status"] = "success";
    newRoot["message"] = "Data processed successfully!";
    
    Json::StreamWriterBuilder writer;
    std::string newJsonStr = Json::writeString(writer, newRoot);
    std::cout << "Generated JSON: " << newJsonStr << std::endl;

    return 0;
}