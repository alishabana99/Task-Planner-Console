#ifndef TASK_HPP_INCLUDED
#define TASK_HPP_INCLUDED

#include<string>
#include <sstream>

#include<Date.h>
#include "ISerializableToString.h"


typedef enum {
    NOT_URGENT_NOT_IMPORTANT= 0,
    NOT_URGENT_IMPORTANT    = 1,
    URGENT_NOT_IMPORTANT    = 2,
    URGENT_IMPORTANT        = 3,
} TaskCategory_t;

/*Task Weight: Indicates how does your task contribute to your long term goal/ the larger task [Specified by the matrix]*/
typedef enum{
    HIGH_WEIGHT, //76% - 100%
    MID_WEIGHT,  //25% - 75%
    LOW_WEIGHT,  //0%  - 25%
}TaskWeight_t;

/*Task Urgency: Indicates the urgency of your task according to its due date [Specified by the matrix]*/
typedef enum{
    NOT_URGENT =0,
    URGENT,
}TaskUrgency_t;

/*Task Importance: Indicates the importance of your task according to its weight/contribution [Specified by the matrix]*/
typedef enum{
    NOT_IMPORTANT =0,
    IMPORTANT,
}TaskImportance_t;


class Task : public ISerializableToString<Task>{


private:
    std::string name;
    Date due_date;
    TaskCategory_t category;
    TaskWeight_t weight;
    TaskUrgency_t urgency;
    TaskImportance_t importance;
    unsigned int id;
    bool done;

public:
    Task() = default;
    Task(std::string n, std::string due, TaskWeight_t w);

    std::string GetName();
    Date GetDue();
    unsigned int GetID();
    TaskCategory_t GetCategory();
    TaskWeight_t GetWeight();
    TaskUrgency_t GetUrgency();
    TaskImportance_t GetImportance();

    void SetCategory(TaskCategory_t cat);
    void SetUrgency(TaskUrgency_t urg);
    void SetImportance(TaskImportance_t imp);
    void SetID(unsigned int id);

    void MarkDone();
    bool IsDone()const;

    std::string Serialize() override;
    Task DeSerialize(const std::string& result) override;


};



#endif // TASK_HPP_INCLUDED
