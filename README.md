> A testing framework

* What it is ?
	* A framework
	* The objectives
* Todo
* Chat
* Todo

# Headers

```c
#include <unit.h> 
``` 

```c
#include <installation.h>
```

# Minimum code

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

## Installation

```bash
curl -fsSL https://raw.githubusercontent.com/shingitai/yubel/master/install | bash
```

