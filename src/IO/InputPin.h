/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InputPin.h
 * Author: ivanberezhnoy
 *
 * Created on 8 июля 2016 г., 0:08
 */

#ifndef INPUTPIN_H
#define INPUTPIN_H

#include "IOPin.h"

#include <boost/shared_ptr.hpp>

class InputPin : public IOPin
{
public:
    InputPin(unsigned pin);
    virtual ~InputPin();

};

using InputPinPtr = boost::shared_ptr<InputPin>;

#endif /* INPUTPIN_H */

