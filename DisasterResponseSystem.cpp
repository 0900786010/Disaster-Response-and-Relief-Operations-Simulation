#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
using namespace std;

// Task structure
struct Task {
    string description;
    int urgency; // higher = more urgent
};

// Comparison for priority queue (higher urgency first)
struct CompareUrgency {
    bool operator()(Task const& t1, Task const& t2) {
        return t1.urgency < t2.urgency;
    }
};

// Disaster Simulation System
class DisasterResponseSystem {
private:
    priority_queue<Task, vector<Task>, CompareUrgency> zoneTasks;  // Task management
    stack<string> reliefTeams;                                     // Team management
    queue<string> supplies;                                        // Supply management
    stack<Task> emergencyTasks;                                    // Emergency priority
    vector<string> completedTasks;                                 // Completion tracking

public:
    // Add a new task
    void addTask(const string& desc, int urgency) {
        Task t{desc, urgency};
        zoneTasks.push(t);
        cout << "Task added: " << desc << " (Urgency: " << urgency << ")\n";
    }

    // Process highest priority task
    void processTask() {
        if (!zoneTasks.empty()) {
            Task t = zoneTasks.top();
            zoneTasks.pop();
            cout << "Processing task: " << t.description << endl;
            completedTasks.push_back(t.description);
        } else {
            cout << "No tasks available.\n";
        }
    }

    // Deploy relief team
    void addTeam(const string& teamName) {
        reliefTeams.push(teamName);
        cout << "Team added: " << teamName << endl;
    }

    void deployTeam() {
        if (!reliefTeams.empty()) {
            cout << "Deploying team: " << reliefTeams.top() << endl;
            reliefTeams.pop();
        } else {
            cout << "No teams available.\n";
        }
    }

    // Manage supplies
    void addSupply(const string& supply) {
        supplies.push(supply);
        cout << "Supply added: " << supply << endl;
    }

    void distributeSupply() {
        if (!supplies.empty()) {
            cout << "Distributed supply: " << supplies.front() << endl;
            supplies.pop();
        } else {
            cout << "No supplies available.\n";
        }
    }

    // Emergency handling
    void escalateEmergency() {
        if (!zoneTasks.empty()) {
            Task t = zoneTasks.top();
            zoneTasks.pop();
            emergencyTasks.push(t);
            cout << "Escalated to emergency: " << t.description << endl;
        } else {
            cout << "No tasks to escalate.\n";
        }
    }

    void handleEmergency() {
        if (!emergencyTasks.empty()) {
            Task t = emergencyTasks.top();
            emergencyTasks.pop();
            cout << "Handling emergency task: " << t.description << endl;
            completedTasks.push_back("Emergency - " + t.description);
        } else {
            cout << "No emergency tasks.\n";
        }
    }

    // Show completed tasks
    void showCompleted() {
        cout << "\nCompleted Tasks Log:\n";
        for (auto &task : completedTasks) {
            cout << "- " << task << endl;
        }
        if (completedTasks.empty()) cout << "No tasks completed yet.\n";
    }
};

// Main Menu
int main() {
    DisasterResponseSystem system;
    int choice;
    string input;
    int urgency;

    cout << "=== Disaster Response & Relief Operations Simulation ===\n";

    do {
        cout << "\n1. Add Task\n2. Process Task\n3. Add Team\n4. Deploy Team\n"
             << "5. Add Supply\n6. Distribute Supply\n7. Escalate Emergency\n8. Handle Emergency\n"
             << "9. Show Completed Tasks\n10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                getline(cin, input);
                cout << "Enter urgency (1-10): ";
                cin >> urgency;
                cin.ignore();
                system.addTask(input, urgency);
                break;

            case 2:
                system.processTask();
                break;

            case 3:
                cout << "Enter team name: ";
                getline(cin, input);
                system.addTeam(input);
                break;

            case 4:
                system.deployTeam();
                break;

            case 5:
                cout << "Enter supply item: ";
                getline(cin, input);
                system.addSupply(input);
                break;

            case 6:
                system.distributeSupply();
                break;

            case 7:
                system.escalateEmergency();
                break;

            case 8:
                system.handleEmergency();
                break;

            case 9:
                system.showCompleted();
                break;

            case 10:
                cout << "Exiting simulation...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 10);

    return 0;
}

