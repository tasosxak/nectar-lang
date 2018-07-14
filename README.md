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
After we created the project let's see how to build it. Writing the below command you can build your poject:
> nectar build nameofproject

The above command initially calls the prenectar program to unite all the nectar files of your project and saves the result in the `final.nrf` file. After this, the nectar compiler is called, which it produces the bytecode in `nameofproject.cex`. The `nameofproject.cex` is stored in `exec` folder.

```swift
pub class Person{

  @name:string
  @age:int
  
  pub new(string name,int age) -> int {
      self.name = name
      self.age = age
      
      return ok
  }
  
}

func main()->int {
  var alice:Person = Person.new("alice",18)
  15 times say "hello world!"
  
  return ok
}
```
