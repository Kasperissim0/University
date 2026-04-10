Task 4
 task4
(*) If an int array contains n distinct values, each of which occurs an even number of times, the array can be divided into parts by a maximum of n cuts such that exactly half of each of the n values ​​are in the even-numbered parts and the other half is in the odd-numbered parts. E.g.:
{1,2,2,1,1,1,2,2} can be divided into {1} {2,2,1,1} {1,2,2}.
In the first and third part there are exactly as many ones and twos as in the second part.
Write a function that takes an array of int values ​​and their length as parameters, determines how many different values ​​are contained, whether division is possible (i.e. each value occurs an even number of times; if not, throw an exception throw) and returns a vector of ints containing the indices at which the array needs to be split (in the example above, the vector {1,5} would be returned).

https://moodle.univie.ac.at/mod/extserver/view.php?id=19368923&lang=en