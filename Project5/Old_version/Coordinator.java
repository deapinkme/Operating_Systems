import java.lang.Exception;
import java.util.Random;
import java.time.Instant;
import java.time.Clock;
import java.time.Duration;

class Coordinator {
	public static void main(String[] args) {
    // instantiating the objects
    BoundedBuffer boundedBuffer = new BoundedBuffer();
    Thread producer = new Thread(new Producer(boundedBuffer));
    Thread consumer = new Thread(new Consumer(boundedBuffer));

    // starts the threads
    producer.start();
    consumer.start();

    // waiting for the threads to join and exiting
    try
    {
        producer.join();
        consumer.join();
    }
    catch(InterruptedException e)
    {
        e.printStackTrace();
    }

    System.out.println("Exiting!");
	}
}

	//Call this function from your producer or your consumer to get the time stamp to be displayed
	public static String getTime() {
		Clock offsetClock = Clock.offset(Clock.systemUTC(), Duration.ofHours(-9));
		Instant time = Instant.now(offsetClock);
		String timeString = time.toString();
		timeString = timeString.replace('T', ' ');
		timeString = timeString.replace('Z', ' ');
		return(timeString);
	}
}