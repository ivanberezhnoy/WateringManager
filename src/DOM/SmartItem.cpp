/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SmartItem.cpp
 * Author: ivanberezhnoy
 * 
 * Created on 8 июля 2016 г., 0:06
 */

#include "SmartItem.h"
#include "Utils/Logger.h"

SmartItem::SmartItem(std::string id) 
{
    itemID = id;
    pauseCounter = 0;
    onCounter = 0;
}

SmartItem::~SmartItem() 
{
}

std::string SmartItem::getID() const
{
    return this->itemID;
}

std::string SmartItem::getItemName() const
{
    return this->itemName;
}

void SmartItem::setItemName(std::string name)
{
    this->itemName = std::move(name);
}

OutputPinPtr SmartItem::getOutputPin() const
{
    return this->outputPin;
}

void SmartItem::setOutputPin(OutputPinPtr pin)
{
    this->outputPin = pin;
}

InputPinPtr SmartItem::getInputActivationPin() const
{
    return this->inputActivationPin;
}

void SmartItem::setInputActivationPin(InputPinPtr inputPin)
{
    this->inputActivationPin = std::move(inputPin);
}

SmartItem::SmartItemState SmartItem::getState() const
{
    if (onCounter == 0)
    {
        return SmartItem::ItemStateOff;
    }
    else if (pauseCounter == 0)
    {
        return SmartItem::ItemStateOn;
    }
    else
    {
        return SmartItem::ItemStatePaused;
    }
}

void SmartItem::pauseItem()
{
    if (!checkOutputPin())
    {
        return;
    }
    
    if (!pauseCounter && onCounter)
    {
        this->outputPin->setState(PinOFF);
    }
    
    ++pauseCounter;
}

void SmartItem::resumeItem()
{
    if (pauseCounter)
    {
        --pauseCounter;
        if (!pauseCounter && onCounter)
        {
            this->outputPin->setState(PinON);
        }
    }
    else
    {
        logError("Unable resume item '" + itemName + "', because it is not paused.");
    }
    
}

void SmartItem::onItem()
{
    if (!checkOutputPin())
    {
        return;
    }
    
    if (!pauseCounter && !onCounter)
    {
        this->outputPin->setState(PinON);
    }
    
    for (const auto& itemToActivate : itemsToActivate)
    {
        itemToActivate->onItem();
    }
    
    for (const auto& itemToDeactivate : itemsToDeactivate)
    {
        itemToDeactivate->offItem();
    }    
    
    ++onCounter;
}

void SmartItem::offItem()
{
    if (!checkOutputPin())
    {
        return;
    }
    
    if (onCounter)
    {
        --onCounter;
        if (!onCounter && !pauseCounter)
        {
            this->outputPin->setState(PinOFF);
        }
    }
    else
    {
        logError("Unable OFF item '" + itemName + "', because it OFF.");
    }
}

void SmartItem::setItemsToActivate(std::list<SmartItemPtr> items)
{
    for (unsigned activeCounter = 0; activeCounter < onCounter; activeCounter++)
    {
        for (const auto& itemToActivate : itemsToActivate)
        {
            itemToActivate->offItem();
        }
    }
    
    itemsToActivate = std::move(items);
    for (unsigned activeCounter = 0; activeCounter < onCounter; activeCounter++)
    {
        for (const auto& itemToActivate : itemsToActivate)
        {
            itemToActivate->onItem();
        }
    }    
}

void SmartItem::setItemsToDeactivate(std::list<SmartItemPtr> items)
{
    for (unsigned activeCounter = 0; activeCounter < onCounter; activeCounter++)
    {
        for (const auto& itemToDeactivate : itemsToDeactivate)
        {
            itemToDeactivate->onItem();
        }
    }
    
    itemsToDeactivate = std::move(items);
    for (unsigned activeCounter = 0; activeCounter < onCounter; activeCounter++)
    {
        for (const auto& itemToDeactivate : itemsToDeactivate)
        {
            itemToDeactivate->offItem();
        }
    }      
}

bool SmartItem::checkOutputPin() const
{
    if (!outputPin)
    {
        logError("Unable change item state '" + itemName + "' without output pin");
        return false;
    }    
    return true;
}


