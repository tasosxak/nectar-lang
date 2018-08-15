<p align="center">
  <img src="https://github.com/tasosxak/nectar-lang/blob/master/nectarnewlogo.png/?style=centerme">
</p>

<div align="center">	
<table align="center"><tr>
<td style="border: 0px;"><img src = "https://img.shields.io/badge/build-pass-green.png?longCache=true&style=flat-square"/></td>	<td style="border: 0px;"><img src = "https://img.shields.io/badge/version-0.2-blue.png?longCache=true&style=flat-square"/></td>
<td style="border: 0px;"><img src = "https://img.shields.io/badge/status-unstable-red.png?longCache=true&style=flat-square"/></td>
<td style="border: 0px;"><img src = "https://img.shields.io/badge/platforms-Linux--Windows-yellow.png?longCache=true&style=flat-square"/></td>
<td style="border: 0px;"><img src = "https://img.shields.io/badge/next-30.August-orange.png?longCache=true&style=flat-square"/></td>
</tr></table>
</center>
</div>
<hr>
<i>Nectar is a new general-purposed programming language. It comprises a combination of both high-level and low-level language features. Nectar supports object-orentied and procedural programming.</i>

Nectar's futures include:

| Feature | Description |
| --- | --- |
| **Portability** | The compiler of Nectar produces bytecode for colibri virtual machine. So you can execute the same bytecode files on a wide variety of different platforms (Windows,Linux,MacOS etc).|
| **Scalability** | You can add libraries and Nectar provides better structure for . |
| **Learnability** | Nectar has clean and easy syntax that allows new developers to learn quickly and easy. |
| **Readability** | Nectar has similar syntax to that of many programming languages (such a Javascript,Ruby, Swift,C++,Java). |

# <i class="icon-file"></i> Installation

* **Linux** :
  > $ git clone  https://github.com/tasosxak/nectar-lang.git
  
  > $ cd nectar-lang
  
  > $ sudo ./init.sh
  
  
  (The downloaded file has already the executable files so it is not necessary to run the last command.)
# Version
Υou can check the version of the compiler you are using by typing:

> $ nectar version


# Create new project
Writing the below command you can create a new project:

> $ nectar create name_of_project

The above command creates the below project tree:
```
name_of_project
    |
    |__ src
          |__ name_of_project.nec
    |
    |__ exec
```

* src : This folder includes all sources files of project.
* exec: This folder includes the executable file (.cex) of project.


If you open the `name_of_project.nec` file in `src` folder you will see the below snippet of code:

```coffeescript
func main()->int {
  say "Hello world!";
  return 0;
}
```
# Build your project
After project creation let's see how to build it. Writing the below command you can build your project:
> $ nectar build name_of_project

The above command initially calls the prenectar program to unite all the nectar files of your project and saves the result in the `name_of_project.nectar` file. After this, the nectar compiler is called, which it produces the bytecode in `name_of_project.cex`. The `name_of_project.cex` is stored in `exec` folder.

# Run your project
After project build let's see how to run it. Writing the below command you can run your project:
> $ nectar run name_of_project

The above command calls the colibri virtual machine with `name_of_project.cex` as input. Colibri-VM executes the bytecode.

# Keywords
The first step of compilation named "Lexical Analysis" and splits the input file to tokens.
In this phase, the compiler recognizes the reserved keywords which are:

 Orange | Apple 
 Bread  | Pie 
 Butter | Ice cream 



{| false  || true  ||  int  ||   return  ||   if |-
| else  ||   while ||   break ||  say   ||     read |-
|}
try      times   use     unless     not
and      or      real    puts       bool
func     class   pub     abstract   var

# Syntax
Let's see some commands.
In nectar you can declare functions, classes and variables.
The execution of nectar program starts from the main function which is one and only one.
* **Import libraries**:
```rust
use math
```
With this command you can import other nectar files. You should write use statements at the top of your program.
* **Class Declaration**:

```coffeescript
pub class Person {


	@name:str;
	@surname:str;
	@height:real;
	@age:int;


	pub new(name:str,surname:str,height:real,age:int)->Person {

		@name = name;
		@surname = surname;
		@height = height;
		@age = age;

		return self;
	}

	pub name()->str {
		return @name;
	}

	pub age()->int {
		return @age;
	}

	pub height()->real {
		return @height;
	}


}

func main()-> int {

	var me:Person;
	
	me = Person.new("Tasos","Temperekidis",1.73,21);
	say "My name is " , me.name() , " and I am " , me.age(), " years old!";

	return 0;
}
```
* **Fields**:
```ruby
@age:int;
```
With the above way you can declare a field in class. Fields are strictly private.

* **Methods**:
```coffeescript
  pub new(name:str,surname:str,height:real,age:int)->Person {

	@name = name;
	@surname = surname;
	@height = height;
	@age = age;

	return self;
 }
```
Methods are by default private. You can make them public by adding the keyword `pub` to the beginning of declaration.

* **Shared Methods**:
```coffeescript
class Console {
  $shared
  pub write(msg:str)->str {
    say msg;
    return msg;
   }
}
 
```
Shared methods are functions which you can call them without creating a new object. For example:

```coffeescript
Console.write("Hello world!");
```

* **Functions**:
```coffeescript
func main()-> int {

	var me:Person;

	me = Person.new("Tasos","Temperekidis",1.73,21);
	say "My name is " , me.name() , " and I am " , me.age(), " years old!";

	return 0;
}
```
With the above way you can declare a function in your program.Instead of method declaration, the declaration of function starts with the keyword `func`.

* **Variable Declaration**:
```javascript
 var x:int;
```
You can declare a variable in methods and functions.

* **Variable Definition & Declaration**:
```javascript
 var x:int = 12;
```
You can declare & define a variable in methods and functions.

* **Assignment**:
```javascript
   x = 53;
```
* **Math & Assignment**:
```coffeescript
   x += 53; # x = x + 53
   y -= x;  # y = y - x
   z *= y+5;  # z = z * ( y+ 5)
   x /= 3;  # x = x / 3
   x++;  # x = x + 1
   ++x;  # x = x + 1
   y**; #  y = y*y
   **y; #  y = y*y
   z--; # z = z-1
   --z; # z = z-1
```
* **Division & Integer Division**:

Nectar has two operators for division.

**Division**:
```python
   say 5 / 2;  # 2.5
```

**Integer Division**:
```python
   say 5 // 2; #2
```


* **Swapping**:
```coffeescript
   var x:int = 5;
   var y:int = 6;
   x,y = y,x;   # x=6 and y=5
```
* **Print with new line**:
```coffeescript
   say "hello world!";
```
Prints out the message "hello world!" and new line.

* **Print without new line**:
```coffeescript
   say "hello ", "world ", "!";
```
Prints out the message "hello world !".

* **Read**:
```coffeescript
   read "Give me a number: ",x;
```
Prints out the message "Give me a number" and waits for input. When the user gives an input and press the enter button,this
command assigns the input to the variable `x`. 

* **if statement**:
```coffeescript
   if( age < 18 ) {
      say "you are kid!";
   }
```
* **if statement with else**:
```coffeescript
   if( age < 18 ) {
      say "you are kid!";
   }
   else {
      say "you are man!";
   }
```
* **While loop**:
```coffeescript
   while(counter < 15){
    read "Give me a number", x;
    say x;
    counter++;
   }
```
* **Times loop**:
```coffeescript
   15 times say "Hello world";
```
* **For each iteration**:
```coffeescript
   for word in "hello" {
   	say word;
   }
```
# Single Statements
Single Statements are statements which you can write in one line, fastly.
The command must be assignment, print,read, expression.

* **command if expression**:
```applescript
   say "Hello world" if x>5;
```
This command will execute the code before `if` , if the expression after `if` is true.


* **command unless expression**:
```ruby
   y++ unless x>5;
```
This command will execute the code before `unless` , if the expression after `unless` is false.
# Build-in types

* **String**:

**Adding strings**:
```applescript
   say "Hello " + "World " + "!!!"; # output: Hello World !!!
```
**String multiplication**:
 ```applescript
    say 3 * "Hello!";  # output: Hello!Hello!Hello!
 ```

# What is Colibri?

<p align="center">
  <img src="https://github.com/tasosxak/nectar-lang/blob/master/colibri_plus_nectar.jpg/?style=centerme">
</p>

Colibri is a virtual machine that reads line per line the bytecode and executes it. This process consists of three phases.
* **Load**: In this phase, Colibri-VM pushes the bytecode into the stack.
* **Compilation**: In this phase, Colibri-VM compiles the bytecode (creates the classes, the labels,the variables etc)
* **Execution**: In this phase, Colibri-VM executes the bytecode, starting from main function.

# The big test...
```coffeescript

#string addition
func test_one(left:str,right:str)->int{
	
	say "Test1: String Addition";
 	say left + " " + right;
	
	return 0;
	
}

#string multiplication
func test_two(x:int,y:int)->int{
	
	say "Test2: String Multiplication";
 	say 150 * "Gello!";
 	say x * "Nectar ";
 	say ( (x + y) // 2) * "Colibri ";
	
	return 0;
	
}

#Print many types inline
func test_three(tomatoes:int, potatoes:int, onions:int)->int{
	
	 say "Test3: Print many types inline";
     say "I have ", tomatoes ," tomatoes, ", potatoes//2 , " potatoes and ", onions + 52 , " onions";
	
	return 0;
	
}


func test_four(x:int, y:int)->int {
	say "Test4: Division";
 	say  "x/y = " , x/y;
	
	return 0;
}

func test_five(x:int, y:int)->int {
	
	say "Test5: Integer Division";
 	say "x//y = " , x//y;
	
	return 0;
}
	
func raw_input(message:str)->str{
	var input:str;
	read message,input;
	
	return input;
}
	
func input(message:str)->int{
	var input:int;
	read message,input;
	
	return input;
}
	
func test_six(name:str,surname:str,age:int)->int {
	
	name = raw_input("What is your name? : ");
 	surname = raw_input("Ok " + name + ", what is your surname? : ");
 	age = input("How old are you? : ");
 	say "So, your name is " , name , " your surname is " , surname, " and you are ", age , " years old!";
	
	return 0;
 
}


func main() -> int { 
	
 var x:int = 3;
 var y:int = 2;
 var age:int;
 var name:str = "Tasos";
 var surname:str = "Temperekidis";
	
 test_one(name,surname);
 test_two(x,y);
 test_three(25,53,1);
 test_four(x,y);
 test_five(x,y);
 test_six(name,surname,age);
 
	  
 return 0;
 
}



```
