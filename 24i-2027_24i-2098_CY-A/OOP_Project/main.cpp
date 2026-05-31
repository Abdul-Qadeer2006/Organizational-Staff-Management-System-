#include"osim.h"

bool hasAssignClearance(const string& role) {
    return role == "manager" || role == "director" || role == "executive";
}

int main()
{
    int choice;

    do
    {
        cout << "\n=====================================\n";
        cout << "|               OSIM                  |\n";
        cout << "=====================================\n";
        cout << "| 1. Login                          |\n";
        cout << "| 2. Register                       |\n";
        cout << "| 3. Exit                           |\n";
        cout << "=====================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            Login login;
            if (!login.performLogin())
            {
                cout << "\n[!] Login failed. Returning to main menu...\n";
                continue;
            }

            string username = login.getUsername();
            string password = login.getPassword();
            string role = login.getRole();

            MessageHandler* emp = nullptr;
            Executive* exec = nullptr;
            Director* dir = nullptr;

            if (role == "junior") emp = new Junior(username, password);
            else if (role == "employee") emp = new Employee(username, password);
            else if (role == "manager") emp = new Manager(username, password);
            else if (role == "director")
            {
                dir = new Director(username, password);
                emp = dir;
            }
            else if (role == "executive")
            {
                exec = new Executive(username, password);
                emp = exec;
            }

            if (emp)
            {
                AuditLogger logger(username, password, role);
                logger.logAction("Logged in");

                int action;
                do
                {
                    cout << "\n+----------------------------+\n";
                    cout << "|         USER MENU         |\n";
                    cout << "+----------------------------+\n";
                    cout << "| 1. Perform Task           |\n";
                    cout << "| 2. Send Message           |\n";
                    cout << "| 3. Display Role           |\n";

                    if (role == "executive")
                    {
                        cout << "| 4. Give Performance Review|\n";
                        cout << "| 5. Respond to Review      |\n";
                        cout << "| 6. Manage Users           |\n";
                        cout << "| 7. View Notifications     |\n";
                        cout << "| 8. Send Notification      |\n";
                        cout << "| 9. Logout                 |\n";
                    }

                    else if (role == "director")
                    {
                        cout << "| 4. Give Performance Review|\n";
                        cout << "| 5. Respond to Review      |\n";
                        cout << "| 6. View Notifications     |\n";
                        cout << "| 7. Logout                 |\n";
                    }

                    else
                    {
                        cout << "| 4. See Messages           |\n";
                        cout << "| 5. View Notifications     |\n";
                        cout << "| 6. Logout                 |\n";
                    }

                    cout << "+----------------------------+\n";
                    cout << "Enter choice: ";
                    cin >> action;

                    if (role == "executive")
                    {
                        switch (action)
                        {
                        case 1: {
                            cout << "\n+------------------------------+\n";
                            cout << "|        Task Creation         |\n";
                            cout << "+------------------------------+\n";
                            string description;
                            int priority;
                            int ttlSeconds;

                            cout << "Enter task description: ";
                            cin.ignore();
                            getline(cin, description);

                            cout << "Enter task priority (1-5): ";
                            cin >> priority;

                            cout << "Enter TTL (seconds): ";
                            cin >> ttlSeconds;

                            Task task(username, description, priority, ttlSeconds);

                            int taskAction;
                            do
                            {
                                cout << "\n========== TASK MENU ==========\n";
                                cout << "1. Assign Task\n2. Mark In Progress\n3. Complete Task\n";
                                cout << "4. Check and Expire Task\n5. Display Task\n6. Back\n";
                                cout << "===============================\n";
                                cout << "Enter your choice: ";
                                cin >> taskAction;

                                switch (taskAction)
                                {
                                case 1: {
                                    if (!hasAssignClearance(role))
                                    {
                                        cout << "[!] No clearance to assign tasks.\n";
                                        break;
                                    }

                                    string assignee;
                                    cout << "Enter assignee name: ";
                                    cin >> assignee;
                                    task.assignTask(assignee);
                                    cout << "Task assigned to " << assignee << ".\n";
                                    break;
                                }

                                case 2:
                                    task.markInProgress(30);
                                    cout << "Task marked as in progress.\n";
                                    break;

                                case 3:
                                    task.completeTask();
                                    cout << "Task completed.\n";
                                    break;

                                case 4:
                                    task.checkAndExpire();
                                    cout << "Checked task for expiration.\n";
                                    break;

                                case 5:
                                    task.displayTask();
                                    break;

                                case 6:
                                    cout << "Returning to user menu...\n";
                                    break;

                                default:
                                    cout << "[!] Invalid task option!\n";
                                }
                            } while (taskAction != 6);
                            break;
                        }
                        case 2:
                            emp->sendMessage();
                            break;

                        case 3:
                            emp->displayRole();
                            break;

                        case 4:
                            exec->reviewPerformance();
                            break;

                        case 5:
                            exec->reviewPerformance();
                            break;

                        case 6:
                            exec->manageUser();
                            break;

                        case 7:
                            GlobalNotifier::viewGlobalNotifications();
                            break;

                        case 8:
                            GlobalNotifier::broadcastNotification(username, role);
                            break;

                        case 9:
                            logger.logAction("Logged out");
                            cout << "[*] Logging out...\n";
                            break;

                        default: cout << "[!] Invalid option!" << endl;
                        }
                    }
                    else if (role == "director")
                    {
                        switch (action)
                        {
                        case 1: {
                            Task task(username, "Sample task description", 1, 300);
                            int taskAction;
                            do {
                                cout << "\n========== TASK MENU ==========\n";
                                cout << "1. Assign Task\n2. Mark In Progress\n3. Complete Task\n";
                                cout << "4. Check and Expire Task\n5. Display Task\n6. Back\n";
                                cout << "===============================\n";
                                cout << "Enter your choice: ";
                                cin >> taskAction;

                                switch (taskAction)
                                {
                                case 1: {
                                    string assignee;
                                    cout << "Enter assignee name: ";
                                    cin >> assignee;
                                    task.assignTask(assignee);
                                    cout << "Task assigned.\n";
                                    break;
                                }
                                case 2:
                                    task.markInProgress(30);
                                    cout << "Task marked as in progress.\n";
                                    break;

                                case 3:
                                    task.completeTask();
                                    cout << "Task completed.\n";
                                    break;

                                case 4:
                                    task.checkAndExpire();
                                    cout << "Checked task for expiration.\n";
                                    break;

                                case 5:
                                    task.displayTask();
                                    break;

                                case 6:
                                    cout << "Returning to user menu...\n";
                                    break;

                                default:
                                    cout << "[!] Invalid task option!\n";
                                }

                            } while (taskAction != 6);
                            break;
                        }
                        case 2:
                            emp->sendMessage();
                            break;

                        case 3:
                            emp->displayRole();
                            break;

                        case 4:
                            dir->reviewPerformance();
                            break;

                        case 5:
                            dir->reviewPerformance();
                            break;

                        case 6:
                            GlobalNotifier::viewGlobalNotifications();
                            break;

                        case 7:
                            logger.logAction("Logged out");
                            cout << "[*] Logging out...\n";
                            break;
                        default: cout << "[!] Invalid option!" << endl;
                        }
                    }
                    else if (role == "junior" || role == "employee" || role == "manager")
                    {
                        switch (action)
                        {
                        case 1: {
                            Task task(username, "Sample task description", 1, 300);
                            int taskAction;
                            do
                            {
                                cout << "\n========== TASK MENU ==========\n";
                                cout << "1. Mark In Progress\n2. Complete Task\n3. Check and Expire\n";
                                cout << "4. Display Task\n5. Back to Menu\n";
                                cout << "===============================\n";
                                cout << "Enter your choice: ";
                                cin >> taskAction;

                                switch (taskAction)
                                {
                                case 1:
                                    task.markInProgress(30);
                                    cout << "Task marked as in progress.\n";
                                    break;

                                case 2:
                                    task.completeTask();
                                    cout << "Task completed.\n";
                                    break;

                                case 3:
                                    task.checkAndExpire();
                                    cout << "Checked task for expiration.\n";
                                    break;

                                case 4:
                                    task.displayTask();
                                    break;

                                case 5:
                                    cout << "Returning to user menu...\n";
                                    break;

                                default:
                                    cout << "[!] Invalid task option!\n";
                                }
                            } while (taskAction != 5);
                            break;

                        }
                        case 2:
                            emp->sendMessage();
                            break;

                        case 3:
                            emp->displayRole();
                            break;

                        case 4:
                            emp->seeMessages();
                            break;

                        case 5:
                            GlobalNotifier::viewGlobalNotifications();
                            break;

                        case 6:
                            logger.logAction("Logged out");
                            cout << "[*] Logging out...\n";
                            break;
                        default: cout << "[!] Invalid option!" << endl;
                        }
                    }

                } while ((role == "executive" && action != 9) || (role == "director" && action != 7) || (role != "executive" && role != "director" && action != 6));
                delete emp;
            }
            else
            {
                cout << "[!] Invalid role specified!" << endl;
            }
        }
        else if (choice == 2) {

            cout << "\n+-----------------------------+\n";
            cout << "|        REGISTRATION         |\n";
            cout << "+-----------------------------+\n";
            string role, username, password;
            cout << "Enter role (junior, employee, manager, director, executive): ";
            cin >> role;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            Register reg(username, password, role);
            reg.registerUser();
        }
        else if (choice == 3)
        {
            cout << "\n[*] Exiting the program. Goodbye!\n";
        }
        else
        {
            cout << "[!] Invalid choice! Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}