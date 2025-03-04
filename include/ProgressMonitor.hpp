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
    uint m_last_percentage_logged;
    std::string m_message;
    std::ostream* m_stream = &std::cerr;

public:
    void add_finished();
    void print_progress_percentage();
    void set_stream(std::ostream& stream);

    ProgressMonitor() = delete;
    ProgressMonitor(size_t num_tasks, const std::string& message = "Progress: ", std::ostream& stream = std::cerr);
    ProgressMonitor(const ProgressMonitor&) = delete;
    ProgressMonitor(ProgressMonitor&&) = delete;
    ProgressMonitor& operator=(const ProgressMonitor&) = delete;
    ProgressMonitor& operator=(ProgressMonitor&&) = delete;
    ~ProgressMonitor() = default;
};


inline void ProgressMonitor::add_finished() {
    std::lock_guard<std::mutex> lck(m_mtx);
    m_finished_tasks++;
}


inline void ProgressMonitor::print_progress_percentage() {
    std::lock_guard<std::mutex> lck(m_mtx);
    uint percentage = (uint)std::floor(float(m_finished_tasks)/float(m_num_tasks)*100.0);

    if (percentage != m_last_percentage_logged) {
        if (m_stream != nullptr)
            *m_stream << m_message << percentage << "%\n";
        m_last_percentage_logged = percentage;
    }
}


inline void ProgressMonitor::set_stream(std::ostream& stream) {
    std::lock_guard<std::mutex> lck(m_mtx);
    m_stream->flush();
    m_stream = &stream;
}


inline ProgressMonitor::ProgressMonitor(size_t num_tasks, const std::string& message, std::ostream& stream)
    : m_num_tasks(num_tasks)
    , m_finished_tasks(0)
    , m_last_percentage_logged(0)
    , m_message(message)
    , m_stream(&stream)
{
}


#endif // PROGRESSMONITOR_HPP