# String calculator
НТ Прогресс test task

#### Build  
```
cmake .
make
build/Calculator
```


#### Tests  
```
cd tests
cmake .
make
./runTests
```


Calculator supports ```+```, ```-```, ```*```, ```/``` operators, ```(```, ```)``` parentheses and float numbers.  
Small syntax sugar expands ```1(2 + 3)``` up to ```1 * (2 + 3)```



#### Examples
Correct expression
```
expression:  1 +(2*(2.5+2.5+(3-2)))-(3/1.5)
result: 11
```

Parentheses error detection  
```
expression:  1 +(2*(2.5+2.5+(3-2))-(3/1.5)
Unmatched parenthese:
        1 +(2*(2.5+2.5+(3-2))-(3/1.5)
                            ^
```

Logic error detection 
```
expression:  1 +(2*(2.5+2.5+(3-)))-(3/1.5)
Logic error:
        1 + ( 2 * ( 2.5 + 2.5 + ( 3 - ) ) ) - ( 3 / 1.5 ) 
                                 ^^^^^^
```

Invalid input detection 
```
Invalid input:
        1 +(2*(2.5+2.5+(3-2)))-(3/x)
                                  ^
```
       
