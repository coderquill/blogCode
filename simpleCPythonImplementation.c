//Understand the simplified version:
//In a do while loop,

do {

    PyTime_t deadline, monotonic;

    //Sets monotonic value to current time, i.e. current time in monotonic
    //If cant, returns, i.e. less than 0 means past time
    if (PyTime_Monotonic(&monotonic) < 0) {
        return -1;
    }

    //timeout - param for sleep
    deadline = monotonic + timeout;

    int err = 0;
    int ret;


// Release the Global Interpreter Lock (GIL) to allow other threads to run
    Py_BEGIN_ALLOW_THREADS

    // Use nanosleep for sleeping with the timeout specified - system call
    ret = nanosleep(&timeout_ts, NULL);
    err = errno;

// Re-acquire the Global Interpreter Lock (GIL) so the current thread can continue executing Python code
    Py_END_ALLOW_THREADS

    if (ret == 0) {
        // Sleep finished successfully
        break;
    }

    //Sets monotonic value to current time, i.e. current time in monotonic
    //If cant, returns, i.e. less than 0 means past time
    if (PyTime_Monotonic(&monotonic) < 0) {
        return -1;
    }

    timeout = deadline - monotonic;

    //Already past the deadline
    if (timeout < 0) {
        break; // If the remaining timeout is negative, exit the loop
    }

    /* Retry nanosleep with the recomputed delay */
} while (1);
