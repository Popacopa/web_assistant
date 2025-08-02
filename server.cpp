#include "lib/httplib.h"
#include <string>
#include <unistd.h>
#include "modules/ComPort.cpp"
#include "modules/PortLst.cpp"
#include "modules/settings.cpp"

#define INFO(x): LOGI << x << "\n";
#define ERROR(x): LOGE << x << "\n";
#define DEBUG(x): LOGD << x << "\n";
#define CRITICAL(x): LOGC << x << "\n";
#define WARN(x): LOGW << x << "\n";


int opt;
bool logging{0};
std::string ip_address{"127.0.0.1"};
int port{5555};
std::string last_request;
int last_status;

int main(int argc, char const *argv[])
{

    Settings::setMainLogStream();
    httplib::Server svr;

    while ((opt = getopt(argc, (char**)argv, "huli:p:")) != -1) {
        switch (opt) {
            case 'i':   ip_address = optarg; break;
            case 'p':   port = std::stoi(optarg); break;
            case 'l':   logging = true; break;
            case 'h':   std::cout << Settings::helpLine << "\n"; return 0;
            case '?':   std::cerr << "type [-h] to get help for this program\n"; return 1;
            default:    std::cerr << "type [-h] to get help for this program\n"; return 1;
        }
    }

    std::string device_port = ChoosePort::choose_port();
    ComPort arduino(device_port);     

    if (logging) {Settings::setFileLogging();}

                                                                LOGI << "selected address: " << ip_address << ":" << port << "\t--start\n";

    svr.Post("/api", [&](const httplib::Request &req, httplib::Response &res) {
        if (req.body != last_request) {
            
                if (last_status) {arduino.reopen();}

                int status;
                std::string hi = "1";
                std::string low = "0";

                if (req.body == "1") {
                    status = arduino.write(hi);                                  
                } else {
                    status = arduino.write(low);
                }

                res.set_content(status ? "sorry, port is not open" : req.body, "text/plain");
                last_request = req.body;

                last_status = status;

                                                                LOGI << " POST " << req.body << "\t"
                                                                            << req.remote_addr << "\t" 
                                                                            << "status: " << status << "\n";
        }
    });
    

    
        try
        {
            svr.listen(ip_address, port);
        }
        catch(...)
        {
            LOGE << "SERVER CAN NOT START\n";
        }
}