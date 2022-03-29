### To 'execute' this module (eg. hello_lkm):
sudo insmod ./hello_lkm.ko 

### To see message output by module:
dmesg | tail OR tail -f /var/log/kern.log

### To get information about module:
modinfo hello_lkm.ko

###To remove the module:
sudo rmmod hello_lkm
