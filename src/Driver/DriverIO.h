/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DriverIO.h
 * Author: ivanberezhnoy
 *
 * Created on 8 июля 2016 г., 12:40
 */

#ifndef DRIVERIO_H
#define DRIVERIO_H

#define PI_DRIVER 0

#include "IO/PinDefs.h"

#include <set>

#include <boost/shared_ptr.hpp>


class DriverIO {
public:
    DriverIO();
    virtual ~DriverIO();
    
    static boost::shared_ptr<DriverIO> sharedDriver();
    
    void registerOutputPin(unsigned outputPin);
    void registerInputPin(unsigned inputPin);
    
    bool setOutputPinState(unsigned outputPin, PinState state);
private:
    std::set<unsigned> registeredOutputPins;
    std::set<unsigned> registeredInputPins;
};

#endif /* DRIVERIO_H */

