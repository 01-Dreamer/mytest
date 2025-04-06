#include "cppjieba/Jieba.hpp"
#include <iostream>

int main() {
    // 字典路径
    const char* DICT_PATH = "cppjieba/dict/jieba.dict.utf8";
    const char* HMM_PATH = "cppjieba/dict/hmm_model.utf8";
    const char* USER_DICT_PATH = "cppjieba/dict/user.dict.utf8";
    const char* IDF_PATH = "cppjieba/dict/idf.utf8";
    const char* STOP_WORD_PATH = "cppjieba/dict/stop_words.utf8";

    // 初始化 Jieba
    cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);

    // 输入句子
    std::string sentence;
    std::getline(std::cin, sentence);

    // 分词
    std::vector<std::string> words;
    jieba.CutForSearch(sentence, words);  // 使用搜索模式分词

    // 输出结果，过滤掉空格
    for (const auto& word : words) {
        if (!word.empty() && word != " ") {  // 过滤掉空格
            std::cout << word << std::endl;
        }
    }

    return 0;
}