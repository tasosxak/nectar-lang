# nectar

Nectar is a new general-purposed programming language. It comprises a combination of both high-level and low-level language features. Nectar supports object-orentied and procedural programming.

Nectar's futures include:
* **Portability** : The compiler of Nectar produces bytecode for colibri virtual machine. So you can execute the same bytecode
files on a wide variety of different platforms (Windows,Linux,MacOS etc).
* **Scalability** : You can add libraries and Nectar provides better structure for .
* **Learnability** : Nectar has clean and easy syntax that allows new developers to learn quickly and easy.
* **Readability** : Nectar has similar syntax to that of many programming languages (such a Javascript,Ruby, Swift,C++,Java).


# Installation

* **Linux** :
  > git clone  https://github.com/tasosxak/nectar-lang.git
  
  > cd nectar-lang
  
  > sudo ./init.sh
  
  
  (The downloaded file has already the executable files so it is not necessary to run the last command.)
 
# Create new project
Writing the below command you can create a new project:

> nectar create nameofproject

The above command creates the below project tree:
```
nameofproject
    |
    |__ src
          |__ nameofproject.nr
    |
    |__ exec
```

* src : This folder includes all sources files of project.
* exec: This folder include the executable file (.cex) of project.


If you open the `nameofproject.nr` file in `src` folder you will see the below snippet of code:

```swift
func main()->int {
  say "Hello world!"
  return 0
}
```
# Build your project
After project creation let's see how to build it. Writing the below command you can build your project:
> nectar build nameofproject

The above command initially calls the prenectar program to unite all the nectar files of your project and saves the result in the `final.nrf` file. After this, the nectar compiler is called, which it produces the bytecode in `nameofproject.cex`. The `nameofproject.cex` is stored in `exec` folder.

# Run your project
After project build let's see how to run it. Writing the below command you can run your project:
> nectar run nameofproject

The above command calls the colibri virtual machine with `nameofproject.cex` as input. Colibri-VM executes the bytecode.

# Keywords
The first step of compilation named "Lexical Analysis" and splits the input file to tokens.
In this phase, the compiler recognizes the reserved keywords which are:


```
false    true    int     return     if 
else     while   break   print      read
println  times   use     unless     not
and      or      real    puts       bool
func     class   pub     abstract   var
```
# Syntax
Let's see some commands.
In nectar you can declare functions, classes and variables.
The execution of nectar program starts from the main function which is one and only one.

* **Class Declaration**:

```swift
pub class Person{

  @name:string
  @age:int
  
  pub new(string name,int age) -> int {
      self.name = name
      self.age = age
      
      return 0
  }
  
}

func main()->int {
  var alice:Person = Person.new("alice",18)
  15 times say "hello world!"
  
  return 0
}
```
* **Fields**:
```ruby
@age:int
```
With the above way you can declare a field in class. Fields are strictly private.

* **Methods**:
```rust
  pub new(string name,int age) -> int {
      self.name = name
      self.age = age
      
      return 0
  }
```
Methods are by default private. You can make them public by adding the keyword `pub` to the beginning of declaration.

* **Functions**:
```swift
func main()->int {
  var alice:Person = Person.new("alice",18)
  15 times say "hello world!"
  
  return 0
}
```
With the above way you can declare a function in your program.Instead method declaration, the declaration of function starts with the keyword `func`.

* **Variable Declaration**:
```javascript
 var x:int
```
You can declare a variable in methods and functions.

* **Variable Definition & Declaration**:
```javascript
 var x:int = 12
```
You can declare & define a variable in methods and functions.

* **Assignment**:
```javascript
   x = 53
```
* **Math & Assignment**:
```javascript
   x += 53 // x = x + 53
   y -= x  // y = y - x
   z *= y+5  // z = z * ( y+ 5)
   x /= 3  // x = x / 3
   x++  // x = x + 1
   ++x  // x = x + 1
   y** //  y = y*y
   **y //  y = y*y
   z-- // z = z-1
   --z // z = z-1
```
* **Swapping**:
```javascript
   var x:int = 5
   var y:int = 6
   x,y = y,x   // x=6 and y=5
```
* **Print with line**:
```swift
   println "hello world!"
```
Prints out the message "hello world" and new line.

* **Print without line**:
```swift
   print "hello world!"
```
Prints out the message "hello world".

* **Puts**:
```swift
   puts "hello world!"
```
Prints out the message "hello world".

* **Read**:
```swift
   read "Give me a number: ",x
```
Prints out the message "Give me a number" and waits for input. When the user gives an input and press the enter button,this
command assigns the input to the variable `x`. The command must be assignment, print,read, expression.

* **if statement**:
```swift
   if( age < 18 ) {
      puts "you are kid!"
   }
```
* **if statement with else**:
```swift
   if( age < 18 ) {
      puts "you are kid!"
   }
   else {
      puts "you are man!"
   }
```
* **While loop**:
```swift
   while(counter < 15){
    read "Give me a number", x
    println x
    counter++
   }
```
* **Times loop**:
```swift
   15 times puts "Hello world"
```

# Single Statements
Single Statements are statements which you can write in one line, fastly.

* **command if expression**:
```C++
   print "Hello world" if x>5
```
This command will execute the code before `if` , if the expression after `if` is true.


* **command unless expression**:
```ruby
   y++ unless x>5
```
This command will execute the code before `unless` , if the expression after `unless` is false.
