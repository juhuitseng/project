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
 * LOGICAL_NAME:    chessDataPublisher.cpp
 * FUNCTION:        OpenSplice Tutorial example code.
 * MODULE:          Tutorial for the C++ programming language.
 * DATE             September 2010.
 ************************************************************************
 *
 * This file contains the implementation for the 'chessDataPublisher' executable.
 *
 ***/
#include <string>
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
  int chessDataPublisher(int argc, char *argv[]);
}

int chessDataPublisher(int argc, char *argv[])
{

  char topic_send[] = "Send";
  char topic_response[] = "Response";
  bool quit = false;
  string responseMessage = "";
  string responseKey = "";
  string temp = "";

  if (argc<2)
  {
    cout << "You need to specify a message to send!" << endl;
    return 1;
  }
 

  send_message(argv[1], topic_send);
  sleep(2);
  send_message(argv[2], topic_send);

  
  responseMessage = get_information(topic_response);

  
  if(argc>2){  
  while(1){
    temp=get_information(topic_response);
    if(temp != responseMessage){
      responseKey = temp;
      break;
    }
  }
  }

  if(argc == 2) cout<<"Your key number is "<<responseMessage<<endl;
  else{
    if(responseKey==argv[2]){
      cout << "Response message: " << responseMessage << endl;
      cout<<"Response key: "<<responseKey<<endl;
    }
  }
 

  
    



  /* The follwing code is the old example
  os_time delay_1s = { 1, 0 };
  DDSEntityManager mgr;

  mgr.createParticipant("chess example");

  MsgTypeSupport_var mt = new MsgTypeSupport();
  mgr.registerType(mt.in());

  char topic_name[] = "chessData_Msg";
  mgr.createTopic(topic_name);

  mgr.createPublisher();

  bool autodispose_unregistered_instances = false;
  mgr.createWriter(autodispose_unregistered_instances);

  DataWriter_var dwriter = mgr.getWriter();
  MsgDataWriter_var chessWriter = MsgDataWriter::_narrow(dwriter.in());

  Msg msgInstance; 
  msgInstance.userID = 1;
  msgInstance.message = DDS::string_dup("Hello World");
  cout << "=== [Publisher] writing a message containing :" << endl;
  cout << "    userID  : " << msgInstance.userID << endl;
  cout << "    Message : \"" << msgInstance.message << "\"" << endl;

  ReturnCode_t status = chessWriter->write(msgInstance, DDS::HANDLE_NIL);
  checkStatus(status, "MsgDataWriter::write");
  os_nanoSleep(delay_1s);
  mgr.deleteWriter();
  mgr.deletePublisher();
  mgr.deleteTopic();
  mgr.deleteParticipant();
  */
  return 0;
}

int OSPL_MAIN (int argc, char *argv[])
{
  return chessDataPublisher (argc, argv);
}
