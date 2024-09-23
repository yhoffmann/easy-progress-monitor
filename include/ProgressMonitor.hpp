#pragma once


#include <stdlib.h>
#include <atomic>
#include <iostream>
#include <fstream>
#include <string>


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