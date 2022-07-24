## Linux Reverse Shell
Target system(attacker) acts an client and sever is setup by connection initiator(victim).

### Advantages
* This remove the requirement of victim's machine IP address and port
* May help an attacker to bypass incoming connection firewall rules.


### Dynamic linking/ Function call hooking

Now to we will be looking at concept of **Function call hooking** using dynamic linking(shared libraries)-
Dynamic linker provides feature for development of shared libraries and debugging purposes. Such LD_PRELOAD environment viriable or /etc/ld.preload.so in linux which make loading specified library function into memory before default libraries.[1](https://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html)

**Function call hooking** refers to a range of techniques used to intercept calls to pre-existing functions and wrap around them to modify the function’s behavior at runtime. [2](https://www.netspi.com/blog/technical/network-penetration-testing/function-hooking-part-i-hooking-shared-library-function-calls-in-linux/)


### Make it invisible & persistent
<!-- will GO here -->

We will be using function call hooking to hides to hides our executables files from /bin/ls




