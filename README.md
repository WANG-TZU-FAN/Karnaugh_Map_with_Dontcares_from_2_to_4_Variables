# Karnaugh_Map_with_Dontcares_from_2_to_4_Variables
## Description
###  Write a program to implement a (2~4 Variable) K-Map simplification process.
### The prime implicants and the essential prime implicants of the K-map should be indicated.
### Show the Minimum SOP (Sum of Product).  
## Requirement 
### Read the input file 
#### Your program will read the input file for the minterm information and don’t care term information: 
#### ![image](https://user-images.githubusercontent.com/64151952/114894798-87013c00-9e41-11eb-83c9-d1127704e6b2.png)
#### -v [Variable number]: Variable number, range(2~4) 
#### -m [index, index …]: Minterm value index, range(0~2v-1) 
#### -d [index, index …]: Don’t care index, range(0~2v-1) 
### Initialize the terms in the K-map  
#### You can create one two-dimensional arrays to allocate all the 1, 0, and X (don’t care) terms of K-map. 
#### ![image](https://user-images.githubusercontent.com/64151952/114895154-d5163f80-9e41-11eb-8a94-1621eaaf6163.png)
### Write the output file (Don’t change the format) 
#### What you need to print in the output file:
#### 1. Kmap 
#### 2. Prime implicant 
#### 3. Essential prime implicant 
#### 4. Minimum SOP 
#### ![image](https://user-images.githubusercontent.com/64151952/114895414-11e23680-9e42-11eb-99b6-4853e9d7ea81.png)
#### ![image](https://user-images.githubusercontent.com/64151952/114895443-17d81780-9e42-11eb-9ac6-cd693e530851.png)

 
