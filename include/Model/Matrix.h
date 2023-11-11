#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include<map>
#include<set>
#include"Task.h"
#include<iostream>
#include<iomanip>
#include<windows.h>
#include<string>
#include "Utility.h"

#include"ISerializableToString.h"


/*
    These macros are used in Matrix Printing Operation
*/
#define ID_WIDTH            8
#define NAME_WIDTH          30
#define DATE_WIDTH          10
#define SEPARATOR_WIDTH     1
#define HEADER_WIDTH        (NAME_WIDTH + ID_WIDTH + DATE_WIDTH + (SEPARATOR_WIDTH*3))

/*
    Macros for Specifying Recommended number of tasks in each of the both important quarters,
    As the system tries to support minimalism and reduce the pressure as much as possible.
*/
#define RECOMMENDED_URGENT_IMPORTANT_TASKS_NUMBER   3
#define RECOMMENDED_NOT_URGENT_IMPORTANT_TASKS_NUMBER   4


#define CONSOLE_RED_TEXT    12
#define CONSOLE_WHITE_TEXT  7
#define CONSOLE_GREEN_TEXT  2
#define CONSOLE_GREY_BACKGROUND  112

class Matrix : public ISerializableToString<Matrix>{
private:
    std::map<int,Task*> urgent_important_tasks;
    std::map<int,Task*> not_urgent_important_tasks;
    std::map<int,Task*> urgent_not_important_tasks;
    std::map<int,Task*> not_urgent_not_important_tasks;
    std::multiset<int> tasks_remaining_days;
    std::map<int,Task> all_tasks; /* Should be stored/retrieved */
    int urgency_threshold;
    unsigned int id_selector; /* Should be stored/retrieved */

    /*Private Methods*/
    void UpdateTaskCategory(Task& t);
    void UpdateTaskImportance(Task& t);
    void UpdateTaskUrgency(Task& t);
    void CalculateMatrixTasksRemainingDays();
    void UpdateMatrixUrgencyThreshold();
    int GetUndoneTasksCount(const std::map<int,Task*>& quarter);
    void StructureTheMatrix();

    public:
    /*Public Methods*/
    Matrix();

    Matrix(const Matrix& ready_matrix);
    Matrix& operator=(const Matrix& rhs);
    
    std::map<int,Task*>& GetUrgentImportantTasks();
    std::map<int,Task*>& GetNotUrgentImportantTasks();
    std::map<int,Task*>& GetUrgentNotImportantTasks();
    std::map<int,Task*>& GetNotUrgentNotImportantTasks();

    void SetUrgentImportantTasks(std::map<int,Task*> tmap);
    void SetNotUrgentImportantTasks(std::map<int,Task*> tmap);
    void SetUrgentNotImportantTasks(std::map<int,Task*> tmap);
    void SetNotUrgentNotImportantTasks(std::map<int,Task*> tmap);

    void AddTaskToMatrix(Task t_arg);

    bool DeleteTaskFromMatrix(int task_id);
    void DeleteAllDone();
    void DeleteAllTasks();
    bool MarkDoneTask(int task_id);


    std::string Serialize() override;
    Matrix DeSerialize(const std::string& result) override;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& dt);

};


#endif // MATRIX_H_INCLUDED
