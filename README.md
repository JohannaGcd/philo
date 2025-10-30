# philo
This project is about simulating philosophers who: Sit around a table - Alternate between thinking, eating, and sleeping. - Need two forks (shared resources) to eat. It’s a synchronization problem : the goal is to learn how to coordinate concurrent access to shared resources (using mutexes) while preventing race conditions.

Todo:
- 1. parsing. 
Check valid input:  The program will receive 4 or 5 arguments so the first thing should be to throw an error if we receive more or less. 
    Example:
    5 — The number of philosophers
    800 — The time a philosopher will die if he doesn’t eat
    200 — The time it takes a philosopher to eat
    200 — The time it takes a philosopher to sleep
    7 — Number of times all the philosophers need to eat before terminating the program (optional - If provided, the simulation will end when every philosopher has eaten this number of times; if not specified, it will end when any philosopher dies.).

So we need to check that the input contains only numbers, they should all be bigger than 0 except the number of meals each philo needs to eat (edge case), and check for max limit (cf. subject) 200 philos. Make sure to print “Warning message” in case of undefined input.

- 2. Set structures: for the table, each philo, and forks.
- 3. Data Initialization: make sure you create exit functions to clean any allocated memory in case of error.
- 4. Thread creation, philo routine and monitoring. Now we need to create the threads and join them. We will create as many threads as philosophers we have, each philo needs to be a thread and we will create an extra thread (I called it faucheuse) which will monitor everything. Each philo thread will run the philo routine function and the observer will run the monitor function. 
    - The routine is the function executed over and over by the philos: Create a loop that will break as soon as the dead flag is set to true, in other words as soon as a philo is dead (cf. subject)
    - So in our loop, they will eat, sleep and think. 
    - Monitor (faucheuse): This thread will be running and monitoring the whole program, it has 2 checks in it that run infinitely until a philo dies or they all ate the number of meals they need to. Basically, we will check that the time a philo needs to die didn’t surpass the last meal he had. If he indeed died we change the dead flag to true and that will break the loop in all of the threads. The other check is to see if all the philos finished eating the amount of meals they need to, and if they did we will again change the dead flag to one and break the threads loop. 
    - Output: 
    *Timestamp: Shows the time in milliseconds since the simulation started.
    *Philosopher Number: Indicates which philosopher is taking the action.
    *Actions: Includes messages like “has taken a fork,” “is eating,” “is sleeping,” “is thinking,” and “died."
    *Each action has to be in a separate line.
    *Don’t delay the dying message; it must be displayed instantly, not more than 10ms after the actual time of death.
- 5. The last step is to destroy all the mutexes you initialized and free all the data allocated.
- 6. you probably need a customised usleep and get_current time function. Otherwise, you can make use of the allowed function in the subject (memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy,pthread_mutex_lock, pthread_mutex_unlock)

Tips to consider:
- Ensure that all threads are created before starting the simulation, otherwise, you have to wait until all threads are ready (so coordinate the start time with a safety padding to ensure all threads are ready).
- think through the strategy to assign forks: i used an odd/even strategy, where an odd philo would take the left fork first and inversely for even philo. 
- When you start the simulation, all philos will be reaching for their forks at the same time. You need to include a small usleep(1) or order odd philos to start thinking, while even philos would start with eating.
- Consider the edge case of 1 philo, what should be done.
- Ensure the code is free from data races, deadlocks, and memory leaks. You can use :
    — DRD: Run with valgrind --tool=drd to check for data races.
    — Helgrind: Run with valgrind --tool=helgrind to find lock issues and potential deadlocks.
    — FSanitise: Compile with -fsanitize=thread to detect threading problems while running

Resources:
- Medium: https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
- Medium: https://medium.com/@denaelgammal/dining-philosophers-problem-42-project-guide-mandatory-part-a20fb8dc530e
- Best tutorial: https://42-cursus.gitbook.io/guide/3-rank-03/philosophers/functions-used - covers all concepts
- video: covers all concepts https://youtu.be/UGQsvVKwe90?si=SVwpfelRf4rHTk1R
- Visualizer: https://nafuka11.github.io/philosophers-visualizer/
- Tester: https://github.com/dantonik/42-philosophers-tester - good tester, but I would also run the tests myself cause it only checks whether the philo dies or not, but not whether the output makes sense -I had a bunch of extra prints which the tester wouldn't catch. 