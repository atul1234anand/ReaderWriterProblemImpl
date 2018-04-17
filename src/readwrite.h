#pragma once

namespace readwrite {
class WriterChecker {
public:
    WriterChecker();
    ~WriterChecker();
};

class ReaderChecker {
public:
    ReaderChecker();
    ~ReaderChecker();
};

#define WRITE_LOCK_GUARD_ WriterChecker wc;
#define READ_LOCK_GUARD_ ReaderChecker rc;
}  // namespace readwrite

