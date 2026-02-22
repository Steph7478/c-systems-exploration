#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include "../entities/user.h"

char *user_get_all_as_json();
void user_to_json_single(void *item, char *dest);

#endif