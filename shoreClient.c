#include <stdio.h>
#include "shoreClient.h"


void shoreCreateTable(char *doid){


}

void shorePut(const char *doid, unsigned int row, char *column, void *data){
    printf("%s, %d, %s",doid,row,column);
}


