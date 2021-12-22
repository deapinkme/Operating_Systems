public class Buffer
{
  // For the homework, since the elements inserted are 0-99, I'll use byte
  private byte[] elements;
  private int head = 0;
  private int tail = -1;
  private int size;
  private int numElements = 0;

  public Byte(int size) {
    this.size = size;
    elements = new byte[size];
  }

  private boolean isFull() {
    return(numElements == size);
  }

  private boolean isEmpty() {
    return(numElements == 0);
  }

  // inserts a buffer element into the circular buffer
  public synchronized void push(byte element)
  {
      if (isFull) wait();
      ++numElements;
      elements[++tail % size] = element;
      notify();
  }

  // removes a buffer element from the circular buffer
  public synchronized byte pop()
  {
      if (isEmpty()) wait();
      --numElements;
      byte r = elements[removeAt++ % fixedSize];
      notify();
      return(r);
  }
}