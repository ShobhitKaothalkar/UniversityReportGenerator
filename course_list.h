#ifndef COURSELIST_H
#define COURSELIST_H

#include <stdio.h>
#include "courses.h"

struct CourseList{
    Course* course;
    struct CourseList* next;
}typedef CourseList;


// Inserts Course into the CourseList of the student
CourseList* InsertCourse(CourseList* head, Course* course);

#endif
