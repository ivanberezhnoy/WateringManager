/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IOPin.cpp
 * Author: ivanberezhnoy
 * 
 * Created on 8 июля 2016 г., 10:35
 */

#include "IOPin.h"

IOPin::IOPin(unsigned pin) 
{
    pinIndex = pin;
}

IOPin::~IOPin()
{
}

PinState IOPin::getState() const
{
    return this->pinState;
}

unsigned IOPin::getPinIndex() const
{
    return this->pinIndex;
}

void IOPin::setState(PinState newState)
{
    if (this->pinState != newState)
    {
        this->pinState = newState;
    }
}
