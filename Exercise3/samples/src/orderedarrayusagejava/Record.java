package orderedarrayusagejava;

import java.util.Objects;

/**
 *
 * @author magro
 */
public class Record {
  private String stringField = null;
  private int integerField;
  
  
  public Record(String stringField,int integerField){
    this.stringField = stringField;
    this.integerField = integerField;
  }
  
  public String getStringField(){
    return this.stringField;
  }
  
  public int getIntegerField(){
    return this.integerField;
  }
  
  
  @Override
  public boolean equals(Object rec){
    if(!(rec instanceof Record))
      return false;
    return ((this.stringField).equalsIgnoreCase(((Record)rec).getStringField()) && this.integerField == ((Record)rec).getIntegerField());
  }

  @Override
  public int hashCode() {
    int hash = 7;
    hash = 71 * hash + Objects.hashCode(this.stringField);
    hash = 71 * hash + this.integerField;
    return hash;
  }
}
