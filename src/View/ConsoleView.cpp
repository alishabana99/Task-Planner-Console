#include"ConsoleView.h"


ConsoleView::ConsoleView() {
    //initializing the presenter
    if (this->presenter.Init()) {
        this->current_frame = USER_MAIN_FRAME;
    }
    else {
        this->current_frame = MAIN_FRAME;
    }
}

void ConsoleView::Run() {


    while (1) {
        switch (this->current_frame) {
            
        case MAIN_FRAME:
            /*------------------------------ Main Frame --------------------------------------*/
            
            this->DisplayMainFrame();
        
            /*------------------------------ Main Frame --------------------------------------*/
            break;
        case LOGIN_FRAME:
            /*------------------------------ Login Frame --------------------------------------*/

            this->DisplayLoginFrame();
            
            /*------------------------------ Login Frame --------------------------------------*/
            break;
            
        case REGISTER_FRAME:
            /*------------------------------ Register Frame --------------------------------------*/
           
            this->DisplayRegisterFrame();

            /*------------------------------ Register Frame --------------------------------------*/
            break;

        case USER_MAIN_FRAME:
            /*------------------------------ User Main Frame --------------------------------------*/

            /*Display logged-in user's matrix and the available prompts that user can address*/
            /*Update {current_frame} value to render the proper frame (next-step frame OR error frame)*/
            this->DisplayUserMainFrame();

            /*------------------------------ User Main Frame --------------------------------------*/
            break;

        case ADD_TASK_FRAME:
            /*------------------------------ Add Task Frame --------------------------------------*/

            /*Handle user's inputs for adding a new task*/
            /*Update {current_frame} value to render the proper frame (next-step frame OR error frame)*/

            this->DisplayAddTaskFrame();

            /*------------------------------ Add Task Frame --------------------------------------*/
            break;
        
        case DELETE_TASK_FRAME:
            /*------------------------------ Delete Task Frame --------------------------------------*/

            this->DisplayDeleteTaskFrame();

            /*------------------------------ Delete Task Frame --------------------------------------*/
            break;
        case MARK_DONE_TASK_FRAME:
            /*------------------------------ Mark Done Frame --------------------------------------*/
            /*Handle user's inputs for deleting a task*/
            /*Update {current_frame} value to render the proper frame (next-step frame OR error frame)*/
            this->DisplayMarkDoneTaskFrame();
            
            /*------------------------------ Mark Done Frame --------------------------------------*/
            break;

        case DELETE_ALL_DONE_TASKS_FRAME:
            /*------------------------------ Delete All Done Frame --------------------------------------*/
            /*Handle user's inputs for deleting all done tasks*/
            /*Update {current_frame} value to render the proper frame (next-step frame OR error frame)*/
            this->DisplayDeleteAllDoneTasksFrame();
           
            /*------------------------------ Delete All Done Frame --------------------------------------*/

            break;

        case DELETE_ALL_TASKS_FRAME:
            /*------------------------------ Delete All Tasks Frame --------------------------------------*/
            /*Handle user's inputs for deleting all tasks*/
            /*Update {current_frame} value to render the proper frame (next-step frame OR error frame)*/
            this->DisplayDeleteAllTasksFrame();
           
            /*------------------------------ Delete All Done Frame --------------------------------------*/

            break;
        case SAVE_FRAME:
            /*------------------------------ Logout Frame --------------------------------------*/
            /*Handle user's inputs for logging out*/
            /*Update {current_frame} value to render the proper frame (next-step frame OR error frame)*/
            this->DisplaySaveFrame();

            /*------------------------------ Logout Frame --------------------------------------*/
            break;

        case LOGOUT_FRAME:
            /*------------------------------ Logout Frame --------------------------------------*/
            /*Handle user's inputs for logging out*/
            /*Update {current_frame} value to render the proper frame (next-step frame OR error frame)*/
            this->DisplayLogoutFrame();

            /*------------------------------ Logout Frame --------------------------------------*/
            break;

        default:
            std::cout << "\n\n\t\tBamoooooooooooot!!!!!!!!\n\n";
            break;
        }

    }
}

/**---------------------Frames Handlers-------------------------------**/



void ConsoleView::DisplayMainFrame() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Error_t error_state ;
    char user_input;


    do {
        this->DisplayMadeWithLove();
        /*Handle whether the user wants to login or register a new account*/
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Register" << std::endl;
        std::cout << "> ";

        error_state = OPERATION_SUCCESS; //reseting the error_state
        std::cin >> user_input;
        std::cin.ignore();
            
        /*Update {current_frame} value to render the proper frame (next-step frame OR|| error frame)*/
        switch (user_input) {
        case '1':
            this->current_frame = LOGIN_FRAME;
            break;
        case '2':
            this->current_frame = REGISTER_FRAME;
            break;
        default:
            error_state = ERROR_INVALID_MENU_OPTION;
            this->DisplayErrorMessage(error_state);
            break;
        }

        system("cls");

    } while (error_state != OPERATION_SUCCESS);

}

void ConsoleView::DisplayLoginFrame() {
    Error_t error_state = OPERATION_SUCCESS;
    std::string username;
    std::string password;
    char ch;

    do {

        /*Accept and Assert username format*/
        do {
            //1. ask for username
            std::cout << "Enter your username, please!" << std::endl;
            std::cout << "> ";
            getline(std::cin,username);
            //2. assert username 
            error_state = ErrorState::AssertUsername(username);
            if (error_state != OPERATION_SUCCESS) {
                this->DisplayErrorMessage(error_state);
            }
            
        } while (error_state != OPERATION_SUCCESS); //repeat untill you get a valid username


        /*Accept and Assert password format*/
        do {
            //3. ask for password
            std::cout << "Enter your password, please!" << std::endl;
            std::cout << "> ";
            //mask the password characters with asterisks
            while (1) {
                ch = _getch(); // Get a character without displaying it

                if (ch == 13) {
                    // Enter key
                    std::cout << std::endl;
                    break;

                } 

                password.push_back(ch); // Store the character
                std::cout << '*'; // Display an asterisk
            }

            //4. assert password
            error_state = ErrorState::AssertPassword(password);
            if (error_state != OPERATION_SUCCESS) {
                this->DisplayErrorMessage(error_state);
            }
        } while (error_state != OPERATION_SUCCESS); //repeat untill you get a valid username

        //NOW we've got a valid username & password 
        //5. let's login
        error_state = this->presenter.LoginUser(username, password);


        //check of logging in is OK
        if (error_state != OPERATION_SUCCESS) {
            this->DisplayErrorMessage(error_state);
            password.clear();
        }
      
        system("cls");
        

    }while (error_state != OPERATION_SUCCESS);

    //We're here, So, logging in is OK
    /*Update {current_frame} value to render the proper frame*/
    this->current_frame = USER_MAIN_FRAME;


}
 
void ConsoleView::DisplayRegisterFrame() {
    
    Error_t error_state = OPERATION_SUCCESS;
    std::string username;
    std::string password;
    char ch;

    do {

        /*Accept and Assert username format*/
        do {
            //1. ask for username
            std::cout << "Enter a username, please!" << std::endl;
            std::cout << "> ";
            getline(std::cin, username);
            //2. assert username 
            error_state = ErrorState::AssertUsername(username);
            if (error_state != OPERATION_SUCCESS) {
                this->DisplayErrorMessage(error_state);
            }
        } while (error_state != OPERATION_SUCCESS); //repeat untill you get a valid username


        /*Accept and Assert password format*/
        do {
            //3. ask for password
            std::cout << "Enter your password, please!" << std::endl;
            std::cout << "> ";
            //mask the password characters with asterisks
            while (1) {
                ch = _getch(); // Get a character without displaying it

                if (ch == 13) {
                    // Enter key
                    std::cout << std::endl;
                    break;

                } 
                password.push_back(ch); // Store the character
                std::cout << '*'; // Display an asterisk
            }
            //4. assert password
            error_state = ErrorState::AssertPassword(password);
            if (error_state != OPERATION_SUCCESS) {
                this->DisplayErrorMessage(error_state);
            }
        } while (error_state != OPERATION_SUCCESS); //repeat untill you get a valid username


        //NOW we've got a valid username & password 
        //5. let's register
        error_state = this->presenter.RegisterUser(username, password);
        //check of Registering  is OK
        if (error_state != OPERATION_SUCCESS) {
            //somethins isn't ok
            this->DisplayErrorMessage(error_state);
            password.clear();

        }

        system("cls");

    } while (error_state != OPERATION_SUCCESS);

    //We're here, So, Registeration is OK
    /*Update {current_frame} value to render the proper frame*/
    this->current_frame = MAIN_FRAME;

}

void ConsoleView::DisplayUserMainFrame() {
    Error_t error_state; 
    char user_input;

    do {

        std::cout << "\t\tWelcome, How can I help You" << std::endl;
        std::cout << "----------------------------------------------------------------------" << std::endl;
        this->presenter.DisplayUserMatrix();
        std::cout << "\n\n";
        //1. Display options menu and take user's option
        std::cout << "1. Add Task" << std::endl;
        std::cout << "2. Delete Task" << std::endl;
        std::cout << "3. Mark Done Task" << std::endl;
        std::cout << "4. Delete All Done Tasks" << std::endl;
        std::cout << "5. Delete All Tasks" << std::endl;
        std::cout << "6. Save" << std::endl;
        std::cout << "7. Logout" << std::endl;
        std::cout << "> ";

        error_state = OPERATION_SUCCESS; //reseting the error_state
        std::cin >> user_input;
        std::cin.ignore();

        switch (user_input) {
        case '1':
            this->current_frame = ADD_TASK_FRAME;
            system("cls");

            break;
        case '2':
            this->current_frame = DELETE_TASK_FRAME;
            break;
        case '3':
            this->current_frame = MARK_DONE_TASK_FRAME;
            break;
        case '4':
            this->current_frame = DELETE_ALL_DONE_TASKS_FRAME;
            break;
        case '5':
            this->current_frame = DELETE_ALL_TASKS_FRAME;
            break;
        case '6':
            this->current_frame = SAVE_FRAME;
            break;
        case '7':
            this->current_frame = LOGOUT_FRAME;
            break;
        default:
            error_state = ERROR_INVALID_MENU_OPTION;
            this->DisplayErrorMessage(error_state);
            break;
        }


    } while (error_state != OPERATION_SUCCESS);

    
}

void ConsoleView::DisplayAddTaskFrame() {
    Error_t error_state;
    std::string tname;
    std::string tdue;
    char tweight;

    //1. Get Task Name & Assert 
    do {

        //1.1 get 
        std::cout << "Enter Task Name: " << std::endl;
        std::cout << "> ";
        std::getline(std::cin, tname);
        
        //1.2 assert
        error_state = ErrorState::AssertTaskName(tname);
        if (error_state != OPERATION_SUCCESS) {
            this->DisplayErrorMessage(error_state);
        }
    } while (error_state != OPERATION_SUCCESS); //repeat untill you get a valid task name


    //2. Get Taks due & Assert
    do {
        //2.1 get 
        std::cout << "Enter Task Due date: " << std::endl;
        std::cout << "> ";
        std::getline(std::cin, tdue);

        //2.2 assert
        error_state = ErrorState::AssertDueDate(tdue);
        if (error_state != OPERATION_SUCCESS) {
            this->DisplayErrorMessage(error_state);
        }
    } while (error_state != OPERATION_SUCCESS); //repeat untill you get a valid task due


    //3. Get Task Weight & Assert
    do {
        //3.1 get 
        std::cout << "Enter Task Weight [H, M, or L]: " << std::endl;
        std::cout << "> ";
        std::cin >> tweight;
        std::cin.ignore();

        //3.2 assert
        error_state = ErrorState::AssertWeight(tweight);
        if (error_state != OPERATION_SUCCESS) {
            this->DisplayErrorMessage(error_state);
        }
    } while (error_state != OPERATION_SUCCESS); //repeat untill you get a valid task weight
    
    
    //4. Send AddTask Request to the Presenter
    this->presenter.AddTask(tname, tdue, tweight);


    //5. Update {current_frame}
    this->current_frame = USER_MAIN_FRAME;

    system("cls");
}

void ConsoleView::DisplayDeleteTaskFrame() {
    Error_t error_state; 
    std::string tid;
    int tid_int;

    do {

        //1. Get Task ID & Assert 
        do {
            //1.1 get 
            std::cout << "Enter Task ID: " << std::endl;
            std::cout << "> ";
            std::getline(std::cin, tid);

            //1.2 assert
            error_state = ErrorState::AssertID(tid);
            if (error_state != OPERATION_SUCCESS) {
                this->DisplayErrorMessage(error_state);
            }
        } while (error_state != OPERATION_SUCCESS); //repeat untill you get a valid task id


        //2. Send Delete Task Request to the Presenter
        std::stringstream tid_stream(tid);
        tid_stream >> tid_int;

        error_state = this->presenter.DeleteTask(tid_int);
        if (error_state != OPERATION_SUCCESS) {
            this->DisplayErrorMessage(error_state);
        }
        

    } while (error_state != OPERATION_SUCCESS);


    //5. Update {current_frame}
    this->current_frame = USER_MAIN_FRAME;
    
    system("cls");

}

void ConsoleView::DisplayMarkDoneTaskFrame() {  
    Error_t error_state;
    std::string tid;
    int tid_int;

    do {
        //1. Get Task ID & Assert 
        do {
            //1.1 get 
            std::cout << "Enter Task ID: " << std::endl;
            std::cout << "> ";
            std::getline(std::cin, tid);

            //1.2 assert
            error_state = ErrorState::AssertID(tid);
            if (error_state != OPERATION_SUCCESS) {
                this->DisplayErrorMessage(error_state);
            }
        } while (error_state != OPERATION_SUCCESS); //repeat untill you get a valid task id


        //2. Send Delete Task Request to the Presenter
        std::stringstream tid_stream(tid);
        tid_stream >> tid_int;
        error_state = this->presenter.MarkDoneTask(tid_int);
        if (error_state != OPERATION_SUCCESS) {
            this->DisplayErrorMessage(error_state);
        }

    } while (error_state != OPERATION_SUCCESS);


    //5. Update {current_frame}
    this->current_frame = USER_MAIN_FRAME;
    system("cls");

}

void ConsoleView::DisplayDeleteAllDoneTasksFrame() { 
    
    this->presenter.DeleteAllDone();

    //update {current_frame}
    this->current_frame = USER_MAIN_FRAME;


    system("cls");
}


void ConsoleView::DisplayDeleteAllTasksFrame() {
    char inp;
    Error_t error_state; 
    
    
    do {
        error_state = OPERATION_SUCCESS; //reseting {error_state} 

        std::cout << "Deleting All Tasks!! Are you sure? [Y/N]:  ";

        std::cin >> inp;
        std::cin.ignore();

        switch (inp)
        {
        case'Y':
        case'y':
            std::cout << "Deleting...\n";
            this->presenter.DeleteAllTasks();
            this->DisplayProgressBar(25);

            //update {current_frame}
            this->current_frame = USER_MAIN_FRAME;
            system("cls");
            break;

        case'N':
        case'n':
            //It was chosen by mistak, nothing to do.
        default:
            //neither y,Y,N, nor n ???
            error_state = ERROR_INVALID_MENU_OPTION;
            this->DisplayErrorMessage(error_state);
            system("cls");
            break;
        }
    } while (error_state != OPERATION_SUCCESS);

}

void ConsoleView::DisplayLogoutFrame() { 
    //1. Send a logout request for the Presenter (which in turn: Saves user's data then logs him out)
    std::cout << "Logging out ...\n";
    this->presenter.LogoutUser();

    this->DisplayProgressBar(25);

    std::cout << "User Saved! User Logged out!" << std::endl;
    
    //2. update frame
    this->current_frame = MAIN_FRAME;


    system("cls");
}

void ConsoleView::DisplaySaveFrame() {
    //1. Save user
    std::cout << "Saving ...\n";
    this->presenter.SaveUser();
    this->DisplayProgressBar(15);
    std::cout << "User Saved!" << std::endl;

    //2. update frame
    this->current_frame = USER_MAIN_FRAME;


    system("cls");

}



void ConsoleView::DisplayErrorMessage(Error_t error_code) {
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, CONSOLE_RED_TEXT);
    std::cout << ErrorState::GetErrorMessage(error_code) << std::endl;

    std::cout << "Press Enter to proceed !" << std::endl;
    
    std::cin.get();
   
    SetConsoleTextAttribute(hConsole, CONSOLE_WHITE_TEXT);
    
    
}


void ConsoleView::DisplayMadeWithLove() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, CONSOLE_GREY_TEXT);

    /*Welcome Message*/
    std::cout << "\t\t\t\tWelcome, Hero!" << std::endl;
    std::cout << "Welcome to ";
    SetConsoleTextAttribute(hConsole, CONSOLE_BEIGE_TEXT);
    std::cout << "[VTS] Virtual Task Scheduler:" << std::endl;
    SetConsoleTextAttribute(hConsole, CONSOLE_GREY_TEXT);
    std::cout << "Your Ultimate Stress Reliever for Task Achieving!" << std::endl;

    std::cout << std::endl;
    std::cout << "\t\t\t\tMade With ";
    SetConsoleTextAttribute(hConsole, CONSOLE_RED_TEXT);
    std::cout << "<3";
    SetConsoleTextAttribute(hConsole, CONSOLE_GREY_TEXT);
    std::cout << ", By Ali"<<std::endl;
    SetConsoleTextAttribute(hConsole, CONSOLE_WHITE_TEXT);
    std::cout << "-----------------------------------------------------------------------------------------------" << std::endl;

}


void ConsoleView::DisplayProgressBar(int sleep_time) {
    int current_progress = 0; // Current progress
    int total_progress = 25; // Current progress

    // Display an initial empty loading bar
    std::cout << "[";
    for (int i = 0; i < total_progress; i++) {
        std::cout << " ";
    }
    std::cout << "]" << std::flush;

    while (current_progress < total_progress) {
        // Move the cursor back to the beginning of the loading bar
        std::cout << "\r[";

        // Fill the loading bar
        for (int i = 0; i < current_progress; i++) {
            std::cout << "#";
        }

        // Display spaces for the remaining progress
        for (int i = current_progress; i < total_progress; i++) {
            std::cout << " ";
        }

        // Close the loading bar
        std::cout << "]" << std::flush;

        // Simulate some work (you can replace this with your actual work)
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));

        current_progress++; // Update the progress
    }
    std::cout << "\n";
}