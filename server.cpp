#include "lib/httplib.h"
#include <string>
#include <unistd.h>
#include "modules/ComPort.cpp"
#include "modules/PortLst.cpp"
#include "modules/settings.cpp"
#include "modules/Signal.cpp"


/* файл сервера, ретранслирующего сигналы из сети 
на ардуино и принимающего ответ от нее */


#define INFO(x): LOGI << x << "\n";             //
#define ERROR(x): LOGE << x << "\n";            //
#define DEBUG(x): LOGD << x << "\n";            // псевдонимы логирования
#define CRITICAL(x): LOGC << x << "\n";         //
#define WARN(x): LOGW << x << "\n";             //


Byte arduino_request(0b00); // 0b00 - default value, 0b01 - high, 0b10 - low, 0b11 - error
Byte arduino_response;      // ответ ардуины

int opt;            // переменная для парса аргументов при запуске сервера
bool logging{0};    // булевая единица логирования
std::string ip_address{"127.0.0.1"}; // адрес сервера по умолчанию
int port{5555};     // порт сервера по умолчанию
std::string last_request; // последнее полученное значение запроса
int last_status;    // послединй статус порта


int main(int argc, char const *argv[])
{

    Settings::setMainLogStream(); // устанавливаем основной поток логирования (консоль)
    httplib::Server svr;          // создаем сервер

    while ((opt = getopt(argc, (char**)argv, "huli:p:")) != -1) {                           //
        switch (opt) {                                                                      //
            case 'i':   ip_address = optarg; break;                                         //
            case 'p':   port = std::stoi(optarg); break;                                    // парс параментров запуска сервера
            case 'l':   logging = true; break;                                              //
            case 'h':   std::cout << Settings::helpLine << "\n"; return 0;                  //
            case '?':   std::cerr << "type [-h] to get help for this program\n"; return 1;  //
            default:    std::cerr << "type [-h] to get help for this program\n"; return 1;  //
        }
    }

    std::string device_port = ChoosePort::choose_port(); // выбор порта для ардуино
    ComPort arduino(device_port);     //создает обьект порта для ардуино

    if (logging) {Settings::setFileLogging();}    // если логирование включено, то устанавливаем поток логирования в файл

                                                                LOGI << "selected address: " << ip_address << ":" << port << "\t--start\n"; 

    svr.Post("/api", [&](const httplib::Request &req, httplib::Response &res) {    //функция обработки POST запроса на /api
        if (req.body != last_request) {                 // если тело запроса не равно последнему запросу, то обрабатываем его
            
                if (last_status) {arduino.reopen();}    // попытка открыть порт при возникновении ошибки с ним

                int status;                             // переменная статуса трансляции сигнала

                if (req.body == "1") {                  //при 1 выставляется высокий первый бит сообщения
                    arduino_request.setBit(1, 0);                                  
                } else {
                    arduino_request.clearBit(1, 0);
                }
                
                status = arduino.write(arduino_request.get_data());

                res.set_content(status ? "sorry, port is not open" : req.body, "text/plain"); // формирование ответа на сервер
                last_request = req.body;                // обновление последнего запроса

                last_status = status;              // обновление статуса порта

                                                                LOGI << " POST " << req.body << "\t"
                                                                            << req.remote_addr << "\t" 
                                                                            << "status: " << status << "\n";
                
                arduino_response.set_data(arduino.read()); //чтение ответа от ардуино
                arduino_response.print(); // печать ответа в логи
        }
    });
    

    
        try
        {
            svr.listen(ip_address, port); // запуск сервера на указанном адресе и порту
        }
        catch(...)
        {
            LOGE << "SERVER CAN NOT START\n";
        }
}