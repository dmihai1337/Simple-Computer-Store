# Simple-Computer-Store

A terminal based application to build a PC by choosing the desired components. Application built while learning C++.


## What does it do

- offers necessary components for building a personal computer
- sorts those components according to price or performance
- offers possibility to create a WISHLIST
- calculates a total price in EUR

## How to run

Download project folder and enter following commands in the terminal:

    g++ main.cpp
    ./a.out
    
Then just use the keyboard to navigate through the menu and enjoy building your PC!

## Observations
### Codes
- processors:    0xxxxx
- ram memory:    1xxxxx
- rom memory:    2xxxxx
- graphics card: 3xxxxx

### Files:
- each component has a dedicated text file which represents the store stock
- the first line in each file is an integer representing the number of the specific components available in store, and then:
- name
- feature (clock speed / memory / memory clock)
- code
- price
