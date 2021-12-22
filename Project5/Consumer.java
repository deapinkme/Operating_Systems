public class Consumer implements Runnable
{
  private Buffer buffer;
  private int total;
  private int sum = 0;
  private int id;

  public Consumer(Buffer buffer, int total, int id) {
    this.buffer = buffer;
    this.total = total;
    this.id = id;
  }

  @Override
  public synchronized void run() {
    for (int count = 0; count<total; count++) {
      // generates and inserts a buffer element
      int element = buffer.pop();
      sum += element;
      System.out.println("\033[0;4mConsumer " +  id + " consumed " + String.format("%3d",element) + " from index " + buffer.getLastHead() + "  at time\033[0;0m " + Coordinator.getTime());
      System.out.flush();
    }
  }

  public int getCheckSum() { return sum; }
}