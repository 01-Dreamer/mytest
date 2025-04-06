#include <alibabacloud/oss/OssClient.h>
#include <iostream>
#include <fstream>

using namespace AlibabaCloud::OSS;

int main() {
    // 1. 初始化SDK
    InitializeSdk();

    // 2. 配置你的OSS信息（替换这些值）
    std::string endpoint = "https://oss-cn-chengdu.aliyuncs.com"; // 成都区域的Endpoint
    std::string accessKeyId = "";
    std::string accessKeySecret = "";
    std::string securityToken = "";
    std::string bucketName = "zxydata";          // 你的Bucket名称
    std::string objectName = "data/test.png";         // 上传后的文件名
    std::string fileToUpload = "./test.png";     // 本地要上传的文件

    // 3. 创建OSS客户端
    ClientConfiguration conf;
    OssClient client(endpoint, accessKeyId, accessKeySecret, securityToken,conf);

    // 4. 执行上传
    auto outcome = client.PutObject(bucketName, objectName, fileToUpload);

    // 4. 执行删除
    //auto outcome = client.DeleteObject(bucketName, objectName);

    // 5. 检查结果
    
    if (!outcome.isSuccess()) {
        std::cout << "上传失败: " 
                  << outcome.error().Code() 
                  << " - " 
                  << outcome.error().Message() 
                  << std::endl;
    } else {
        std::cout << "文件上传成功！ETag: " 
                  << outcome.result().ETag() 
                  << std::endl;
    }
    
    /*
    if (!outcome.isSuccess()) {
        std::cout << "删除失败: " 
                  << outcome.error().Code() 
                  << " - " 
                  << outcome.error().Message() 
                  << std::endl;
    } else {
        std::cout << "文件删除成功！" << std::endl;
    }*/

    // 6. 清理资源
    ShutdownSdk();
    return 0;
}