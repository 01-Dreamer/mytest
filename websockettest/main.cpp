#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <boost/asio/ip/address.hpp>
#include <functional>
#include <iostream>


typedef websocketpp::server<websocketpp::config::asio> server;

class websocket_server {
public:
    websocket_server() {
        echo_server.init_asio();
        echo_server.set_open_handler(std::bind(&websocket_server::on_open, this, std::placeholders::_1));
        echo_server.set_message_handler(std::bind(&websocket_server::on_message, this, std::placeholders::_1, std::placeholders::_2));
        echo_server.set_close_handler(std::bind(&websocket_server::on_close, this, std::placeholders::_1));
    }

    void run() {
        // 绑定到指定的IP和端口
        boost::asio::ip::address ip_address = boost::asio::ip::address::from_string("0.0.0.0");
        echo_server.listen(ip_address, 9002);
        echo_server.start_accept();
        echo_server.run();
    }

private:
    void on_open(websocketpp::connection_hdl hdl) {
        echo_server.send(hdl, "Welcome to the WebSocket server!", websocketpp::frame::opcode::text);
        std::cout << "Client connected, sent welcome message!" << std::endl;
    }

    void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg) {
        std::cout << "Received message: " << msg->get_payload() << std::endl;
        std::string reply = "Echo: " + msg->get_payload();
        echo_server.send(hdl, reply, websocketpp::frame::opcode::text);
        std::cout << "Sent message: " << reply << std::endl;
    }

    void on_close(websocketpp::connection_hdl hdl) {
        std::cout << "Client disconnected." << std::endl;
    }

    server echo_server;
};

int main() {
    try {
        websocket_server ws_server;
        ws_server.run();
    } catch (const websocketpp::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
