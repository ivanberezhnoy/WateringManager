/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DriverIO.cpp
 * Author: ivanberezhnoy
 * 
 * Created on 8 июля 2016 г., 12:40
 */

#include "DriverIO.h"
#include "Utils/Logger.h"

#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/lexical_cast.hpp>

#if PI_DRIVER > 0
#include <wiringPi.h>

#else
const int OUTPUT=1;
const int INPUT=0;
const int HIGH = 1;
const int LOW = 0;

void digitalWrite (int /*pin*/, int /*value*/)
{
}

void wiringPiSetupSys ()
{
    
}

void pinMode(int /*pin*/, int /*mode*/)
{
}
#endif

boost::shared_ptr<DriverIO> sharedDriverPtr = nullptr;
static boost::recursive_mutex driverMtx;

DriverIO::DriverIO() 
{
    if (sharedDriverPtr)
    {
        logError("Invalid DriverIO initialization. Driver is already initialized.");
    }  
    
    wiringPiSetupSys();
}

DriverIO::~DriverIO() 
{
}

boost::shared_ptr<DriverIO> DriverIO::sharedDriver()
{
    if (sharedDriverPtr)
    {
        return sharedDriverPtr;
    }
    else
    {
        boost::lock_guard<boost::recursive_mutex> lock(driverMtx);
        if (!sharedDriverPtr) 
        {
           sharedDriverPtr = boost::shared_ptr<DriverIO>(new DriverIO());
        }
        return sharedDriverPtr;
    }
}

void DriverIO::registerOutputPin(unsigned outputPin)
{
    if (registeredOutputPins.find(outputPin) != registeredOutputPins.end())
    {
        logError("Unable register output pin with index: {" + boost::lexical_cast<std::string>(outputPin) + "'} in's alredy registered as output");
        return;
    }
    
    if (registeredInputPins.find(outputPin) != registeredInputPins.end())
    {
        logError("Unable register output pin with index: {" + boost::lexical_cast<std::string>(outputPin) + "'} in's alredy registered as input");
        return;
    }    
    
    registeredOutputPins.insert(outputPin);
    pinMode(outputPin, OUTPUT);
    setOutputPinState(outputPin, PinOFF);
}

void DriverIO::registerInputPin(unsigned inputPin)
{
    if (registeredOutputPins.find(inputPin) != registeredOutputPins.end())
    {
        logError("Unable register input pin with index: {" + boost::lexical_cast<std::string>(inputPin) + "'} in's alredy registered as output");
        return;
    }
    
    if (registeredInputPins.find(inputPin) != registeredInputPins.end())
    {
        logError("Unable register input pin with index: {" + boost::lexical_cast<std::string>(inputPin) + "'} in's alredy registered as input");
        return;
    }    
    
    registeredOutputPins.insert(inputPin);
    pinMode(inputPin, INPUT);   
}

bool DriverIO::setOutputPinState(unsigned outputPin, PinState state)
{
    if (registeredOutputPins.find(outputPin) != registeredOutputPins.end())
    {
        logError("Unable change output pin state with index: {" + boost::lexical_cast<std::string>(outputPin) + "'}. Pin is not registered.");
        return false;
    }
    
    digitalWrite(outputPin, state == PinON ? LOW : HIGH);
    
    return true;
}