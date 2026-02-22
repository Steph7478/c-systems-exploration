#include <string.h>
#include "user_repository.h"
#include "../../data/user_data.h"
#include "../entities/user.h"
#include <stdlib.h>

static User user_cache[100];

static void map_user(User *dest, int index)
{
    dest->id = raw_user_ids[index];
    strncpy(dest->name, raw_user_names[index], sizeof(dest->name) - 1);
    dest->name[sizeof(dest->name) - 1] = '\0';
}

User *user_repo_find_all(int *count)
{
    *count = user_table_size;

    User *users = malloc(sizeof(User) * user_table_size);
    if (!users)
        return NULL;

    for (int i = 0; i < user_table_size; i++)
    {
        map_user(&users[i], i);
    }

    return users;
}