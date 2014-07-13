SKeylogger
==========

SKeylogger is a simple keylogger. I had previously been using a few other open source keyloggers, but they stopped working when I upgraded my operating system. I tried to look through the code of those keyloggers, but it was undocumented, messy, and complex. I decided to make my own highly documented and very simple keylogger.

To build and run, clone the repository and run `make`. Then run `sudo ./skeylogger`. The keylogger will start and log all keypresses to `/var/log/skeylogger`.

Start on boot in Ubuntu
-----------------------
While Ubuntu isn't my main operating system (I'm an [Arch Linux](https://www.archlinux.org/) user), I got a few questions about how to start the keylogger when Ubuntu boots up. Here are the steps for Ubuntu 14.04:

1. Edit `/etc/rc.local` and add `/path/to/skeylogger` above the line with `exit 0`. Replace `/path/to/skeylogger` with the full path to the keylogger binary.

2. Allow sudo access without a password (Note: this may be a security threat. Do at your own risk). To do this, add the following line to `/etc/sudoers` making sure to replace the path with the path you used above and the username with your username:
    ```
    username ALL = NOPASSWD: /path/to/skeylogger
    ```
3. Reboot ubuntu. Open a terminal and type `pgrep skeylogger`. You should find one `skeylogger` process running.
