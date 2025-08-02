#include <boost/asio.hpp>
#include <iostream>
#include <vector>


std::string default_path{"/dev/cu.usbserial-"};

class GetPortList {
public:

    static std::vector<std::string> ports_list() {
        std::vector<std::string> paths;
        std::string tmp = find_port();
        while (tmp != "" && std::find(paths.begin(), paths.end(), tmp) == paths.end()) {
            paths.push_back(tmp);
        }
        return paths;
    }
private:
    static std::string find_port() {

        for (int i = 0; i < 3000; ++i) {
            try {
                std::string path{default_path + std::to_string(i)};
                boost::asio::io_context io;
                boost::asio::serial_port port(io);
                port.open(path);
                port.close();
                return path;
            } catch (boost::system::system_error& e) {}
        }
        return "";
    }
};



class ChoosePort {


public:
    static std::string choose_port() {
        std::vector<std::string> device_ports = GetPortList::ports_list();
        std::string device_port;
        int u{0};
        std::cout << "ports : ";

        if (device_ports.empty()) {
            std::cerr << "No serial ports found. Please connect a device.\n";
        } else {

            if (device_ports.size() == 1) {
                device_port = device_ports[0];
                std::cout << "Found one port: " << device_port << "\n";
            } else {                                                                
                std::cout << "Found " << device_ports.size() << " ports:\n";

                for (int i=0; i < device_ports.size(); ++i) {
                    std::cout << device_ports[i] << (i < device_ports.size() - 1 ? " " : "\n");
                }

                std::cout << "Enter serial port num (0 to " << device_ports.size() - 1 << "): ";
                std::cin >> u;
                device_port = device_ports[u];
            }
        }
        return device_port;
    }
};





