#include <glog/logging.h>  // glog 头文件

int main(int argc, char* argv[]) {
    // 初始化 glog
    google::InitGoogleLogging(argv[0]);
    
    // 关键配置：将所有日志输出到 stderr（控制台）
    FLAGS_logtostderr = true;
    
    // 可选配置：设置最低日志级别
    FLAGS_minloglevel = google::INFO;  // 只输出 INFO 及以上级别的日志
    
    // 不同级别的日志输出
    LOG(INFO) << "这是一条 INFO 级别的日志，仅输出到控制台";
    LOG(WARNING) << "这是一条 WARNING 级别的日志";
    LOG(ERROR) << "这是一条 ERROR 级别的日志";
    
    // 条件日志示例
    int value = 42;
    LOG_IF(INFO, value > 10) << "值大于10，当前值为: " << value;
    
    // 定期日志示例
    for (int i = 0; i < 20; i++) {
        LOG_EVERY_N(INFO, 5) << "每5次记录一次，这是第 " << google::COUNTER << " 次";
    }
    
    // 关闭 glog（可选，程序退出时会自动关闭）
    google::ShutdownGoogleLogging();
    
    return 0;
}