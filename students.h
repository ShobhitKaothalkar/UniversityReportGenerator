#ifndef STUDENTS_H
#define STUDENTS_H

#include <stdio.h>
#include "classes.h"
#include "course_list.h"

struct Student{
    int roll_no;
    char name[100];
    Class* student_class; // store address of class 
    CourseList* student_courses; // linked list where each node will store address to a course
    struct Student* left;
    struct Student* right;
    int height;
}typedef Student;

int students_added;

// Adds student into the AVL tree of students and the students database text file
Student* addStudent(Student* students, char* name, Class* student_class, CourseList* student_courses, char* file_address);

// Searches for a student in the students tree
Student* searchStudent(Student* students, int roll_no);

// Creates students avl tree from the students database text file
Student* createStudents(char* file_path, Class* classes, Course* courses);

#endif
