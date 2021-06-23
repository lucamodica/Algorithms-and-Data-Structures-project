package orderedarray;

import java.util.ArrayList;
import java.util.Comparator;

/**
 *
 * @author magro
 * @param <T>: type of the ordered array elements
 */
public class OrderedArray<T> {
  private ArrayList<T> array = null;
  private Comparator<? super T> comparator = null;

  /**
   * It creates an empty ordered array.
   * It accepts as input a comparator implementing the
   * precedence relation between the array elements.
   * @param comparator: a comparator implementing the precedence relation between the array elements.
   * @throws OrderedArrayEception if the parameter is null.
   */
  public OrderedArray(Comparator<? super T> comparator) throws OrderedArrayException{
    if(comparator == null) throw new OrderedArrayException("OrderedArray constructor: comparator parameter cannot be null");
    this.array = new ArrayList<>();
    this.comparator = comparator;
  }

  /**
  * @return true iff this ordered array is empty
  */
   public boolean isEmpty(){
    return (this.array).isEmpty();
  }

  /**
  * @return: the number of elements currently stored in this ordered array.
  */
  public int size(){
    return (this.array).size();
  }


  /**
  * It adds the specified element to the ordered array in the right position.
  * @param element: the element to be added
  * @throws orderedarray.OrderedArrayException iff the parameter is null
  */
  public void add(T element) throws OrderedArrayException{
    if(element == null)
      throw new OrderedArrayException("addElement: element parameter cannot be null");

    int index = getIndexInsert(element);

    (this.array).add(index, element);
  }

  /**
  *
  * @param i: index of the element that should be returned
  * @return: the element at index i
  * @throws OrderedArrayException iff i is out og the array bounds
  */
  public T get(int i) throws OrderedArrayException{
    if(i<0 || i>=(this.array).size()) throw new OrderedArrayException("Index "+i+"is out of the array bounds");

    return (this.array).get(i);
  }



  //returns the position where the new element must be inserted
  private int getIndexInsert(T element){
    int index = 0;
    boolean cont = true;
   T currEl = null;
   while((index<(this.array).size())&&cont){
     currEl = (this.array).get(index);
     if((this.comparator).compare(element, currEl)<0)
       cont = false;
     else index++;
    }//while

    return index;
  }
}
