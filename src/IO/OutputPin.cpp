/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OutputPin.cpp
 * Author: ivanberezhnoy
 * 
 * Created on 8 июля 2016 г., 0:08
 */

#include "OutputPin.h"
#include "Driver/DriverIO.h"

OutputPin::OutputPin(unsigned pin) : IOPin(pin)
{
    DriverIO::sharedDriver()->registerOutputPin(pin);
}

OutputPin::~OutputPin() 
{
}

void OutputPin::setState(PinState newState)
{
    if (this->getState() != newState)
    {
        IOPin::setState(newState);
        DriverIO::sharedDriver()->setOutputPinState(this->getPinIndex(), this->getState());
    }
}

