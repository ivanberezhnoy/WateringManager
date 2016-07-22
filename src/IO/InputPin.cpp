/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InputPin.cpp
 * Author: ivanberezhnoy
 * 
 * Created on 8 июля 2016 г., 0:08
 */

#include "InputPin.h"
#include "Driver/DriverIO.h"

InputPin::InputPin(unsigned pin) : IOPin(pin)
{
    DriverIO::sharedDriver()->registerInputPin(pin);
}

InputPin::~InputPin() 
{
}

