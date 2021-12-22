import java.lang.Exception;
import java.util.Random;
import java.time.Instant;
import java.time.Clock;
import java.time.Duration;
import java.lang.Thread;

class Coordinator {
  static int size; 
  static int num;
  static int cons;
  static int prods;
  static int seed;

	public static void main(String[] args) {
    if (args.length != 5) {
      System.out.println("Usage: <buffersize> <numitems> <numconsumers> <numproducers> <seed>");
      System.exit(1);
    }

    size = Integer.parseInt(args[0]);
    if (size < 1) {
      System.out.println("Buffer must have at least size of 1");
      System.exit(1);
    }
    num = Integer.parseInt(args[1]);
    cons = Integer.parseInt(args[2]);
    if (cons < 1 || cons > 3) {
      System.out.println("Number of consumers must be 1-3");
      System.exit(1);
    }
    prods = Integer.parseInt(args[3]);
    if (prods < 1 || prods > 3) {
      System.out.println("Number of producers must be 1-3");
      System.exit(1);
    }
    seed = Integer.parseInt(args[4]);

    // instantiating the objects
    Buffer buffer = new Buffer(size);

    Producer ps[] = new Producer[prods];
    Consumer cs[] = new Consumer[cons];
    Thread ts[] = new Thread[prods + cons];

    // Create all threads
    for (int pid = 0; pid <prods; pid++) {
      Thread p = new Thread(ps[pid] = new Producer(buffer, (0 == pid)?(num/prods + num%prods):(num/prods), pid, seed));
      ts[pid] = p;
    }
    for (int cid = 0; cid <cons; cid++) {
      Thread c = new Thread(cs[cid] = new Consumer(buffer, (0 == cid)?(num/cons + num%cons):(num/cons), cid));
      ts[prods + cid] = c;
    }

    // Fire them up
    for (int i=0; i<ts.length; i++) { ts[i].start();}

    // waiting for the threads to join and exiting
    try {
      int sumProd = 0;
      for (int i=0; i<prods; i++) { 
        ts[i].join();
        sumProd += ps[i].getCheckSum();
      }
      System.out.println();
      System.out.println("Producer(s): Finished producing " + num + " items with checksum being " + sumProd);
      int sumCons = 0;
      for (int i=prods; i<ts.length; i++) { 
        ts[i].join();
        sumCons += cs[i-prods].getCheckSum();
      }
      System.out.println("Consumer(s): Finished consuming " + num + " items with checksum being " + sumCons);
    } catch(InterruptedException e) {
      e.printStackTrace();
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