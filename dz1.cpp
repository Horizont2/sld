#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Text {
protected:
    string task;
public:
    Text(const string& task) : task(task) {}
    virtual void display() const {
        cout << task << endl;
    }
    virtual ~Text() = default;
};

// Клас для важливих завдань
class GreaterTask : public Text {
public:
    GreaterTask(const string& task) : Text(task) {}
    void display() const override {
        cout << task << " !!! (Важливе завдання)" << endl;
    }
};

// Клас для термінових завдань
class DeadLineTask : public Text {
    string deadline;
public:
    DeadLineTask(const string& task, const string& deadline) : Text(task), deadline(deadline) {}
    void display() const override {
        cout << task << " (Термінове, до: " << deadline << ")" << endl;
    }
};

// Клас для щоденних завдань
class DailyTask : public Text {
    string time;
public:
    DailyTask(const string& task, const string& time) : Text(task), time(time) {}
    void display() const override {
        cout << task << " (Щоденне, час: " << time << ")" << endl;
    }
};

void displayTasks(const vector<Text*>& tasks) {
    for (const auto& task : tasks) {
        task->display();
    }
}

int main() {
    vector<Text*> tasks;

    tasks.push_back(new Text("Прочитати книгу"));
    tasks.push_back(new GreaterTask("Закінчити проект"));
    tasks.push_back(new DeadLineTask("Відправити звіт", "2024-10-06"));
    tasks.push_back(new DailyTask("Зробити зарядку", "08:00"));

    displayTasks(tasks);

    for (auto& task : tasks) {
        delete task;
    }
    tasks.clear();

    return 0;
}
