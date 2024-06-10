#include<iostream>
#include<cstring>
using namespace std;

/* Create a Student structure that stores data for one student. For the student information about the student's name(string of chars),
 * the index, the number of courses he/she listens to, a series of codes of the courses he/she listens to is stored.
 * Then, to create a structure Course in which data about course name(char array), course code(int) and number of students taking it,
 * To make a function: int get_most_popular_course(Course * course, int num_courses) which reverses the code of the most popular course.
 * Note: First the number of students is entered, then the number of courses. Then the courses and students are entered, while for each student
 * the codes of the courses are read.*/

struct Student{
    char name[50];
    int index;
    int numCourses;
    int courseCodes[40];
    void read(){
        cin.ignore();
        cin.getline(name,50);
        cin >> index >> numCourses;
        for(int i = 0; i < numCourses; i++){
            cin >> courseCodes[i];
        }
    }
    void print(){
        cout << name << " " << index << " " << numCourses << " ";
        for(int i = 0; i < numCourses; i++){
            cout << courseCodes[i] << " ";
        }
    }
};

struct Course{
    char name[50];
    int code;
    void read(){
        cin.ignore();
        cin.getline(name,50);
        cin >> code;
    }
    void print(){
        cout << name << " " << code;
    }
};

int get_most_popular_course(Student * students, int num_students, Course * course, int num_courses){
    int courseC[40] = {0};
    for(int i = 0; i < num_students; i++){
        for(int j = 0; j < students[i].numCourses; i++){
            int cnt = students[i].courseCodes[j];
            courseC[cnt]++;
        }
    }
    int max = 0;
    int mostPC = 0;
    for(int i = 0; i < num_courses; i++){
        if(courseC[i] > max){
            max = courseC[i];
            mostPC = i;
        }
    }
    return  mostPC;
}

int main(){
    Student student[10];
    Course course[10];
    int nS; cin >> nS;
    int nC; cin >> nC;
    for(int i = 0; i < nC; i++){
        course[i].read();
    }
    for(int i = 0; i < nS; i++){
        student[i].read();
    }
    int mostPopularCourse = get_most_popular_course(student,nS,course,nC);
    cout << course[mostPopularCourse].name << endl;
    return 0;
}