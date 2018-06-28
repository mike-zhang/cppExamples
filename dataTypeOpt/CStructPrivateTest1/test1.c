#include "obj.h"
#include <stdlib.h>

int main()
{
    Obj *o = NULL;
    o = create_obj(1,"test1");
    printf("id : %d\n",o->id);
    //printf("id : %d\n",get_obj_id(o));
    release_obj(o);
}

