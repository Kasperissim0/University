//§ Requisities
  //§ Includes
    #include <cstddef>
    #include <iostream>
    #include <fstream>
    #include <filesystem>
  //.
  //§ Aliases
    using namespace std;
    namespace fs = filesystem;
    using st = size_t;
  //.
//.
st lengthOfSubArrayMeetingCondition(const st arr[], const st amountOfElements, const st sumLessOrEqualTo) {
  const st *start = arr, *end = start; 
  st sum = 0, length = 0; 

  while   (end < (arr + amountOfElements)) {
                                                          sum += *(end++);
    while (sum > sumLessOrEqualTo)                        sum -= *(start++);
                                                          length = max<st>(length, end - start);
    if    (length >= (amountOfElements - (start - arr)))  break;
  } return length;
}
int main() { // output: 506128108109782787219207541247589993221416922442134626965530
  ifstream dataSource(fs::path("/Users/kasperissim0/Code/Archive/University/2026s/ads1/challenge/task-1/input.txt")); 
  st amountOfArrays; dataSource >> amountOfArrays; // if this is meant to be tested, then the path for the input file (obviously) needs to be changed 
                                                   // i couldn't get it to work with relative paths for some reason
  for (st currentArrayIndex = 0; currentArrayIndex < amountOfArrays; ++currentArrayIndex) {
    st size, condition; dataSource >> size >> condition; 
    st *currentArray = new st[size];

    for (st i = 0; i < size; ++i) 
      dataSource >> currentArray[i];

    cout << lengthOfSubArrayMeetingCondition(currentArray, size, condition);
    delete[] currentArray;
  } cout << endl;
  dataSource.close();
  return 0;
}