#include <jansson.h>
#include <string.h>
#include <stdio.h>

#define SHORE_CLIENT_JSON_VERBOSE
#define SHORE_CLIENT_STRING_LENGTH 4096

void json_fixstring(char *jsonstr, int length){
    int i;
    int s=0;
    for(i=0; i<length; i++){
        if(jsonstr[i]=='{') s++;
        if(jsonstr[i]=='}') s--;
        if(s==0){
            jsonstr[i+1]='\0';
            break;
        }
    }
}

void json_getvalue(char *jsonstr, char deststr[], char *result){

    json_error_t error;
    json_t *root = json_loads(jsonstr, SHORE_CLIENT_STRING_LENGTH,  &error );

    if(!root){
#ifdef SHORE_CLIENT_JSON_VERBOSE
        printf("json_getvalue: root ==  null\n");
#endif
    }

    json_t *jsonData = json_object_get(root, deststr);
    const char *r = json_string_value( jsonData );

    strcpy(result,r);
#ifdef SHORE_CLIENT_JSON_VERBOSE
    printf("json_string_value: %s\n",result);
#endif

    json_decref( root );

}



