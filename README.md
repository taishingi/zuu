# What is it ? 

> It's a framework to tests applications written in c.

# Installation

```bash
    git clone https://github.com/shingitai/yubel
```

```bash
    cd yubel && cmake . && sudo make install
```


# tests
|  Function     | Do                                                           | Arguments                 |            
|---------------|--------------------------------------------------------------|---------------------------|
|  ok           |  test if actual value return true                            | boolean                   |   
|  ko           |  test if actual value return false                           | boolean                   |
|  equals       |  test if values are equals                                   | numbers                   |
|  unequals     |  test if values are unequals                                 | numbers                   |
|  identical    |  test if two values are identical                            | strings                   |
|  differrent   |  test if two values are different                            | strings                   |
|  def          |  test if values are defined                                  | pointer                   |
|  undef        |  test if values are not defined                              | pointer                   |
|  empty        |  test if values is empty                                     | string                    |
|  full         |  test if the value is at the maximum value                   | string                    |
|  scenario     |  group logic test in a function                              | string,pointer            |
|  theory       |  check if a theory is true or false                          | string,bool,pointer       |
|  is           |  check if a value is equal to an value                       | string,bool,pointer       |
|  not          |  check if a value is not equal to an another value           | string,bool,pointer       |

# Minimum test code

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
 * Function executed after al test
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

# Usage

```bash 
    oh *.c
```