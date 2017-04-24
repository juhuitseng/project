#ifndef CHESSDATASPLTYPES_H
#define CHESSDATASPLTYPES_H

#include "ccpp_chessData.h"

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>

extern c_metaObject __chessData_chessData__load (c_base base);

extern c_metaObject __chessData_Msg__load (c_base base);
extern const char * __chessData_Msg__keys (void);
extern const char * __chessData_Msg__name (void);
struct _chessData_Msg ;
extern  c_bool __chessData_Msg__copyIn(c_base base, struct chessData::Msg *from, struct _chessData_Msg *to);
extern  void __chessData_Msg__copyOut(void *_from, void *_to);
struct _chessData_Msg {
    c_long userID;
    c_string message;
};

#endif
