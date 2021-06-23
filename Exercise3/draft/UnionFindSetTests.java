package orderedarray;

import java.util.Comparator;
import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;

/**
 *
 * @author 
 */
public class UnionFindSetTests {

  class IntegerComparator implements Comparator<Integer> {
    @Override
    public int compare(Integer i1, Integer i2) {
      return i1.compareTo(i2);
    }
  }


  private Integer i1,i2,i3;
  private OrderedArray<Integer> orderedArray;

  @Before
  public void createOrderedArray() throws OrderedArrayException{
    
  }

  @Test
  public void testIsEmpty_zeroEl(){
    
  }

  @Test
  public void testIsEmpty_oneEl() throws Exception{
    
  }


  @Test
  public void testSize_zeroEl() throws Exception{
    
  }

  @Test
  public void testSize_oneEl() throws Exception{
    
  }

  @Test
  public void testSize_twoEl() throws Exception{
    
  }

  @Test
  public void testAddGet_oneEl() throws Exception{
    
  }


  @Test
  public void testArray_threeEl() throws Exception{

  }

}
