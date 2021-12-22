public class Buffer
{
  // the circular buffer
  private double[] bufferElements = new double[fixedSize];
  private int removeAt = 0;
  private int addAt = -1;
  private int size = 0;

  private boolean isFull() {
    if (size == fixedSize) return true;
  }

  // returns if the circular buffer is empty
  private boolean isEmpty() {
    if (size == 0) return true;
  }

  // inserts a buffer element into the circular buffer
  public synchronized void push(double bufferElement)
  {
      while(isFull())
      {
          // since it is full,
          // we have to wait
          try
          {
              wait();
          }
          catch(InterruptedException e)
          {
              e.printStackTrace();
          }
      }

      // insertion and notification
      ++size;
      bufferElements[++addAt % fixedSize] = bufferElement;
      notify();
  }

  // removes a buffer element from the circular buffer
  public synchronized double pop()
  {
      while(isEmpty())
      {
          // since it is empty,
          // we have to wait
          try
          {
              wait();
          }
          catch(InterruptedException e)
          {
              e.printStackTrace();
          }
      }

      // removes a buffer element and notifies a waiting thread
      --size;
      notify();
      return bufferElements[removeAt++ % fixedSize];
  }
}