cmd_/home/ghye/program/ko/hello/hello.ko := ld -r -m elf_x86_64 -T /usr/src/linux-headers-3.2.0-39-generic/scripts/module-common.lds --build-id  -o /home/ghye/program/ko/hello/hello.ko /home/ghye/program/ko/hello/hello.o /home/ghye/program/ko/hello/hello.mod.o