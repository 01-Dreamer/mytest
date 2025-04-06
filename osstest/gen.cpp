#include <iostream>
#include <string>
#include <alibabacloud/core/AlibabaCloud.h>
#include <alibabacloud/sts/StsClient.h>

using namespace AlibabaCloud;
using namespace AlibabaCloud::Sts;

std::string generateSTSToken(
    const std::string& accessKeyId,
    const std::string& accessKeySecret,
    const std::string& roleArn,
    const std::string& roleSessionName
) {
    InitializeSdk();
    
    ClientConfiguration config("cn-chengdu");
    StsClient client(accessKeyId, accessKeySecret, config);

    // 简化后的策略，仅允许上传到任意目录
    std::string policy = R"({
        "Version": "1",
        "Statement": [
            {
                "Effect": "Allow",
                "Action": ["oss:PutObject"],
                "Resource": ["acs:oss:*:*:zxydata/*"]
            }
        ]
    })";

    Model::AssumeRoleRequest request;
    request.setRoleArn(roleArn);
    request.setRoleSessionName(roleSessionName);
    request.setDurationSeconds(900);
    request.setPolicy(policy);

    try {
        auto outcome = client.assumeRole(request);
        if (!outcome.isSuccess()) {
            ShutdownSdk();
            throw std::runtime_error("STS请求失败: " + outcome.error().errorMessage());
        }
        
        const auto& result = outcome.result().getCredentials();
        std::string stsToken = "AccessKeyId: " + result.accessKeyId + "\n" +
                              "AccessKeySecret: " + result.accessKeySecret + "\n" +
                              "SecurityToken: " + result.securityToken + "\n" +
                              "Expiration: " + result.expiration;

        ShutdownSdk();
        return stsToken;
    } catch (const std::exception& e) {
        ShutdownSdk();
        throw std::runtime_error(std::string("生成STS Token失败: ") + e.what());
    }
}

int main() {
    try {
        std::string stsToken = generateSTSToken(
            "",// Id
            "",// Secret
            "acs:ram::1115114980714494:role/failedman",
            "oss-uploader"
        );
        std::cout << "STS Token信息:\n" << stsToken << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}