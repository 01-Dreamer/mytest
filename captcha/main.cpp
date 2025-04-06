#include <Magick++.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace Magick;

// 生成随机六位验证码
string generateCaptchaText(int length) {
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string captchaText = "";
    srand(time(0));

    for (int i = 0; i < length; i++) {
        int randIndex = rand() % chars.size();
        captchaText += chars[randIndex];
    }

    return captchaText;
}

// 添加干扰线
void addNoise(Image &image) {
    int width = image.columns();
    int height = image.rows();
    srand(time(0));
    
    for (int i = 0; i < 30; i++) {  // 增加到30条干扰线
        int x1 = rand() % width;
        int y1 = rand() % height;
        int x2 = rand() % width;
        int y2 = rand() % height;
        
        image.strokeColor(Color("gray"));
        image.strokeWidth(1);
        image.draw(DrawableLine(x1, y1, x2, y2));
    }
}

// 生成随机背景颜色并混合
void generateRandomBackground(Image &image) {
    int width = image.columns();
    int height = image.rows();
    srand(time(0));

    // 创建一个基础颜色层
    int r1 = rand() % 256;
    int g1 = rand() % 256;
    int b1 = rand() % 256;
    image.fillColor(ColorRGB(r1 / 255.0, g1 / 255.0, b1 / 255.0));
    image.opaque(Color("transparent"), image.fillColor());

    // 添加随机混合颜色块
    for (int i = 0; i < 5; i++) {  // 随机生成5个颜色块
        int r = rand() % 256;
        int g = rand() % 256;
        int b = rand() % 256;
        int x = rand() % width;
        int y = rand() % height;
        int radius = rand() % 50 + 20;  // 随机半径20-70

        image.fillColor(ColorRGB(r / 255.0, g / 255.0, b / 255.0));
        image.draw(DrawableEllipse(x, y, radius, radius, 0, 360));
    }

    // 添加轻微模糊效果，使颜色混合更自然
    image.blur(5.0, 1.5);
}

int main(int argc, char *argv[]) {
    InitializeMagick(*argv);

    // 生成6位验证码
    string captchaText = generateCaptchaText(6);
    
    // 设置图像大小
    int width = 300;
    int height = 100;
    
    // 创建图像
    Image image(Geometry(width, height), Color("transparent"));  // 从透明背景开始
    
    // 生成随机背景颜色
    generateRandomBackground(image);
    
    // 设置字体和文字属性
    image.font("Helvetica");  // 可替换为其他字体
    image.fillColor(Color("black"));
    image.strokeColor(Color("transparent"));
    image.strokeWidth(0);
    
    // 设置字体大小
    int fontSize = height / 2;
    image.fontPointsize(fontSize);

    // 逐个字符绘制，添加适度倾斜和扭曲效果
    int xOffset = 20;  // 初始水平位置
    int yOffset = height / 1.5;  // 垂直居中
    srand(time(0));

    for (char c : captchaText) {
        string singleChar(1, c);  // 将单个字符转为字符串
        
        // 创建临时图像用于绘制单个字符
        Image charImage(Geometry(50, height), Color("transparent"));
        charImage.font("Helvetica");
        charImage.fillColor(Color("black"));
        charImage.fontPointsize(fontSize);
        
        // 绘制字符
        charImage.draw(DrawableText(0, yOffset, singleChar));
        
        // 适度随机倾斜（shear）
        double shearX = (rand() % 14 - 7);  // -7 到 7 度
        charImage.shear(shearX, 0);
        
        // 适度波浪扭曲（wave）
        charImage.wave(3.0, 25.0);  // 波浪幅度3.0，波长25.0
        
        // 将字符图像叠加到主图像上
        image.composite(charImage, xOffset, 0, OverCompositeOp);
        
        // 更新xOffset，留出间距
        xOffset += fontSize * 0.8;  // 根据字体大小调整间距
    }

    // 添加干扰线
    addNoise(image);

    // 保存验证码图像
    image.write("captcha.png");

    cout << "验证码已生成并保存为 captcha.png，验证码内容为: " << captchaText << endl;

    return 0;
}
