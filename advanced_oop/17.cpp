#include<iostream>
#include<cstring>

using namespace std;

class Student {
private:
    char *name;
    int age;
    char *major;

    void copy(const Student &s) {
        name = new char[strlen(s.name) + 1];
        strcpy(name, s.name);
        major = new char[strlen(s.major) + 1];
        strcpy(major, s.major);
        age = s.age;
    }

public:
    Student(){}
    Student(char *name, int age, char *major) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->major = new char[strlen(major) + 1];
        strcpy(this->major, major);
        this->age = age;
    }

    Student(const Student &other) {
        copy(other);
    }

    ~Student() {
        delete[] name;
        delete[] major;
    }

    char *getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    friend ostream& operator<<(ostream & out, Student & s){
        out << s.name << " " << s.major << " " << s.age << endl;
        return out;
    }

};


class Classroom {
private:
    Student *students;
    int n, capacity;

    void copy(const Classroom &c) {
        n = c.n;
        capacity = c.capacity;
        students = new Student[this->capacity];
        for (int i = 0; i < n; i++) {
            this->students[i] = c.students[i];
        }
    }

public:
    Classroom(){
        this->n = 0;
        this->capacity = 0;
    }
    Classroom(int n, int capacity) {
        students = new Student[0];
        this->n = n;
        this->capacity = capacity;

    }
    Classroom(const Classroom & other){
        copy(other);
    }
    ~Classroom() {
        delete[] students;
    }

    void add(const Student &newStudent) {
        if (n < capacity) {
            students[n++] = newStudent;
        } else {
            cout << "Full!" << endl;
        }
    }

    void remove(const char *name) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (strcmp(students[i].getName(), name) == 0) {
                idx = i;
                break;
            }
        }
        if (idx != -1) {
            for (int i = idx; i < n - 1; i++) {
                students[i] = students[i + 1];
            }
            n--;
        }
    }
    void printStudents(){
        for(int i =0 ; i < n; i++){
            cout << students[i];
        }
    }
    friend  double findMedianAge(const Classroom & c);
};
double findMedianAge(const Classroom & c);

int main() {
    int numClassrooms, numStudents;
    cin >> numClassrooms;
    Classroom classrooms[100];
    Student students[100];

    // Testing add method
    for (int i = 0; i < numClassrooms; i++) {
        cin >> numStudents;
        for (int j = 0; j < numStudents; j++) {
            char name[100], major[100];
            int age;
            cin >> name >> age >> major;
            Student student(name, age, major);
            classrooms[i].add(student);
            students[i*numStudents + j] = student;
        }
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }


    // Testing findMedianAge method
    int targetClassroom;
    cin >> targetClassroom;
    double medianAge = findMedianAge(classrooms[targetClassroom]);
    cout << "The median age in classroom " << targetClassroom << " is: " << medianAge << endl;
    cout<<"After removing the elements:"<<endl; // Added
    // Testing remove method
    cin >> numStudents;
    for (int j = 0; j < numStudents; j++) {
        char name[100];
        cin >> name;
        for (int i = 0; i < numClassrooms; i++) {
            classrooms[i].remove(name);
        }
    }
    for (int i = 0; i < numClassrooms; i++) {
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }

    return 0;
}
double findMedianAge(const Classroom & c) {
    if (c.n == 0) {
        return 0.0;
    }
    for (int i = 0; i < c.n - 1; i++) {
        for (int j = 0; j < c.n - i - 1; j++) {
            if (c.students[i].getAge() > c.students[j + 1].getAge()) {
                Student temp = c.students[j];
                c.students[j] = c.students[j + 1];
                c.students[j + 1] = temp;
            }
        }
    }
    if (c.n % 2 == 0) {
        return (c.students[c.n / 2 - 1].getAge() + c.students[c.n / 2].getAge()) / 2.0;
    } else {
        return c.students[c.n / 2].getAge();
    }
}