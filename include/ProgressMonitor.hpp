#pragma once
#ifndef PROGRESSMONITOR_HPP
#define PROGRESSMONITOR_HPP


#include <stdlib.h>
#include <atomic>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


class ProgressMonitor {
protected:
    std::atomic_uint m_num_tasks;
    std::atomic_uint m_finished_tasks;
    std::atomic<float> m_last_percentage_logged;
    std::string m_message;

public:
    void add_finished();
    void print_progress_percentage(std::ostream& stream = std::cout);
    ProgressMonitor() = delete;
    ProgressMonitor(uint num_tasks, const std::string& message = "Progress: ");
    ProgressMonitor(const ProgressMonitor&) = default;
    ProgressMonitor(ProgressMonitor&&) = default;
    ProgressMonitor& operator=(const ProgressMonitor&) = default;
    ProgressMonitor& operator=(ProgressMonitor&&) = default;
    ~ProgressMonitor() = default;
};


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


#endif // PROGRESSMONITOR_HPP