#include <Magick++.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <b64/encode.h>  // 确保包含 base64 编码头文件
#include <cstring>  // 添加 memcpy 所需的头文件

// 生成随机六位验证码
std::string generateCaptchaText(int length) {
    std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string captchaText = "";
    std::srand(std::time(0));

    for (int i = 0; i < length; i++) {
        int randIndex = std::rand() % chars.size();
        captchaText += chars[randIndex];
    }

    return captchaText;
}

// 添加干扰线
void addNoise(Magick::Image &image) {
    int width = image.columns();
    int height = image.rows();
    std::srand(std::time(0));
    
    for (int i = 0; i < 15; i++) {  // 增加到15条干扰线
        int x1 = std::rand() % width;
        int y1 = std::rand() % height;
        int x2 = std::rand() % width;
        int y2 = std::rand() % height;
        
        image.strokeColor(Magick::Color("gray"));
        image.strokeWidth(1);
        image.draw(Magick::DrawableLine(x1, y1, x2, y2));
    }
}

// 生成随机背景颜色并混合
void generateRandomBackground(Magick::Image &image) {
    int width = image.columns();
    int height = image.rows();
    std::srand(std::time(0));

    // 创建一个基础颜色层
    int r1 = std::rand() % 256;
    int g1 = std::rand() % 256;
    int b1 = std::rand() % 256;
    image.fillColor(Magick::ColorRGB(r1 / 255.0, g1 / 255.0, b1 / 255.0));
    image.opaque(Magick::Color("white"), image.fillColor());  // 使用白色背景代替透明背景

    // 添加随机混合颜色块
    for (int i = 0; i < 5; i++) {  // 随机生成5个颜色块
        int r = std::rand() % 256;
        int g = std::rand() % 256;
        int b = std::rand() % 256;
        int x = std::rand() % width;
        int y = std::rand() % height;
        int radius = std::rand() % 50 + 20;  // 随机半径20-70

        image.fillColor(Magick::ColorRGB(r / 255.0, g / 255.0, b / 255.0));
        image.draw(Magick::DrawableEllipse(x, y, radius, radius, 0, 360));
    }

    // 添加轻微模糊效果，使颜色混合更自然
    image.blur(5.0, 1.5);
}

// 将图像数据转换为 Base64 编码
std::string base64_encode(const std::string &input) {
    // 使用流式接口
    std::stringstream input_stream(input);
    std::stringstream output_stream;
    
    base64::encoder encoder;
    encoder.encode(input_stream, output_stream);  // 修正类型错误，使用正确的输出流
    
    return output_stream.str();  // 返回 Base64 编码字符串
}

int main(int argc, char *argv[]) {
    // Magick::InitializeMagick(*argv);

    // 生成6位验证码
    std::string captchaText = generateCaptchaText(6);
    
    // 设置图像大小
    int width = 300;
    int height = 100;
    
    // 创建图像，使用白色背景
    Magick::Image image(Magick::Geometry(width, height), Magick::Color("white"));  // 使用白色背景代替透明背景
    
    // 生成随机背景颜色
    generateRandomBackground(image);
    
    // 设置字体和文字属性
    image.font("Helvetica");  // 可替换为其他字体
    image.fillColor(Magick::Color("black"));
    image.strokeColor(Magick::Color("transparent"));
    image.strokeWidth(0);
    
    // 设置字体大小
    int fontSize = height / 2;
    image.fontPointsize(fontSize);

    // 逐个字符绘制，添加适度倾斜和扭曲效果
    int xOffset = 20;  // 初始水平位置
    int yOffset = height / 1.5;  // 垂直居中
    std::srand(std::time(0));

    for (char c : captchaText) {
        std::string singleChar(1, c);  // 将单个字符转为字符串
        
        // 创建临时图像用于绘制单个字符
        Magick::Image charImage(Magick::Geometry(50, height), Magick::Color("white"));
        charImage.font("Helvetica");
        charImage.fillColor(Magick::Color("black"));
        charImage.fontPointsize(fontSize);
        
        // 绘制字符
        charImage.draw(Magick::DrawableText(0, yOffset, singleChar));
        
        // 适度随机倾斜（shear）
        double shearX = (std::rand() % 14 - 7);  // -7 到 7 度
        charImage.shear(shearX, 0);
        
        // 适度波浪扭曲（wave）
        charImage.wave(3.0, 25.0);  // 波浪幅度3.0，波长25.0
        
        // 将字符图像叠加到主图像上
        image.composite(charImage, xOffset, 0, Magick::OverCompositeOp);
        
        // 更新xOffset，留出间距
        xOffset += fontSize * 0.8;  // 根据字体大小调整间距
    }

    // 添加干扰线
    addNoise(image);

    // 创建一个 Blob 对象来保存图像数据
    Magick::Blob blob;
    image.write(&blob, "PNG");  // 显式指定输出格式为 PNG，正确写入 Blob

    // 获取 Blob 中的图像数据
    std::vector<unsigned char> imageData(blob.length());
    std::memcpy(imageData.data(), blob.data(), blob.length());

    // 转换为字符串
    std::string base64Image = base64_encode(std::string(imageData.begin(), imageData.end()));

    // 将 Base64 编码结果保存到 .txt 文件
    std::ofstream outFile("captcha_base64.txt");
    outFile << base64Image;
    outFile.close();

    std::cout << "验证码已生成并保存为 captcha_base64.txt，验证码内容为: " << captchaText << std::endl;

    return 0;
}
