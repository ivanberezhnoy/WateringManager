/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IOPin.h
 * Author: ivanberezhnoy
 *
 * Created on 8 июля 2016 г., 10:35
 */

#ifndef IOPIN_H
#define IOPIN_H

#include "PinDefs.h"

class IOPin 
{
public:
    IOPin(unsigned pin);
    virtual ~IOPin();
    
    unsigned getPinIndex() const;
    PinState getState() const;

protected:
    virtual void setState(PinState newState);    
protected:
   PinState pinState; 
   unsigned pinIndex;
};

#endif /* IOPIN_H */

