# UniversityReportGenerator

URG (University Report Generator) is a software that can manage a large 
number of students, courses and classes in a university and generate useful 
reports from the data.
Features of URG:-
1) Manage Classes and Courses in a university
2) Manage Students in a university
3) Generate two text reports
a. report1 – lists all the classes and the number of students in them
b. report2 – lists all the students and their details
4) 7 digit roll number system 
5) Database system to store data for later use
6) Thoughtful use of data structures to make the program fast
7) Proper error handling 
8) User friendly UI

User can manage the classes and courses by modifying “classes.txt” and 
“courses.txt” respectively and the changes will appear in the program.

Roll no. -
0100005

The first three digits of the roll no. are assigned according to the class id 
associated with the class of the student.
The last four digits of the roll no. are assigned according to the no of students 
in the class of the student.

# Choice of Data Structures

For Classes and Courses:
Most of the functionality regarding classes and courses had to deal with 
accessing a specific class or course and assigning it to a student. Therefore we 
needed a data structure with fast accessing time. Therefore we decided to go 
with using array data structure which has accessing time complexity of O(1).

We know the number of classes and courses in the starting of the program as 
we read the classes and courses from their respective text files. So we initialize 
the arrays in the heap memory using malloc function for classes and courses 
with the number of classes and courses.

For CourseList:
We needed a data structure to store the courses selected by a specific student. 
We needed this data structure to be of variable length as the student can 
select any number of courses and have fast insertion time. 
So we decided to use Linked List which is a variable length data structure and 
has insertion time complexity of O(1) if are inserting a node in the beginning.

For Students:
For students, we needed to store the students in sorted manner according to
their roll numbers. Also we are giving the functionality to update student 
details that requires searching for a specific student. 
So we decided to use AVL Tree (Self balancing BST) for storing students. Which 
has insertion and searching time complexity of O(logn). Since it is a selfbalancing Binary Search Tree, the students will be stored in a sorted manner 
and we can do Inorder traversal to get students in order of their roll numbers.
Each student node will have a pointer to Class associated with it that will 
contain the address to his/her class. It will also have a pointer to a CourseList
associated with it, which will be a linked list in which each node will contain 
address to one of the courses selected by the student.
