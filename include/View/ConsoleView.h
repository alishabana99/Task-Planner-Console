#ifndef CONSOLEVIEW_H_INCLUDED
#define CONSOLEVIEW_H_INCLUDED

#include <iostream>
#include "ErrorState.h"
#include "Presenter.h"
#include <string>
#include<windows.h>
#include <conio.h>
#include <chrono>
#include <thread>


#define CONSOLE_RED_TEXT    12
#define CONSOLE_WHITE_TEXT  7
#define CONSOLE_GREEN_TEXT  2
#define CONSOLE_GREY_TEXT  8
#define CONSOLE_BEIGE_TEXT  0x0e
#define CONSOLE_GREY_BACKGROUND  112


typedef enum{
    MAIN_FRAME = 0,
    LOGIN_FRAME,
    REGISTER_FRAME,
    USER_MAIN_FRAME,
    ADD_TASK_FRAME,
    DELETE_TASK_FRAME,
    MARK_DONE_TASK_FRAME,
    DELETE_ALL_DONE_TASKS_FRAME,
    DELETE_ALL_TASKS_FRAME,
    LOGOUT_FRAME,
    SAVE_FRAME,
}UI_Frames_t;


class ConsoleView{

private:
    /* Private: Date */
    UI_Frames_t current_frame;
    std::string current_username;
    Presenter presenter;

    /* Private: Metohds */
    void DisplayMainFrame();
    void DisplayLoginFrame();
    void DisplayRegisterFrame();
    void DisplayUserMainFrame();
    void DisplayAddTaskFrame();
    void DisplayDeleteTaskFrame();
    void DisplayMarkDoneTaskFrame();
    void DisplayDeleteAllDoneTasksFrame();
    void DisplayDeleteAllTasksFrame();
    void DisplayLogoutFrame();
    void DisplaySaveFrame();
    void DisplayErrorMessage(Error_t error_code);
    void DisplayMadeWithLove();
    void DisplayProgressBar(int total_progress);
public:
    /* Public: Data */

    
    /* Public: Metohds */
    ConsoleView();
    void Run();

};


#endif // CONSOLEVIEW_H_INCLUDED
