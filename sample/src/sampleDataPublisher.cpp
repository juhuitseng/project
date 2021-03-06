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
 * LOGICAL_NAME:    HelloWorldDataPublisher.cpp
 * FUNCTION:        OpenSplice Tutorial example code.
 * MODULE:          Tutorial for the C++ programming language.
 * DATE             September 2010.
 ************************************************************************
 *
 * This file contains the implementation for the 'HelloWorldDataPublisher' executable.
 *
 ***/
#include <string>
#include <sstream>
#include <iostream>
#include "DDSEntityManager.h"
#include "ccpp_HelloWorldData.h"
 #include "higherfunc.h"
#if defined VORTEX_COMMUNITY
  #include "os.h"
#else
  #include "vortex_os.h"
#endif


#include "example_main.h"

using namespace DDS;
using namespace HelloWorldData;

/* entry point exported and demangled so symbol can be found in shared library */
extern "C"
{
  OS_API_EXPORT
  int HelloWorldDataPublisher(int argc, char *argv[]);
}

int HelloWorldDataPublisher(int argc, char *argv[])
{

  if (argc<2)
  {
    cout << "You need to specify a message to send!" << endl;
    return 1;
  }

  char topic_send[] = "Send";
  char topic_response[] = "Response";
  send_message(argv[1], topic_send);
  string responseMessage = get_information(topic_response);
  cout << "The response message is " << responseMessage << endl;


  /* The follwing code is the old example
  os_time delay_1s = { 1, 0 };
  DDSEntityManager mgr;

  mgr.createParticipant("HelloWorld example");

  MsgTypeSupport_var mt = new MsgTypeSupport();
  mgr.registerType(mt.in());

  char topic_name[] = "HelloWorldData_Msg";
  mgr.createTopic(topic_name);

  mgr.createPublisher();

  bool autodispose_unregistered_instances = false;
  mgr.createWriter(autodispose_unregistered_instances);

  DataWriter_var dwriter = mgr.getWriter();
  MsgDataWriter_var HelloWorldWriter = MsgDataWriter::_narrow(dwriter.in());

  Msg msgInstance; 
  msgInstance.userID = 1;
  msgInstance.message = DDS::string_dup("Hello World");
  cout << "=== [Publisher] writing a message containing :" << endl;
  cout << "    userID  : " << msgInstance.userID << endl;
  cout << "    Message : \"" << msgInstance.message << "\"" << endl;

  ReturnCode_t status = HelloWorldWriter->write(msgInstance, DDS::HANDLE_NIL);
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
  return HelloWorldDataPublisher (argc, argv);
}
