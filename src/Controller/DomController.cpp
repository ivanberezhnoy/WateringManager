/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DomController.cpp
 * Author: ivanberezhnoy
 * 
 * Created on 8 июля 2016 г., 10:07
 */

#include "DomController.h"
#include "Utils/Logger.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

DomController::DomController() 
{
}

DomController::~DomController() 
{
}

void DomController::loadItemsFromFile(const std::string& pathToFile)
{
    using namespace boost;
    using namespace property_tree;
    
    ptree xmlTree;
    
    try
    {
        read_xml(pathToFile, xmlTree); 
        
        BOOST_FOREACH(ptree::value_type const& smartItemNode, xmlTree.get_child("settings.smartItems"))
        {
            if(smartItemNode.first == "item" ) 
            {
                std::string itemName = smartItemNode.second.get<std::string>("name");
                std::string itemID = smartItemNode.second.get<std::string>("id");
                SmartItemPtr smartItem = SmartItemPtr(new SmartItem(std::move(itemID)));
                smartItem->setItemName(std::move(itemName));
                
                auto outputPinNode = smartItemNode.second.get_child_optional("outputPin");
                if(outputPinNode)
                {
                    unsigned outputPinNumber = outputPinNode->get_value<unsigned>();
                    OutputPinPtr outputPin(new OutputPin(outputPinNumber));
                    smartItem->setOutputPin(std::move(outputPin));
                }     
                
                auto inputPinNode = smartItemNode.second.get_child_optional("inputPin");
                if(inputPinNode)
                {
                    unsigned inputPinNumber = inputPinNode->get_value<unsigned>();
                    InputPinPtr inputPin(new InputPin(inputPinNumber));
                    smartItem->setInputActivationPin(std::move(inputPin));
                }
                
                smartItems.push_back(std::move(smartItem));
            }
        }
    }
    catch(const ptree_error& e)
    {
        logError(std::string("Unable to open file '") + pathToFile + "'. error: " + e.what());
    }
}
