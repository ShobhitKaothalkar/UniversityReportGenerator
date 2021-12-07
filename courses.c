#include"courses.h"
#include<stdio.h>
#include<string.h>

int top_courses = -1;
int courses_added = 0;

Course* InitializeCourses(int no_of_courses){
    Course* courses = (Course*)malloc(sizeof(Course)*no_of_courses);
    return courses;
}

void AddCourse(Course* courses, char* course_name, char* course_code, char* faculty_name){
    courses_added++;
    top_courses++;
    Course* new_course = (Course*)malloc(sizeof(Course));
    new_course -> course_id = courses_added;
    strcpy(new_course -> course_name, course_name);
    strcpy(new_course -> course_code, course_code);
    strcpy(new_course -> faculty_name, faculty_name);
    courses[top_courses] = *new_course;
} 

Course* CreateCourses(char* file_address){

    FILE *fp;
    char str[1024];
    Course* courses = NULL;

    fp = fopen(file_address, "r");

    if(fp == NULL) printf("Failed to open\n");
    else{
        int no_of_lines = 0;
        while(fgets(str, 200, fp) != NULL){
            no_of_lines++;
        }
        courses = InitializeCourses(no_of_lines - 1);

        rewind(fp);
        // while(fgets(str, 200, fp) != NULL){
        //     printf("%s", str);
        // }
        int row = 0;
        int column = 0;
        char course_name[200];
        char course_code[50];
        char faculty_name[100];
        while (fgets(str, 1024, fp)) {

            str[strcspn(str, "\n")] = 0;

            column = 0;
            row++;
            // To avoid printing of column
            // names in file can be changed
            // according to need
            if (row == 1)
                continue;
  

            // Splitting the data
            char* value = strtok(str, ",");
  
            while (value) {
                // Column 1
                if (column == 0) {
                    strcpy(course_name, value);
                }
  
                // Column 2
                if (column == 1) {
                    strcpy(course_code, value);
                }
  
                // Column 3
                if (column == 2) {
                    strcpy(faculty_name, value);
                }

                // printf("%s\n", value);
                value = strtok(NULL, ",");
                column++;
            }

            AddCourse(courses, course_name, course_code, faculty_name);
        }
        fclose(fp);
    }   
    return courses;
}

