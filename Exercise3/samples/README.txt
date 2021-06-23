****COMPILAZIONE***

----PER COMPILARE LE CLASSI PER LA STRUTTURA DATI OrderedArray NEL PACKAGE orderedarray---
1) posizionarsi in .../OrderedArray_Java/src
2) javac -d ../classes orderedarray/OrderedArray.java

---PER COMPILARE IL PACKAGE orderedarrayusagejava---
1) posizionarsi in .../OrderedArray_Java/src
2) javac -d ../classes orderedarrayusagejava/OrderedArrayUsageJava.java

---PER COMPILARE LE CLASSI PER GLI UNIT TEST NEL PACKAGE orderedarray---
1) posizionarsi in .../OrderedArray_Java/src
2) javac -d ../classes -cp '.;../junit-4.12.jar;../hamcrest-core-1.3.jar' orderedarray/*.java (ATTENZIONE: i classpath devono essere separati da ";" come in Windows, non da ":" come in Unix, inoltre, occorre mettere l'elenco dei classpath fra apici semplici!)


***ESECUZIONE***

---PER ESEGUIRE orderedarrayusagejava/OrderedArrayUsageJava---
1) posizionarsi in .../OrderedArray_Java/classes
2) java orderedarrayusagejava/OrderedArrayUsageJava "../../ordered_array_sample_file.csv"

---PER ESEGUIRE orderedarray/OrderedArrayJava_TestsRunner---
1) posizionarsi in .../OrderedArray_Java/classes
2) java -cp '.;../junit-4.12.jar;../hamcrest-core-1.3.jar'  orderedarray/OrderedArrayJava_TestsRunner
