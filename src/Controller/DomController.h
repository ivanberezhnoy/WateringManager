/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DomController.h
 * Author: ivanberezhnoy
 *
 * Created on 8 июля 2016 г., 10:07
 */

#ifndef DOMCONTROLLER_H
#define DOMCONTROLLER_H

#include "DOM/SmartItem.h"

#include <list>

class DomController {
public:
    DomController();
    virtual ~DomController();
    void loadItemsFromFile(const std::string& pathToFile);
private:
    std::list<SmartItemPtr> smartItems;
};

using DomControllerPtr = boost::shared_ptr<DomController>;

#endif /* DOMCONTROLLER_H */

