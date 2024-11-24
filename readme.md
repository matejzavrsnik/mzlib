 
# What is mzlib?

It is a library containing a reusable collection of snippets I have written over time. It is my hobby project on its own and a side effect of other hobby projects. When I write software, I like to write it in a way that can be generalised and put into a library to be reused. This is it.

Most of this library was written either tired in the evening or overexcited during weekends. Parts of it were just meant as a joke. Over-engineering amuses me. Some of it will be reimplementations of things that already exist in other libraries, but I wanted to do it myself in order to learn.

# What's the point then?

- fun
- learning how difficult it would be to write X
- proof of concept for my ideas
- being as persnickety as I want without wasting my employer's time
- practising my C++-fu
- solving interesting problems that were not worth solving at work
- a playground to take new language features for a spin
- something that doesn't need to be released on an overly optimistic date so that I can stop and endulge in researching anything I find intriguing
- transfer of useful code between my hobby projects
- sharing code with others to aid discussion about specific programming topics
- a backup location for some of my code

# How to use it

Doesn't need to be compiled because it's meant as a header-only library. That makes it easier to transfer the code to other contexts. Just copy paste the code into your project, or copy the files across and include them. Or get the whole repo and include from there.

You can compile mzlib, but that will compile the unit tests rather than create an .so or an .dll to be linked.

# Design guidelines

  - It is as copy/pastable to another context as possible. Like a collection of code snippets, but organised.
  - Header-only library. Makes it easier to move around and doesn't need the latest compiler to compile just one header file.
  - Follow the STL look and feel:
    - users should not be paying what they don't use
    - not a framework; uses templates instead where possible
    - write for iterators when possible, not whole containers
  - aim for 100% unit test coverage, unless it's not fun anymore
  - enforce correctness in compile time as much as possible
  - never-mind if it doesn't build on Windows and old compilers, too much hassle
  - solving problems with free functions as much as possible because they are easiest to test and reuse

# Licence

I reserve all rights for the code that I wrote. This is not because I don't want anybody to use it, I'd just like to know who needs it and why before I give it away. Contact me.

There are snippets of code in here that are not written by me, but they are clearly marked and attributed. Needless to say, I claim no rights over that code.

# Documentation

Doxygen. Below is an example to be used.

Reason to document is to get as much help in the tooltip as possible and to possibly some day generate entire list of all that's there.

I like comments on arguments inline because it makes it harder to inadvertently diverge the two.

Didn't find a good way to document templated stuff, so using HTML less-then tag for now.

    /**
     * @brief Brief
     * @details Details
     * @tparam Template extended_setting
     * @example
     * \code{.cpp}
     * std::vector &lt; std::string> var;
     * fun(var);
     * \endcode
     * @return Return
     */
    int fun(
       std::string& str, /**< [in/out] Str */
       int size /**< [in] Size */ 
    )
    {} 

# Folder structure

- **cmake** stuff needed for conan+cmake
- **doc** additional documentation that didn't fit in the comments
- **test_data** content needed for testing. Yes, unit tests are great, but at some point it's good to see stuff actually gets written to the disk, for example.
- **include** header files with actual code and tests for it
  - **abstract** highly abstract stuff
  - **apps** functions that could've been small apps if compiled on their own
  - **extension** snippets that are extending other libraries rather than just standard one. There will be a sub-folder for each such other library.
  - **filesystem** snippets to do with filesystem
  - **greatest_hits** textbook algorithms
  - **iterators** operations on iterators
  - **joke** bare jokes man
  - **lang** snippets that improve (or otherwise) the use of the language itself rather than perform any useful extrinsic operation
  - **laws** natural "laws", like physical or mathematical
  - **mocks** not a fan of mocks, but sometimes you need them, and here they are
  - **nature** snippets that represent something from the nature
  - **string** string operations; interesting how many of them we need!
  - **tools** generic name for generic operations that didn't fully fit anywhere else

# Include order

1) header of the cpp
2) files from this project
3) files from other projects in same solution
4) 3rdParty libraries
   1) my libraries
   2) other libraries
5) standard library

# Style

- snake case in my code
- interfaces prefixed with i_
- classes not prefixed with anything
- for external libraries, whatever case is natural to that library
- two empty lines between functions
- unit tests are in cpp files, code in h, both in same folder to be near each other
- one thing per file, even if it is small (unless it is tiny).
- functions named is_ return boolean information

# 3rdparty stuff used

- **gtest** for testing
- **libxmlpp** for testing the extensions of libxmlpp

# 3rdparty source preference

1) conan
2) submodule in 3rdparty
3) system install

If I can, I stick to these separately for different OSes.

# Board

I can afford to just have a list of things I want to achieve here rather than something more fancy and less transferable.

🚁 - feature, 🐞 - bug, 🔧 - refactor.

The order implies priority.

Open:
- 🚁 try implementing some of the iterator stuff with ranges to see how it works
