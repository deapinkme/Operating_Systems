public class Consumer implements Runnable
{
    private static final int LIMIT = 1000000; // total number of buffer elements to be consumed

    private BoundedBuffer boundedBuffer; // the bounded buffer object
    private int numberOfItemsConsumed; // counter to keep track of the number of items consumed
    private double bufferValueCounter = 0; // keeps a track of the cumulative sum of buffer values

    public Consumer(BoundedBuffer boundedBuffer)
    {
        this.boundedBuffer = boundedBuffer;
    }

    @Override
    public synchronized void run()
    {
        for(numberOfItemsConsumed = 1; numberOfItemsConsumed <= LIMIT; ++numberOfItemsConsumed)
        {
            // consumes the buffer elements
            double bufferElement = boundedBuffer.pop();
            bufferValueCounter += bufferElement;

            // prints the value of the counters every time 100000 elements are consumed
            if(numberOfItemsConsumed % 100000 == 0)
            {
                System.out.printf("Consumer: Consumed %d items, Cumulative value of consumed items=%.3f\n", numberOfItemsConsumed, bufferValueCounter);
            }
        }

        // finished
        System.out.println("Consumer: Finished consuming 1000000 items");
    }
}