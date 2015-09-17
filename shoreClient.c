#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <zmq.h>
#include <jansson.h>
#include <string.h>
#include "shoreClient.h"

bool isZmqInited = false;
void *zmq_context;
void *zmq_requester;


char *generate_json_data(const char *operation, const char *doid, const char *column, const unsigned int row, const unsigned int *shape) {
    char *ret_strings = NULL;
    json_t *root = json_object();
    json_object_set_new(root, "operation", json_string(operation));
    json_object_set_new(root, "doid", json_string(doid));
    json_object_set_new(root, "column", json_string(column));
    json_object_set_new(root, "row", json_integer(row));
    if (shape){
        json_t *dim = json_array();
        json_object_set_new(root, "shape", dim);
        int i;
        for (i=1; i<=shape[0]; i++){
            json_array_append(dim, json_integer(shape[i]));
        }
    }
    ret_strings = json_dumps( root, 0 );
    json_decref(root);
    return ret_strings;
}

void zmqInit(){
    char *address = getenv("SHORE_DAEMON_ADDRESS");
    if (!address){
        printf("SHORE_DAEMON_ADDRESS system environment variable not set! \n");
        return;
    }
    printf("shoreClient ZMQ inited. Address = %s\n", address);

    isZmqInited = true;

    zmq_context = zmq_ctx_new ();
    zmq_requester = zmq_socket (zmq_context, ZMQ_REQ);
    zmq_connect (zmq_requester, address);
}

void shorePut(const char *doid, const char *column, unsigned int row, unsigned int *shape, void *data){
    if(!isZmqInited) zmqInit();
    printf("%s, %d, %s, %d \n",doid,row,column, *(int*)data);
    char *request = generate_json_data("put", doid, column, row, shape);
    char buf[2048];

    zmq_send (zmq_requester, request, strlen(request), 0);
    zmq_recv (zmq_requester, buf, 2048, 0);

    printf("%s\n",request);
    printf("%s\n",buf);
}

