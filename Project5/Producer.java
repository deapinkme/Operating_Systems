import java.util.Random;

public class Producer extends java.lang.Thread {
	//Necessary variables and object declaration
	private Random randomWithSeed;
  private Buffer buffer;
  private int total;
  private int sum = 0;
  private int id;

	public Producer(Buffer buffer, int total, int id, int seed) {
		this.buffer = buffer;
    this.total = total;
    this.id = id;
    randomWithSeed = new Random(seed);
	}

	@Override
	public void run() {
    for (int count = 0; count<total; count++) {
      Random random = new Random();
      int element = random.nextInt(100);
      buffer.push(element);
      sum += element;
      System.out.println("Producer " + id + " inserted " + String.format("%3d",element) + " at   index " + buffer.getTail() + "  at time " + Coordinator.getTime());
      System.out.flush();
    }
	}

    public int getCheckSum() { return sum; }
}