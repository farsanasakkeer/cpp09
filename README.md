# cpp09-ex00

The line `std::map<std::string, double> database;` declares a `std::map` named `database` that stores key-value pairs where:

- The **key** is a `std::string` (date).
- The **value** is a `double` (exchange rate).


- A `std::map` is an associative container that stores elements in a key-value pair format.
- The keys in a `std::map` are unique, meaning that each key can only appear once in the map.
- The map automatically keeps its elements sorted by the key.




```
size_t delimiterPosition = line.find(",");
std::string date = line.substr(0, delimiterPosition);
std::string rate = line.substr(delimiterPosition + 1);
database.insert(std::make_pair(date, atof(rate.c_str())));
```


   ```
   size_t delimiterPosition = line.find(",");
   ```
   - `line.find(",")` searches for the first occurrence of a comma in the string `line`.
   - `delimiterPosition` stores the index of the comma in the line.

   ```
   std::string date = line.substr(0, delimiterPosition);
   ```
   - `line.substr(0, delimiterPosition)` extracts the substring from the start of the string up to the position of the comma.
   - This substring is stored in the `date` variable, representing the date from your data file (e.g., `"2010-08-14"`).


   ```
   std::string rate = line.substr(delimiterPosition + 1);
   ```
   - `line.substr(delimiterPosition + 1)` extracts the substring starting just after the comma to the end of the line.
   - This substring is stored in the `rate` variable, representing the rate from your data file (e.g., `"0"` or `"0.07"`).

**Inserting into the Database:**
   ```
   database.insert(std::make_pair(date, atof(rate.c_str())));
   ```
   - `std::make_pair(date, atof(rate.c_str()))` creates a pair where the first element is the `date` and the second element is the `rate` converted to a `float` (or `double`) using `atof`.
   - `database.insert(...)` inserts this pair into the `database`.

### Example
For the line `"2010-08-14,0"`:
- `delimiterPosition` would be `10` (the position of the comma).
- `date` would be `"2010-08-14"`.
- `rate` would be `"0"`.
- The pair `("2010-08-14", 0.0)` would be inserted into the `database`.

