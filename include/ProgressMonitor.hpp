#pragma once
#ifndef PROGRESSMONITOR_HPP
#define PROGRESSMONITOR_HPP


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <mutex>


class ProgressMonitor {
protected:
    std::mutex m_mtx;
    size_t m_num_tasks;
    size_t m_finished_tasks;
    float m_last_percentage_logged;
    std::string m_message;

public:
    void add_finished();
    void print_progress_percentage(std::ostream& stream = std::cout);
    ProgressMonitor() = delete;
    ProgressMonitor(size_t num_tasks, const std::string& message = "Progress: ");
    ProgressMonitor(const ProgressMonitor&) = default;
    ProgressMonitor(ProgressMonitor&&) = default;
    ProgressMonitor& operator=(const ProgressMonitor&) = default;
    ProgressMonitor& operator=(ProgressMonitor&&) = default;
    ~ProgressMonitor() = default;
};


void ProgressMonitor::add_finished() {
    std::lock_guard<std::mutex> lck(m_mtx);
    m_finished_tasks++;
}


void ProgressMonitor::print_progress_percentage(std::ostream& stream) {
    std::lock_guard<std::mutex> lck(m_mtx);
    float percentage = std::floor(float(m_finished_tasks)/float(m_num_tasks)*100.0);

    if (percentage != m_last_percentage_logged) {
        stream << m_message << percentage << "%\n";
        m_last_percentage_logged = percentage;
    }
}


ProgressMonitor::ProgressMonitor(size_t num_tasks, const std::string& message)
    : m_num_tasks(num_tasks)
    , m_finished_tasks(0)
    , m_last_percentage_logged(0)
    , m_message(message)
{
}


#endif // PROGRESSMONITOR_HPP