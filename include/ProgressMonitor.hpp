#pragma once


#include <string>


class ProgressMonitor
{
    unsigned int m_num_tasks;
    unsigned int m_finished_tasks;
    unsigned int m_last_percentage_logged;
    std::string m_message;
public:
    void add_finished();
    //unsigned int get_num_tasks();
    void print_progress_percentage();
    ProgressMonitor(unsigned int num_tasks);
    ProgressMonitor(unsigned int num_tasks, std::string message);
    ProgressMonitor() = delete;
};