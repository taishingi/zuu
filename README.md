# What is it ? 

> It's a framework to tests applications written in c.

# Installation

```bash
git clone https://github.com/shingitai/yubel
```

```bash
cd yubel && cmake . && sudo make install
```


# Tests


> Units testing macros 

```c
#include <unit.h>
```

|  macro                            | Do                                                           | Arguments                                              |
|-----------------------------------|--------------------------------------------------------------|--------------------------------------------------------|
|  ok(actual)                       |  test if actual value return true                            | bool                                                   |
|  ko(actual)                       |  test if actual value return false                           | bool                                                   |
|  equals(a,b)                      |  test if values are equals                                   | int|double|float...                                    | 
|  unequals(a,b)                    |  test if values are unequals                                 | int|double|float..                                     |
|  identical(a,b)                   |  test if two values are identical                            | char *|const char *                                    |
|  differrent(a,b)                  |  test if two values are different                            | char *|const char *                                    |
|  def(actual)                      |  test if values are defined                                  | void *                                                 |
|  undef(actual)                    |  test if values are not defined                              | void *                                                 |
|  empty(actual)                    |  test if values is empty                                     | char *|const char *                                    |
|  full(actual,max)                 |  test if the value is at the maximum value                   | char *|const char *                                    |
|  scenario(description,f)          |  group logic test in a function                              | char *|const char *, void (*f)(void)                   |
|  theory(description,expected,f)   |  check if a theory is true or false                          | char *|const char *,bool,void*                         | 
|  is(a,b)                          |  check if a value is equal to an value                       | char *|const char *,bool,void*                         |
|  not(a,b)                         |  check if a value is not equal to an another value           | char *|const char *,bool,void*                         |
```
# The unit minimum test code

```c
#include <yugi.h>

/**
 * 
 * Function executed before all tests
 * 
 **/
void before_all(void)
{

}

/**
 * 
 * Function excecuted before a test
 * 
 **/ 
void before(void)
{

}

/**
 * 
 * Function executed after a test
 * 
 **/
void after(void)
{

}

/**
 * 
 * Function executed after all test
 * 
 **/
void after_all(void)
{
    
}

int main(void)
{
    return status;
}
```

# Test usage

```bash 
oh *.c
```