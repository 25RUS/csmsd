#include <iostream>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <chrono>

int write(std::vector<std::string> atv, std::string com)
{
    const char* c_com = com.c_str();
    int port = open(c_com, O_RDWR | O_NOCTTY);
    if (port < 0)
    {
        // Обработка ошибки открытия порта
        std::cerr << "Failed to open COM port" << std::endl;
        return 1;
    }

    struct termios options;
    tcgetattr(port, &options);

    // Установка настроек скорости передачи данных, битности, контроля четности и т. д.
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    tcsetattr(port, TCSANOW, &options);

    // Запись данных в порт
    for(std::string at : atv)
    {
        const char* data = at.c_str();
        ssize_t bytesWritten = write(port, data, strlen(data));

        std::cout << "SENT: " << data << std::endl;

        if (bytesWritten < 0)
        {
            // Обработка ошибки записи данных в порт
            std::cerr << "Failed to write data to COM port" << std::endl;
            close(port);
            return 1;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }


    const int bufferSize = 100;  // Размер буфера для чтения
    char buffer[bufferSize];
    ssize_t bytesRead;
    bool portIsOpen = true;


    while (portIsOpen)
    {
        bytesRead = read(port, buffer, bufferSize - 1);
        if (bytesRead > 0)
        {
            buffer[bytesRead] = '\0';  // Добавляем нулевой символ в конец считанных данных
            std::cout << "Read from COM port: " << buffer << std::endl;
            break;
        }
        else if (bytesRead < 0)
        {
            // Обработка ошибки чтения из порта
            std::cerr << "Failed to read from COM port" << std::endl;
            break;  // Прерываем цикл чтения
        }
        else
        {
            // Если bytesRead == 0, это означает, что порт закрыт
            portIsOpen = false;
        }
    }


    // Закрытие порта
    close(port);


    return 0;
}
