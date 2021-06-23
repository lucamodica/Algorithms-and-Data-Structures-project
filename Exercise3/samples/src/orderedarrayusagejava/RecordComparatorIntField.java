package orderedarrayusagejava;

import java.util.Comparator;

/**
 *
 * @author magro
 */
public class RecordComparatorIntField implements Comparator<Record>{
  @Override
  public int compare(Record r1, Record r2) {
    int result = (new Integer(r1.getIntegerField())).compareTo(r2.getIntegerField());
    if(result != 0)
      return result;
    return (String.CASE_INSENSITIVE_ORDER).compare(r1.getStringField(), r2.getStringField());
   }
}
