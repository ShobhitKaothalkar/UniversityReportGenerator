#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "course_list.h"

CourseList* InsertCourse(CourseList* head, Course* course){
    CourseList* new_node = (CourseList*)malloc(sizeof(CourseList));
    new_node -> course = course;
    new_node -> next = head;
    head = new_node;
    return head; 
}
