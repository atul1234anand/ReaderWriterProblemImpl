#include "readwrite.h"
#include <mutex>
#include "log.h"

namespace {
std::mutex reader_counter_mutex;
int reader_counter = 0;
std::mutex writer_counter_mutex;
int writer_counter = 0;
std::mutex new_reader_mutex;
std::mutex reading_mutex;
std::mutex writing_mutex;
}  // namespace

using namespace readwrite;

WriterChecker::WriterChecker() {
    /* update wcounter */
    {
        /* 2-n writer wait here */
        std::lock_guard<std::mutex> lock(::writer_counter_mutex);
        ::writer_counter++;
        if (::writer_counter == 1) {
            /* writer first */
            ::new_reader_mutex.lock();
            /* first writer wait for readers who are reading */
            QI_LOG("start waitting for reading");
            ::reading_mutex.lock();
            QI_LOG("end waitting for reading");
        }
    }
    /* only one writer */
    ::writing_mutex.lock();
    QI_LOG("start writing");
}

WriterChecker::~WriterChecker() {
    QI_LOG("end writing");
    /* for next writer */
    ::writing_mutex.unlock();
    /* update wcounter */
    {
        std::lock_guard<std::mutex> lock(::writer_counter_mutex);
        ::writer_counter--;
        if (::writer_counter == 0) {
            ::reading_mutex.unlock();
            ::new_reader_mutex.unlock();
        }
    }
}

ReaderChecker::ReaderChecker() {
    { std::lock_guard<std::mutex> lock(::new_reader_mutex); }
    {
        /* 2-n reader waiting here */
        std::lock_guard<std::mutex> lock(::reader_counter_mutex);
        ::reader_counter++;
        /* the first reader wait for*/
        if (::reader_counter == 1) {
            /* the first reader wait for writers */
            QI_LOG("start waitting for writing");
            ::reading_mutex.lock();
            QI_LOG("end waitting for writing");
        }
    }
    QI_LOG("start reading");
}

ReaderChecker::~ReaderChecker() {
    QI_LOG("end reading");
    /* update rc */
    {
        std::lock_guard<std::mutex> lock(::reader_counter_mutex);
        ::reader_counter--;
        if (::reader_counter == 0) {
            ::reading_mutex.unlock();
        }
    }
}
