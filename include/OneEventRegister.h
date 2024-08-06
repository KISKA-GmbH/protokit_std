//
// Created by f.wimmer on 7/11/2024.
//

#ifndef PROTOKIT_STD_ONEEVENTREGISTER_H
#define PROTOKIT_STD_ONEEVENTREGISTER_H

/**
 * One variable readable, will return the current value of an event.
 * @tparam T
 */
template <typename T>
class EventStoreReadable {
public:
    virtual T collect() = 0;
    virtual ~EventStoreReadable() = default;
};

/**
 * One variable writable, will set or clear the event.
 */
class OneEventStoreWritable {
public:
    virtual void set() = 0;
    virtual void clear() = 0;

    virtual ~OneEventStoreWritable() = default;
};

#endif //PROTOKIT_STD_ONEEVENTREGISTER_H
