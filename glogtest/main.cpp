#include <glog/logging.h>  // glog 头文件

int main(int argc, char* argv[]) {
    // 初始化 glog
    google::InitGoogleLogging(argv[0]);
    
    // 关键配置：将所有日志输出到 stderr（控制台）
    FLAGS_logtostderr = true;
    FLAGS_colorlogtostderr = true; 
    
    // 设置日志显示为只到秒（没有微秒）和没有线程 ID
    FLAGS_minloglevel = google::INFO;  // 只输出 INFO 及以上级别的日志
    FLAGS_logbuflevel = -1;  // 禁止缓冲区
    FLAGS_logbufsecs = 0;  // 实时输出日志
    FLAGS_max_log_size = 100;  // 设置日志文件大小
    
    // 设置日志输出格式：去掉线程 ID（glog 默认输出线程 ID，无法完全去除）
    // 默认不支持直接去除线程 ID。要完全去掉线程 ID，需要手动修改源码，或者使用更灵活的日志库如 spdlog。
    
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
