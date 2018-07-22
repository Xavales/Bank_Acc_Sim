# Bank Transactions Simulation 
A program which simulates the way a bank handles its transactions with its clients. The program is divided into two submodules:

 - **Bankserver**
 - **Bankclient**
 
## About the Servers
-**Bankserver**:  Bankserver accepts commands(requests) from bankclients through socket connections. When bankserver starts, it waits for a port connection. Each connection is placed in an execution queue. The server contains a thread pool of workers with a static size. Each worker thread handles a client connection from the execution queue. Then, it is responsible for executing the commands received from that client and for responding back to him through the socket. When a client finishes his work, the corresponding thread that handled his requests is returned to the worker thread pool and waits for a new active connection in the execution queue. It is assumed that the execution queue has a max size. If the queue is found empty, all available worker threads wait till a client connection is established, and then a thread handles that connection's requests. In an almost impropable case scenario where the queue is found full the client waits until his requests are served.

-**Bankclient**: Bankclient establashes a connection with the bankserver through an IP and port which are defined from the user input. Then it begins to accept commands from stdin or an input file and prints the answers it receives from bankserver in stdout.

## Command and Execution Details

Bankserver execution from command input: 
```
./bankserver -p <port> -s <thread pool size> -q <queue size> 
```
where:
  - *port*: The port where the socket listens for client connections and command input.
  - *thread pool size*: The number of worker threads.
  - *queue size*: The size of the execution queue.

Bankclient execution from command input:
```
./bankclient -h <server host> -p <server port> -i <command file>  
```  
where:
  - *server host*: The symbolic server name.
  - *server port*: The port where the server listens for active connections.
  - *command file*: The file which contains executable commands for server.
  
All the command line arguments are required for both programms, server and client.

### Bankclient commands:

1. ``` add account <init amount> <name> [delay] ```

  Initializes an account with an initial balance. 

2. ``` add transfer <amount> <src name> <dst name> [delay] ```

  Transfers an amount between two accounts.

3. ``` add multi transfer <amount> <src name> <dst name1> <dst name2> ... [delay] ```

  Transfers an amount from one account to multiple ones.

4. ``` print balance <name> ```

  Returns the current balance of an account.

5. ``` print multi balance <name1> <name2> ... ```

  Returns the current balance of multiple accounts.

6. ``` sleep <time> ```

  Delays the next commnand to the bank server.
  
7. ``` exit ``` 

  Terminates bankclient programm.
  
where:
* *name*: The account name.
* *init amount*: The inital amount for the account.
* *delay*: The minimum time the server needs to process a command in msec.
* *src name*: The source account for the amount transfer.
* *dst name*: The destination account for the amount transfer.
* *sleep*: Time in msec where the bankclient has to wait before sending the next command to the bankserver.

The delay parameter is optional for the first 3 commands. All the other parameters are mandatory.


### Bankserver responses:

1. For  **add_account**: 

 * On success: Success. Account creation (name:init_amount)
 * On Failure: Error. Account creation failed (name:init amount)

2. For  **add_transfer**:

 * On success: Success. Transfer addition (src name:dst name:amount[:delay])
 * On Failure: Error. Transfer addition failed (src name:dst name:amount[:delay])

3. For  **add_multi_transfer**:

 * On success: Success. Multi-Transfer addition (src name:amount[:delay])
 * On Failure: Error. Multi-Transfer addition failed (src name:amount[:delay])

4. For  **print_balance**:

 * On success: Success. Balance (name:amount)
 * On Failure: Error. Balance (name)

5. For  **print_multi_balance**:

 * On success: Success. Multi-Balance (name1/amount1:name2/amount2:...)
 * On Failure: Multi-Balance (name1:name2:...)

6. For  **another input/command**:

  Error. Unknown command
  

### Conventions:

1. All functions assume that they take correct arguments. For example you cannot give names with many spaces between letters, negative amounts etc.

2. If print multi balance function fails, then it prints all the names it failed to find and not the names that were given as argument.

3. The server shuts down via the signal ^C (ctrl + C).
  
  
  
  
  
  
  
  
  
