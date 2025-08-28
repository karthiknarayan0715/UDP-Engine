#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

class MySqlConnector {
public:
    void TestConnect() {
        try {
            sql::mysql::MySQL_Driver* driver;
            std::unique_ptr<sql::Connection> con;
            std::unique_ptr<sql::Statement> stmt;
            std::unique_ptr<sql::ResultSet> res;

            // Replace with your Windows MySQL IP
            std::string host = "tcp://172.20.32.1:3306";
            std::string user = "root";
            std::string password = "root";
            std::string database = "game_db"; // Replace with your database name

            // Initialize MySQL driver and connect
            driver = sql::mysql::get_mysql_driver_instance();
            con.reset(driver->connect(host, user, password));

            // Select database
            con->setSchema(database);

            // Execute SELECT query
            stmt.reset(con->createStatement());
            res.reset(stmt->executeQuery("SELECT gameId, user_id FROM gameinfo;")); // Replace with your table

            // Print results
            while (res->next()) {
                std::cout << "Game ID: " << res->getString("gameId") 
                          << ", User ID: " << res->getString("user_id") << std::endl;
            }

        } catch (sql::SQLException &e) {
            std::cerr << "SQL Error: " << e.what() << std::endl;
        }
    }
};
