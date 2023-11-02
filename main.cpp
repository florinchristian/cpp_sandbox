#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>

using namespace std;

class Printable {
public:
    virtual string toString() = 0;
};

// 2.9
template<class T>
T sum(T a, T b) {
    return a + b;
}

void test29() {
    cout << sum(1, 2) << "\n";
    cout << sum(3.14, 33.2) << "\n";
}

// 2.13
class Person {
private:
    string name;
    int age;
public:
    Person(string name, int age) {
        this->name = name;
        this->age = age;
    }

    string getName() const {
        return this->name;
    }

    int getAge() const {
        return this->age;
    }

    friend ostream &operator<<(ostream &os, const Person &person) {
        os << person.getName() << " of age " << person.getAge();
        return os;
    }
};


void test213() {
    vector<Person> people;

    people.emplace_back("John", 13);
    people.emplace_back("Alex", 22);
    people.emplace_back("Jessica", 18);

    sort(people.begin(), people.end(), [](const Person &a, const Person &b) -> bool {
        return a.getAge() > b.getAge();
    });

    for_each(people.begin(), people.end(), [](const Person &person) {
        cout << person << "\n";
    });
}

// 3.6
class Student : public Printable {
private:
    string name;
    double grade;

    explicit Student(int grade) {
        this->grade = grade;
    }

public:
    Student(string name) : Student(8) {
        this->name = name;
    }

    Student(string name, int grade) : Student(grade) {
        this->name = name;
    }

    const string getName() const {
        return name;
    }

    void setName(const string &name) {
        this->name = name;
    }

    double getGrade() const {
        return grade;
    }

    void setGrade(double grade) {
        this->grade = grade;
    }

    string toString() override {
        return "Student " + this->name;
    }
};

void test36() {
    Student a("Ion");
    Student b("Alex", 10);

    cout << a.getGrade() << "\n";
    cout << b.getGrade() << "\n";
}

class Car : public Printable {
private:
    string name;
public:
    Car(string name) {
        this->name = name;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        this->name = name;
    }

    string toString() override {
        return "Car " + this->name;
    }
};

// 3.12
class Logger {
private:
    static map<string, ofstream> handlers;

    string filePath;

    Logger(const string& filePath) {
        if (Logger::handlers.find(filePath) == Logger::handlers.end()) {
            Logger::handlers[filePath] = ofstream(filePath, std::ios_base::app);
        }

        this->filePath = filePath;
    }

public:
    static Logger getLogger(const string& filePath) {
        return Logger(filePath);
    }

    void write(const string& message, const string& endWith = "\n") {
        if (Logger::handlers[this->filePath]) {
            Logger::handlers[this->filePath] << message << endWith;
        }
    }

    void write(Printable& object, const string& endWith = "\n") {
        this->write(object.toString(), endWith);
    }

};

map<string, ofstream> Logger::handlers;

void test312() {
    Student student("Alex");
    Car car("Dacia");

    Logger::getLogger("output.txt").write("Message 123");

    Logger::getLogger("output.txt").write(car);
    Logger::getLogger("output.txt").write(student);
}

int main() {
    test312();
}
