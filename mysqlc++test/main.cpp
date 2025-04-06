#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <iostream>

int main() {
    try {
        // 创建 MySQL 驱动程序实例
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *con;

        // 初始化 MySQL 驱动
        driver = sql::mysql::get_mysql_driver_instance();
        
        // 创建连接
        con = driver->connect("tcp://127.0.0.1:3306", "failedman", "123456");

        // 选择数据库
        con->setSchema("Test");

        // 创建查询
        sql::PreparedStatement *pstmt;
        pstmt = con->prepareStatement("SELECT * from Message");
        //pstmt->setInt(1, 1);  // 设置查询条件（例如id为1）

        // 执行查询并获取结果
        sql::ResultSet *res;
        res = pstmt->executeQuery();

        // 输出查询结果
        while (res->next()) {
            std::cout << "time: " << res->getInt("time") << ", chat: " << res->getString("chat") << std::endl;
        }

        // 清理资源
        delete res;
        delete pstmt;
        delete con;
    } catch (sql::SQLException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
