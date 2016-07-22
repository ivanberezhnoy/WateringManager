/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ivanberezhnoy
 *
 * Created on 18 апреля 2016 г., 20:50
 */

#include <cstdlib>
#include <stdio.h>
#include <unistd.h>

#include <Wt/WApplication>
#include <Wt/WBreak>
#include <Wt/WContainerWidget>
#include <Wt/WLineEdit>
#include <Wt/WPushButton>
#include <Wt/WText>

#include "Controller/DomController.h"

using namespace Wt;

/*
 * A simple hello world application class which demonstrates how to react
 * to events, read input, and give feed-back.
 */
class SmartHouseApplication : public WApplication
{
public:
  SmartHouseApplication(const WEnvironment& env);

private:
  WLineEdit *nameEdit_;
  WText *greeting_;
  DomControllerPtr domController;

  void greet();
};

/*
 * The env argument contains information about the new session, and
 * the initial request. It must be passed to the WApplication
 * constructor so it is typically also an argument for your custom
 * application constructor.
*/
SmartHouseApplication::SmartHouseApplication(const WEnvironment& env)
  : WApplication(env)
{
  domController = DomControllerPtr(new DomController());
  domController->loadItemsFromFile("settings.xml");
  setTitle("Smart House");                               // application title

  root()->addWidget(new WText("Your name, please Ivan? "));  // show some text
  nameEdit_ = new WLineEdit(root());                     // allow text input
  nameEdit_->setFocus();                                 // give focus

  WPushButton *button
    = new WPushButton("Greet me.", root());              // create a button
  button->setMargin(5, Left);                            // add 5 pixels margin

  root()->addWidget(new WBreak());                       // insert a line break

  greeting_ = new WText(root());                         // empty text

  /*
   * Connect signals with slots
   *
   * - simple Wt-way
   */
  button->clicked().connect(this, &SmartHouseApplication::greet);

  /*
   * - using an arbitrary function object (binding values with boost::bind())
   */
  nameEdit_->enterPressed().connect
    (boost::bind(&SmartHouseApplication::greet, this));

  /*
   * - using a c++0x lambda:
   */
  // button->clicked().connect(std::bind([=]() { 
  //       greeting_->setText("Hello there, " + nameEdit_->text());
  // }));
}

void SmartHouseApplication::greet()
{
  /*
   * Update the text, using text input into the nameEdit_ field.
   */
  greeting_->setText("Hello there, " + nameEdit_->text());
}

WApplication *createApplication(const WEnvironment& env)
{
  /*
   * You could read information from the environment to decide whether
   * the user has permission to start a new application
   */
  return new SmartHouseApplication(env);
}

//#include <wiringPi.h>
#include <stdio.h>

//int main (int argc, char** argv)
//{
//  printf("Program is started");
//  wiringPiSetupSys () ;
//  pinMode (2, OUTPUT) ;
//  for (;;)
//  {
//    digitalWrite (2, HIGH) ; delay (500) ;
//    digitalWrite (2,  LOW) ; delay (500) ;
//  }
//  return 0 ;
//}

int main(int argc, char **argv)
{
  return WRun(argc, argv, &createApplication);
}
