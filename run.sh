# -no-reboot -no-shutdown
#      -> is used to not reboot in case of system hlt for debug
# -d
#      -> int used to display debug of registers while the kernel is running
# -boot d
#      -> configure the boot order to boot on the drive/optical drive/cdrom
# -m
#      -> set the RAM to 1024
qemu-system-i386 -no-reboot -no-shutdown -d int -boot d -cdrom kfs.iso -m 1024
