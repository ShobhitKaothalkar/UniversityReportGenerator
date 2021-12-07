#include <stdio.h>
#include <string.h>
#include "classes.h"
#include "course_list.h"
#include "students.h"
#define max(a, b) ((a > b)? a : b)

int students_added = 0;

int height(Student* N){
    if(N == NULL) return 0;
    return N -> height;
}

Student* getNewStudent(int roll_no, char* name, Class* student_class, CourseList* student_courses){
    Student* new_student = (Student*)malloc(sizeof(Student));
    new_student -> roll_no = roll_no;
    strcpy(new_student -> name, name);
    new_student -> student_class = student_class; 
    new_student -> student_courses = student_courses;
    new_student -> left = NULL;
    new_student -> right = NULL;
    new_student -> height = 1; // new new_student is initially added at leaf
    return new_student;
}

// A utility function to right rotate subtree rooted with y
Student* rightRotate(Student* y){
    Student* x = y -> left;
    Student* T2 = x -> right;
    
    x -> right = y;
    y -> left = T2;

    y -> height = max(height(y -> left), height(y -> right))+1;
    x -> height = max(height(x -> left), height(x -> right))+1;

    return x;
}

// A utility function to left rotate subtree rooted with x
Student* leftRotate(Student* x){
    Student* y = x -> right;
    Student* T2 = y -> left;

    y -> left = x;
    x -> right = T2;

    x -> height = max(height(x -> left), height(x -> right))+1;
    y -> height = max(height(y -> left), height(y -> right))+1;

    return y;
}

// Get Balance Factor of node N
int getBalance(Student* N){
    if(N == NULL) return 0;
    return height(N -> left) - height(N -> right);
}

Student* insert(Student* node, int roll_no, char* name, Class* student_class, CourseList* student_courses){
    if(node == NULL) return getNewStudent(roll_no, name, student_class, student_courses);

    if(roll_no < node -> roll_no) node -> left = insert(node -> left, roll_no, name, student_class, student_courses);
    else if(roll_no > node -> roll_no) node -> right = insert(node -> right, roll_no, name, student_class, student_courses);
    else return node;

    // Update height of this ancestor node
    node -> height = 1 + max(height(node -> left), height(node -> right));

    int balance = getBalance(node);

    // Left Left Case
    if(balance > 1 && roll_no < node -> left -> roll_no) return rightRotate(node);

    // Right Right Case
    if(balance < -1 && roll_no > node -> right -> roll_no) return leftRotate(node);

    // Left Right Case
    if(balance > 1 && roll_no > node -> left -> roll_no){
        node -> left = leftRotate(node -> left);
        return rightRotate(node);
    }

    // Right Left Case
    if(balance < -1 && roll_no < node -> right -> roll_no){
        node -> right = rightRotate(node -> right);
        return leftRotate(node);
    }

    return node;
}

// Create roll no according to class
int createRollNo(int class_id, int no_of_students){
    char roll_string[8];
    roll_string[7] = '\0';
    for(int i = 0; i < 7; ++i) roll_string[i] = '0';
    int j = 2;
    while(class_id > 0 && j >= 0){
        roll_string[j] = class_id%10 + '0';
        class_id /= 10;
        j--;
    }
    j = 7;
    while(no_of_students > 0 && j-- >= 4){
        roll_string[j] = no_of_students%10 + '0';
        no_of_students /= 10;
    }
    // coverting string to integer
    int roll_no = atoi(roll_string);
    return roll_no;
}

Student* addStudent(Student* students, char* name, Class* student_class, CourseList* student_courses, char* file_address){
    students_added++;
    FILE* fp;
    (student_class -> no_of_students)++;
    int roll_no = createRollNo(student_class -> class_id, student_class -> no_of_students);
    students = insert(students, roll_no, name, student_class, student_courses);
    fp = fopen(file_address, "a");
    fprintf(fp, "%07d\n", roll_no);
    fprintf(fp, "%s\n", name);
    fprintf(fp, "%d\n", student_class -> class_id);
    CourseList* temp = student_courses;
    int n = 0;
    while(temp){
        n++;
        temp = temp->next;
    }
    fprintf(fp, "%d\n", n);
    temp = student_courses;
    while(temp){
        fprintf(fp, "%d\n", temp -> course -> course_id);
        n++;
        temp = temp->next;
    }
    fclose(fp);
    return students;
}

void inOrder(Student* root){
    if(root){
        inOrder(root -> left);
        printf("%d ", root -> roll_no);
        inOrder(root -> right);
    }
}

Student* searchStudent(Student* students, int roll_no){
    if(students == NULL || students -> roll_no == roll_no) return students;
    else if(students -> roll_no > roll_no) return searchStudent(students -> left, roll_no);
    else if(students -> roll_no < roll_no) return searchStudent(students -> right, roll_no);
}

Student* createStudents(char* file_address, Class* classes, Course* courses){
    
    FILE* fp;
    char str[1024];
    char name[100];
    Student* students = NULL;

    fp = fopen(file_address, "r");
    if(fp == NULL) printf("Failed to open\n");
    else{
        while(fgets(str, 1024, fp)){
            int roll_no = atoi(str);
            fgets(str, 1024, fp);
            str[strcspn(str, "\n")] = 0;
            strcpy(name, str);
            int class_id = atoi(fgets(str, 1024, fp));
            classes[class_id - 1].no_of_students++;
            CourseList* new_list = NULL;
            int n = atoi(fgets(str, 1024, fp));
            for(int i = 0; i < n; i++){
                int temp = atoi(fgets(str, 1024, fp));
                new_list = InsertCourse(new_list, courses + temp - 1);
            }
            students_added++;
            students = insert(students, roll_no, name, classes + class_id - 1, new_list);
        }
    }
    fclose(fp);
    return students;
}