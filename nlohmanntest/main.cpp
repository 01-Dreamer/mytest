#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

int main() {
    // 解析字符串

    try {
      json j = json::parse(R"({"name":"张三","age":25,"skills":["C++","Python"]})");
      std::cout << j["name"] << std::endl;  // 输出："张三"
    } catch (const json::parse_error& e) {
      std::cerr << e.what() << std::endl;
    }

    // 构建JSON
    json data;
    data["project"] = "Elasticsearch";
    data["stars"] = 50000;
    data["tags"] = {"search", "C++", "JSON"};

    // 输出格式化JSON
    std::cout << data.dump() << std::endl;
    /* 输出：
    {
      "project": "Elasticsearch",
      "stars": 50000,
      "tags": ["search", "C++", "JSON"]
    }
    */

    return 0;
}