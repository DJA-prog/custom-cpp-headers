# Curl = Client URL or Command-line URL

# curl_wrapper.h

# CurlWrapper Datasheet
## Description
The CurlWrapper class provides a simple and convenient wrapper around the libcurl library for making HTTP requests in C++. It allows you to fetch the contents of a URL and retrieve the response as a string.

## Installation
To use the CurlWrapper class, you need to have the libcurl library installed on your Linux system. You can install it by running the following command:
```
    sudo apt install libcurl4-openssl-dev
```

## Compilation
To compile your code that uses the CurlWrapper class, you need to link against the libcurl library. You can use the following command:
```
    g++ -o main main.cpp curl_wrapper.cpp -lcurl
```

## Usage
To use the CurlWrapper class in your code, you need to include the "curl_wrapper.h" header file. Here's an example of how to use the CurlWrapper class:
```
#include "curl_wrapper.h"

int main() {
    CurlWrapper curl;
    std::string response = curl.fetchUrl("https://www.example.com");
    std::cout << response << std::endl;
    return 0;
}
```
In the example above, we create an instance of the CurlWrapper class called curl. We then use the fetchUrl function to fetch the contents of the specified URL ("https://www.example.com") and store the response in the response string. Finally, we print the response to the console.

## Class Members
## CurlWrapper()
- Constructor for the CurlWrapper class.
- Initializes the libcurl library and creates a CURL handle.

## ~CurlWrapper()
- Destructor for the CurlWrapper class.
- Cleans up the CURL handle and frees resources.

## std::string fetchUrl(const std::string& url)
- Fetches the contents of the specified URL.
- Parameters:
    - url: The URL to fetch.
- Returns:
    - A string containing the response from the URL.
- Note:
    - If an error occurs during the HTTP request, an error message will be printed to the standard error stream.

## static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata)
- Callback function used by libcurl to write the received data.
- Parameters:
    - ptr: A pointer to the received data buffer.
    - size: The size of each data element.
    - nmemb: The number of data elements.
    - userdata: A pointer to user-specific data.

- Returns:
    - The total number of bytes written.
- Note:
    - This function is used internally by the fetchUrl function and should not be called directly.

## Example
Here's a complete example demonstrating the usage of the CurlWrapper class:
```
#include "curl_wrapper.h"

int main() {
    CurlWrapper curl;
    std::string response = curl.fetchUrl("https://www.example.com");
    std::cout << response << std::endl;
    return 0;
}
```
In this example, we fetch the contents of "https://www.example.com" and print the response to the console.

## Dependencies
- libcurl: The libcurl library is required to compile and use the CurlWrapper class. Make sure it is installed on your system.

### License
This code is provided under the MIT license. Feel free to modify and use it in your projects.

# curl.hpp

# cURL Wrapper Datasheet
## Description
The curl function provides a convenient way to fetch the content of a URL using the cURL library in C++. It takes a URL as input and returns the response as a string.

## Dependencies
To use this cURL wrapper, you need to have the cURL library installed on your system. Use the following command to install the required header files and libraries:
```
    sudo apt install libcurl4-openssl-dev
```

## Usage
1. Include the curl.hpp header file in your C++ code:
```
    #include "curl.hpp"
```

2. Call the curl function with the desired URL as the argument:
```
    std::string url = "https://www.example.com";
    std::string *response = curl(url);
```

3. Access the response string by dereferencing the pointer:
```
    std::cout << *response << std::endl;
```

## Example
Here's an example of how to use the curl function:
```
#include <iostream>
#include "curl.hpp"

int main()
{
    std::string url = "https://www.example.com";
    std::string *response = curl(url);
    std::cout << *response << std::endl;
    return 0;
}
```

## Compilation and Execution
To compile and run the code, use the following commands:
```
g++ curl_example.cpp -o curl_example -lcurl
./curl_example
```
Make sure to replace curl_example.cpp with the name of your C++ file if it's different.

Please note that this code assumes you have the cURL library installed and properly linked during the compilation process.