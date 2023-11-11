#include"Model/Task.h"



/**
    Task Constructor: to construct tasks using its main properties, and assigns and unique id for each task.
**/
Task::Task(std::string n, std::string due, TaskWeight_t w) {
    this->name = n;
    this->due_date = Date(due);
    this->weight = w;
    this->done = false;

    //Assigning a Unique ID For each task
    // + Involving Date is to guarantee that tasks will be ordered based on who's sooner.


    /*Task Urgency will be determined later ,when it's added to the related matrix
        ,OR when the matrix is re-structured */
    this->importance = NOT_IMPORTANT;

    /*Also Task Urgency will be determined later ,when it's added to the related matrix
        ,OR when the matrix is re-structured */
    this->urgency = NOT_URGENT; //default

    /*Subsequently, Task Category Will be determined later, when it's added to the related matrix
        ,OR when the matrix is re-structured*/
    this->category = NOT_URGENT_NOT_IMPORTANT; //default


}


std::string Task::GetName() {
    return this->name;
}


Date Task::GetDue() {
    return this->due_date;
}

unsigned int Task::GetID() {
    return this->id;
}

TaskCategory_t Task::GetCategory() {
    return this->category;
}

bool Task::IsDone()const {
    return this->done;
}

void Task::MarkDone() {

    this->done = true;

}

TaskWeight_t Task::GetWeight() {
    return this->weight;
}
TaskUrgency_t Task::GetUrgency() {
    return this->urgency;
}

TaskImportance_t Task::GetImportance() {
    return this->importance;
}

void Task::SetCategory(TaskCategory_t cat) {
    this->category = cat;
}

void Task::SetUrgency(TaskUrgency_t urg) {
    this->urgency = urg;
}
void Task::SetImportance(TaskImportance_t imp) {
    this->importance = imp;
}

void Task::SetID(unsigned int id) {
    this->id = id;
}



std::string Task::Serialize() {
    std::string result = "";
    result += "\t\tT: ";

    result += this->name;

    result += " ,";
    result += this->due_date.GetDate_str();

    result += " ,";
    result += std::to_string(this->weight);

    result += " ,";
    result += std::to_string(this->id);

    result += " ,";
    result += std::to_string(this->done);

    return result;
}

Task Task::DeSerialize(const std::string& result) {
    /*
        Note that fields must be de-serialized in the same order they were serialized in.
    */

    std::string task_name;
    std::string task_due;
    int task_weight;
    unsigned int task_id;
    bool task_done;
    std::istringstream iss(result);


    char _; // To discard commas

    iss.ignore(100, ':'); // Discard "T: ", by ignoring and thing until the ':'
    std::getline(iss, task_name, ','); // Read the task name until a comma

    iss>> task_due >> _ >> task_weight >> _ >> task_id >> _ >> task_done;

    TaskWeight_t tweight = static_cast<TaskWeight_t>(task_weight);
    unsigned int tid = task_id;
    bool tdone = static_cast<bool>(task_done);

    Task deserialized_task(task_name,task_due,tweight);
    deserialized_task.id = tid;
    deserialized_task.done = tdone;

    return deserialized_task;

}

