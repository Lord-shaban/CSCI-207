#include <iostream>
#include <string>
using namespace std;

// 1 Student Management using Single Linked List
struct Student {
    int id;
    string name, email, phone, address, password;
    Student* next;

    Student(int id, string name, string email, string phone, string address, string password)
        : id(id), name(name), email(email), phone(phone), address(address), password(password), next(nullptr) {}
};

class StudentManager {
private:
    Student* head;

public:
    StudentManager() : head(nullptr) {}

    void addStudent(int id, string name, string email, string phone, string address, string password) {
        Student* newStudent = new Student(id, name, email, phone, address, password);
        newStudent->next = head;
        head = newStudent;
        cout << "Student added successfully!\n";
    }

    void removeStudent(int id) {
        Student* current = head;
        Student* prev = nullptr;

        while (current && current->id != id) {
            prev = current;
            current = current->next;
        }

        if (!current) {
            cout << "Student not found!\n";
            return;
        }

        if (!prev) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
        cout << "Student removed successfully!\n";
    }

    void displayStudents() {
        Student* current = head;
        while (current) {
            cout << "ID: " << current->id << ", Name: " << current->name << ", Email: " << current->email << "\n";
            current = current->next;
        }
    }

    Student* findStudent(int id) {
        Student* current = head;
        while (current) {
            if (current->id == id) return current;
            current = current->next;
        }
        return nullptr;
    }

    // Bubble Sort to sort students by ID
    void sortStudentsByID() {
        if (!head) return;

        bool swapped;
        do {
            swapped = false;
            Student* current = head;
            while (current && current->next) {
                if (current->id > current->next->id) {
                    // Swap student data
                    swap(current->id, current->next->id);
                    swap(current->name, current->next->name);
                    swap(current->email, current->next->email);
                    swap(current->phone, current->next->phone);
                    swap(current->address, current->next->address);
                    swap(current->password, current->next->password);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);

        cout << "Students sorted by ID.\n";
    }
};

// 2 Course Management using Binary Search Tree
struct Course {
    int id;
    string name;
    int credits;
    string instructor;
    Course* left;
    Course* right;

    Course(int id, string name, int credits, string instructor)
        : id(id), name(name), credits(credits), instructor(instructor), left(nullptr), right(nullptr) {}
};

class CourseManager {
private:
    Course* root;

    Course* insert(Course* node, int id, string name, int credits, string instructor) {
        if (!node) return new Course(id, name, credits, instructor);

        if (id < node->id) {
            node->left = insert(node->left, id, name, credits, instructor);
        } else {
            node->right = insert(node->right, id, name, credits, instructor);
        }

        return node;
    }

    Course* findMin(Course* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    Course* remove(Course* node, int id) {
        if (!node) return nullptr;

        if (id < node->id) {
            node->left = remove(node->left, id);
        } else if (id > node->id) {
            node->right = remove(node->right, id);
        } else {
            if (!node->left) {
                Course* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Course* temp = node->left;
                delete node;
                return temp;
            } else {
                Course* temp = findMin(node->right);
                node->id = temp->id;
                node->name = temp->name;
                node->credits = temp->credits;
                node->instructor = temp->instructor;
                node->right = remove(node->right, temp->id);
            }
        }

        return node;
    }

    void inorder(Course* node) {
        if (!node) return;
        inorder(node->left);
        cout << "ID: " << node->id << ", Name: " << node->name << "\n";
        inorder(node->right);
    }

public:
    CourseManager() : root(nullptr) {}

    void addCourse(int id, string name, int credits, string instructor) {
        root = insert(root, id, name, credits, instructor);
        cout << "Course added successfully!\n";
    }

    void removeCourse(int id) {
        root = remove(root, id);
        cout << "Course removed successfully!\n";
    }

    void displayCourses() {
        inorder(root);
    }

    // Binary Search for Courses by ID
    Course* binarySearchCourse(int id) {
        Course* current = root;
        while (current) {
            if (current->id == id) return current;
            if (id < current->id) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr;
    }
};

// 3 Enrollment Management using Double Linked List
struct Enrollment {
    int studentId;
    int courseId;
    Enrollment* next;
    Enrollment* prev;

    Enrollment(int studentId, int courseId)
        : studentId(studentId), courseId(courseId), next(nullptr), prev(nullptr) {}
};

class EnrollmentManager {
private:
    Enrollment* head;
    Enrollment* tail;

public:
    EnrollmentManager() : head(nullptr), tail(nullptr) {}

    void addEnrollment(int studentId, int courseId) {
        Enrollment* newEnrollment = new Enrollment(studentId, courseId);
        if (!head) {
            head = tail = newEnrollment;
        } else {
            tail->next = newEnrollment;
            newEnrollment->prev = tail;
            tail = newEnrollment;
        }
        cout << "Enrollment added successfully!\n";
    }

    void displayEnrollments(int studentId) {
        Enrollment* current = head;
        cout << "Enrollments for student " << studentId << ":\n";
        while (current) {
            if (current->studentId == studentId) {
                cout << "Course ID: " << current->courseId << "\n";
            }
            current = current->next;
        }
    }

    bool isEnrolled(int studentId, int courseId) {
        Enrollment* current = head;
        while (current) {
            if (current->studentId == studentId && current->courseId == courseId) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

// 4 Prerequisite Validation using Stack (Implemented Manually)
class Stack {
private:
    struct Node {
        int courseId;
        Node* next;
        Node(int courseId) : courseId(courseId), next(nullptr) {}
    };

    Node* top;

public:
    Stack() : top(nullptr) {}

    void push(int courseId) {
        Node* newNode = new Node(courseId);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (!top) {
            cout << "Stack is empty!\n";
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    int peek() {
        if (!top) {
            cout << "Stack is empty!\n";
            return -1;
        }
        return top->courseId;
    }
};

class PrerequisiteManager {
private:
    Stack prerequisites;

public:
    void addPrerequisite(int courseId) {
        prerequisites.push(courseId);
    }

    bool validatePrerequisites(EnrollmentManager& enrollments, int studentId) {
        Stack tempStack = prerequisites;
        while (!tempStack.isEmpty()) {
            int courseId = tempStack.peek();
            if (!enrollments.isEnrolled(studentId, courseId)) {
                return false;
            }
            tempStack.pop();
        }
        return true;
    }

    void displayPrerequisites() {
        Stack tempStack = prerequisites;
        cout << "Prerequisites: ";
        while (!tempStack.isEmpty()) {
            cout << tempStack.peek() << " ";
            tempStack.pop();
        }
        cout << "\n";
    }
};

// 5 Waitlist Management using Queue (Implemented Manually)
class Queue {
private:
    struct Node {
        int studentId;
        Node* next;
        Node(int studentId) : studentId(studentId), next(nullptr) {}
    };

    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    void enqueue(int studentId) {
        Node* newNode = new Node(studentId);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (!front) {
            cout << "Queue is empty!\n";
            return;
        }
        Node* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
    }

    int peek() {
        if (!front) {
            cout << "Queue is empty!\n";
            return -1;
        }
        return front->studentId;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

class WaitlistManager {
private:
    Queue waitlist;

public:
    void addToWaitlist(int studentId) {
        waitlist.enqueue(studentId);
        cout << "Student " << studentId << " added to waitlist.\n";
    }

    void enrollNextStudent() {
        if (waitlist.isEmpty()) {
            cout << "No students on the waitlist.\n";
            return;
        }
        int studentId = waitlist.peek();
        waitlist.dequeue();
        cout << "Student " << studentId << " has been enrolled.\n";
    }

    void displayWaitlist() {
        Queue tempQueue = waitlist;
        cout << "Waitlist: ";
        while (!tempQueue.isEmpty()) {
            cout << tempQueue.peek() << " ";
            tempQueue.dequeue();
        }
        cout << "\n";
    }
};

// 6 Hashing for Fast Course Access
class CourseHashTable {
private:
    static const int TABLE_SIZE = 10;
    struct HashNode {
        int id;
        string name;
        int credits;
        string instructor;
        HashNode* next;
        HashNode(int id, string name, int credits, string instructor)
            : id(id), name(name), credits(credits), instructor(instructor), next(nullptr) {}
    };

    HashNode* table[TABLE_SIZE];

    int hashFunction(int id) {
        return id % TABLE_SIZE;
    }

public:
    CourseHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    void insertCourse(int id, string name, int credits, string instructor) {
        int index = hashFunction(id);
        HashNode* newNode = new HashNode(id, name, credits, instructor);
        newNode->next = table[index];
        table[index] = newNode;
        cout << "Course added to hash table successfully!\n";
    }

    string getCourseName(int id) {
        int index = hashFunction(id);
        HashNode* current = table[index];
        while (current) {
            if (current->id == id) {
                return current->name;
            }
            current = current->next;
        }
        return "Course not found";
    }

    void displayHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Bucket " << i << ": ";
            HashNode* current = table[i];
            while (current) {
                cout << current->id << " ";
                current = current->next;
            }
            cout << "\n";
        }
    }
};

// Main Function
int main() {
    StudentManager studentManager;
    CourseManager courseManager;
    EnrollmentManager enrollmentManager;
    PrerequisiteManager prerequisiteManager;
    WaitlistManager waitlistManager;
    CourseHashTable courseHashTable;

    while (true) {
        cout << "\nUniversity Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Remove Student\n";
        cout << "3. Display Students\n";
        cout << "4. Add Course\n";
        cout << "5. Remove Course\n";
        cout << "6. Display Courses\n";
        cout << "7. Add Enrollment\n";
        cout << "8. View Enrollments\n";
        cout << "9. Validate Prerequisites\n";
        cout << "10. Add to Waitlist\n";
        cout << "11. Enroll Next Student\n";
        cout << "12. Display Waitlist\n";
        cout << "13. Add Course to Hash Table\n";
        cout << "14. Search Course in Hash Table\n";
        cout << "15. Display Hash Table\n";
        cout << "16. Sort Students by ID\n";
        cout << "17. Search Student by ID\n";
        cout << "18. Search Course by ID (Binary Search)\n";
        cout << "19. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name, email, phone, address, password;
                cout << "Enter student ID: ";
                cin >> id;
                cout << "Enter student name: ";
                cin >> name;
                cout << "Enter email: ";
                cin >> email;
                cout << "Enter phone: ";
                cin >> phone;
                cout << "Enter address: ";
                cin >> address;
                cout << "Enter password: ";
                cin >> password;
                studentManager.addStudent(id, name, email, phone, address, password);
                break;
            }
            case 2: {
                int id;
                cout << "Enter student ID to remove: ";
                cin >> id;
                studentManager.removeStudent(id);
                break;
            }
            case 3:
                studentManager.displayStudents();
                break;
            case 4: {
                int id, credits;
                string name, instructor;
                cout << "Enter course ID: ";
                cin >> id;
                cout << "Enter course name: ";
                cin >> name;
                cout << "Enter course credits: ";
                cin >> credits;
                cout << "Enter course instructor: ";
                cin >> instructor;
                courseManager.addCourse(id, name, credits, instructor);
                break;
            }
            case 5: {
                int id;
                cout << "Enter course ID to remove: ";
                cin >> id;
                courseManager.removeCourse(id);
                break;
            }
            case 6:
                courseManager.displayCourses();
                break;
            case 7: {
                int studentId, courseId;
                cout << "Enter student ID: ";
                cin >> studentId;
                cout << "Enter course ID: ";
                cin >> courseId;
                enrollmentManager.addEnrollment(studentId, courseId);
                break;
            }
            case 8: {
                int studentId;
                cout << "Enter student ID to view enrollments: ";
                cin >> studentId;
                enrollmentManager.displayEnrollments(studentId);
                break;
            }
            case 9: {
                int studentId;
                cout << "Enter student ID to validate prerequisites: ";
                cin >> studentId;
                if (prerequisiteManager.validatePrerequisites(enrollmentManager, studentId)) {
                    cout << "Prerequisites are satisfied.\n";
                } else {
                    cout << "Prerequisites are not satisfied.\n";
                }
                break;
            }
            case 10: {
                int studentId;
                cout << "Enter student ID to add to waitlist: ";
                cin >> studentId;
                waitlistManager.addToWaitlist(studentId);
                break;
            }
            case 11:
                waitlistManager.enrollNextStudent();
                break;
            case 12:
                waitlistManager.displayWaitlist();
                break;
            case 13: {
                int id, credits;
                string name, instructor;
                cout << "Enter course ID: ";
                cin >> id;
                cout << "Enter course name: ";
                cin >> name;
                cout << "Enter course credits: ";
                cin >> credits;
                cout << "Enter course instructor: ";
                cin >> instructor;
                courseHashTable.insertCourse(id, name, credits, instructor);
                break;
            }
            case 14: {
                int id;
                cout << "Enter course ID to search: ";
                cin >> id;
                string courseName = courseHashTable.getCourseName(id);
                if (courseName != "Course not found") {
                    cout << "Course found: " << courseName << "\n";
                } else {
                    cout << "Course not found.\n";
                }
                break;
            }
            case 15:
                courseHashTable.displayHashTable();
                break;
            case 16:
                studentManager.sortStudentsByID();
                studentManager.displayStudents();
                break;
            case 17: {
                int id;
                cout << "Enter student ID to search: ";
                cin >> id;
                Student* student = studentManager.findStudent(id);
                if (student) {
                    cout << "Student found: " << student->name << "\n";
                } else {
                    cout << "Student not found.\n";
                }
                break;
            }
            case 18: {
                int id;
                cout << "Enter course ID to search (Binary Search): ";
                cin >> id;
                Course* course = courseManager.binarySearchCourse(id);
                if (course) {
                    cout << "Course found: " << course->name << "\n";
                } else {
                    cout << "Course not found.\n";
                }
                break;
            }
            case 19:
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}