/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SmartItem.h
 * Author: ivanberezhnoy
 *
 * Created on 8 июля 2016 г., 0:06
 */

#ifndef SMARTITEM_H
#define SMARTITEM_H

#include "IO/OutputPin.h"
#include "IO/InputPin.h"
#include <string>
#include <list>

class SmartItem;
using SmartItemPtr = boost::shared_ptr<SmartItem>;

class SmartItem 
{
public:
    
    enum SmartItemState
    {
        ItemStateOn,
        ItemStateOff,
        ItemStatePaused
    };


    SmartItem(std::string id);
    virtual ~SmartItem();
    
    std::string getID() const;
    
    std::string getItemName() const;
    void setItemName(std::string name);
    
    OutputPinPtr getOutputPin() const;
    void setOutputPin(OutputPinPtr pin);
    
    InputPinPtr getInputActivationPin() const;
    void setInputActivationPin(InputPinPtr inputPin);
    
    SmartItemState getState() const;
    void pauseItem();
    void resumeItem();
    void onItem();
    void offItem();
    
    void setItemsToActivate(std::list<SmartItemPtr> items);
    void setItemsToDeactivate(std::list<SmartItemPtr> items);
private:  
    bool checkOutputPin() const;
private:
    OutputPinPtr outputPin;
    InputPinPtr inputActivationPin;
    std::list<SmartItemPtr> itemsToActivate;
    std::list<SmartItemPtr> itemsToDeactivate;
    unsigned pauseCounter;
    unsigned onCounter;
    std::string itemName;
    std::string itemID;
};

#endif /* SMARTITEM_H */

