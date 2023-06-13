#ifndef READER_H
#define READER_H

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
/**
 * @class reader
 * @brief Klasa obsługująca odczyt danych.
 */
class reader
{
private:
    int ax=0; /**< Wartość przyspieszenia w osi x. */
    int ay=0; /**< Wartość przyspieszenia w osi y. */
public:
/**
     * @brief Obsługuje odczyt danych z urządzenia.
     * @param fd Deskryptor pliku urządzenia.
     */
    void handleRead(int fd);
    /**
     * @brief Zwraca wartość przyspieszenia w osi x.
     * @return Wartość przyspieszenia w osi x.
     */
    int getAx() const;

    /**
     * @brief Zwraca wartość przyspieszenia w osi y.
     * @return Wartość przyspieszenia w osi y.
     */
    int getAy() const;
};

#endif // READER_H
