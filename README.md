# ReaderWriterProblemImpl

## Reader

+ multi-reader could read at the same time.

+ if there is a writer, current readers would continue, new readers would be blocked.

## Writer

+ only one writer could write.

+ if there are readers who are reading, wait.

## Usage

+ `./build.sh`. `install-dir/lib/libreadwrite.a` and `install-dir/include/readwrite.h`.

+ add `#define QUICK_DEBUG_LOG` could print debug log(as you see in `log.h`).

+ like `guard`. `readwrite::READ_LOCK_GUARD_` and `READ_LOCK_GUARD_`.

+ demo in `install-dir/bin/rw.out`.
