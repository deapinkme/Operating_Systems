public class Buffer
{
  private int[] elements;
  private int head = 0;
  private int tail = -1;
  private int size;
  private int numElements = 0;

  public int getLastHead() { return ((head-1)+size) % size; }

  public int getTail() { return tail; }

  public Buffer(int size) {
    this.size = size;
    elements = new int[size];
  }

  private boolean isFull() {
    return(numElements == size);
  }

  private boolean isEmpty() {
    return(numElements == 0);
  }

  // inserts a buffer element into the circular buffer
  public synchronized void push(int element)
  {
      while (isFull())
      try {
        wait();
      } catch(InterruptedException e) {
        e.printStackTrace();
      }
      ++numElements;
      elements[++tail % size] = element;
      notify();
  }

  // removes a buffer element from the circular buffer
  public synchronized int pop()
  {
      while (isEmpty()) 
      try {
        wait();
      } catch(InterruptedException e) {
        e.printStackTrace();
      }
      --numElements;
      int r = elements[head++ % size];
      notify();
      return(r);
  }
}