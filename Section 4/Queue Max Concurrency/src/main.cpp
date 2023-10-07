#include "queue.h"

int main()
{
    sequentialQueue<int> queue;
    queue.push(5645);
    queue.push(87456);
    queue.push(94564);
    queue.push(2347);
    queue.push(634);

    queue.printData();

    cout << "Removing: " << *(queue.pop().get()) << endl;
    cout << "Removing: " << *(queue.pop().get()) << endl;
    queue.printData();
    return EXIT_SUCCESS;
}