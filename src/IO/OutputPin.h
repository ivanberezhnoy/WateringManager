/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OutputPin.h
 * Author: ivanberezhnoy
 *
 * Created on 8 июля 2016 г., 0:08
 */

#ifndef OUTPUTPIN_H
#define OUTPUTPIN_H

#include <boost/shared_ptr.hpp>

#include "IOPin.h"

class OutputPin : public IOPin 
{
public:
    OutputPin(unsigned pin);
    virtual ~OutputPin();
    void setState(PinState newState);
};

using OutputPinPtr = boost::shared_ptr<OutputPin>;

#endif /* OUTPUTPIN_H */

