/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Logger.h
 * Author: ivanberezhnoy
 *
 * Created on 8 июля 2016 г., 0:11
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <boost/shared_ptr.hpp>

class Logger {
public:
    Logger();
    ~Logger();
    static boost::shared_ptr<Logger> sharedLogger();
    void logError(std::string errorText);
private:

};

void logError(std::string errorText);

#endif /* LOGGER_H */

