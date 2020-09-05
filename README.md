

# Milestone2

#### Creators: 
##### Shira Turgeman & Noa Elishmereni
#####  [our GitHub](https://github.com/noaElish/milestone2)

### **Basic information**
* Purpose of this extercise-
implement a few searches algorithms, compare them (by who had the smalles run time), 
and using the best algorithm as the problem solver on the server side.
among this create parallel server (that can work with multiple clients), 
and a serial server (that can accept clients one after the other.


### **important classes, variables and objects:**
* Namespace server
   * parallel server
   * serial server
* Class client handler
* diffrent search algorithm such as DFS, Best first search
   
### **how does it work?**
our programm creates server that is responsible to connect to client,
this server can also recive multiple clients (in my parallel server class)
and also client in an order (in my serial server class)

we read the problem from the server, in this milestone wer'e working with matrix/
after creating the matching matrix from the lines we read, we can now send it to solver. 
before solving this problem we check if we already solved this algorithm in the cache. if we can't find it there we send it to solver.
we used "Bridge" design pattern to connect between the search algorithms to the problem, 






