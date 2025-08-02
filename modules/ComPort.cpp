#include <boost/asio.hpp>
#include <iostream>


using namespace boost::asio;


class ComPort {
private:
    io_context io;
    serial_port main_port_{io};
    std::string device_;

public:

    ComPort(std::string& device) : device_(device) { 
        
        // Сохраняем путь к устройству

        try {
            main_port_.open(device); // Или "/dev/ttyUSB0" для Linux
            configure_port();
        } catch (const std::exception& e) {
            std::cerr << "Error: " << "UART connection refused" << std::endl;
        }
    }

    ~ComPort() {
        if (main_port_.is_open()) {
            main_port_.close();
        }
    }

    int write(const std::string& data) {
        if (!main_port_.is_open()) {
            std::cerr << "Error: Port is not open." << std::endl;
            return 1;
        }
        try {
            main_port_.write_some(buffer(data));
            return 0;
        } catch (const boost::system::system_error& e) {return 1;}
    }

    int reopen() {
        try {
                main_port_.close();
                main_port_.open(device_);
                configure_port();
                return 0;
            
            
        } catch (...) {
            return 1;
        }
    }

    int configure_port() {
        main_port_.set_option(serial_port_base::baud_rate(9600));
        main_port_.set_option(serial_port_base::character_size(8));
        main_port_.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
        main_port_.set_option(serial_port_base::parity(serial_port_base::parity::none));
        return 0;
    }

};