#include "../include/ProgressMonitor.hpp"
#include <iostream>
#include <math.h>


void ProgressMonitor::add_finished() {
    m_finished_tasks++;
}


void ProgressMonitor::print_progress_percentage (std::ostream& stream) {
    float percentage = std::floor(float(m_finished_tasks)/float(m_num_tasks)*100.0);

    if (percentage != m_last_percentage_logged) {
        stream << m_message << percentage << "%\n";
        m_last_percentage_logged = percentage;
    }
}


ProgressMonitor::ProgressMonitor (unsigned int num_tasks, const std::string& message)
    : m_num_tasks(num_tasks)
    , m_finished_tasks(0)
    , m_last_percentage_logged(0)
    , m_message(message)
{
}