#include "user_service.h"
#include "../utils/json.h"
#include "../repository/user_repository.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *user_get_all_as_json()
{
    int count = 0;
    User *users = user_repo_find_all(&count);

    if (!users || count <= 0)
    {
        if (users)
            free(users);
        return strdup("[]");
    }

    static JsonField user_fields[] = {
        {"id", offsetof(User, id), JSON_INT, 0},
        {"username", offsetof(User, name), JSON_STRING_FIXED, sizeof(((User *)0)->name)}};

    char *json = json_serialize_array(
        users,
        count,
        sizeof(User),
        user_fields,
        sizeof(user_fields) / sizeof(user_fields[0]));

    free(users);
    return json;
}