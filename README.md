# philo
This project is about simulating philosophers who: Sit around a table - Alternate between thinking, eating, and sleeping. - Need two forks (shared resources) to eat. It’s a synchronization problem : the goal is to learn how to coordinate concurrent access to shared resources (using mutexes) while preventing race conditions.

Todo:
- 1. parsing. check valid input:  The program will receive 4 or 5 arguments so the first thing should be to throw an error if we receive more or less. 
    Example:
    5 — The number of philosophers
    800 — The time a philosopher will die if he doesn’t eat
    200 — The time it takes a philosopher to eat
    200 — The time it takes a philosopher to sleep
    7 — Number of times all the philosophers need to eat before terminating the program (optional - If provided, the simulation will end when every philosopher has eaten this number of times; if not specified, it will end when any philosopher dies.).  Make sure to print “Warning message” in case of undefined input 
So we need to check that the input contains only numbers, they should all be bigger than 0 except the number of meals each philo needs to eat (edge case), and check for max limit (cf. subject) 200 philos.
- 2. Set structures: for each philo, and for shared info
- 3. initialization:  either you can avoid dealing with leaks, freeing, and allocating, you can use a stack, using arrays. But we don't want that.
- 4. Thread creation, philo routine and monitoring. Now we need to create the threads and join them. We will create as many threads as philosophers we have, each philo needs to be a thread and we will create an extra thread (I called it observer) which will monitor everything. Each philo thread will run the philo routine function and the observer will run the monitor function. (is the observer needed?)
    - The routine is the function executed over and over by the philos. Create a loop that will break as soon as the dead flag is 1, in other words as soon as a philo is dead (cf. subject)
    - So in our loop, they will eat, sleep and think. So in our loop, they will eat, sleep and think. 
    - monitor: This thread will be running and monitoring the whole program, it has 2 checks in it that run infinitely until a philo dies or they all ate the number of meals they need to (last input argument). Basically, we will check that the time a philo needs to die didn’t surpass the last meal he had and that he is not concurrently eating. If he indeed died we change the dead flag to 1 and that will break the loop in all of the threads. The other check is to see if all the philos finished eating the amount of meals they need to, and if they did we will again change the dead flag to one and break the threads loop. --> might not be needed, especially if we have an efficient allocating strategy for the forks? Might help to monitor who has waited the longest to prevent starvation.
    - Output: 
    *Timestamp: Shows the time in milliseconds since the simulation started.
    *Philosopher Number: Indicates which philosopher is taking the action.
    *Actions: Includes messages like “has taken a fork,” “is eating,” “is sleeping,” “is thinking,” and “died."
    *Each action has to be in a separate line.
    *Don’t delay the dying message; it must be displayed instantly, not more than 10ms after the actual time of death.
- 5. The last step is to Destroy all the mutexes you initialized and free all the data allocated.
- 6. you probably need a customised usleep and get_current time function. Otherwise, you can make use of the allowed function in the subject (memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock)


Tips to consider:
- Ensure that all threads are created before starting the simulation, otherwise, you have to wait until all threads are ready.
- Consider the case of 1 philo, what should be done
- How can you identify the dead philosophers, and what steps should be taken in this scenario? One solution is to create a death monitoring thread to track each philosopher by calculating starving duration, or you might consider an alternative strategy. If a philosopher dies, the simulation must be terminated.
- Ensure the code is free from data races, deadlocks, and memory leaks. You can use :
    — DRD: Run with valgrind --tool=drd to check for data races.
    — Helgrind: Run with valgrind --tool=helgrind to find lock issues and potential deadlocks.
    — FSanitise: Compile with -fsanitize=thread to detect threading problems while running
    
    what about allocating strategy ? use odd even or Resource ordering
Always lock lower-index fork first

Resources:
- Medium: https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
- Medium: https://medium.com/@denaelgammal/dining-philosophers-problem-42-project-guide-mandatory-part-a20fb8dc530e
- best tutorial: https://42-cursus.gitbook.io/guide/3-rank-03/philosophers/functions-used - covers all concepts
- video: covers all concepts https://youtu.be/UGQsvVKwe90?si=SVwpfelRf4rHTk1R

- Visualizer: https://nafuka11.github.io/philosophers-visualizer/