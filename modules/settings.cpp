#include <iostream>
#include "../lib/logger/includes/logger.h"
#include "../lib/logger/includes/filelogger.h"
#include "../lib/logger/includes/consolelogger.h"


namespace Settings {



    std::string helpLine{"============================================\n\
\tThis is a simple HTTP server\n"
              "It will listen for POST requests on /api\n"
              "and log the request body to the console and file.\n"
              "\n" \
                "Usage: ./server \n  -h  --  to show help list\n\
  -l -- set to .log files (default path: ./)\n\
  -i -- set ip address (default address: 127.0.0.1)\n\
  -p -- set port (default port: 5555)\n"

              "============================================\n"};


    void setMainLogStream() {
        ILogListener* consoleLogger = new ConsoleLogger; 
        SimpleLogger::AddListener(consoleLogger);
    }

    int setFileLogging() {
        try
        {
            ILogListener* fileLogger = new FileLogger;
            SimpleLogger::AddListener(fileLogger);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return 1;
        }
        return 0;
    }

};