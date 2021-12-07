#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "classes.h"

int top_classes = -1;
int classes_added = 0;

Class* InitializeClasses(int no_of_classes){
    Class* classes= (Class*)malloc(sizeof(Class)*no_of_classes);
    return classes;
}

void AddClass(Class* classes, char* class_name){
    top_classes++;
    classes_added++;
    Class* new_class= (Class*)malloc(sizeof(Class));
    new_class -> class_id = classes_added;
    strcpy(new_class -> class_name, class_name);
    new_class -> no_of_students = 0;
    classes[top_classes] = *new_class;
}

Class* CreateClasses(char* file_address){
    
    FILE *fp;
    char str[1024];
    Class* classes = NULL;

    fp = fopen(file_address, "r");

    if(fp == NULL) printf("Failed to open\n");
    else{
        // counting no of lines 
        int no_of_lines = 0;
        while(fgets(str, 1024, fp) != NULL){
            no_of_lines++;
        }

        // creating array of required size
        classes = InitializeClasses(no_of_lines - 1);

        rewind(fp);
        int row = 0;
        while (fgets(str, 1024, fp)) {

            // trimming newline character at the end
            str[strcspn(str, "\n")] = 0;
            row++;

            // skipping row 1
            if (row == 1)
                continue;
            
            // Adding class in array
            AddClass(classes, str);
        }
        fclose(fp);
    }   
    return classes;
}