#define VORTEX_COMMUNITY

/*
 *                         OpenSplice DDS
 *
 *   This software and documentation are Copyright 2006 to 2013 PrismTech
 *   Limited and its licensees. All rights reserved. See file:
 *
 *                     $OSPL_HOME/LICENSE
 *
 *   for full copyright notice and license terms.
 *
 */

/************************************************************************
 * LOGICAL_NAME:    chessDataSubscriber.cpp
 * FUNCTION:        OpenSplice chess example code.
 * MODULE:          chess for the C++ programming language.
 * DATE             September 2010.
 ************************************************************************
 *
 * This file contains the implementation for the 'chessDataSubscriber' executable.
 *
 ***/
#include <string>
#include <string.h>
#include <sstream>
#include <iostream>
#include "DDSEntityManager.h"
#include "ccpp_chessData.h"
#include "higherfunc.h"
#if defined VORTEX_COMMUNITY
  #include "os.h"
#else
  #include "vortex_os.h"
#endif


#include "example_main.h"
#include "unistd.h"
using namespace DDS;
using namespace chessData;

/* entry point exported and demangled so symbol can be found in shared library */
extern "C"
{
  OS_API_EXPORT
  int chessDataSubscriber(int argc, char *argv[]);
}

int chessDataSubscriber(int argc, char *argv[])
{

  char topic_send[] = "Send";
  char topic_response[] = "Response";
  string message_from_send_topic = "";
  string str_key_from_send_topic = "";
  string temp;
  char reply_message[] = "I got you";
  char end_message[] = "~~End of the program~~";
  bool quit = false;
  string last_message="";
  int key_value=1;
  char char_key[20];
  cout << "Please input 'quit' to terminate the program!" << endl;
  
  while(!quit) 
  {
    //get message from send
    while(1){
      temp = get_information(topic_send);

      if(temp != str_key_from_send_topic && temp != last_message){
        message_from_send_topic = temp;
        last_message = message_from_send_topic;
        break;
      }
    }
    if(message_from_send_topic == "join"){
      temp=key_value+'0';
      strcpy(char_key, temp.c_str());

      send_message(char_key, topic_response);
      key_value++;

    }
    //get key from send
    else{
    
      while(1){
        temp=get_information(topic_send);
        if(temp!=message_from_send_topic){
          str_key_from_send_topic = temp;
          break;
        }
      }
    
     
    char char_key_from_send_topic[20];
    strcpy(char_key_from_send_topic, str_key_from_send_topic.c_str());
    if (message_from_send_topic!="quit")
    {
      cout << "Received message: " << message_from_send_topic << endl;
      cout << "Received key: " << str_key_from_send_topic<<endl;
      send_message(reply_message, topic_response);
      sleep(2);
      send_message(char_key_from_send_topic, topic_response);
      
    } 
    else
    {
      quit=true;
      cout << "~~End of the program~~" << endl;
      send_message(end_message, topic_response);
    }
  }
  }  
/* The following code is the old example
  os_time delay_2ms = { 0, 2000000 };
  os_time delay_200ms = { 0, 200000000 };
  MsgSeq msgList;
  SampleInfoSeq infoSeq;

  DDSEntityManager mgr;

  mgr.createParticipant("chess example");

  MsgTypeSupport_var mt = new MsgTypeSupport();
  mgr.registerType(mt.in());

  char topic_name[] = "chessData_Msg";
  mgr.createTopic(topic_name);

  mgr.createSubscriber();

  mgr.createReader();

  DataReader_var dreader = mgr.getReader();
  MsgDataReader_var chessReader = MsgDataReader::_narrow(dreader.in());
  checkHandle(chessReader.in(), "MsgDataReader::_narrow");

  cout << "=== [Subscriber] Ready ..." << endl;

  bool closed = false;
  ReturnCode_t status =  - 1;
  int count = 0;
  while (!closed && count < 1500) 
  {
    status = chessReader->take(msgList, infoSeq, LENGTH_UNLIMITED,
      ANY_SAMPLE_STATE, ANY_VIEW_STATE, ANY_INSTANCE_STATE);
    checkStatus(status, "msgDataReader::take");
    for (DDS::ULong j = 0; j < msgList.length(); j++)
    {
      cout << "=== [Subscriber] message received :" << endl;
      cout << "    userID  : " << msgList[j].userID << endl;
      cout << "    Message : \"" << msgList[j].message << "\"" << endl;
      closed = true;
    }
    status = chessReader->return_loan(msgList, infoSeq);
    checkStatus(status, "MsgDataReader::return_loan");
    os_nanoSleep(delay_200ms);
    ++count;
  }

  os_nanoSleep(delay_2ms);

  mgr.deleteReader();
  mgr.deleteSubscriber();
  mgr.deleteTopic();
  mgr.deleteParticipant();
*/
  return 0;
}

int OSPL_MAIN (int argc, char *argv[])
{
  return chessDataSubscriber (argc, argv);
}
