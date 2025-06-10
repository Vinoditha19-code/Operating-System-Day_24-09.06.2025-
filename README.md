# Operating-System-Day_24-09.06.2025-

Exersice_02 
This C program demonstrates inter-process communication using two pipes and fork() to calculate the area of different geometric shapes (Circle, Triangle, Square, Rectangle).

01.Pipe Creation
    Two pipes are created:
      pipe1: For communication from parent → child
      pipe2: For communication from child → parent

02.Process Creation
    fork() creates a child process.
    After this point, both parent and child will execute separately.
      
03. Parent Process (pid > 0)
 a. Close Unused Pipe Ends
        Ensures that each process only uses relevant ends of the pipe.

 b. Take Input from User
        Asks the user to select a shape.
        Accepts necessary inputs (e.g., radius, side, length/width).
 
 c. Write Data to Child
       Sends the user's choice and input values to the child through pipe1.

 d. Read Result from Child   
       Receives the calculated area from the child via pipe2.

 e. Display Area
       Displays the result with 2 decimal places.


04. Child Process (pid == 0)
  a. Close Unused Pipe Ends
         Closing unused pipe ends prevents unnecessary resource usage and ensures that EOF (end-of-file) is properly detected during reads.


 b.  Read Data from Parent
         Reading data from the pipe ensures that the child process receives exactly what it needs to perform calculations independently. The correct order and size of reads are essential for reliable communication.

c.  Perform Area Calculation
         Calculates the area based on the input data and selected shape.

d. Send Result to Parent
         This action enables the parent to receive and display the calculated area. It demonstrates how child-to-parent communication is established using a pipe, completing a full request-response interaction between two processes. 



This program showcases a practical and educational example of two-way communication between a parent and child process using pipes in C. The parent handles user interaction and passes data to the child, which performs the area computation and returns the result. This modular design illustrates clear separation of concerns, reinforcing core concepts in process management and inter-process communication (IPC).


![image](https://github.com/user-attachments/assets/4c745217-36db-420f-9382-2309aff82f62)

