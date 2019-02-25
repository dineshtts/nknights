# nknights
Hamiltonian path in nxn size of knight. using MPI cluster
Chapter 6: Procedure
-----------------
Set up network 
Physical configuration of the network
All the systems are connected using wired LAN technology.
Set the IP address of each node.
Here we are using  DHCP to set the IP address of the individual nodes
Class-C type of IP address is used
-----------------
Configuration of the nodes
Create a user for each nodes with same username and password.
To identify each node in the network to others, add the hostname and IP Address
/etc/hosts file is modified to have the following format: 
IP address     Hostname         alias 
192.168.1.2         sys1         node1 
192.168.1.3         sys2         node2 
. . 
Respectively 
Where sys1 is the hostname and node1 is the alias name
/etc/hosts file are copied to /etc/hosts.equiv  
Modify the .rhosts file to allow trusted access to given host/user combinations without the need for a password

.rhosts file is modified to contain following format
sys1    project
sys2    project
sys3    project
sys4    project
sys5    project
sys6    project
sys7    project         where project is the name of user

To provide the "remote authentication"  for  rcp, rlogin, and rsh commands. The files /etc/hosts.equiv and .rhosts file are modified, these files bypass the standard password-based user authentication mechanism. They specify remote hosts and users that are considered trusted 
Permission of  .rhosts file is changed so that all user can read and execute .rhosts file, while only the owner can write the .rhosts file. 
Edit the file /etc/securetty to enable system services like rsh, rlogin and rexec. 
The /etc/securetty file allows you to specify which TTY devices the root user is allowed to login on. The /etc/securetty file is read by the login program usually /bin/login. 
/etc/securetty file will have the following format
tty55
tty56
tty57
tty58
tty59
tty60
tty61
tty62
tty63
rsh
rlogin
rexec

rsh executes command on the specified hostname. To do so, it must connect to a rshd service on the hostname machine. rshd provides remote execution facilities with authentication based on privileged port numbers from trusted hosts. rlogin starts a terminal session on the remote host specified as host.
Configuration of the node is now complete 
User may now test the configuration by using the rsh command
rsh node1
rsh node2… so on
User can successfully between the nodes if the configuration has the setup properly.

-----------------
Setting up LAM Environment 
Create a file named ‘host file’ on the node where MPI programs needs to be run subsequently. It provides a listing of the machines to be booted in a MPI session.
Hostfile is modified to be in this format.

node1
node2
node3
node4

where node1,node2…. Are alias name to identify the system

-----------------
Compile and Execute MPI program
Write a sequential program to test Knight’s problem in single processor
Compile the sequential program in a single processor 
cc testp2.c
where testp2 is the sequential program 
After compiling we execute the program using 
./a.out

Write a parallel program to test in a Cluster environment
Choose a master node that subsequently fetches the problem and distributes it to the slave nodes
In the master node start the LAM on the machines described in hostfile
lamboot will resolve all names in <hostfile> on the node in which lamboot was invoked (the master node). After that, LAM will only use IP addresses, not names. Specifically, the name resolution configuration on all other nodes is not used. Hence, the the master  node must be able to resolve all the names in <hosfilet> to addresses that are reachable by all other nodes.

lamboot -v hostfile

LAM 7.1.2/MPI 2 C++/ROMIO - Indiana University

n-1<5953> ssi:boot:base:linear: booting n0 (node1)
n-1<5953> ssi:boot:base:linear: booting n1 (node2)
n-1<5953> ssi:boot:base:linear: booting n2 (node3)
n-1<5953> ssi:boot:base:linear: booting n3 (node4)
n-1<5953> ssi:boot:base:linear: finished
This Provide incredibly detailed reports on what is happening at each stage in the boot process.
The master node sends a copy  of the job to each node 
 rcp test.exe node1:/home/project
 rcp test.exe node2:/home/project
 rcp test.exe node3:/home/project
      rcp test.exe node4:/home/project
Compile the Parallel implementation of the problem 
mpicc testp1.c -lm -o test.exe

Successful compilation generates a output exe file called test.exe  
Run the output of compiled program
mpirun -np 2 test.exe

Slave node computes the number of Hamiltonian path and send the corresponding answer to the master node
A Master node gathers the answer and publishes the result.


-----------------
Create an Application to automatically setup the Cluster Environment
Create a shell application to automatically setup the cluster environment
The  software tools needed are installed if not already present, user may wish to skip this routine
User is asked for the IP address of the systems that need to be made into a cluster environment
The user is asked to enter the user name and password , this is to ensure remote authentication
The needed network files are automatically setup, now the system whose IP address are added have now become a part of the cluster environment
User may wish to boot the   LAM (Local Area Multicomputer) now or may wish to manually do it later.
Permission of the shell application is changed so that it can be executed by all the users.
