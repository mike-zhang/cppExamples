#ifndef _OBJ_H_
#define _OBJ_H_

typedef struct Obj Obj;

Obj* create_obj(int id,const char* name);
void release_obj(Obj* o);

int get_obj_id(const Obj* o);

#endif

