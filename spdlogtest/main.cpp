#include <spdlog/spdlog.h>

int main() {
    // 设置日志格式，添加文件名和行号
    spdlog::set_pattern("%^[%H:%M:%S] [%L] %v%$");

    // 设置日志级别
    spdlog::set_level(spdlog::level::info);

    // 打印不同级别的日志
    spdlog::info("This is an info message with color!");
    spdlog::warn("This is a warning message with color!");
    spdlog::error("This is an error message with color!");

    return 0;
}
