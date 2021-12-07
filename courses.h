#ifndef COURSES_H
#define COURSES_H

#include<stdio.h>
#include<stdlib.h>

struct Course {
    int course_id;
    char course_name[200];
    char course_code[50];
    char faculty_name[100];
    int taken;
} typedef Course;

// top index of courses array
int top_courses;

// no of courses added
int courses_added;

// returns a pointer to an dynamic array of size no_of_courses
Course* InitializeCourses(int no_of_courses);

// adds class
void AddCourse(Course* courses, char* course_name, char* course_code, char* faculty_name);

// returns courses from a text file
Course* CreateCourses(char* file_address);

#endif

