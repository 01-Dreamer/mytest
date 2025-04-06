#include <mysql/mysql.h>
#include <iostream>
#include <string>

int main() {
    // 初始化 MySQL 连接
    MYSQL* conn = mysql_init(nullptr);
    if (!conn) {
        std::cerr << "MySQL initialization failed!" << std::endl;
        return 1;
    }

    // 连接到 MySQL 服务器
    conn = mysql_real_connect(conn, "localhost", "failedman", "123456", "ChatBase", 0, nullptr, 0);
    if (!conn) {
        std::cerr << "Connection failed: " << mysql_error(conn) << std::endl;
        return 1;
    }

    std::cout << "Connected to MySQL server successfully!" << std::endl;

    // 执行 SQL 查询
    const char* query = "SELECT * FROM Messages";
    if (mysql_query(conn, query)) {
        std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // 获取查询结果
    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        std::cerr << "Failed to store result: " << mysql_error(conn) << std::endl;
        mysql_close(conn);
        return 1;
    }

    // 获取列数
    int num_fields = mysql_num_fields(result);

    // 输出查询结果
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            std::cout << (row[i] ? row[i] : "NULL") << " ";
        }
        std::cout << std::endl;
    }

    // 释放结果集
    mysql_free_result(result);

    // 关闭连接
    mysql_close(conn);

    std::cout << "Connection closed." << std::endl;
    return 0;
}