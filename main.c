#include "courses.h"
#include "course_list.h"
#include "classes.h"
#include "students.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h> // for modifying text color
#define TABLE_COLOR 3
#define SUCCESS_COLOR 10
#define ERROR_COLOR 4
#define WAITING_COLOR 14
#define DEFAULT_COLOR 7

CourseList *CoursesMenu(Student *students, Course *courses)
{
    int no_of_courses, temp;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Creating a course list for this student
    CourseList *new_course_list = NULL;

    // Getting the courses of the student
    SetConsoleTextAttribute(hConsole, WAITING_COLOR);
    printf("\n                                Select Courses: \n\n");
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
    SetConsoleTextAttribute(hConsole, TABLE_COLOR);
    printf("                             _______________________________________________________________________________________________________\n");
    printf("                            |    Id     |    Course Name                        |     Course Code       |      Faculty Name         |\n");
    for (int i = 0; i < courses_added; ++i)
    {
        printf("                            |-----------|---------------------------------------|-----------------------|---------------------------|\n");
        courses[i].taken = 0;
        printf("                            |    %-2d\t|\t%-30s\t|\t%-10s\t|\t%-20s|\n", courses[i].course_id, courses[i].course_name, courses[i].course_code, courses[i].faculty_name);
    }
    printf("                            |___________|_______________________________________|_______________________|___________________________|\n");
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
    printf("\n                            Enter the number of courses you wish to opt: ");
    scanf("%d", &no_of_courses);
    while (no_of_courses <= 0 || no_of_courses > courses_added)
    {
        SetConsoleTextAttribute(hConsole, ERROR_COLOR);
        printf("                            Please enter a valid course Id from menu\n");
        SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
        printf("\n                            Enter the number of courses you wish to opt: ");
        scanf("%d", &no_of_courses);
    }
    // Inserting courses in the course list
    for (int i = 0; i < no_of_courses; ++i)
    {
        printf("\n                            Enter course Id %d: ", i + 1);
        scanf("%d", &temp);
        while (temp <= 0 || temp > courses_added)
        {
            SetConsoleTextAttribute(hConsole, ERROR_COLOR);
            printf("\n                            Please enter a valid Id!!!\n");
            SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
            printf("\n                            Enter course Id %d: ", i + 1);
            scanf("%d", &temp);
        }
        if (courses[temp - 1].taken != 1)
        {
            courses[temp - 1].taken = 1;
        }
        else
        {
            SetConsoleTextAttribute(hConsole, ERROR_COLOR);
            printf("\n                            You have already taken this course!!!\n");
            SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
            --i;
            continue;
        }
        new_course_list = InsertCourse(new_course_list, courses + temp - 1);
    }

    return new_course_list;
}

Student *AddStudentMenu(Student *students, Class *classes, Course *courses, char *file_address)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int student_class, no_of_courses, temp;
    char name[100];

    // Getting the name of the student
    SetConsoleTextAttribute(hConsole, WAITING_COLOR);
    printf("\n                                Enter your name: ");
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
    scanf(" %[^\n]", name);

    // Getting the class of the student
    SetConsoleTextAttribute(hConsole, WAITING_COLOR);
    printf("\n\n                                Select a class: \n\n");
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
    SetConsoleTextAttribute(hConsole, TABLE_COLOR);
    printf("                                 _______________________________________________\n");
    printf("                                | Id    | Class name                            |\n");
    for (int i = 0; i < classes_added; ++i)
    {
        printf("                                |-------|---------------------------------------|\n");
        printf("                                | %-2d\t| %-30s        |\n", classes[i].class_id, classes[i].class_name);
    }
    printf("                                |_______|_______________________________________|\n");
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
    printf("\n                                Enter the option number: ");
    scanf("%d", &student_class);
    while (student_class <= 0 || student_class > classes_added)
    {
        SetConsoleTextAttribute(hConsole, ERROR_COLOR);
        printf("\n                                Please enter a valid Id!!!\n");
        SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
        printf("\n                                Enter the option number: ");
        scanf("%d", &student_class);
    }

    CourseList *new_course_list = CoursesMenu(students, courses);

    students = addStudent(students, name, classes + student_class - 1, new_course_list, file_address);

    return students;
}

void InOrder(Student *students, FILE *fp)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (students)
    {
        InOrder(students->left, fp);

        fprintf(fp, "|%07d |	%-20s|  %-30s       		|  ", students->roll_no, students->name, students->student_class->class_name);
        CourseList *temp = students->student_courses;
        int i = 1;
        while (temp)
        {
            if (i == 1)
            {
                fprintf(fp, "%-30s     |           %-10s     |\n", temp->course->course_name, temp->course->course_code);
                fprintf(fp, "|        |                      |                                               |-------------------------------------|--------------------------|\n");
                i++;
            }
            else if (temp->next != NULL)
            {
                fprintf(fp, "| 		 |					    |												|  %-30s     |           %-10s     |\n", temp->course->course_name, temp->course->course_code);
                fprintf(fp, "|        |                      |                                               |-------------------------------------|--------------------------|\n");
            }
            else
            {
                fprintf(fp, "| 		 |					    |												|  %-30s     |           %-10s     |\n", temp->course->course_name, temp->course->course_code);
            }
            temp = temp->next;
        }
        fprintf(fp, "|————————|——————————————————————|———————————————————————————————————————————————|—————————————————————————————————————|——————————————————————————|");
        fprintf(fp, "\n");
        InOrder(students->right, fp);
    }
}

// Generating report two
void GenerateReportTwo(Student *students)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *fp;
    fp = fopen("report2.txt", "w");
    fprintf(fp, "\nThe total number of students in the university: %d\n", students_added);
    fprintf(fp, "\nThe total number of courses in the university: %d\n\n", courses_added);
    fprintf(fp, "Student Details:\n\n");
    fprintf(fp, "|‾‾‾‾‾‾‾‾|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|\n");
    fprintf(fp, "|  Id	 |  Name			    |  Class Name									|  Course Name		                  |   		Course Code      |\n");
    fprintf(fp, "|________|______________________|_______________________________________________|_____________________________________|__________________________|\n");
    InOrder(students, fp);
    fprintf(fp, "|                                               *******************THE END*******************                                                    |\n");
    fprintf(fp, "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾");
    fclose(fp);
}

// Generating report one
void GenerateReportOne(Class *classes)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *fp;
    fp = fopen("report1.txt", "w");
    fprintf(fp, "Class Details:\n\n");
    fprintf(fp, "_____________________________________________________________________\n");
    fprintf(fp, "| Id  | Class Name                               |  No. Of Students |\n");
    fprintf(fp, "|—————|——————————————————————————————————————————|——————————————————|\n");
    for (int i = 0; i < classes_added; ++i)
    {
        fprintf(fp, "| %-3d | %-40s |  %7d         |\n", classes[i].class_id, classes[i].class_name, classes[i].no_of_students);
        fprintf(fp, "|—————|——————————————————————————————————————————|——————————————————|\n");
    }
    fprintf(fp, "|                    **********THE END**********                    |\n");
    fprintf(fp, "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾");
    fclose(fp);
}

void InOrderDatabase(Student *students, FILE *fp)
{
    if (students)
    {
        InOrderDatabase(students->left, fp);
        fprintf(fp, "%07d\n", students->roll_no);
        fprintf(fp, "%s\n", students->name);
        fprintf(fp, "%d\n", students->student_class->class_id);
        CourseList *temp = students->student_courses;
        int n = 0;
        while (temp)
        {
            n++;
            temp = temp->next;
        }
        fprintf(fp, "%d\n", n);
        temp = students->student_courses;
        while (temp)
        {
            fprintf(fp, "%d\n", temp->course->course_id);
            n++;
            temp = temp->next;
        }
        InOrderDatabase(students->right, fp);
    }
}

void UpdateStudentMenu(Student *students, Course *courses)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int roll_no;
    SetConsoleTextAttribute(hConsole, WAITING_COLOR);
    printf("\n\n                            Enter the Roll no. : ");
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);

    scanf("%7d", &roll_no);
    CourseList *temp;
    Student *student = searchStudent(students, roll_no);
    if (student != NULL)
    {
        SetConsoleTextAttribute(hConsole, 10);
        printf("Student Found!!!!\n\n");
        SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
        printf(" ________________________________________________________________________________________________________________________________________________________\n");
        printf("|  Id	 |  Name		    |  Class Name		     			|  Course Name	                      |   	Course Code      |\n");
        printf("|________|__________________________|___________________________________________________|_____________________________________|__________________________|\n");
        printf("|%07d |	%-20s|  %-30s       		|  ", student->roll_no, student->name, student->student_class->class_name);
        CourseList *temp = student->student_courses;
        int i = 1;
        while (temp)
        {
            if (i == 1)
            {
                printf("%-30s     |           %-10s     |\n", temp->course->course_name, temp->course->course_code);
                printf("|        |                          |                                                   |-------------------------------------|--------------------------|\n");
                i++;
            }
            else if (temp->next != NULL)
            {
                printf("| 	 |		            |							|  %-30s     |           %-10s     |\n", temp->course->course_name, temp->course->course_code);
                printf("|        |                          |                                                   |-------------------------------------|--------------------------|\n");
            }
            else
            {
                printf("| 	 |		            |							|  %-30s     |           %-10s     |\n", temp->course->course_name, temp->course->course_code);
            }
            temp = temp->next;
        }
        printf("|________|__________________________|___________________________________________________|_____________________________________|__________________________|");
        printf("\n");

        int flag = 1, option;
        char new_name[100];
        printf("\n                            What do you want to update?\n");
        while (flag)
        {
            SetConsoleTextAttribute(hConsole, TABLE_COLOR);
            printf("\n                                         ::::::MENU::::::\n\n");
            printf("                                 ________________________________________________________\n");
            printf("                                | MENU   | DESCRIPTION                                   |\n");
            printf("                                |________|_______________________________________________|\n");
            printf("                                |   1.   | Update Name of the student                    |\n");
            printf("                                |--------|-----------------------------------------------|\n");
            printf("                                |   2.   | Update Courses selected by the student        |\n");
            printf("                                |--------|-----------------------------------------------|\n");
            printf("                                |   3.   | Exit                                          |\n");
            printf("                                |________|_______________________________________________|\n");
            SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
            printf("\n                                Enter Your Menu Choice: ");
            scanf("%d", &option);
            switch (option)
            {
            case 1:
                printf("\n\n                            Current Name: %s\n", student->name);
                printf("                            Enter the new Name: ");
                scanf(" %[^\n]", new_name);
                strcpy(student->name, new_name);
                SetConsoleTextAttribute(hConsole, 10);
                printf("                            Name of the student updated successfully!!!\n");
                SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
                break;
            case 2:
                // deleting the old courses list
                temp = student->student_courses;
                student->student_courses = NULL;
                while (temp != NULL)
                {
                    CourseList *next_node = temp->next;
                    free(temp);
                    temp = next_node;
                }
                SetConsoleTextAttribute(hConsole, WAITING_COLOR);
                printf("                            Select new courses:\n\n");
                SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
                temp = CoursesMenu(students, courses);
                student->student_courses = temp;
                SetConsoleTextAttribute(hConsole, 10);
                printf("\n                            Courses have been updated\n");
                SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
                break;
            case 3:
                flag = 0;
                break;
            default:
                SetConsoleTextAttribute(hConsole, ERROR_COLOR);
                printf("Enter a valid choice");
                SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
                break;
            }
        }
        FILE *fp;
        fp = fopen("students.txt", "w");
        InOrderDatabase(students, fp);
        fclose(fp);
    }
    else
    {
        SetConsoleTextAttribute(hConsole, ERROR_COLOR);
        printf("                            Student not found!!!\n");
        SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
    }
}

int main()
{
    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Startup animation

    int x;
    double y;
    char alphabet1[] = "\n\n This is University Report Generator";
    char alphabet2[] = "\n\n \t\t\t\t\t\t URG, By";
    char alphabet3[] = "\n\n \t\t\t\t\t\t\t\t ~ Shivam(2006135), Shobhit Kaothalkar(2006139), Sandhya Kumari(2006126), Ekta Aggarwal(2006193), Anand Raj(2006192)\n\n\n";
    printf("\n\n");
    for (x = 0; alphabet1[x] != '\0'; x++)
    {
        printf("%c", alphabet1[x]);
        for (y = 0; y <= 7777777; y++)
        {
        }
    }
    printf("\n\n");
    for (x = 0; alphabet2[x] != '\0'; x++)
    {
        printf("%c", alphabet2[x]);
        for (y = 0; y <= 7777777; y++)
        {
        }
    }
    printf("\n\n");
    for (x = 0; alphabet3[x] != '\0'; x++)
    {
        printf("%c", alphabet3[x]);
        for (y = 0; y <= 7777777; y++)
        {
        }
    }
    FILE *logo = fopen("logo.txt", "r");
    char buffer[1024];
    while (fgets(buffer, 1024, logo))
    {
        printf("%s", buffer);
    }
    fclose(logo);
    printf("\n\n\nPress Enter to continue!\n");
    getch();

    system("cls");

    // Generating courses data structure from text file
    Course *courses = CreateCourses("courses.txt");

    // Generating classes data structure from text file
    Class *classes = CreateClasses("classes.txt");

    // Root node for students
    Student *students = createStudents("students.txt", classes, courses);

    // Menu
    int flag = 1, option;
    while (flag)
    {
        SetConsoleTextAttribute(hConsole, TABLE_COLOR);

        printf("\n                                         ::::::MENU::::::\n\n");
        printf("                                 __________________________________\n");
        printf("                                | MENU   | DESCRIPTION             |\n");
        printf("                                |________|_________________________|\n");
        printf("                                |   1.   | Add a new student       |\n");
        printf("                                |--------|-------------------------|\n");
        printf("                                |   2.   | Generate reports        |\n");
        printf("                                |--------|-------------------------|\n");
        printf("                                |   3.   | Update student details  |\n");
        printf("                                |--------|-------------------------|\n");
        printf("                                |   4.   | Exit                    |\n");
        printf("                                |________|_________________________|\n");
        SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);

        SetConsoleTextAttribute(hConsole, WAITING_COLOR);
        printf("\n                                Choose your action:  ");
        SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            students = AddStudentMenu(students, classes, courses, "students.txt");
            SetConsoleTextAttribute(hConsole, 10);
            printf("\n                            Student added succesfully!!!\n");
            SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
            break;
        case 2:
            GenerateReportOne(classes);
            GenerateReportTwo(students);
            SetConsoleTextAttribute(hConsole, 10);
            printf("\n                            Reports generated!!!\n\n");
            printf("                            Report One is generated in text file report1.txt\n\n");
            printf("                            Report Two is generated in text file report2.txt\n\n");
            SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
            break;
        case 3:
            UpdateStudentMenu(students, courses);
            break;
        case 4:
            flag = 0;
            break;
        default:
            SetConsoleTextAttribute(hConsole, ERROR_COLOR);
            printf("                                Please pick a valid option.\n");
            SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
            break;
        }
    }
    SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);

    return 0;
}