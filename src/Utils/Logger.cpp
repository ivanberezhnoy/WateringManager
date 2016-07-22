/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Logger.cpp
 * Author: ivanberezhnoy
 * 
 * Created on 8 июля 2016 г., 0:11
 */

#include "Logger.h"
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/lock_guard.hpp>

static boost::shared_ptr<Logger> sharedLoggerPtr = nullptr;
static boost::recursive_mutex mtx;

Logger::Logger() 
{
    if (sharedLoggerPtr)
    {
        sharedLoggerPtr->logError("Invalid Logger initialization. Logger is already initialized.");
    }
}

Logger::~Logger() 
{
}

boost::shared_ptr<Logger> Logger::sharedLogger()
{
    if (sharedLoggerPtr)
    {
        return sharedLoggerPtr;
    }
    else
    {
        boost::lock_guard<boost::recursive_mutex> lock(mtx);
        if (!sharedLoggerPtr) 
        {
           sharedLoggerPtr = boost::shared_ptr<Logger>(new Logger());
        }
        return sharedLoggerPtr;
    }
}

void Logger::logError(std::string /*errorText*/)
{
}


void logError(std::string errorText)
{
    Logger::sharedLogger()->logError(errorText);
}