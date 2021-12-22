import java.util.Random;

public class Producer extends java.lang.Thread {
	//Necessary variables and object declaration
	Random randomWithSeed;

	public Producer(Buffer buff, int count, int id, int seed) {
		//Assign values to the variables
		randomWithSeed = new Random(seed);
	}

	@Override
	public void run() {
		/* Your code goes in here
		*
		*
		*
		--->To generate a value between 0 (inclusive) and 99 (inclusive) using the seeded random  number generator use the following code
		--->          int variable = randomWithSeed.nextInt(100);
		*
		*
		*
		*/

    private static final int LIMIT = 1000000; // total number of buffer elements to be generated

    private BoundedBuffer boundedBuffer; // the bounded buffer object
    private int numberOfItemsGenerated; // counter to keep track of the number of items generated
    private double bufferValueCounter = 0; // keeps a track of the cumulative sum of buffer values

    public Producer(BoundedBuffer boundedBuffer)
    {
        this.boundedBuffer = boundedBuffer;
    }

    @Override
    public void run()
    {
        for(numberOfItemsGenerated = 1; numberOfItemsGenerated <= LIMIT; ++numberOfItemsGenerated)
        {
            // generates and inserts a buffer element
            Random random = new Random();
            Double bufferElement = random.nextDouble() * 100.0;
            boundedBuffer.push(bufferElement);
            bufferValueCounter += bufferElement;

            // prints the value of the counters every time 100000 elements are generated
            if(numberOfItemsGenerated % 100000 == 0)
            {
                System.out.printf("Producer: Generated %d items, Cumulative value of generated items=%.3f\n", numberOfItemsGenerated, bufferValueCounter);
            }
        }

        // finished
        System.out.println("Producer: Finished generating 1000000 items");
    }
	}
}