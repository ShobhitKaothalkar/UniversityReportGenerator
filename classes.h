#ifndef CLASSES_H
#define CLASSES_H

#include <stdio.h>

struct Class
{
    int class_id;
    char class_name[100];
    int no_of_students;
}typedef Class;

// top index of classes arrray
int top_classes;

// no of classes added
int classes_added;

// returns a pointer to an dynamic array of size no_of_classes
Class* InitializeClasses(int no_of_classes);

// adds class
void AddClass(Class* classes, char* class_name);

// returns classes from a text file
Class* CreateClasses(char* file_address);

#endif