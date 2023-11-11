#include"Matrix.h"
#include <iostream>


Matrix::Matrix() {

    this->id_selector = 1;
    this->urgency_threshold = 0;

}


/*Handling the copy constructor*/
Matrix::Matrix(const Matrix& ready_matrix) :
    id_selector(ready_matrix.id_selector),
    urgency_threshold(ready_matrix.urgency_threshold),
    all_tasks(ready_matrix.all_tasks),
    tasks_remaining_days(ready_matrix.tasks_remaining_days)
{

    this->StructureTheMatrix();
    
}


/*Overloading the assignment operator*/
Matrix& Matrix::operator=(const Matrix& ready_matrix) {
    
    if (this == &ready_matrix) {
        return *this;  // Self-assignment, no action needed
    }

    //deep copying these:
    this->id_selector = ready_matrix.id_selector;
    this->urgency_threshold = ready_matrix.urgency_threshold;
    this->all_tasks = ready_matrix.all_tasks;
    this->tasks_remaining_days = ready_matrix.tasks_remaining_days;

    
    //the other 4 maps that have Task* pointers will be automatically well-initialized using StructureMatrix
    this->StructureTheMatrix();
    

    return *this;
}



std::map<int,Task*>& Matrix::GetUrgentImportantTasks() {
    return this->urgent_important_tasks;
}
std::map<int,Task*>& Matrix::GetNotUrgentImportantTasks() {
    return this->not_urgent_important_tasks;
}
std::map<int,Task*>& Matrix::GetUrgentNotImportantTasks() {
    return this->urgent_not_important_tasks;
}
std::map<int,Task*>& Matrix::GetNotUrgentNotImportantTasks() {
    return this->not_urgent_not_important_tasks;
}

void Matrix::SetUrgentImportantTasks(std::map<int,Task*> tmap) {
    this->urgent_important_tasks = tmap;
}
void Matrix::SetNotUrgentImportantTasks(std::map<int,Task*> tmap) {
    this->not_urgent_important_tasks = tmap;
}
void Matrix::SetUrgentNotImportantTasks(std::map<int,Task*> tmap) {
    this->urgent_not_important_tasks = tmap;
}
void Matrix::SetNotUrgentNotImportantTasks(std::map<int,Task*> tmap) {
    this->not_urgent_not_important_tasks = tmap;

}

/**
    => Any other matrix operation operates on the all_tasks map,
        then, it's this function's role to reflect those changes to the Original matrix.

    => This Function MUST be called in the following circumstances:
        - After Any Task Addition
        - After Any Task Deletion
        - After Any Task Marking Done.
        - (At Startup) After loading User's Data from database.
**/
void Matrix::StructureTheMatrix() {


    /* 1. Update {urgency_threshold}*/
    //Calculates Remaining days of all the tasks THEN Calculates the median of them as the {urgency_threshold}
    UpdateMatrixUrgencyThreshold();


    /* 2. assign */
    this->urgent_important_tasks.clear();
    this->not_urgent_important_tasks.clear();
    this->urgent_not_important_tasks.clear();
    this->not_urgent_not_important_tasks.clear();

    /* 3. loop through the maintained map of all_tasks and add them to new matrix
          std::map<int, Task*> all_tasks;  */
    for(auto& p : this->all_tasks) {

        UpdateTaskCategory(p.second);
        switch(p.second.GetCategory()) {
        case URGENT_IMPORTANT:
            urgent_important_tasks.emplace(p.first,&(p.second));
            break;
        case NOT_URGENT_IMPORTANT:
            not_urgent_important_tasks.emplace(p.first,&(p.second));
            break;
        case URGENT_NOT_IMPORTANT:
            urgent_not_important_tasks.emplace(p.first,&(p.second));
            break;
        case NOT_URGENT_NOT_IMPORTANT:
            not_urgent_not_important_tasks.emplace(p.first,&(p.second));
            break;
        }
    }

}

/**
    - Adding specific task to the matrix of the associated user.
    - Which matrix quarter depends on the priority of the to-be-added task.
**/
void Matrix::AddTaskToMatrix(Task t) {


    unsigned int tkey = t.GetDue().GetDate_int();

    while( (this->all_tasks).find(tkey) != (this->all_tasks).end() ) {
        tkey = tkey + (Matrix::id_selector++);
    }

    t.SetID(tkey);
    /*Maintaining the list of tasks*/
    this->all_tasks.emplace(t.GetID(),t);

    /*Structure Matrix (as any other operation that requires restructuring)
        operates on the all_tasks map not on the original matrix itself*/
    StructureTheMatrix();
}


/**
    Deleting a Task corespondent to the provided {task_id} by searching in the 4 tasks groups.
**/
bool Matrix::DeleteTaskFromMatrix(int task_id) {

    /*Maintaining the list of the tasks
        by deleting the task that is to be deleted from its quarter*/
    std::map<int,Task>::iterator iter = all_tasks.find(task_id);
    if (iter != all_tasks.end())
        all_tasks.erase(iter);
    else
        return false;

    StructureTheMatrix();

    return true;

}

/**
    Delete any task that has the attribute done as true.
**/
void Matrix::DeleteAllDone() {

    for (auto it = all_tasks.begin(); it != all_tasks.end(); ) {
        if (it->second.IsDone()) {
            // Erase the element and advance the iterator to the next element
            it = all_tasks.erase(it);
        } else {
            // Move to the next element
            ++it;
        }
    }

    StructureTheMatrix();
}

void Matrix::DeleteAllTasks() {

    for (auto it = all_tasks.begin(); it != all_tasks.end(); ) {

        it = all_tasks.erase(it);        
        
    }
}


bool Matrix::MarkDoneTask(int task_id) {

    //first we find the desired task using the provided {task_id}
    //thins we mark it as done
    std::map<int,Task>::iterator search_result;

    if (this->all_tasks.find(task_id) != all_tasks.end()) {
        all_tasks[task_id].MarkDone();
    }
    else {
        return false;
    }

    StructureTheMatrix();

    return true;
}

/**
    Counts the number of the tasks of the given Quarter (map) without counting done tasks.
**/
int Matrix::GetUndoneTasksCount(const std::map<int,Task*>& quarter) {

    int undoneCount = 0;

    for (const auto& p : quarter) {
        if ((*(p.second)).IsDone() == false) {
            undoneCount++;
        }
    }

    return undoneCount;

}

/**
    Updates Task category depending on its importance AND urgency
**/
void Matrix::UpdateTaskCategory(Task& t) {
    TaskCategory_t temp_task_category = NOT_URGENT_NOT_IMPORTANT;
    int temp_category_int = static_cast<int>(temp_task_category);

    //1. Update Task Urgency
    UpdateTaskUrgency(t);

    //2. Update Task Importance
    UpdateTaskImportance(t);

    //3. Decide the category
    switch(t.GetImportance()) {
    case IMPORTANT:
        temp_category_int += 1;
        break;
    case NOT_IMPORTANT:
        temp_category_int += 0;
        break;
    }

    switch(t.GetUrgency()) {
    case URGENT:
        temp_category_int += 2;
        break;
    case NOT_URGENT:
        temp_category_int += 0;
        break;
    }

    //4. Assign
    temp_task_category = static_cast<TaskCategory_t>(temp_category_int);
    t.SetCategory(temp_task_category);
}

/**
    Updates task importance depending on its weight ,other tasks' weight
    ,and the number of tasks already exists in the targeted category
**/
void Matrix::UpdateTaskImportance(Task& t) {
    /**CAUTION: TASK URGENCY MUST BE CALCULATED FIRST**/
    /*Check task's weight*/
    switch(t.GetWeight()) {

    //if It's HIGH_WEIGHT -> It's definitely important.
    case HIGH_WEIGHT:
        t.SetImportance(IMPORTANT);
        break;

    //if it's MID_WEIGHT  -> it's destiny will be determined depending on the RECOMMENDED_TASKS_NUMBER
    // of the related urgent/not_urgent quarter [This why you must calculate the urgency first before this function call]
    case MID_WEIGHT:
        if(t.GetUrgency() == URGENT) {
            //it's urgent -> let's decide if it's urgent_important OR urgent_not_important
            if( (this->GetUndoneTasksCount(this->urgent_important_tasks)) >= RECOMMENDED_URGENT_IMPORTANT_TASKS_NUMBER ) {
                //we can't add more tasks as URGENT_IMPORTANT
                //Maybe later, if the user marks done OR deletes any task
                t.SetImportance(NOT_IMPORTANT);
            } else {
                t.SetImportance(IMPORTANT);
            }
        } else {
            //It's NOT_URGENT -> let's decide if it's not_urgent_important OR not_urgent_not_important
            if( (this->GetUndoneTasksCount(this->not_urgent_important_tasks)) >= RECOMMENDED_NOT_URGENT_IMPORTANT_TASKS_NUMBER ) {
                //we can't add more tasks as URGENT_IMPORTANT
                //Maybe later, if the user marks done OR deletes any task
                t.SetImportance(NOT_IMPORTANT);
            } else {
                t.SetImportance(IMPORTANT);
            }
        }
        break;

    //if it's LOW_WEIGHT  -> It's definitely not important
    case LOW_WEIGHT:
        t.SetImportance(NOT_IMPORTANT);
        break;
    }
}


/**
    Updates task urgency depending on its due and other tasks' due
**/
void Matrix::UpdateTaskUrgency(Task& t) {

    /*2. Decide the new urgency*/
    if(t.GetDue().GetRemainingDays() > this->urgency_threshold) {
        //It's not that urgent
        t.SetUrgency(NOT_URGENT);
    } else {
        //Maybe it's urgent enough
        t.SetUrgency(URGENT);
    }

}

/**
    Calculates the remaining days of each task and stores them in one set {remaining_days} set,
    preparing them to be later processed to calculate the {urgency_threshold} out of them.
**/
void Matrix::CalculateMatrixTasksRemainingDays() {

    int temp_remaining_days;


    //clearing the {tasks_remaining_days} set
    for(std::multiset<int>::iterator set_iter = (this->tasks_remaining_days).begin(); set_iter != (this->tasks_remaining_days).end(); ) {
        (this->tasks_remaining_days).erase(set_iter++);
    }

    //Saving all tasks remaining days to be used in further calculations
    for( auto& task_pair : this->all_tasks) {

        temp_remaining_days = task_pair.second.GetDue().GetRemainingDays();
        this->tasks_remaining_days.insert(temp_remaining_days);
    }

}

/**
    - Calculate remaining days of all the tasks and saves them in {tasks_remaining_days} set.
    - Calculating the {urgency_threshold} out of the all remaining days of the all tasks, those are in the set.
    - {urgency_threshold} is calculated as the average of all tasks' remaining days.
    - Median is used to calculate the average to avoid the outliers effect.
**/
void Matrix::UpdateMatrixUrgencyThreshold() {

    //1. Updating the set that maintains the remaining days of the tasks, in anticipation of any changes (Added/deleted task)
    CalculateMatrixTasksRemainingDays();

    //2. Calculate the Median
    size_t set_size = (this->tasks_remaining_days).size();
    //if there're no tasks -> no need for calculations -> threshold = 0
    if (set_size == 0) {
        this->urgency_threshold = 0;
        return;
    }


    std::multiset<int>::iterator set_iter  = (this->tasks_remaining_days).begin();
    std::advance(set_iter, set_size / 2); // Move the iterator to the middle element

    //Checking if the set has Even or Odd number of elements, As the method of calculating the median differs in the both cases.
    if (set_size && set_size % 2 == 0) {
        //It has Even number of elements
        std::multiset<int>::iterator set_iter2 = set_iter;
        --set_iter2; // Move to the element before the middle one

        double median = (*set_iter + *set_iter2) / 2.0; //the

        this->urgency_threshold = static_cast<int>(median);

    } else {
        //It has Odd number of elements
        this->urgency_threshold = *set_iter;
    }

}


std::string Matrix::Serialize(){

    std::string result = "";
    result += "\tM: ";

        result += std::to_string(Matrix::id_selector);
        result += '\n';

        for(auto p: this->all_tasks){
            result+=  p.second.Serialize();
            result += '\n';
        }

return result;

}

Matrix Matrix::DeSerialize(const std::string& result) {
/*
    Note that fields must be de-serialized in the same order they were serialized in.
*/
    Matrix m;
    int id_selector_state;
    std::map<int,Task> matrix_all_tasks;
    std::istringstream iss(result);
    std::string task_line; //for reading the string line by line


    char _; // To discard commas

    iss.ignore(100, ':'); // Discard "M: ", by ignoring and thing until the ':'


    iss>> id_selector_state >> _; //reading the to-be used next {id_selector} of that matrix


    //reading tasks, task per line
    while (std::getline(iss, task_line)){
        Task t;
        t = t.DeSerialize(Utility::TrimRecordIndentation(task_line));
        matrix_all_tasks.emplace(t.GetID(),t);
    }

    //building up our matrix object
    m.id_selector = id_selector_state;
    m.all_tasks = matrix_all_tasks;

return m;

}


/**
    - Overloading the output operator enables us to print class objects
    - cout<< m_Matrix << endl; //just like that
**/
std::ostream& operator<<(std::ostream& os, const Matrix& m) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Matrix mutableCopy = m;

    std::map<int,Task*>& quarter1 = mutableCopy.GetUrgentImportantTasks();          //Top-Left
    std::map<int,Task*>& quarter2 = mutableCopy.GetNotUrgentImportantTasks();       //Top-Right
    std::map<int,Task*>& quarter3 = mutableCopy.GetUrgentNotImportantTasks();       //Down-Left
    std::map<int,Task*>& quarter4 = mutableCopy.GetNotUrgentNotImportantTasks();    //Down-Right

    //Used to build up strings to print
    std::string temp_string;

    /*___________________________Urgent/Important Tasks___________________________*/
//header
    // Setting the background color to blue
    SetConsoleTextAttribute(hConsole, CONSOLE_GREY_BACKGROUND);
    os 	 <<std::left<<std::setw(HEADER_WIDTH)<< "Urgent/Important Tasks"<<std::endl;
    SetConsoleTextAttribute(hConsole, CONSOLE_WHITE_TEXT);

//body

    //add empty line if it's empty [just for space reservation and formatting]
    if(quarter1.empty()) {
        os<<" "<<std::endl;

    }

    for( auto p : quarter1) {
        if(p.second->IsDone()) {
            SetConsoleTextAttribute(hConsole, CONSOLE_GREEN_TEXT);
        }
        //Printing ID
        temp_string ="[" + std::to_string(p.first) + "] ";
        os <<std::left<<std::setw(ID_WIDTH)<< temp_string;
        //Printing Name
        os  <<std::left<< std::setw(NAME_WIDTH)<< p.second->GetName();
        //Printing Date
        os  <<std::left<< std::setw(DATE_WIDTH)<<  p.second->GetDue().GetDate_str();
        os <<std::endl;
        SetConsoleTextAttribute(hConsole, CONSOLE_WHITE_TEXT);
    }
    os<<" "<<std::endl;


    /*___________________________Not Urgent/Important Tasks___________________________*/
//header
    // Setting the background color to blue
    SetConsoleTextAttribute(hConsole, CONSOLE_GREY_BACKGROUND);
    os 	 <<std::left<<std::setw(HEADER_WIDTH)<< "Not Urgent/Important Tasks"<<std::endl;
    SetConsoleTextAttribute(hConsole, CONSOLE_WHITE_TEXT);
//body

    //add empty line if it's empty [just for space reservation and formatting]
    if(quarter2.empty()) {
        os<<" "<<std::endl;
    }

    for( auto p : quarter2) {
        if(p.second->IsDone()) {
            SetConsoleTextAttribute(hConsole, CONSOLE_GREEN_TEXT);
        }
        //Printing ID
        temp_string ="[" + std::to_string(p.first) + "] ";
        os <<std::left<<std::setw(ID_WIDTH)<< temp_string;
        //Printing Name
        os  <<std::left<< std::setw(NAME_WIDTH)<< p.second->GetName();
        //Printing Date
        os  <<std::left<< std::setw(DATE_WIDTH)<<  p.second->GetDue().GetDate_str();
        os <<std::endl;
        SetConsoleTextAttribute(hConsole, CONSOLE_WHITE_TEXT);
    }
    os<<" "<<std::endl;


    /*___________________________Urgent/Not Important Tasks___________________________*/
//header
    // Setting the background color to blue
    SetConsoleTextAttribute(hConsole, CONSOLE_GREY_BACKGROUND);
    os 	 <<std::left<<std::setw(HEADER_WIDTH)<< "Urgent/Not Important Tasks"<<std::endl;
    SetConsoleTextAttribute(hConsole, CONSOLE_WHITE_TEXT);
//body

    //add empty line if it's empty [just for space reservation and formatting]
    if(quarter3.empty()) {
        os<<" "<<std::endl;
    }

    for( auto p : quarter3) {
        if(p.second->IsDone()) {
            SetConsoleTextAttribute(hConsole, CONSOLE_GREEN_TEXT);
        }
        //Printing ID
        temp_string ="[" + std::to_string(p.first) + "] ";
        os <<std::left<<std::setw(ID_WIDTH)<< temp_string;
        //Printing Name
        os  <<std::left<< std::setw(NAME_WIDTH)<< p.second->GetName();
        //Printing Date
        os  <<std::left<< std::setw(DATE_WIDTH)<<  p.second->GetDue().GetDate_str();
        os <<std::endl;
        SetConsoleTextAttribute(hConsole, CONSOLE_WHITE_TEXT);
    }
    os<<" "<<std::endl;


    /*___________________________Not Urgent/Not Important Tasks___________________________*/
//header
    // Setting the background color to blue
    SetConsoleTextAttribute(hConsole, CONSOLE_GREY_BACKGROUND);
    os 	 <<std::left<<std::setw(HEADER_WIDTH)<< "Not Urgent/Not Important Tasks"<<std::endl;
    SetConsoleTextAttribute(hConsole, CONSOLE_WHITE_TEXT);
//body
    //add empty line if it's empty [just for space reservation and formatting]
    if(quarter4.empty()) {
        os<<" "<<std::endl;
    }

    for( auto p : quarter4) {
        //if the task is done, make it green.
        if(p.second->IsDone()) {
            SetConsoleTextAttribute(hConsole, CONSOLE_GREEN_TEXT);
        }

        //Printing ID
        temp_string ="[" + std::to_string(p.first) + "] ";
        os <<std::left<<std::setw(ID_WIDTH)<< temp_string;
        //Printing Name
        os  <<std::left<< std::setw(NAME_WIDTH)<< p.second->GetName();
        //Printing Date
        os  <<std::left<< std::setw(DATE_WIDTH)<<  p.second->GetDue().GetDate_str();
        os <<std::endl;
        SetConsoleTextAttribute(hConsole, CONSOLE_WHITE_TEXT);
    }
    os<<" "<<std::endl;


    return os;
}

