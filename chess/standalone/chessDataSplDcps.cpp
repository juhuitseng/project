#include "chessDataSplDcps.h"
#include "ccpp_chessData.h"
#include "dds_type_aliases.h"

const char *
__chessData_Msg__name(void)
{
    return (const char*)"chessData::Msg";
}

const char *
__chessData_Msg__keys(void)
{
    return (const char*)"userID";
}

#include <v_kernel.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

c_bool
__chessData_Msg__copyIn(
    c_base base,
    struct ::chessData::Msg *from,
    struct _chessData_Msg *to)
{
    c_bool result = OS_C_TRUE;
    (void) base;

    to->userID = (c_long)from->userID;
#ifdef OSPL_BOUNDS_CHECK
    if(from->message){
        to->message = c_stringNew(base, from->message);
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'chessData::Msg.message' of type 'c_string' is NULL.");
        result = OS_C_FALSE;
    }
#else
    to->message = c_stringNew(base, from->message);
#endif
    return result;
}

void
__chessData_Msg__copyOut(
    void *_from,
    void *_to)
{
    struct _chessData_Msg *from = (struct _chessData_Msg *)_from;
    struct ::chessData::Msg *to = (struct ::chessData::Msg *)_to;
    to->userID = (::DDS::Long)from->userID;
    to->message = DDS::string_dup(from->message ? from->message : "");
}

