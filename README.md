# nectar

Nectar is a new general-purposed programming language. It comprises a combination of both high-level and low-level language features. Nectar supports object-orentied and procedural programming.

Nectar's futures include:
* **Portability** : The compiler of Nectar produces bytecode for colibri virtual machine. So you can execute the same bytecode
files on a wide variety of different platforms (Windows,Linux,MacOS etc).
* **Scalability** : You can add libraries and Nectar provides better structure for .
* **Learnability** : Nectar has clean and easy syntax that allows new developers to learn quickly and easy.
* **Readability** : Nectar has similar syntax to that of many programming languages (such a Javascript, Swift,C++,Java).


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
