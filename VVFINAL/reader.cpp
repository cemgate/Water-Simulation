#include "reader.h"

/**
     * @brief Metoda obsługująca odczyt danych.
     * @param fd Deskryptor pliku do odczytu.
     */
void reader::handleRead(int fd)
{
    fd = open("/dev/hidraw1", O_RDONLY);
    if(fd<0)
    {
        std::cout<<"???????";
        return;

    }
    else
    {
        char buffer[128];
        ssize_t count=read(fd, buffer, 128);





        ax = buffer[41]<<8 | buffer[42];
        ay =buffer[43]<<8 | buffer[44];


        fflush(stdout);

    }
    close(fd);

}
/**
     * @brief Metoda zwracająca wartość osi x.
     * @return Wartość osi x.
     */
int reader::getAx() const
{
    return ax;
}
 /**
     * @brief Metoda zwracająca wartość osi y.
     * @return Wartość osi y.
     */
int reader::getAy() const
{
    return ay;
}
